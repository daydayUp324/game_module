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
int n,m,a,b,c;
int w[N];
int top;
void solve() {
    cin >> n >> m;
    // n 门考试 m 天
    multiset<int> mst;// 存每一个间隙
    int res = INF;
    w[0] = 0;
    for(int i = 1;i <= n;i ++) {
        cin >> w[i];
        res = min(res,w[i] - w[i - 1] - 1);// 初始为最小间隙
        mst.insert(w[i] - w[i - 1] - 1);
    }
    if(n == 1) {
        cout<<m - 1<<"\n";
        return ;
    }
    // 删除每一门考试 , 会使下一门的考试时间增加
    // 然后放置的位置 ：
    // 1. 最末尾的位置
    // 2. 当前休息时间最长的考试的休息时间中间
    for(int i = 1;i < n;i ++) {
        // 枚举取消每一段间隙
        a = w[i] - w[i - 1] - 1;// a 表示需要删除的休息时间
        b = w[i + 1] - w[i] - 1;// b 表示后一个需要改变的考试时间
        c = w[i + 1] - w[i - 1] - 1;// c 表示后一个考试改变后的休息时间
        mst.erase(mst.find(a));
        mst.erase(mst.find(b));
        mst.insert(c);
        // 1. 放到当前的休息时间的最长的考试中间
        res = max(min(*mst.begin(),(*mst.rbegin() - 1) / 2),res);
        // 2. 放到最后
        res = max(res,min(m - w[n] - 1,*mst.begin()));
        // 最后修复现场
        mst.erase(mst.find(c));
        mst.insert(a);
        mst.insert(b);
    }
    // 对最后一个特判
    a = w[n] - w[n - 1] - 1;
    mst.erase(mst.find(a));
    // 1. 放到当前的休息时间的最长的考试中间
    res = max(min(*mst.begin(),(*mst.rbegin() - 1) / 2),res);
    // 2. 放到最后
    res = max(res,min(m - w[n - 1] - 1,*mst.begin()));
    cout<<res<<"\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while(T --) solve();
    return 0;
}