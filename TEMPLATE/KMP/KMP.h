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