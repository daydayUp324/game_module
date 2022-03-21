#include <bits/stdc++.h>
using namespace::std;
using LL = long long;
using PII = pair<int,int>;
#define x first
#define y second
#define VALID (nx >= 0 && nx < n && ny >= 0 && ny < m)
#define SQR(x)     ((x)*(x))
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
int exp_pow(int a,int b) {int res = 1; while(b) {if(b&1) res = (LL) a * res % MOD;b >>= 1;a = (LL) a * a % MOD;}return res;}
int exp_mul(int a,int b) {int res = 0; while(b) {if(b&1) res = ((LL) res + a) % MOD;b >>= 1;a = (LL) a * 2 % MOD;}return res;}
int gcd(int a,int b) {return b == 0 ? a : gcd(b,a % b);}
const int dir[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,-1},{-1,1}};
const char oe[10] = {'a','e','i','o','u','A','E','I','O','U'};
const double EPS = 1e-6;
const int N = 2e5 + 7;
LL n,m,k,a,b,c;
LL w[N];
bool muti = false;
LL dp[5005][5005];// dp[i][j] 从 i 开始选 有 j 段 的最大和
LL pre[N];
LL dfs(int curp,int o) {
    if(dp[curp][o] != -1) return dp[curp][o];
    LL res = 0;
    res = dfs(curp + 1,o);
    res = max(res,dfs(curp + m,o - 1) + pre[curp + m - 1] - pre[curp - 1]);
    dp[curp][o] = res;
    return res;
}
void solve() {
    cin >> n >> m >> k;
    LL res = 0;
    pre[0] = 0;
    for(int i = 1;i <= n;i ++) {
        cin >> w[i];
        pre[i] = pre[i - 1] + w[i];
    }
    if(m == 1) {
        sort(w + 1,w + n + 1,greater<LL>());
        for(int i = 1;i <= k;i ++) res += w[i];
        cout<<res<<"\n";
        return ;
    }
    for(int i = 1;i <= n;i ++) {
        for(int j = 1;j <= k;j ++) dp[i][j] = -1;
        dp[i][0] = 0;
    }
    dp[n + 1][0] = 0;
    // sum{i:j} = pre[j] - pre[i - 1];
    // sum{n - m + 1:n}
    int r = n;
    for(int i = 1;i <= k;i ++) {
        dp[r - m + 1][i] = pre[n] - pre[r - m];
        // cout<<r<<" , "<<r - m + 1<<" = "<<dp[r - m + 1][i]<<endl;
        r = r - m;
    }
    cout<<dfs(1,k)<<"\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    if(muti) cin >> T;
    else T = 1;
    while(T --) solve();
    return 0;
}