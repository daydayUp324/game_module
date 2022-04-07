#

## 质数筛

补充小知识 : 小于等于 $n$ 的质数的 $x$ 个数大致在 $n / logn$ 左右

### 数学原理

1. 任何正整数（除1外），所有正整数均能分解为素数的乘积。
2. 比 n 小的 **某合数** $a$ , $a$ 的 **最小质因数** 一定不会大于 $\sqrt{n}$
    > **证明** : 设 : $x$ 为 $a$ 的 **最小质因数** , 得 :
        $a / x \ge x$ 得到 : $n > a >= x * x$ , 即 $x < \sqrt{n}$

### 计算流程

朴素的判断一个数 $x$ 是否是素数需要 $O(\sqrt{x})$ 的复杂度 , 所以要得到 自然数 $n$ 以内的全部素数 复杂度就会到 $O(n * \sqrt{n})$

```cpp
bool judge(int x) {
    for(int i = 2;i * i <= x;i ++) {
        if(x % i == 0) return false;
    }
    return true;
}
```

---

而 `埃氏筛` 可以到 $O(n*logn*logn)$ 的 **时间复杂度**。

`埃氏筛` : 要得到自然数 $n$ 以内的全部 **素数** , 必须把不大于 $\sqrt{n}$的所有 **素数** 的倍数剔除，剩下的就是素数。

```cpp
for(int i = 2;i * i <= n;i ++) {
    if(isprime[i]) {
        for(int j = 2;j * i <= n;j ++) isprime[i * j] = false;
    }
}
// 最后 isprime[i] = true 的 i 就是质数
```

---

**优化 :**
我们看到 : 对于 $[1,100]$ 中的 , 21 在 3 和 7 的时候都被筛选了一遍 , 所以优化的方向是 : 我们希望对于每一个数都能被他的 **最小质因子** 所删除。

那么我们首先设置一个数组 `Min_prim_fac[]` , `Min_prim_fac[i] = j` 表示 $i$ 的 **最小质因子** 为 $j$ , 用 `prim[]` 来存储当前筛选出来的质数。那么对于当前的数字 $i$ 我们 **从小到大** 枚举现有的全部质数 $p$ , 来使 : `Min_prim_fac[i * p] = p` , 当 `i % p == 0` 时退出。

> 因为我们需要每一个数被它最小质因数所筛出
    因为 $p$ 是从小到大枚举的 , 所以如果 $i \% p == 0$ 时 : 说明 $i$ 的最小质数就是 $p$。当 $p$ 再往下时 $i * p$ 的 **最小质因数** 就不是 $p$ 了

```cpp
void EulerSieve(int n) {
    memset(Min_prim_fac,0,4 * n + 4);
    cnt = 0;
    for(int i = 2;i <= n;i ++) {
        if(!Min_prim_fac[i]) {
            prim[cnt ++] = i;// 第 cnt 个质数 
            Min_prim_fac[i] = i;// 质数 i 的最小质数为 i
        }
        for(int j = 0;j < cnt && i * prim[j] <= n;j ++) {
            Min_prim_fac[i * prim[j]] = prim[j];
            if(i % prim[j] == 0) break;
        }
    }
}
```

**此时** 整体的时间复杂度 : $O(n)$

同时 : `Min_prim_fac[]` 也可以把 $x$ 的全部 **质因子筛选出来**

```cpp
cout<<x<<"' all prime factory : \n";
while(x > 1) {
    cout<<Min_prim_fac[x]<<" ";
    x /= Min_prim_fac[x];
}
cout<<"\n";
```

---

### 主要用途

1. **质数表** : 可以用于得到 $[2,n]$ 内的质数表 , $n$ 可以达到 $10^6$ 级别
2. **区间素数筛** : 计算 $[a,b]$ 内的素数个数 : $a < b < 10^{12} , b - a <= 10^6$
   > 因为不大于 $b$ 的合数的 **最小质因数** 一定 $\le \sqrt{b}$ , 所以我们预处理 $[2,\sqrt{b}]$ 的一个质数表 , 然后用得到的 质数表 去处理 $[a,b]$ 区间即可。
   > **如何处理 :**
   > 比如有一个质数 $x$ , 那么需要把 $x$ 的倍数从 $[a,b]$ 区间去除 , $[a,b]$ 区间中第一个 $x$ 的倍数 **(至少需要 2 倍)** 是 :
   $begin = \max\{2,(a + x - 1) / x\} * x$

   ```cpp
   // 从 [a,b] 中剔除 质数 x 的倍数
   for(int i = begin;i <= b;i += x) isprime[i] = false;
   ```

   > 而实际 $isprime[]$ 并不能开到 $b$ 的大小 , 所以还需要做一个映射 : $[a,b] -> [0,b-a]$ , 这样我们只需要开一个 $b-a$ 大小的区间即可

   ```cpp
   for(int i = begin - a;i <= b - a;i += x) isprime[i] = false;
   ```
