#include <bits/stdc++.h>
using namespace std;
class RangeModule_Seg
{
    /***
     * @author : daydayUppp
     * 适用范围 : 
     * 1. 用于区间 [l:r] 的 add 和 remove 
     * 2. 区间管理 区间没有属性 每一段区间都没有重叠部分
     * 3. 可以扩展为 O(1) 得到目前区间的最大长度 mst.rbegin();
     * 4. mst_flag 用于维护当前区间的长度
     * 
     * 题目链接 : 
     * [715. Range 模块](https://leetcode-cn.com/problems/range-module/)
     * [352. 将数据流变为多个不相交区间](https://leetcode-cn.com/problems/data-stream-as-disjoint-intervals/)
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
    void Print_Len() {// 测试用 : 输出当前全部的区间长度
        cout<<"mst  : \n";
        for(auto& i : mst) cout<<i<<" ";
        cout<<"\n";
    }
    void remove_seq(int len) {// 移除区间长度
        mst.erase(mst.find(len));
    }
    void add_seq(int len) {// 增加区间长度
        mst.insert(len);
    }
    void erase(int l,int r) {// 删除与 [l:r] 有关的区间
        if(r < l) return ;
        // 没有相交的情况
        if(seqs.empty() || r < seqs.begin()->second || l > seqs.rbegin()->first) return ;
        auto t = seqs.lower_bound(l);// [ll,rr]
        // 1. 该区间被包含
        if(t->second <= l && t->first >= r) {// [ll,rr] -> [ll,l) (r,rr]
            int ll = t->second , rr = t->first;
            if(mst_flag) remove_seq(rr - ll + 1);
            seqs.erase(t);
            if(ll < l) {
                seqs[l - 1] = ll;
                if(mst_flag) add_seq(l - ll);
            } 
            if(r < rr) {
                seqs[rr] = r + 1;
                if(mst_flag) add_seq(rr - r);
            } 
            return ;
        }
        // 2. 该区间与其他区间无交集
        if(t->second > r) return ;
        // 3. 左相交
        if(t->second < l) {// [ll,rr] -> [ll,l)
            int ll = t->second;
            if(mst_flag) {
                remove_seq(t->first - ll + 1);
                if(ll < l) add_seq(l - ll);
            } 
            if(t->first == seqs.rbegin()->first) {
                if(ll < l) seqs[l - 1] = ll;
                seqs.erase(t);
                return ;
            } 
            seqs.erase(t ++);
            if(ll < l) seqs[l - 1] = ll;
        }
        // 4. [ll,rr] 被包含 迭代删除
        while(t->second >= l && t->first <= r) {// [ll,rr] X
            if(mst_flag) remove_seq(t->first - t->second + 1);
            if(t->first == seqs.rbegin()->first) {
                seqs.erase(t);
                return ;
            } 
            seqs.erase(t ++);
        }
        // 5. 右相交
        if(t->second <= r) {// [ll,rr] -> (r,rr]
            if(mst_flag) {
                remove_seq(t->first - t->second + 1);
                if(r < t->first) add_seq(t->first - r);
            } 
            int rr = t->first;
            if(r < rr) seqs[rr] = r + 1;
            else seqs.erase(rr);
        }
    }

    void add(int l,int r) {// 加入区间 [l:r]
        if(r < l) return ;
        // 没有相交的情况 直接加入
        if(seqs.empty() || r < seqs.begin()->second - 1 || l > seqs.rbegin()->first + 1) {
            if(mst_flag) add_seq(r - l + 1);
            seqs[r] = l; return ;
        }
        if(r == seqs.begin()->second - 1)  {// [l,r] + [ll,rr] -> [l,rr]
            if(mst_flag) {
                remove_seq(seqs.begin()->first - seqs.begin()->second + 1);
                add_seq(seqs.begin()->first - l + 1);
            } 
            seqs.begin()->second = l;
            return ;
        }
        if(l == seqs.rbegin()->first + 1) {// [ll,rr] + [l,r] -> [ll,r]
            auto t = seqs.rbegin()->first;
            if(mst_flag) {
                remove_seq(seqs.rbegin()->first - seqs.rbegin()->second + 1);
                add_seq(r - seqs.rbegin()->second + 1);
            }
            l = seqs.rbegin()->second; seqs.erase(t); seqs[r] = l;
            return ;
        }
        auto t = seqs.lower_bound(l);// [ll,rr]
        // 1. 该区间被包含
        if(t->second <= l && t->first >= r) return ;// 无需额外操作
        // 2. 该区间与其他区间无交集 [_l,_r] [l,r] [l_,r_]
        if(t->second > r + 1 && !seqs.count(l - 1)) {
            seqs[r] = l;
            if(mst_flag) {
                add_seq(r - l + 1);
            }
            return ;
        }
        // 3. 左相交
        if(t->second <= l) {// [ll,rr] + [l,r] -> [ll,r]
            l = t->second;
            if(mst_flag) remove_seq(t->first - t->second + 1);
            if(t->first == seqs.rbegin()->first) {
                seqs.erase(t);
                seqs[r] = l;
                if(mst_flag) add_seq(r - l + 1);
                return ;
            } 
            seqs.erase(t ++);
        } 
        // 4. [ll,rr] 被包含 迭代删除
        while(t->second >= l && t->first <= r) {// [ll,rr] X
            if(mst_flag) remove_seq(t->first - t->second + 1);
            if(t->first == seqs.rbegin()->first) {
                if(mst_flag) add_seq(r - l + 1);
                seqs.erase(t);
                seqs[r] = l;
                return ;
            } 
            seqs.erase(t ++);
        }
        // 5. 右相交
        if(t->second <= r) {// [l,r] + [ll,rr] -> [l,rr]
            r = t->first;
            if(mst_flag) remove_seq(t->first - t->second + 1);
            seqs.erase(t);
        } 

        // 最后判断前后相交的情况
        if(seqs.count(l - 1)) {
            int lt = l - 1;
            l = seqs[l - 1];
            if(mst_flag) remove_seq(lt - l + 1);
            seqs.erase(lt);
        }

        if(!seqs.empty() && seqs.rbegin()->first > r) {
            auto t = seqs.lower_bound(r + 1);
            if(t->second == r + 1) {
                if(mst_flag) remove_seq(t->first - r);
                r = t->first;
                seqs.erase(t->first);
            }
        }

        seqs[r] = l;
        if(mst_flag) add_seq(r - l + 1);
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
