#

## 马拉车 (manacher) 算法

**参考链接 :** [一文让你彻底明白马拉车算法](https://zhuanlan.zhihu.com/p/70532099)

主要的思想 :

> 充分利用 **回文串** 的 **对称性**
>
>> 1. 首先为了避免 **回文长度奇数和偶数的讨论** , 我们对给定字符串 $s$ 进行预处理 —— (比如 `s = abcba` -> `s' = ^#a#b#c#b#a#$`)
>>      - 在每两个字符之间加上 '#'
>>  
>>      对于 `s[i]` 对应的 `s'` 中的坐标为 : $(i + 1) * 2$
>>      对于 `s'[i]` 对应的 `s` 中的坐标就是 : $(i - 1) / 2$
>>
>> 2. 我们用 `R[i]` 来表示 `s'[i]` 的 **最大回文半径** (不算 `s'[i]`)
>>      - 那么此时 : 原串中的回文串为 : `s[(i - R[i] - 1) / 2 , (i + R[i] - 1) / 2)` **注意左闭右开** 因为 `s'` 中每一个回文串一定是 `'#'` 结尾的 而最后一个 `'#'` 对应的 `s` 中的字符是不参与的原串的回文串的
>>        1. 左边界为 : $l = i - R[i]$ 对应的 `s[(l - 1) / 2]`
>>        2. 右边界为 : $r = i + R[i]$ 对应的 `s[(r - 1) / 2 - 1]`

---

### 求 R[] 的具体方法

1. 假设当前我们需要计算 $R[i]$ 且知道了 $R[0:i-1]$ 的信息 , 现在前面 `s'` 中 记 :
    - C 为 `s'[0:i - 1]` 中右边界最远的回文串的中心位置
    - RP = C + R[C] , 为该回文串的最右位置
    - LP = C - R[C] , 为该回文串的最左位置
2. 那么对于 $i$ 我们有如下可能 :
   1. $i < RP$ : 设 $i'$ 为 $i$ 关于 $C$ 的对称

    ---
      a. 如果 $i' - R[i'] >= LP$ 那么根据 **对称性** $R[i] = R[i']$ , 不过此时需要特别注意 **当 $i' - R[i']$ 为左边界时** 对于 $i$ 还是需要从 $R[i'] + 1$ 开始 **中心扩展**

    ---

      b. 否则 $i' - R[i] < LP$ 那么对于 $s[i]$ 来说 至少 $Len = i' - LP$ 是不需要中心扩展的 , 然后对于 $i$ 来说只需要从 $len + 1$ 开始 **中心扩展** 即可
   2. $i == RP$ : 那么直接从 $i$ 开始 **中心扩展** 即可

### 代码

具体看 `./manacher.h`

参考题目 : [214. 最短回文串](https://leetcode-cn.com/problems/shortest-palindrome/)

```cpp
#include <bits/stdc++.h>
using namespace::std;
class manacher
{
public:
    int n;
    int* R;
    string s;
    void init() {
        n = s.size();
        R = new int[n + 1]; R[0] = 0 , R[1] = 0;
        int C , RP;
        C = 1 , RP = 1;// RP 当前的最右位置 LP = 2 * C - RP
        for(int i = 2;i < n;i ++) {
            // 计算 R[i]
            if(i >= RP) {
                R[i] = 0;
                for(int j = 1;i + j < n;j ++ , R[i] ++) {
                    if(s[i + j] != s[i - j]) break;
                }
            } else {
                int i_mirror = 2 * C - i;// i 关于 C 的对称
                int LP = 2 * C - RP;// 最左的位置
                int o = i_mirror - R[i_mirror];// i_mirror 的最左的位置
                if(o <= LP) {// 需要中心扩展的情况
                    R[i] = i_mirror - LP;
                    for(int j = R[i] + 1;j < n;j ++ , R[i] ++) {
                        if(s[i + j] != s[i - j]) break;
                    }
                } else {
                    R[i] = R[i_mirror];
                }
            }
            if(i + R[i] > RP) RP = i + R[i] , C = i;
        }
    }

    manacher(string& s_) {
        s = "^#";
        for(auto& c : s_) s += c , s += "#";
        s += "$";
        init();
    }
    ~manacher() {
        delete []R;
    }
};
class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.empty()) return "";
        manacher h(s);
        // 相当于找最长的回文前缀 即找到的回文串的对应原串的 l 要等于 0
        string res;
        int r = 0;
        int n = h.s.size();
        for(int i = 1;i < n;i ++) {
            if(i - h.R[i] == 1) {
                r = max(r,i + h.R[i] - 1) / 2 - 1;
            }
        }
        res = s.substr(r + 1);
        reverse(res.begin(),res.end());
        return res + s;
    }
};
```
