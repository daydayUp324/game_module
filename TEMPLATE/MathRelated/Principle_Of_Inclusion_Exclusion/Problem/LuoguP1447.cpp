// 题目链接 : [P1447 [NOI2010] 能量采集](https://www.luogu.com.cn/problem/P1447)
/*
解题思路 :

每一个点 (i,j) 的中间的点的个数 cnt : gcd(i,j) - 1

那么全部的点能量损失就是 :

ans = sum{gcd(i,j) * 2 - 1}
    = 2 * sum{gcd(i,j)} - n * m

*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e5 + 7;
int n,m;
LL f[N];
void solve() {
    cin >> n >> m;
    if(n == 1 && m == 1) {
        cout<<"1\n"; return ;
    }
    LL res = 0;
    int r = max(n,m);
    for(int i = r;i;i --) {
        // l * l 的 一个矩阵
        f[i] = (long long) (n / i) * (m / i);
        for(int j = i + i;j <= r;j += i) {
            f[i] -= f[j];
        }
        res += f[i] * i * 2;
    }
    cout<<res - (long long) n * m<<"\n";
}
int main() {
    solve();
    return 0;
}