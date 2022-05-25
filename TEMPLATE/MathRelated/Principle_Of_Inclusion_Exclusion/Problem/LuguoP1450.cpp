// 题目链接 : [P1450 [HAOI2008]硬币购物](https://www.luogu.com.cn/problem/P1450)
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e5 + 7;
int n,m;
int d[5];
int c[5];
LL dp[N];// dp[i] 表示四种硬币无限次数的情况下 构成 i 的方案数
int cnt[16];// 每一个状态的个数
void solve() {
    for(int i = 0;i < 4;i ++) cin >> c[i];// 硬币的面额
    // 预处理
    for(int i = 0;i < N;i ++) dp[i] = 0;
    dp[0] = 1;
    for(int i = 0;i < 4;i ++) {
        for(int j = c[i];j < N;j ++) {
            dp[j] += dp[j - c[i]];
        }
    }
    cnt[0] = 0;
    for(int i = 1;i < 16;i ++) cnt[i] = cnt[i & (i - 1)] + 1;
    cin >> n;
    while(n --) {
        for(int i = 0;i < 4;i ++) cin >> d[i];
        cin >> m;
        LL res = dp[m];
        // 构成 m 的方案数
        // 容斥原理
        for(int S = 1;S < 16;S ++) { // 选择的集合
            int t = m;
            for(int i = 0;i < 5;i ++) {
                if(S >> i & 1) {
                    t -= c[i] * (d[i] + 1);
                }
            }
            if(t >= 0) {
                if(cnt[S] & 1) res -= dp[t];
                else res += dp[t];
            }
        }
        cout<<res<<"\n";
    }
}
int main() {
    solve();
    return 0;
}