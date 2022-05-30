#include <bits/stdc++.h>
using namespace std;
using LL = long long;
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
const int SZ = 7e6;
struct Node {
    int l,r;// 表示 [l:r] 区间
    bool lazy;// 懒标记
    LL val;// 当前区间共性
    LL sum;// 当前区间和
    int lson,rson;// 左右子树 0 表示空
} tn[SZ];// tree node

int cur_idx = 1;// 每次从 cur_idx 开始分配子树序号

int bulid_subTree(int l_,int r_,bool lazy_ = false,LL val_ = 0) { // 分配一个子树
    tn[cur_idx].l = l_ , tn[cur_idx].r = r_;
    tn[cur_idx].lson = 0 , tn[cur_idx].rson = 0;
    tn[cur_idx].lazy = lazy_;
    tn[cur_idx].val = val_;
    tn[cur_idx].sum = (r_ - l_ + 1) * val_;
    return cur_idx ++;
}

bool is_intersect(const int cl,const int cr,const int& tl,const int&  tr) { // 判断 [cl,cr] 与 [tl,tr] 是否有重合
    if(cl > tr || cr < tl) return false;
    return true;
}

void push_down(Node& root) { // 从当前节点往下传递信息
    root.lazy = false;
    if(!root.lson) {
        root.lson = bulid_subTree(root.l,(root.l + root.r) / 2,true,root.val);
    } else {
        tn[root.lson].val = root.val;
        tn[root.lson].sum = (LL) root.val * ((root.l + root.r) / 2 - root.l + 1);
        tn[root.lson].lazy = true;
    }
    if(!root.rson) {
        root.rson = bulid_subTree((root.l + root.r) / 2 + 1,root.r,true,root.val);
    } else {
        tn[root.rson].val = root.val;
        tn[root.rson].sum = (LL) root.val * (root.r - (root.l + root.r) / 2);
        tn[root.rson].lazy = true;
    }
}

void push_up(Node& root) { // 两棵子树往上传递信息
    root.sum = 0;
    if(root.lson) root.sum += tn[root.lson].sum;
    else root.sum += (LL) ((root.l + root.r) / 2 - root.l + 1) * root.val;
    if(root.rson) root.sum += tn[root.rson].sum;
    else root.sum += (LL) (root.r - (root.l + root.r) / 2) * root.val;
}

void dst_update(int root,const int tl,const int tr,const int v) { // 更新区间 [tl,tr] -> v
    Node& temp = tn[root];
    if(temp.l > tr || temp.r < tl) return ;// 无交集
    if(temp.l >= tl && temp.r <= tr) { // 被包含
        temp.val = v;
        temp.sum = (LL) (temp.r - temp.l + 1) * v;
        if(temp.r > temp.l) temp.lazy = true;
        return ;
    }
    int mid = (temp.l + temp.r) / 2;
    if(temp.lazy) {
        push_down(temp);
    } else {
        if(!temp.lson && is_intersect(temp.l,mid,tl,tr)) {
            temp.lson = bulid_subTree(temp.l,mid,true,temp.val);
        }
        if(!temp.rson && is_intersect(mid + 1,temp.r,tl,tr)) {
            temp.rson = bulid_subTree(mid + 1,temp.r,true,temp.val);
        }
    }
    if(temp.lson) dst_update(temp.lson,tl,tr,v);
    if(temp.rson) dst_update(temp.rson,tl,tr,v);
    push_up(temp);
}

LL dst_query(int root,const int tl,const int tr) { // 查询 [tl,tr] 区间和
    Node& temp = tn[root];
    if(temp.l > tr || temp.r < tl) return 0;// 无交集
    if(temp.l >= tl && temp.r <= tr) { // 被包含
        return temp.sum;
    }
    if(temp.lazy) push_down(temp);
    LL res = 0;
    if(temp.lson) res += dst_query(temp.lson,tl,tr);
    if(temp.rson) res += dst_query(temp.rson,tl,tr);
    return res;
}