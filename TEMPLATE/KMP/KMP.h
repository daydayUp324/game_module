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
        Cal_next();
        Cal_z();
    }
    ~KMP() {
        if(z_f) delete []z; 
        if(next_f) delete []next;
    }
};