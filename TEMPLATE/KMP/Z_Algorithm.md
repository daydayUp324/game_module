#

## Z Algorithm (扩展 KMP)

参考链接 : [Z 函数（扩展 KMP）](https://oi-wiki.org/string/z-func/)

约定：字符串下标以 $0$ 为起点。

对于个长度为 $n$ 的字符串 。定义函数 $z[i]$ 表示 $s$ 和 $s[i:n-1]$（即以 $s[i]$ 开头的后缀）的 **最长公共前缀（LCP）** 的长度。 被称为  的 **Z 函数**。特别地，$z[0] = 0$。

国外一般将计算该数组的算法称为 **Z Algorithm**，而国内则称其为 **扩展 KMP**。

### 线性算法

和 `KMP` 中的 `next[]` 的计算一样 , 我们在计算 `z[i]` 的时候可以考虑使用 `z[j]` , `j < i`。

1. 记 : 对于 `i` 匹配的字符串为 : `s[i : i + z[i] - 1]` , 称为 `i` 的 `Z-box`。
2. 我们维护一个最靠右的 **匹配段** $[l,r]$ , 使得  $[l,r]$ 是 $i' \le i$ 的最右边的 `Z-box`。则根据定义 : $s[l,r]$ 为 $s$ 的一个前缀。则对于 `i` 来说一定满足 $l <= i$。初始时 : $l = r = 0$

#### 计算 `Z[i]` 过程

1. 如果 `i <= r` , 那么根据 `[l,r]` 的定义 `s[l:r] == s[0:r-l]` 得 : `s[i:r] == s[i-l:r-l]`。那么 可以得到 : $z[i] \ge \min\{z[i-l],r-i+1\}$ (**Tip** : 为什么要加 $min$ ? : 因为即使 `z[i-l]` 很大 , 但是仍不能超过 `s[i:r]` 的长度) 。这时 :
   - 若 $z[i-l] < r - l + 1$ 时 : $z[i] = z[i-l]$
   - 否则 : 先令 $z[i-l] = r - l + 1$ , 然后往后暴力扩展即可。
2. 否则 `i > r` : 直接 **暴力求解** `z[i]` 即可
3. 最后更新 `[l,r]`。

**时间复杂度** : $O(n)$ 因为 `i,j` 都时单调右移的。

#### Z_ALGRITHRM_CODE

```cpp
void Cal_z() {
    z_f = true;
    z = new int[n + 1];
    int l,r;
    z[0] = l = r = 0;
    for(int i = 1;i < n;i ++) {
        if(i <= r) {// p[i:r] == p[i-l:r-l]
            if(z[i - l] < r - i+ 1) z[i] = z[i - l];
            else {
                z[i] = r - i + 1;;
                while(i + z[i] < n && p[z[i]] == p[i + z[i]]) z[i] ++;
            }
        } else {// brute-force
            z[i] = 0;
            while(i + z[i] < n && p[z[i]] == p[i + z[i]]) z[i] ++;
        }
        // update
        if(i + z[i] - 1 > r) l = i , r = i + z[i] - 1;
    }
}
```

---

#### APPLICATION

---

##### 匹配所有子串

###### 问题描述_1

对于一个文本串 `s` , 求模式串 `p` 出现的次数。

###### 思路分析_1

那么我们分析 : 如果设 `s'` = `p + '#' + s` , 其中 `'#'` 为不在 `s` 和 `p` 中出现的字符。如果现在求得 `s'` 的 `z 数组` , 那么按照 `z 数组` 的定义 , 若对于某一个 `i` , $i > p.size()$ 有 `z[i] = p.size()` , 那么 `s[i:i + p.size() - 1]` 就是模式串 `p`。也是 原文本串 `s` 中对应的位置。

###### 时间复杂度_1

$O(p.size() + s.size())$

---

###### 本质不同子串数

###### 问题描述_2

给定一个长度为 $n$ 的字符串 `s` , 计算 `s` 的本质上不同字串的数目。

###### 思路分析_2

**从小问题到大问题 :**

如果我们知道了 `s[:i]` 中所有的**本质不同的子串**的数目 , 那么我们在 `s[:i]` 后面加入 字符 `c` , 记 : `t = s[:i] + c`。
则 : 多出来的 **本质不同的子串** 只有可能是 `t[j:]`。`j` 不合法的情况是 : `t[j:] = t[l:r]`。那么我们将 `t` 进行反转 : `rt = reverse(t)` , 对 `rt` 求一次 `z[] 数组` 得到 `z_max` (`z[] 数组` 中的最大值 , 该值即为不合法的 `j` 的数目)。那么会产生的新的 `本质不同的子串` 的个数就是 `t.size() - z_max`。

那么一直往下增加到 `t == s` 即可。

###### 时间复杂度_2

每加入一个 `字符 c` 需要求一次 `z[] 数组` : $O(n^2)$

---

###### 字符串整周期

###### 问题描述_3

给定一个长度为 $n$ 的 `字符串 s` , 找到其最短的**整周期** , 即找到一个最短的 `字符串 t` 使得 $s$ 可以被若干个 $t$ 拼接而成。

###### 思路分析_3

计算 $s$ 的 `z[] 数组` , 最短的整周期 `i` 为满足以下条件的最小 `i` :

1. $n \% i == 0$
2. $i + z[i] == n$

充分性证明 :

对于这样一个 `i` , `s[i:]` 一定是 `s` 的一个**前缀** , 设 : `n = k * i`。那么令 : $s = s_1  s_2  ... s_k$ , 那么 $s[i:] = s_2...s_k$。

1. 当 $k = 1$ 时 : 整周期就是 `n` 满足要求
2. 当 $k = 2$ 时 : `s` 的前一半和后一半刚好相同即也满足要求
3. 当 $k > 2$ 时 : $s1...s_{k-1} = s_2...s_k$ , 即 : $s_i = s_{i + 1}$ , 那么 $s1 = s2 = s3 = ... = s_k$ , 即也同样满足要求。

---

##### [6036. 构造字符串的总得分和](https://leetcode-cn.com/problems/sum-of-scores-of-built-strings/)

[![qLDhcR.png](https://s1.ax1x.com/2022/04/05/qLDhcR.png)](https://imgtu.com/i/qLDhcR)

##### CODE_1

```cpp
#include<bits/stdc++.h>
using namespace std;
class KMP
{
    /**
     * @author : daydayUppp
     */
public:
    string p;
    int* next;
    int* z;
    bool z_f,next_f;
    int n;
    int suc;// 匹配成功的标志
    void Cal_next() {
        next_f = true;
        next = new int[n];
        next[0] = -1;
        for(int i = 1 , j = -1;i < n;i ++) {
            while(j + 1 && p[i] != p[j + 1]) j = next[j];
            if(p[i] == p[j + 1]) j ++;
            next[i] = j;
        }
    }
    void Cal_z() {
        z_f = true;
        z = new int[n + 1];
        int l,r;
        z[0] = l = r = 0;
        for(int i = 1;i < n;i ++) {
            if(i <= r) {// p[i:r] == p[i-l:r-l]
                if(z[i - l] < r - i+ 1) z[i] = z[i - l];
                else {
                    z[i] = r - i + 1;;
                    while(i + z[i] < n && p[z[i]] == p[i + z[i]]) z[i] ++;
                }
            } else {// brute-force
                z[i] = 0;
                while(i + z[i] < n && p[z[i]] == p[i + z[i]]) z[i] ++;
            }
            // update
            if(i + z[i] - 1 > r) l = i , r = i + z[i] - 1;
        }
    }
    int Match_s(string& s) {// 模式串 p 匹配主串 s '
        // return s 匹配 p 的第一个位置
        // return -1 说明匹配不成功
        if(s.size() < n) return -1;
        for(int i = 0 , j = -1;i < s.size();i ++) {
            while(j + 1 && s[i] != p[j + 1]) j = next[j];
            if(s[i] == p[j + 1]) j ++;
            if(j == suc) return i - n + 1;
        }
        return -1;
    }
    KMP(string& p_) {
        z_f = next_f = false;
        n = p_.size(); suc = n - 1;
        this->p = p_;
        // Cal_next();
        Cal_z();
    }
    ~KMP() {
        if(z_f) delete []z; 
        if(next_f) delete []next;
    }
};
class Solution {
public:
    int* o;
    long long sumScores(string s) {
        KMP h(s);
        long long res = h.n;
        for(int i = 1;i < s.size();i ++) {
            // cout<<i<<" , "<<h.z[i]<<"\n";
            res += h.z[i];
        } 
        return res;
    }
};
```
