#

## 相关题目

### [214. 最短回文串](https://leetcode-cn.com/problems/shortest-palindrome/)

#### 题目描述_1

![image.png](https://s2.loli.net/2022/03/24/OXAG3wSDxT2p6Fj.png)

#### 代码参考_1

```cpp
using PII = pair<int,int>;
using LL = long long;
/**
 * @author : daydayUppp
 * 
 * 1. 用 Random_ 类 来产生 Base 作为 StringHash 的参数
 * 2. StringHash 中 string 也可以用 vector 等作为参数传入
 */
class Random_ 
{
public:
    int getARandom(int l = 1e6, int r = 1e7) {
        mt19937 gen{random_device{}()};
        auto dis = uniform_int_distribution<int>(l, r); 
        return dis(gen);
    }
    Random_() {};
};
class StringHash
{
private:
    static constexpr int MOD1 = 1000000007;
    static constexpr int MOD2 = 1000000009;
    int Base1, Base2;// 两个基底
    struct pairhash {
        size_t operator() (const pair<int, int>& p) const {
            auto fn = hash<int>();
            return (fn(p.first) << 16) ^ fn(p.second);
        }
    };
    int n;// 字符串长度
    vector<LL> pre1, pre2;
    vector<LL> pow1, pow2;
    unordered_set<PII, pairhash> piist;
public:
    void initial(string& s) {
        pow1.resize(n), pow2.resize(n), pre1.resize(n), pre2.resize(n);
        pow1[0] = pow2[0] = 1;
        pre1[0] = s[0] , pre2[0] = s[0];
        for(int i = 1;i < n;i ++) {
            pow1[i] = (pow1[i - 1] * Base1) % MOD1;
            pow2[i] = (pow2[i - 1] * Base2) % MOD2;
            pre1[i] = (pre1[i - 1] * Base1 + s[i]) % MOD1;
            pre2[i] = (pre2[i - 1] * Base2 + s[i]) % MOD2;
        } 
    }
    void add(PII& t) {// 加入某一个状态
        piist.insert(t);
    }
    int getNumber() {// 返回不同的状态数
        return piist.size();
    }
    PII getHash(int l,int r) {// return hash( s[l,r] )
        int hash1, hash2;
        if (l == 0) hash1 = pre1[r], hash2 = pre2[r];
        else {
            hash1 = (pre1[r] - ((pre1[l - 1] * pow1[r + 1 - l]) % MOD1) + MOD1) % MOD1;
            hash2 = (pre2[r] - ((pre2[l - 1] * pow2[r + 1 - l]) % MOD2) + MOD2) % MOD2;
        } 
        return {hash1,hash2};
    }
    StringHash(string& s, int Base1_, int Base2_) : n(s.size()), Base1(Base1_), Base2(Base2_) {
        initial(s);
    };
    StringHash(string& s) : n(s.size()) {
        Random_ h; 
        this->Base1 = h.getARandom(); 
        this->Base2 = h.getARandom();
        while(this->Base2 == Base1) this->Base2 = h.getARandom();
        initial(s);
    }
};
class Solution {
public:
    string shortestPalindrome(string s) {
        // 相当于找最长的前缀 s[:r] 使得 s[0:r] 为一个回文串
        // 令 rs 为 s 的翻转串 : 则 : s[i:j] 对应 rs[n - 1 - j:n - 1 - i]
        // 相当于 :
        // 1. s[0:r] 为奇数长度 需要 s[0:r/2 - 1] 和 rs[n - 1 - r:n - 2 - r/2] 相同
        // 2. s[0:r] 为偶数长度 需要 s[0:r/2] 和 rs[n - 1 - r:n - 2 - r/2]
        int n = s.size();
        if(!n) return "";
        string rs = s; reverse(rs.begin(),rs.end());
        Random_* R = new Random_();
        int Base1 = R->getARandom() , Base2 = R->getARandom();
        StringHash* h = new StringHash(s,Base1,Base2);
        StringHash* rh = new StringHash(rs,Base1,Base2);
        int p = 0;
        for(int i = 1;i < n;i ++) {
            if(i & 1) {
                // 偶数长度
                if(h->getHash(0,i / 2) == rh->getHash(n - 1 - i , n - 2 - i / 2)) p = i;
            } else {
                // 奇数长度
                if(h->getHash(0,i / 2 - 1) == rh->getHash(n - 1 - i , n - 2 - i / 2)) p = i;
            }
        }
        // 使 : s[p + 1:] 翻转后贴到前面
        string res = "";
        for(int i = n - 1;i > p;i --) res += s[i];
        res += s;
        return res;
    }
};
```

### [1316. 不同的循环子字符串](https://leetcode-cn.com/problems/distinct-echo-substrings/)

#### 题目描述_2

![image.png](https://s2.loli.net/2022/03/24/AipKTvYEJgQHRxI.png)

#### 代码参考_2

```cpp
#include <bits/stdc++.h>
using namespace  std;
using PII = pair<int,int>;
using LL = long long;
class Random_ 
{
    /**
     * @author : daydayuppp
     * 用于产生 Base 时使用 , 需要 Base 来初始化 StringHash 对象
     */
public:
    int getARandom(int l = 1e6,int r = 1e7) {
        mt19937 gen{random_device{}()};
        auto dis = uniform_int_distribution<int>(l,r); 
        return dis(gen);
    }
    Random_() {};
};
class StringHash
{
    /**
     * @author : daydayUppp
     * StringHash : 
     * 用 PII 的双哈希来减小冲突的可能 , hash<int>() 用于产生一个哈希值
     * 
     * 算法 :
     * 1. 首先产生两个随机数 Base1 , Base2 作为基底 , Base1 , Base2 都用随机数生成
     * 2. hash(s[i:j]) = {h1,h2}
     *      - h1 = (index = i->j) sum{ s[index] * Base1^(j - index) } % MOD1
     *      - h2 = (index = i->j) sum{ s[index] * Base2^(j - index) } % MOD2
     * 3. 所以预处理 : 
     *      - pow1[i] = (Base1 ^ i) % MOD1 , pow2[i] = (Base2 ^ i) % MOD2
     *      - pre1[i] = hash( s[0:i] ) : Base1 , pre2[i] = hash( s[0:i] ) : Base2
     * 4. 那么计算 对于 Base1 来说 :
     *      hash( s[i : j] ) : Base1 : 
     *      - 1. i == 0 : return pre1[j];
     *      - 2. return pre1[j] - pre1[i - 1] * pow1[j + 1 - i];
     * 5. 计算 对于 Base2 来说同理可得
     * 
     * 注意 : 减法时的负数问题
     */
private:
    static constexpr int MOD1 = 1000000007;
    static constexpr int MOD2 = 1000000009;
    int Base1,Base2;// 两个基底
    struct pairhash {
        size_t operator() (const pair<int, int>& p) const {
            auto fn = hash<int>();
            return (fn(p.first) << 16) ^ fn(p.second);
        }
    };
    int n;// 字符串长度
    vector<LL> pre1,pre2;
    vector<LL> pow1,pow2;
    unordered_set<PII,pairhash> Piist;
public:
    void initial(string& s) {
        pow1.resize(n) , pow2.resize(n) , pre1.resize(n) , pre2.resize(n);
        pow1[0] = pow2[0] = 1;
        pre1[0] = s[0] , pre2[0] = s[0];
        for(int i = 1;i < n;i ++) {
            pow1[i] = (pow1[i - 1] * Base1) % MOD1;
            pow2[i] = (pow2[i - 1] * Base2) % MOD2;
            pre1[i] = (pre1[i - 1] * Base1 + s[i]) % MOD1;
            pre2[i] = (pre2[i - 1] * Base2 + s[i]) % MOD2;
        } 
    }
    PII getHash(int l,int r) {// return hash( s[l,r] )
        int hash1 , hash2;
        if(l == 0) hash1 = pre1[r] , hash2 = pre2[r];
        else {
            hash1 = (pre1[r] - ((pre1[l - 1] * pow1[r + 1 - l]) % MOD1) + MOD1) % MOD1;
            hash2 = (pre2[r] - ((pre2[l - 1] * pow2[r + 1 - l]) % MOD2) + MOD2) % MOD2;
        } 
        return {hash1,hash2};
    }
    void addPII(PII& t) {
        Piist.insert(t);
    }
    int getAns() {
        return Piist.size();
    }
    StringHash(string& s,int Base1_,int Base2_) {
        this->n = s.size();
        this->Base1 = Base1_ , this->Base2 = Base2_;
        initial(s);
    };
};
class Solution {
public:
    int distinctEchoSubstrings(string s) {
        int res = 0;
        Random_* R = new Random_();
        int a = R->getARandom() , b = R->getARandom();
        StringHash* sh = new StringHash(s,a,b);
        for(int i = 2;i <= s.size();i += 2) {
            for(int o = 0;o + i <= s.size();o ++) {
                // s[o : o + i - 1] -> s[o:o + i / 2 - 1] s[o + i / 2:o + i - 1]
                PII t1 = sh->getHash(o,o + i / 2 - 1) , t2 = sh->getHash(o + i / 2,o + i - 1);
                if(t1 == t2)sh->addPII(t1);
            }
        }
        return sh->getAns();
    }
};
```

### [1960. 两个回文子字符串长度的最大乘积](https://leetcode-cn.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/)

#### 题目描述_3

![image.png](https://s2.loli.net/2022/03/24/JuVzFjDNSyfm8TZ.png)

#### 解题思路_3

1. **二分** 每一个位置 $p$ 作为中心的最大半径 $R[p]$
   - 可用 **字符串哈希** 解决 同样需要 $rs$ 的 $StringHash$)
   - 或者用 **Manacher** 算法
2. 然后用 $M[i]$ 表示 从 $[i:]$ 的 **最长奇数回文串长度**
3. 然后 **从左往右** 遍历即可

### [6036. 构造字符串的总得分和](https://leetcode-cn.com/problems/sum-of-scores-of-built-strings/)

#### 题目描述_4

![image.png](https://s2.loli.net/2022/04/04/2au4njKAgsoBtFH.png)

#### 解题思路_4

知识点 : **二分 + 字符串哈希** / **扩展 KMP (具体见 KMP 对应 Application)**

因为对于每一个长度的后缀 $s[n - len:]$ , 与 $s$ 的相同 **前缀长度** 具有单调性质 , 所以 二分最大的与 $s$ 的相同前缀长度即可

#### 代码参考_4

```cpp
#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
using LL = long long;
/**
 * @author : daydayUppp
 * 
 * 1. 用 Random_ 类 来产生 Base 作为 StringHash 的参数
 * 2. StringHash 中 string 也可以用 vector 等作为参数传入
 */
class Random_ 
{
public:
    int getARandom(int l = 1e6,int r = 1e7) {
        mt19937 gen{random_device{}()};
        auto dis = uniform_int_distribution<int>(l,r); 
        return dis(gen);
    }
    Random_() {};
};
class StringHash
{
private:
    static constexpr int MOD1 = 1000000007;
    static constexpr int MOD2 = 1000000009;
    int Base1,Base2;// 两个基底
    struct pairhash {
        size_t operator() (const pair<int, int>& p) const {
            auto fn = hash<int>();
            return (fn(p.first) << 16) ^ fn(p.second);
        }
    };
    int n;// 字符串长度
    vector<LL> pre1,pre2;
    vector<LL> pow1,pow2;
    unordered_set<PII,pairhash> piist;
public:
    void initial(string& s) {
        pow1.resize(n) , pow2.resize(n) , pre1.resize(n) , pre2.resize(n);
        pow1[0] = pow2[0] = 1;
        pre1[0] = s[0] , pre2[0] = s[0];
        for(int i = 1;i < n;i ++) {
            pow1[i] = (pow1[i - 1] * Base1) % MOD1;
            pow2[i] = (pow2[i - 1] * Base2) % MOD2;
            pre1[i] = (pre1[i - 1] * Base1 + s[i]) % MOD1;
            pre2[i] = (pre2[i - 1] * Base2 + s[i]) % MOD2;
        } 
    }
    void add(PII& t) {// 加入某一个状态
        piist.insert(t);
    }
    int getNumber() {// 返回不同的状态数
        return piist.size();
    }
    PII getHash(int l,int r) {// return hash( s[l,r] )
        int hash1 , hash2;
        if(l == 0) hash1 = pre1[r] , hash2 = pre2[r];
        else {
            hash1 = (pre1[r] - ((pre1[l - 1] * pow1[r + 1 - l]) % MOD1) + MOD1) % MOD1;
            hash2 = (pre2[r] - ((pre2[l - 1] * pow2[r + 1 - l]) % MOD2) + MOD2) % MOD2;
        } 
        return {hash1,hash2};
    }
    StringHash(string& s,int Base1_,int Base2_) {
        this->n = s.size();
        this->Base1 = Base1_ , this->Base2 = Base2_;
        initial(s);
    };
    StringHash(string& s) {
        this->n = s.size();
        Random_ h; 
        this->Base1 = h.getARandom(); 
        this->Base2 = h.getARandom();
        while(this->Base2 == Base1) this->Base2 = h.getARandom();
        initial(s);
    }
};
class Solution {
public:
    long long sumScores(string s) {
        StringHash* h = new StringHash(s);
        int n = s.size();
        LL res = 0;
        for(int len = 1;len <= n;len ++) {
            int l = 1;
            int r = len;
            // [n - len,n - 1]
            while(l <= r) {
                auto mid = (l + r) / 2;
                if(h->getHash(n - len,n - len + mid - 1) == \
                  h->getHash(0,mid - 1)) l = mid + 1;
                else r = mid - 1;
            }
            res += l - 1;
        }
        return res;
    }
};
```
