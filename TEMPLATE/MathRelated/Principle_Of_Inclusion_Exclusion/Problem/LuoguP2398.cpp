// 题目链接 : [P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)
/*
解题思路 :

总共有 n*n 个 序对 , 如果暴力是肯定不行的

那么我们换一个思路来解决 :

计算有多少个 gcd(i,j) = x , 那么直接 x*cnt 即可

由 Application_3.md 可得 : f[i] 表示 最大公约数为 i 的序对个数 即为上面的定义

那么答案就是 sum{f[i] * i}


*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e5 + 7;
int n,m;
long long f[N];
void solve() {
    long long res = 0;
    cin >> n;
    for(int i = n;i;i --) {
        f[i] = (long long) (n / i) * (n / i);
        for(int j = i + i;j <= n;j += i) f[i] -= f[j];
        res += f[i] * i;
    }
    cout<<res<<"\n";
}
int main() {
    solve();
    return 0;
}