#

## 第 k 大的子集和 （Find-the-K-sum-of-an-array）

**题目链接 ：[2386. 找出数组的第 K 大和](https://leetcode.cn/problems/find-the-k-sum-of-an-array/)**

### 问题描述

给你一个整数数组 $nums$ 和一个 **正整数** $k$ 。你可以选择数组的任一 **子序列** 并且对其全部元素求和。

数组的 **第 $k$ 大和** 定义为：可以获得的第 $k$ 个 **最大子序列和 （子序列和允许出现重复）**

返回数组的 **第 $k$ 大和**。

子序列是一个可以由其他数组删除某些或不删除元素排生而来的数组，且派生过程不改变剩余元素的顺序。

**注意：空子序列的和视作 0 。**

### 样例输入

**输入：** $nums = [2,4,-2]$, $k = 5$
**输出：** $2$
**解释：** 所有可能获得的子序列和列出如下，按递减顺序排列：

- $6,4,4,2,2,0,0,-2$

数组的第 $5$ 大和是 $2$。

### 思路分析

首先很明确，最大的一个子集和一定是全部正数相加所得的数，我们记全部正数相加所得的数为 $sum$（如果没有正数因为空子集的和记为 $0$，所以此时 $sum$ 也为 $0$）。那么我们需要使得 $sum$ 变小，那么只有两种操作，每次从 $sum$ 中去除一个非负数或者加上一个负数。为了使操作统一，我们得到 $sum$ 后让数组中的负数全部取绝对值，那么为了让 $sum$ 变小，就只能从 $sum$ 中减去一些非负数。那么问题也就可以转化为求此时的数组（全部都为非负数）的第 $k$ 小的子集和。又因为第 $k$ 小的子集和最多用到的数个数不会超过原数组中最小的 $k$ 个数。因为每次单独用原数组中最小的 $k$ 个数此时就有 $k$ 种情况了，那么假设存在第 $i$ 小的子集和中有除了原数组中最小的 $k$ 个数，$i \le k$。那么我们一定可以用最小的 $k$ 个数中没有用到过的数来代替该数，这样一定不会使结果变得更大，所以用原数组中最小的 $k$ 个数即可。

1. 可以考虑最短路的思想出发，从最小的开始往后遍历，每次更新最小的使之变大，那么淘汰掉 $k-1$ 个最小的之后，那么剩下的最小就是数组中的第 $k$ 小的子集。那么我们用 $\{curnum, pos\}$ 记录每一个状态：$curnum$ 表示现在积累的子集和，$pos$ 表示现在需要加上的数字。初始状态是 $\{0, 0\}$ 表示选择的是一个空集的时候。因为此时是的和一定是最小的，每次加的时候一定会产生不小于当前和的一个子集和。又因为每一个状态都是从小到大来逐渐更新每一个状态的：
   $$\{curnum, pos\}$$
因为对于某一个位置存在两种情况——该位置前面一个位置是否进行选择，从而得到新的两个状态：
   $$\{curnum + nums[pos], pos + 1\}, \{curnum - nums[pos-1] + nums[pos],pos + 1\}$$

   对于这样一个需求可以通过 **最小堆** 来实现，整个的时间复杂度为：$O(n \times \log n + k \times \log k)$，主要为 $nums$ 的复杂度和每一个状态的 $push$ 的复杂度。

    ```cpp
    using PLI = pair<long long, int>;
    class Solution {
    public:
        long long kSum(vector<int>& nums, int k) {
            long long o = 0;
            for (auto& i : nums) {
                if (i > 0) o += i;
                else i = -i;
            }
            if (k == 1) return o;
            sort(nums.begin(), nums.end());
            priority_queue<PLI, vector<PLI>, greater<PLI>> q;
            q.push({0, 0});
            while (-- k) {
                auto t = q.top(); q.pop();
                auto a = t.first;
                auto b = t.second;
                if (b == nums.size()) continue;
                q.push({a + nums[b], b + 1}); // 前一个位置保留
                if (b) q.push({a - nums[b - 1] + nums[b], b + 1}); // 前一个位置删除
            }
            return o - q.top().first;
        }
    };
    ```

1. 我们也可以通过 **归并排序** 来进行求解第 $k$ 小的子集和。最开始只有空集的情况为 $0$。然后从最小的数开始加入，维护一个大小不超过 $k$ 的数组来当前的最小的 $k$ 个子集和的大小即可，维护的过程可以用 **归并排序来实现**。

    ```cpp
    class Solution {
    public:
        long long kSum(vector<int>& nums, int k) {
            // 归并排序
            // 相当于找到最小的 k 个数字
            // 最大的肯定是全部正数相加
            long long res = 0;
            for (auto& i : nums) {
                if (i > 0) res += i;
                else i = -i;
            }
            if (k == 1) return res; // 小剪
            sort(nums.begin(), nums.end());
            vector<long long> h;
            if (nums.size() > k) nums.erase(nums.begin() + k, nums.end()); // 只需要用到最小的 k 个数字即可
            vector<long long> a;
            vector<long long> b;
            a.push_back(0); // 初始为 0
            for (auto& t : nums) {
                // b.clear();
                // 归并排序的是 a[] 和 a[] + t
                int i = 0, j = 0;
                while (b.size() < k && i < a.size() && j < a.size()) {
                    if (a[i] < a[j] + t) b.push_back(a[i ++]);
                    else b.push_back(a[j ++] + t);
                }
                if (j == 0 && b.size() == k) {
                    a = move(b);
                    break;
                }
                while (b.size() < k && i < a.size()) b.push_back(a[i ++]); 
                while (b.size() < k && j < a.size()) b.push_back(a[j ++] + t);
                a = move(b);
            }
            return res - a[k - 1];
        }
    };
    ```
