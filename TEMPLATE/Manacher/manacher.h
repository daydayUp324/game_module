#include <bits/stdc++.h>
using namespace::std;
class manacher
{
    /**
     * @author : daydayUppp
     * @brief : 传入原串 s , 构造生成 s'
     * 
     * 1. s[i] 中对应 s' 中的坐标为 (i + 1) * 2
     * 2. s'[i] 中对应 s 中的坐标为 (i - 1) / 2
     * 
     * R[i] 表示 s'[i] 的最大回文半径
     * 
     * 得到的原串 s 中的字符串为 : 
     * int l = (i - h.R[i] - 1) / 2;
     * int r = (i + h.R[i] - 1) / 2 - 1;
     * s.substr(l,r - l + 1);
     * 
     * ------------- 分割线 (扩展版) ------------------
     * 
     * 对于只需要查找奇数长度的回文串 : 
     * 只需要令 s = "^" + s + "$" 即可 那么 [i - R[i] , i + R[i]] 就是原串对应的回文串
     * 
     */
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
            // cout<<"DEBUG : "<<i<<" , "<<C<<" , "<<R[C]<<" , "<<RP<<"\n";
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
        // cout<<"Before : "<<s_<<"\n"<<"After : "<<s<<"\n";
        init();
    }
    ~manacher() {
        delete []R;
    }
};