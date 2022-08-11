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
