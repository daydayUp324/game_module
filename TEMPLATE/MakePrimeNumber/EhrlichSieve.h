#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayuppp
 * 埃氏筛 : 
 * 
 * <= n 的质数的个数大致在 n / logn 左右
 * 
 * 数学原理：
 * 1. 任何正整数（除1外），所有正整数均能分解为素数的乘积。
 * 2. 比 n 小的某合数 a , a 的最小质因数一定不会大于 sqrt(n) :
 *      证明 : 设 : x 为 a 的最小质因数 , 得 :
 *             a / x >= x
 *             ---> n > a >= x * x , 即 x < sqrt(n)
 * 
 * 要得到自然数n以内的全部素数，必须把不大于sqrt(n)的所有素数的倍数剔除，剩下的就是素数。
 * 而正常的判断每一个数是否是素数需要 O(sqrt(n)) 的复杂度 , 整的复杂度就会到 O(n * sqrt(n))
 * 
 * 埃氏筛复杂度 :
 * 时间复杂度 : O(n * logn * logn)
 * 空间复杂度 : O(n) 
 * 
 * 
 * 主要用途 :
 * 1. 可以用于得到 [2,n] 内的质数表 , n 可以达到 1e6 级别
 * 2. 区间素数筛 : 计算 [a,b] 内的素数个数 : a < b < 1e12 , b - a <= 1e6
 *      因为不大于 b 的合数的最小质因数 <= sqrt(n)
 *      所以我们预处理 [2,sqrt(b)] 的一个质数表
 *      然后用 得到的 质数表 去处理 [a,b] 区间即可
 */
int primes[100005];
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
void EhrlichSieve(int n) {// 得到 < n 的全部质数
    memset(f,true,n); cnt1 = 0;
    for(int i = 2;i < n;i ++) {
        if(f[i]) {
            primes[cnt1 ++] = i;
            for(int j = i;j < n;j += i) f[j] = false;
        }
    }
}