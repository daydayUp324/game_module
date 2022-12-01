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