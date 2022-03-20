#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class Solution {
public:
    int dp[1005][1005];
    int a;
    int n;
    int dfs(string& s,int curp,int p) {
        if(dp[curp][p] != -1) return dp[curp][p];
        int res = 1e9 + 7;
        if(s[curp] == '0') res = dfs(s,curp + 1,p);// 0 不用管
        else {
            res = 1 + dfs(s,curp + 1,p);
            res = min(res,dfs(s,min(curp + a,n),p - 1));
        }
        dp[curp][p] = res;
        return res;
    }
    int minimumWhiteTiles(string s, int b, int a_) {
        n = s.size();
        a = a_;
        for(int i = 0;i < n;i ++) {
            for(int j = 1;j <= b;j ++) {
                dp[i][j] = -1;
            }
        }
        for(int j = 0;j <= b;j ++) dp[n][j] = 0;
        int t = 0;
        for(int i = n - 1;i >= 0;i --) {
            if(s[i] == '1') t ++;
            dp[i][0] = t;
        }
        return dfs(s,0,b);
    }
};