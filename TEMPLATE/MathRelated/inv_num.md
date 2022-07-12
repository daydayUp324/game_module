#

## 求逆元

**具体参考于 :** [HERE](https://www.cnblogs.com/chy-2003/p/9656801.html)

### 逆元概念

一个数 `a` 的逆元就是存在一个 `x` 使得 : $a * x \equiv 1 (mod$&nbsp;$p)$

数字 $b$ 逆元存在的条件 : `当 gcd(b,p) = 1` 时 , $b$ 在 模 $p$ 的情况下存在逆元。

> 证明 : 贝祖定理 , 对于任何整数 $a,b$ , 和 他们的最大公约数 $d$ , 那么对于任意的整数 $x,y$ , $a*x + b*y$ 一定是 $d$ 的倍数 , 特别地 , 一定存在整数 $x,y$ 使得 $a*x + b*y = d$ 成立
>
> 那么当 $gcd(b,p) = 1$ 时 , 一定存在 $x,y$ 使得 $b*x+p*y=1$ 成立 , 即一定存在 $x$ 使得 : $b*x\equiv1(mod$ &nbsp; $p)$ , 即此时 $b$ 在 模$p$ 下存在逆元。证毕。

---

#### 扩展欧几里得求逆元

[![LKk0YV.png](https://s1.ax1x.com/2022/04/13/LKk0YV.png)](https://imgtu.com/i/LKk0YV)

##### CODE_1

```cpp
#include <bits/stdc++.h>
using namespace std;
void ExPower( int b, int p, int & a, int & k ) {
    // 最终的 a 即为 b 在模 p 下的逆元
    if( p == 0 ) {
        a = 1; k = 0;
        return;
    }
    ExPower( p, b % p, k, a );
    k -= b / p * a;
    return;
}
int main() {
    int b, p;
    cin >> b >> p;
    int a, k;
    ExPower( b, p, a, k );
    if( a < 0 ) a += p;
    cout << a << endl;
    return 0;
}
```

##### 复杂度分析_1

求某一个数字逆元的时间复杂度 :$O(lnp)$

---

#### 费马小定理求解逆元

`费马小定理 :`

> 如果 $p$ 是一个 **质数** 而 $gcd(a,p) \equiv 1$ 则 : $a ^ {p-1} \equiv 1 (mod$ &nbsp; $p)$

> 那么很容易得 : $a * a ^ {p-2} \equiv 1 (mod$ &nbsp; $p)$ , 即得到 $a$ 得 __逆元__ 为 $a ^ {p-2} mod$ &nbsp; $p$ 然后用 **快速幂** 也可以快速求解。

##### CODE_2

```cpp
int exe_mi(int a,int p,const int& TMOD) {
    // return a ^ p
    int res = 1;
    while(p) {
        if(p&1) res = ((long long) res * a) % TMOD;
        a = ((long long) a * a) % TMOD;
        p >>= 1;
    }
    return res;
}
int cal_inv(int x,int p) {
    // 求 x 在 模 p 下的逆元
    return exe(x,p-2,p);
}
```

##### 复杂度分析_2

求某一个数字逆元的时间复杂度 :$O(logp)$ , 主要是 **快速幂** 的开销

---

#### 线性求逆元

如果我们需要求 `[1,p)` 关于 `p` 的逆元 , 那么按照上面的方法 , 时间复杂度会到 : $O(p * logp)$ 的一个时间复杂度。现在给出一个 $O(p)$ 时间内的线性求解方法 :

假设现在求出了 `1,i-1` 的逆元 , 那么对于 `i` 设 : `p = k * i + r` :

以下等式都是 `mod p` 的情况下

> $k*i+r\equiv0$
>
> $k*i*(ri*rr)+r*(ri*rr)\equiv0$ , $ri,rr$ 为 $i,r$ 在 $p$ 下的逆元
>
> $k*rr+ri\equiv0$
>
> $ri\equiv{-k*rr}=-\frac{p}{i}*rr$
> 而 $rr$ 一定小于 $i$ 所以可以直接使用

##### CODE_3

```cpp
void cal_inv(cosnt int p) {
    inv[1] = 1;
    for(int i = 2;i <p;i ++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
    }
}
```

##### 复杂度分析_3

求出全部 `[1,p)` 在 `模p` 下的逆元 , 时间复杂度为 : $O(p)$

---

#### 阶乘逆元

求解 `0!` 到 `n!` 的逆元 , 可以类似上述

用处 : 在用 `组合数公式` 计算 `组合数` 的时候 : 当求解 $C[i][j]=\frac{j!}{i!*(j-i)!}$ 时 , 对于除法的处理就可以使用逆元来进行操作了 :

$C[i][j]=(j!)*(r_i!)*(r_{j - i}!)$

对于 `n!` 的阶乘求逆元 `rn` :

> $n!*rn\equiv1$
>
> $\frac{(n + 1)!}{n + 1}*rn\equiv1$
>
> $rn\equiv(n+1)*r_{n+1}$

相当于我们 __从后往前__ 利用已经求得的信息来帮助求解 `n!` 的逆元

##### CODE_4

```cpp
const int N = 1e5 + 7;
int fac[N];
int INV[N];
int exe_mi(int a,int p,const int& TMOD) {
    // return a ^ p
    int res = 1;
    while(p) {
        if(p&1) res = ((long long) res * a) % TMOD;
        a = ((long long) a * a) % TMOD;
        p >>= 1;
    }
    return res;
}
int cal_inv(int x,int p) {
    // 求 x 在 模 p 下的逆元
    return exe_mi(x,p-2,p);
}
void init(int n,const int& TMOD) {
    fac[0] = 1;
    for(int i = 1;i <= n;i ++) {
        fac[i] = (long long) fac[i - 1] * i % TMOD;
    }
    // INV[n] 需要初始化
    INV[n] = cal_inv(fac[n],TMOD);
    for(int i = n - 1;i;i --) {
        INV[i] = (long long) (i + 1) * INV[i + 1] % TMOD;
    }
    INV[0] = 1;
}
```
