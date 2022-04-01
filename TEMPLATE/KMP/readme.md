#

## KMP 算法

用于 **字符串的匹配问题 :**
主串 : $s$ , $s.size() = n$
模式串 : $p$ , $p.size() = m$
(下标都是从 0 开始)

重点在于 模式串 $p$ 的 $next[]$ 数组的理解 :

1. $next[i] + 1$ 的实际上是 $p[0 : i]$ 串的 **最长相同前后缀串** 的长度。
   - 所以 `KMP` 的一个扩展应用就是 : 计算 字符串$p$ 的 **最长相同前后缀串** (具体可见下方的 **应用题目二** )
2. $next[i]$ 表示当 $p[i]$ 与某一个要之匹配的字符不相同时 , 匹配的指针 $j = next[i]$。
3. 其中完整串不做为相同的前后缀 , 即 : $next[i] \neq i$ , 因为完整串说明此时匹配成功。

### 计算 next[] 过程

1. 首先对于模式串 $p$ , $i$ 表示现在要匹配的 $j$ 表示已经匹配的 , 初始化 :
   - $next[0] =  -1 , i = 1 , j = -1$
     - 对于 $next[0]$ 的理解 : 从 $next[]$ 的定义出发 , $p[0:-1]$ 的最长公共前后缀长度不存在
     - 因为空串是一定匹配的所以 $j = -1$
     - 因为 $i = 0$ 时 , $next[i] = 1$ 没有意义 , 所以 $i = 2$ 开始
2. 则每一步需要匹配的是 $p[i]$ 和 $p[j + 1]$ 如果相同的话说明 $next[i] = j + 1 , j = j + 1$。否则 :

    ```cpp
    while(j + 1 && p[i] != p[j]) j = next[j];
    // 最后 j == -1 的话说明又要从空串进行匹配
    ```

### 匹配过程

正常 **双指针** 匹配 , 每次匹配不成功时用 $next[]$ 来进行移动 $j$

```cpp
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
```

### 代码参考

完整代码见 `KMP.h`

### 复杂度

**时间复杂度 :** $O(logm)$

### 应用

#### 题目一

题目链接 : [28. 实现 strStr()](https://leetcode-cn.com/problems/implement-strstr/)

![image.png](https://s2.loli.net/2022/04/01/1Hs5Q7F9SdpIbn3.png)

```cpp
#include<bits/stdc++.h>
using namespace std;
class KMP
{
public:
    string p;
    int* next;
    int n;
    int suc;// 匹配成功的标志
    void Cal_next() {
        next = new int[n];
        next[0] = -1;
        for(int i = 1 , j = -1;i < n;i ++) {
            while(j + 1 && p[i] != p[j + 1]) j = next[j];
            if(p[i] == p[j + 1]) j ++;
            next[i] = j;
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
        n = p_.size(); suc = n - 1;
        this->p = p_;
        Cal_next();
    }
    ~KMP() {
        delete []next;
    }
};
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.empty()) return 0;
        KMP h(needle);
        return h.Match_s(haystack);
    }
};
```

#### 题目二

题目链接 : [214. 最短回文串](https://leetcode-cn.com/problems/shortest-palindrome/)

![image.png](https://s2.loli.net/2022/04/01/8PwHNeyQ72VphMu.png)

##### 思路分析

题目本质是找最长的前缀使得 : $s[0:i]$ 是一个回文串 即我们将 $s$ 拆分成 : $s  = s' + t$ , $s'$ 为 **最长的前缀回文串** , 现在我们需要求的就是 $s'$ 的长度。通过 **KMP** 的学习 , 我们可以知道 $next[i] + 1$ 是 $s[0:i]$ 的 **最长的相同前后缀长度**。那么我们是否可以构造一个以 $s'$ 为 **最长的相同前后缀长度** 的字符串呢 ？

答案是可以的 : $s' + t + '\#' + rt + rs'$ , 其中 `'#'` 为字符串 $s$ 中没有出现的字符 , $rt,rs'$ 分别为 $t,s$ 的翻转字符串。那么此时的 $next[s.size() - 1]$ 就是 **最长的前缀回文串长度**。而加入 `'#'` 的原因就是为了防止 最后的 **最长的相同前后缀长度** 大于原串的长度

```cpp
#include<bits/stdc++.h>
using namespace std;
class KMP
{
public:
    string p;
    int* next;
    int n;
    int suc;// 匹配成功的标志
    void Cal_next() {
        next = new int[n];
        next[0] = -1;
        for(int i = 1 , j = -1;i < n;i ++) {
            while(j + 1 && p[i] != p[j + 1]) j = next[j];
            if(p[i] == p[j + 1]) j ++;
            next[i] = j;
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
        n = p_.size(); suc = n - 1;
        this->p = p_;
        Cal_next();
    }
    ~KMP() {
        delete []next;
    }
};
class Solution {
public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string rs = s; reverse(rs.begin(),rs.end());
        s += "#" + rs;
        KMP h(s);
        int o = h.next[2 * n] + 1;// 下标从 0 开始的情况
        string res = s.substr(o,n - o); reverse(res.begin(),res.end());
        res += s.substr(0,n);
        return res;
    }
};
```
