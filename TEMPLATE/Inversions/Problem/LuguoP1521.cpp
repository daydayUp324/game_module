// 题目链接 : 
// [P1521 求逆序对](https://www.luogu.com.cn/problem/P1521)
// [P2513 [HAOI2009]逆序对数列](https://www.luogu.com.cn/problem/P2513)
// 解题思路 : n 个数来依次进行放置 来计算贡献值 dp 问题
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e4;
int dp[1005][1005];// 数字 n 个 m 个逆序对的方案数
int main() {
    int n , m;
    cin >> n >> m;
    // n 个数字 m 个逆序对
    dp[1][0] = 1;
    for(int i = 2;i <= m;i ++) dp[1][i] = 0;
    for(int i = 2;i <= n;i ++) {
        dp[i][0] = 1;
        int o = dp[i-1][0];
        for(int j = 1;j <= m;j ++) {
            // dp[i][j] = sum{dp[i-1][j],dp[i-1][j-1],...,dp[i-1][j + 1 - i]}
            o = (o + dp[i-1][j]) % MOD;
            if(j - i >= 0) o = (o - dp[i-1][j - i] + MOD) % MOD;
            dp[i][j] = o;
        }
    }
    cout<<dp[n][m]<<"\n";
    return 0;
}