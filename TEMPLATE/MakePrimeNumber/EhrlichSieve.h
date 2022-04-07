#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayuppp
 * 
 */
int primes[100005];
int Min_prim_fac[100005];
int primesSeq[100005];// 某一段区间上的质数
bool f[100005];
bool g[100005];
int cnt1,cnt2;
// cnt1 表示 区间 [1,b] 上的质数
// cnt2 表示 区间 [a,b] 上的质数
void primesInSeq(long long a,long long b) {// 计算区间 [a,b] 上的质数个数
    cnt2 = 0;
    int sz = sqrt(b) + 1;
    int R = b - a + 1;
    memset(f,true,sz);// [2,sqrt(b)] 的质数表
    memset(g,true,R);// [a,b] 上的表 进行了下标索引 -> [0 : b - a]
    for(int i = 2;i < sz;i ++) {
        if(f[i]) {
            /*
            因为 i 为质数 所以至少要找到 x >= a , x > i 的第一个数
            而 (a + i - 1) / i * i 是第一个 大于等于 a 的且是 i 的倍数的数
            */ 
            for(int j = max((long long)2,(a + i - 1) / i) * i - a;j < R;j += i) g[j] = false;
            for(int j = 2 * i;j < sz;j += i) f[j] = false;
        }
    }
    if(a == 1) g[0] = false;
    for(int i = 0;i < R;i ++) if(g[i]) primesSeq[cnt2 ++] = a + i;// 该质数为 a + i
}
void EulerSieve_n(int n) { // O(n)
    memset(Min_prim_fac,0,4 * n + 4);
    cnt1 = 0;
    for(int i = 2;i <= n;i ++) {
        if(!Min_prim_fac[i]) {
            primes[cnt1 ++] = i;// 第 cnt 个质数 
            Min_prim_fac[i] = i;// 质数 i 的最小质数为 i
        }
        for(int j = 0;j < cnt1 && i * primes[j] <= n;j ++) {
            Min_prim_fac[i * primes[j]] = primes[j];
            if(i % primes[j] == 0) break;
        }
    }
}
void EhrlichSieve_lognlogn(int n) { // O(nlognlogn)
    memset(f,true,n); cnt1 = 0;
    for(int i = 2;i < n;i ++) {
        if(f[i]) {
            primes[cnt1 ++] = i;
            for(int j = i;j < n;j += i) f[j] = false;
        }
    }
}