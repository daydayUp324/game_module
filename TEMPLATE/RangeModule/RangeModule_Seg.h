#include <bits/stdc++.h>
using namespace std;
class RangeModule_Seg
{
    /***
     * 适用范围 : 
     * 1. 用于区间 [l:r] 的 add 和 remove 
     * 2. 区间管理 区间没有属性 每一段区间都没有重叠部分
     * 3. 可以扩展为 O(1) 得到目前区间的最大长度 mst.rbegin();
     * 
     * 题目链接 : [715. Range 模块](https://leetcode-cn.com/problems/range-module/)
    */
private:
    multiset<int> mst;// 每一段区间长度
    map<int,int> seqs;// 用 map 来存储每一段 区间 {r,l} seqs[r] = l
    bool mst_flag;// 用于判断是否需要更新 mst
public:
    void Print_Seq() {// 测试用 : 输出当前全部区间
        for(auto& [r,l] : seqs) {
            cout<<" [ "<<l<<" , "<<r<<" ]\n";
        }
        cout<<"\n";
    }
    void remove_seq(int l,int r) {// 移除区间
        mst.erase(mst.find(r - l + 1)); seqs.erase(r);
    }
    void add_seq(int l,int r) {// 增加区间
        mst.insert(r - l + 1); seqs[r] = l;
    }
    void erase(int l,int r) {// 删除与 [l:r] 有关的区间
        if(r < l) return ;
        // 没有相交的情况
        if(seqs.empty() || r < seqs.begin()->second || l > seqs.rbegin()->first) return ;
        auto t = seqs.lower_bound(l);// [ll,rr]
        // 1. 该区间被包含
        if(t->second <= l && t->first >= r) {
            // [ll,l) (r,rr]
            int ll = t->second , rr = t->first;
            seqs.erase(t);
            if(ll < l) seqs[l - 1] = ll;
            if(r < rr) seqs[rr] = r + 1;
            return ;
        }
        // 2. 该区间与其他区间无交集
        if(t->second > r) return ;
        // 3. 左相交
        if(t->second < l) {
            int ll = t->second;
            // 剩下 [ll,l)
            if(t->first == seqs.rbegin()->first) {
                if(ll < l) seqs[l - 1] = ll;
                seqs.erase(t);
                return ;
            } 
            seqs.erase(t ++);
            if(ll < l) seqs[l - 1] = ll;
        }
        // 4. [ll,rr] 被包含 迭代删除
        while(t->second >= l && t->first <= r) {
            if(t->first == seqs.rbegin()->first) {
                seqs.erase(t);
                return ;
            } 
            seqs.erase(t ++);
        }
        // 5. 右相交
        if(t->second <= r) {
            int rr = t->first;
            // 剩下 (r,rr]
            if(r < rr) seqs[rr] = r + 1;
            else seqs.erase(rr);
        }
    }

    void add(int l,int r) {// 加入区间 [l:r]
        if(r < l) return ;
        // 没有相交的情况
        if(seqs.empty() || r < seqs.begin()->second - 1 || l > seqs.rbegin()->first + 1) {
            seqs[r] = l;
            return ;
        }
        if(r == seqs.begin()->second - 1)  {
            auto t = seqs.begin()->first;
            seqs[t] = l; return ;
        }
        if(l == seqs.rbegin()->first + 1) {
            auto t = seqs.rbegin()->first;
            l = seqs[t]; seqs.erase(t); seqs[r] = l;
            return ;
        }
        auto t = seqs.lower_bound(l);// [ll,rr]
        // 1. 该区间被包含
        if(t->second <= l && t->first >= r) return ;// 无需额外操作
        // 2. 该区间与其他区间无交集
        if(t->second > r) {
            seqs[r] = l;
            return ;
        }
        // 3. 左相交
        if(t->second <= l) {
            l = t->second;
            if(t->first == seqs.rbegin()->first) {
                seqs.erase(t);
                seqs[r] = l;
                return ;
            } 
            seqs.erase(t ++);
        } 
        // 4. [ll,rr] 被包含 迭代删除
        while(t->second >= l && t->first <= r) {
            if(t->first == seqs.rbegin()->first) {
                seqs.erase(t);
                seqs[r] = l;
                return ;
            } 
            seqs.erase(t ++);
        }
        // 5. 右相交
        if(t->second <= r) {
            r = t->first;
            seqs.erase(t);
        } 

        while(seqs.count(l - 1)) {
            int t = l - 1;
            l = seqs[l - 1];
            seqs.erase(t);
        }

        while(!seqs.empty() && seqs.rbegin()->first > r) {
            auto t = seqs.lower_bound(r + 1);
            if(t->second > r + 1) break;
            r = t->first;
            seqs.erase(seqs.rbegin()->first);
        }

        seqs[r] = l;
    }
    bool query(int l,int r) {// 查询区间 [l:r] 是否存在 
        if(l > r) return false;
        if(seqs.empty() || r < seqs.begin()->second || l > seqs.rbegin()->first) {
            return false;
        }
        auto t = seqs.lower_bound(l);// [ll,rr]
        if(t->second <= l && t->first >= r) return true;
        return false;
    }
    int getMaxRLen() {// 返回区间的最大长度
        if(mst.empty()) return 0;
        return *mst.rbegin();
    }
    RangeModule_Seg(bool flag = false) {
        mst_flag = flag;
    };
};