// 题目链接 : [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)
/*
解题思路 :

以 观测点的上为 y 轴正方向 右测为 x 轴正方向

把观测点 的 上,右 两个点先算上
然后其他的点 (i,j) 我们来看它的性质 :
被 (i,j) 所挡住的点 (x,y) -> x/i = y/j , 那么即 当 gcd(i,j) != 1 时一定会被遮挡

所以最后就是求 gcd(i,j) = 1 的个数 + 2
*/
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e5 + 7;
int n,m;
LL f[N];
void solve() {
    LL res = 2;
    cin >> n;
    if(n == 1) {
        cout<<"0\n"; return ;
    }
    n --;
    for(int i = n;i;i --) {
        f[i] = (long long) (n / i) * (n / i);
        for(int j = i + i;j <= n;j += i) {
            f[i] -= f[j];
        }
    }
    cout<<f[1]+2<<"\n";
}
int main() {
    solve();
    return 0;
}