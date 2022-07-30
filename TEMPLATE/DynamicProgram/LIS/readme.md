#

## LIS (Longest Increasing Subsequence) 最长递增子序列

**动态规划求解**

问题描述：

给你一个整数数组 $nums$，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，$[3,6,2,7]$ 是数组 $[0,3,1,6,2,2,7]$ 的子序列。

1. 朴素做法

用`dp[i]` 表示以 `nums[i]` 结束的最长子序列长度，那么对于 `dp[i]` 的求解就可以通过转移方程来实现：

    $$dp[i] = max\{ dp[j] + 1 \}, nums[j] < nums[i]$$

这是一个 $O(n^2)$ 复杂度的算法。

**代码参考**

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n,1);
        int res = 1;
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (nums[i] > nums[j]) dp[i] = max(dp[i], dp[j] + 1);
                // if (nums[i] >= nums[j]) dp[i] = max(dp[i], dp[j] + 1); // 非严格递增的情况
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

2. 二分

用 `dp[i]` 表示当前为止，长度为`i` 的最长递增子序列结尾的最小数字。因为以 `dp[]` 满足：`dp[i] > dp[j]` 一定成立，所以存在单调性质，所以对于遍历到的 `nums[i]` 就可以用二分来进行更新。

这是一个时间复杂度为 $O(n \log n)$ 的算法。

**代码参考**

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp;
        for (auto& i : nums) {
            if (dp.empty() || i > dp.back()) dp.push_back(i);
            else {
                auto idx = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
                dp[idx] = i;
            }
        }
        /*
        如果不是严格递增的情况
        for (auto& i : nums) {
            if (dp.empty() || i >= dp.back()) dp.push_back(i);
            else {
                auto idx = upper_bound(dp.begin(), dp.end(), i) - dp.begin();
                dp[idx] = i;
            }
        }
        */
        return dp.size();
    }
};
```
