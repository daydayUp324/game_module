#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class DST{ // Dynamic open point seqment tree
    /**
     * author : daydayUppp
     *
     * 动态开点线段树 (数组版)
     * 
     * 功能 :
     * 1. 区间更新 : [l,r,v] , 区间 val([l:r]) = v
     * 2. 区间查询 : [l,r] , 区间 [l:r] 的 "和" ("最大最小" 等需要自己修改)
     *
     * */
public:
    DST* lson;
    DST* rson;
    int l,r;
    bool lazy;// 懒标记
    LL val;// 当前区间的共性
    LL sum;// 当前的区间和
    void push_down() { // 从当前节点往下传递信息
        lazy = false;
        if(!lson) lson = new DST(l,(l + r) / 2,val,true);
        else {
            lson->val = val;
            lson->lazy = true;
            lson->sum = (LL) ((l + r) / 2 - l + 1) * val;
        }

        if(!rson) rson = new DST((l + r) / 2 + 1,r,val,true);
        else {
            rson->val = val;
            rson->lazy = true;
            rson->sum = (LL) (r - (l + r) / 2) * val;
        }
    }
    void push_up() { // 两个子节点往上上传信息
        sum = 0;
        if(lson) sum += lson->sum;
        else sum += (LL) ((l + r) / 2 - l + 1) * val;
        if(rson) sum += rson->sum;
        else sum += (LL) (r - (l + r) / 2) * val;
    }
    bool is_intersect(const int cl,const int cr,const int& tl,const int&  tr) { // 判断 [cl,cr] 与 [tl,tr] 是否有重合
        if(cl > tr || cr < tl) return false;
        return true;
    }
    void dst_update(const int tl,const int tr,const int v) { // 需要更新的区间为 [tl,tr] 更新值为 v
        if(l > tr || r < tl) return ;// 无交集的情况
        if(l >= tl && r <= tr) { // 当前节点的区间被包含 更新区间
            val = v;
            sum = (LL) v * (r - l + 1);
            if(l < r) lazy = true;
            return ;
        }
        int mid = (l + r) / 2;
        /*
        创建时 : 有交集才进行创建 , 和有 lazy 标记下传时创建 lson,rson
        */
        if(lazy) {
            push_down();
        } else {
            if(!lson && is_intersect(l,mid,tl,tr)) { // [l,mid] : lson
                lson = new DST(l,mid,val,true);
            } 
            if(!rson && is_intersect(mid + 1,r,tl,tr)) { // [mid + 1,r] : rson
                rson = new DST(mid + 1,r,val,true);
            } 
        }
        if(lson) lson->dst_update(tl,tr,v);
        if(rson) rson->dst_update(tl,tr,v);
        push_up();
    }
    LL dst_query(const int tl,const int tr) { // 查询 [tl:tr] 区间的某一个性质 (以 求和 为例)
        if(l > tr || r < tl) return 0;// 无交集
        if(l >= tl && r <= tr) return sum;
        if(lazy) push_down();// 懒标记下传
        LL res = 0;
        int mid = (l + r) / 2;
        // [l:mid] : lson
        if(lson) {
            res += lson->dst_query(tl,tr);
        }
        // [mid+1:r] : rson
        if(rson) {
            res += rson->dst_query(tl,tr);
        } 
        return res;
    }
    DST(int l_,int r_,LL val_ = 0,bool lazy_ = false) {
        lson = nullptr , rson = nullptr;
        lazy = lazy_;
        l = l_ , r = r_ , val = val_;
        sum = val * (r - l + 1);
    }
};