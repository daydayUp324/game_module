#

## LPS (Longest Palindromic Subsequence) 最长回文子序列

**动态规划求解**

问题描述：

给你一个字符串 $s$，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。

相关问题：对于求「最长回文子串」可以通过「马拉车」算法来进行求解。

1. 动态规划

用 $dp[i][j]$ 来表示字符串 $s[i:j]$ 的最长回文子序列，其中 $s[i:j]$ 包含其左右端点 $s[i]$ 与 $s[j]$，那么我们从小到大来枚举长度即可。对于边界情况就是当 $i = j$ 的时候，单个字符构成长度为 1 的一个回文字符串。那么对于长度 $j - i + 1 > 1$ 时m，计算 $s[i:j]$：

- 如果 $s[i] = s[j]$：那么 $dp[i][j] = dp[i + 1][j -  1] + 2$
- 否则 ：$dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])$

因为我们是长度从小到大来进行枚举的，所以在计算单个 $dp[i][j]$ 所需要用到的变量实际上已经在之前已被计算得到。

**时间复杂度：** $O(n^2)$，$n$ 为字符串 $s$ 的长度。

**代码参考**

```cpp
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0)); // dp[i][j] 表示 s[i:j] 的最长回文子序列的长度
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            if (i + 1 < n) {
                if (s[i] == s[i + 1]) dp[i][i + 1] = 2;
                else dp[i][i + 1] = 1;
            }
        } 
        for (int len = 3; len <= n; len++) {
            // 枚举长度
            for (int i = 0, j = i + len - 1; j < n; i++, j++) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }
};
```
