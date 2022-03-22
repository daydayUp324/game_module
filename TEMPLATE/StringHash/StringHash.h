#include <bits/stdc++.h>
using namespace  std;
using PII = pair<int,int>;
using LL = long long;
class StringHash
{
    /**
     * @author : daydayUppp
     * StringHash : 
     * 用 PII 的双哈希来减小冲突的可能 , hash<int>() 用于产生一个哈希值
     * 
     * 算法 :
     * 1. 首先产生两个随机数 base1 , base2 作为基底
     * 2. 
     * s[i:j] = 
     * 
     */
private:
    static constexpr int mod1 = 1000000007;
    static constexpr int mod2 = 1000000009;
    struct pairhash {
        size_t operator() (const pair<int, int>& p) const {
            auto fn = hash<int>();
            return (fn(p.first) << 16) ^ fn(p.second);
        }
    };
public:
    StringHash(string& s) {
        // 
        // 
    };
};

