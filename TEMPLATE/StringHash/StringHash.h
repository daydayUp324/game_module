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