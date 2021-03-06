#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
/// 整数比较
/// \param a 整数A 
/// \param b 整数B
/// \return 大于0，等于0，小于0
int cmp(const int *a, const int *b) {
    return *(int *) a > *(int *) b;
}
/// 深度优先搜索
/// \param nums 待排列数组
/// \param numsSize 待排数组大小
/// \param returnArr 结果数组
/// \param returnSize 结果数组大小
/// \param returnColumnSizes 返回结果列的大小
/// \param tempArr 临时数组
/// \param tempSize 临时数组大小
/// \param used 是否使用数组
void dfs(int *nums, int numsSize, int **returnArr, int *returnSize, int **returnColumnSizes, int *tempArr, int tempSize,
         int *used) {
    if (tempSize == numsSize) {
        // 排列完成，添加到结果数组
        returnArr[*returnSize] = (int *) malloc(sizeof(int) * tempSize);
        (*returnColumnSizes)[*returnSize] = tempSize;
        memcpy(returnArr[(*returnSize)++], tempArr, sizeof(int) * tempSize);
        return;
    }
    for (int i = 0; i < numsSize; ++i) {
        // 大剪枝
        if (used[i]) {
            continue;
        }
        // 剪枝去重
        if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 0) {
            continue;
        }
        used[i] = 1;
        tempArr[tempSize++] = nums[i];
        dfs(nums, numsSize, returnArr, returnSize, returnColumnSizes, tempArr, tempSize, used);
        tempSize--;     // 回退
        used[i] = 0;    // 状态重置
    }
}
/// 排列
/// \param nums 待排数组
/// \param numsSize 数组大小
/// \param returnSize 返回结果的数组大小
/// \param returnColumnSizes 返回结果的数组列的大小
/// \return 返回的结果二维数组
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) {
    *returnSize = 0;
    if (nums == NULL || numsSize < 1) {
        return NULL;
    }
    // 排序，用于去重
    qsort(nums, numsSize, sizeof(int), cmp);
    // 结果数组
    int **returnArr = (int **) malloc(sizeof(int *) * MAX_SIZE);
    *returnColumnSizes = (int *) malloc(sizeof(int) * MAX_SIZE);
    // used标记元素是否使用
    int *used = (int *) malloc(sizeof(int) * numsSize);
    memset(used, 0, sizeof(int) * numsSize);
    // 临时数组存储排列结果
    int *tempArr = (int *) malloc(sizeof(int) * numsSize);
    int tempSize = 0;
    // 深度优先搜索
    dfs(nums, numsSize, returnArr, returnSize, returnColumnSizes, tempArr, tempSize, used);
    // 释放申请的堆空间
    free(tempArr);
    free(used);
    return returnArr;
}

