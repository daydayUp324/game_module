# 离散化概念

把无限空间中有限的个体映射到有限的空间中去，以此提高算法的时空效率。基本思想就是在众多可能的情况中，只考虑需要用的值。

## 实现操作

```cpp
// 排序 + 去重
// 注意 : 该数组会改变。 如果要求原数组不变的情况 需要先把原数组 copy 到一个辅助数组中
void orderly(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
}
// 二分查找序号
// 注意 : 前提需要确保该数在数组中
int getIndex(vector<int>& nums,int target) {
    return lower_bound(nums.begin(),nums.end(),target) - nums.begin();
}
```
