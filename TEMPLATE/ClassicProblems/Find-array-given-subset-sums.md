#

## 从子集和还原数组（Find-array-given-subset-sums）

**题目链接 ：[1982. 从子集的和还原数组](https://leetcode.cn/problems/find-array-given-subset-sums/)**

### 问题描述

存在一个未知数组需要你进行还原，给你一个整数 $n$ 表示该数组的长度。另给你一个数组 $sums$ ，由未知数组中全部 $2n$ 个 子集的和 组成（子集中的元素没有特定的顺序）。

返回一个长度为 $n$ 的数组 $ans$ 表示还原得到的未知数组。如果存在多种答案，只需返回其中 任意一个 。

如果可以由数组 $arr$ 删除部分元素（也可能不删除或全删除）得到数组 $sub$ ，那么数组 $sub$ 就是数组 $arr$ 的一个 子集 。$sub$ 的元素之和就是 $arr$ 的一个子集的和。一个空数组的元素之和为 $0$。

注意：生成的测试用例将保证至少存在一个正确答案。

### 样例输入

**输入：** $n = 3$, $sums = [-3,-2,-1,0,0,1,2,3]$
**输出：** $[1,2,-3]$
**解释：** $[1,2,-3]$ 能够满足给出的子集的和：

- $[]$：和是 $0$
- $[1]$：和是 $1$
- $[2]$：和是 $2$
- $[1,2]$：和是 $3$
- $[-3]$：和是 $-3$
- $[1,-3]$：和是 $-2$
- $[2,-3]$：和是 $-1$
- $[1,2,-3]$：和是 $0$
注意，[$1,2,-3]$ 的任何排列和 $[-1,-2,3]$ 的任何排列都会被视作正确答案。

### 思路分析

#### 方法一：转化问题 + 子集枚举

**思路参考：**[HERE](https://leetcode.cn/problems/find-array-given-subset-sums/solution/ti-jie-cong-zi-ji-de-he-huan-yuan-shu-zu-q9qw/)

首先思考一个更简单的问题：如果原始数组中全部的数字都为非负数，其他条件不变时，那么排序后除去 $0$ (空集的情况) 后的最小的数 $num_{mi}$ 一定在原数组中，然后从最大的往前找不包括 $num_{mi}$ 的子集和。这样就可以找到全部没有 $num_{mi}$ 的子集和，然后按照这样的思路还原整个数组即可。
但是现在原数组中存在 **负数** 的情况，那么我们考虑是否能进行转化：首先最小的数一定是全部负数的和。那么让全部的子集都减去这个最小的数 $mi$，那么整个数组就变成了一个非负数数组 $after$，那么我们可以看到：

> 对于原来子集中存在某负数的情况，那么就等价于现在不存在该负数，而原来子集中不存在该负数，则等价于现在包含了它的相反数

那么此时我们按 $after$ 来按照非负数的情况来还原他的初始的数组 $ori$。然后我们在 $ori$ 中得到一个子集和为 $-mi$，然后对这个子集中的元素全部取反即可得到最初数组的对应原始数组。（具体证明可以见思路参考的题解）

```cpp
class Solution {
public:
    vector<int> help(int n, vector<int>& sums) {
        // 从 非负整数 nums[] 还原数组
        sort(sums.begin(), sums.end());
        vector<int> res;
        vector<int> temp;
        for (int T = 0; T < n; T++) {
            res.push_back(sums[1]);
            temp.push_back(0); // 空集的情况
            for (int i = 2, j = 1; i < sums.size(); i++) {
                if (j < temp.size() && sums[i] == temp[j] + sums[1]) {
                    // 如果当前数是前面没有 sums[1] 的子集加上 sums[1] 而来的话
                    j++;
                    continue;
                } else {
                    temp.push_back(sums[i]);
                }
            }
            sums = move(temp);
        }
        return res;
    }
    vector<int> recoverArray(int n, vector<int>& sums) {
        vector<int> res;
        int mi = 0; // 记录最小的值（全部负数相加）
        for (auto& i : sums) mi = min(mi, i);
        if (mi == 0) return help(n, sums);
        for (auto& i : sums) i -= mi;
        res = help(n, sums);
        int all = (1 << res.size());
        mi *= -1;
        for (int i = 1; i < all; i++) {
            int o = 0;
            for (int j = 0; j < n; j++) {
                if (i >> j & 1) o += res[j];
            }
            if (o == mi) {
                for (int j = 0; j < n; j++) {
                    if (i >> j & 1) res[j] *= -1;
                }
                break;
            }
        }
        return res;
    }
};
```

#### 方法二：迭代 + 双指针

上面转化为非负整数的思维难度比较大，我们也可以朴实的来考虑这个问题：首先将原数组排序得到 $sums$，那么最小的和次小的数 $a,b$，且 $x = a-b$ 那么 $x$ 或者 $-x$ 一定会是原数组中的一个数（因为最小的数一定是全部负数相加的情况，那么为了变大只能去掉一个负数或者加上一个正数来得到次小值，即最小值和次小值之间只相差一个数），且这个数可以将 $sums$ 分为两部分 $A$ 和 $B$，且 $A$ 和 $B$ 中的数能一一对应（即相差的数 $A_i - B_i = diff$ 为一个定值）。而能继续往下分的需要存在数字 $0$。那么迭代往下即可。

```cpp
class Solution {
public:
    vector<int> recoverArray(int n, vector<int>& sums) {
        sort(sums.begin(), sums.end());
        vector<int> res;
        for (int T = 0; T < n; T++) {
            int diff = sums[1] - sums[0];
            vector<int> A = {sums[0]};
            vector<int> B = {sums[1]};
            // A_i + diff = B_i
            for (int i = 2, j = 1; i < sums.size(); i++) {
                if (j < B.size() && B[j] == sums[i]) {
                    j ++;
                    continue;
                }
                A.push_back(sums[i]);
                B.push_back(sums[i] + diff);
            }
            bool flagA = false; // A 中是否有 0
            for (auto& i :  A) {
                if (!i) {
                    flagA = true;
                    break;
                }
            }
            // 有 0 的一定是能被分解的
            // 如果是 A 中有 0，说明 A 包含的只是没有 A 的子集和
            // 那么此时原数组中的数就是 diff
            // 否则就是 -diff
            if (flagA) {
                res.push_back(diff);
                sums = A;
            } else {
                res.push_back(-diff);
                sums = B;
            }
        }
        return res;
    }
};
```
