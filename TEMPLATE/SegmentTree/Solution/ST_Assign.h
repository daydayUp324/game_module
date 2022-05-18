#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class ST
{
    /**
     * @author : daydayUppp
     * 维护区间更新 区间更新 lazy[p] = 0 说明该点不需要更新
     * 
     * (l,r,v) : 将 : [l:r] 区间都更新为 v
     * query(l,r) : 求 [l:r] 区间的和
     */
public:
    LL* tree;// 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1节点 表示区间 [1,n]
    LL* lazy;// "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n;// 数组的长度
    void build(int l,int r,int p) {
        // 构建线段树 以 维护区间和 为例进行说明
        lazy[p] = 0;// FLAG
        tree[p] = 1;
        if(l == r) {
            return ;
        }
        int mid = (l + r) / 2;
        build(l,mid,p * 2);
        build(mid + 1,r,p * 2 + 1);
    }
    void push_down(int p,int l,int r) {// FLAG
        int mid = (l + r) / 2;
        // update lazy[]
        lazy[p * 2] = lazy[p];
        lazy[p * 2 + 1] = lazy[p];
        // update tree[]
        tree[p * 2] = lazy[p];
        tree[p * 2 + 1] = lazy[p];
        // reset lazy[p]
        lazy[p] = 0;
    }
    void update(int l,int r,int d) {// FLAG
        return help_update(l,r,1,1,n,d);
    }
    void help_update(int l,int r,int p,int cl,int cr,int d) {
        // update Seg : [l : r] , cur_Seg : (p) [cl : cr]
        // d : update info
        if(l > cr || r < cl) return ;// 1. [l : r] 与 [cl : cr] 无交集
        if(l <= cl && r >= cr) {// 2. [cl : cr] 是 [l : r] 的子集
            tree[p] = d;// FLAG
            if(cl < cr) lazy[p] = d;// FLAG
            return ;
        }
        if(lazy[p]) push_down(p,cl,cr);// 3. [l : r] 与 [cl : cr] 有交集
        int mid = (cl + cr) / 2;
        help_update(l,r,p * 2,cl,mid,d) , help_update(l,r,p * 2 + 1,mid + 1,cr,d);
    }
    LL query(int l,int r) {// 查询 [l:r] 区间的性质
        return help_query(l,r,1,1,n);
    }
    LL help_query(int l,int r,int p,int cl,int cr) {// FLAG
        // 求 [l : r] 区间的和
        if(cr < l || cl > r) return 0;// 原则 : 不会该改变 [l : r] 的性质
        if(cl >= l && cr <= r) return tree[p];
        if(lazy[p]) push_down(p,cl,cr);// lazy 标记下传
        int mid = (cl + cr) / 2;
        return help_query(l,r,p * 2,cl,mid) + help_query(l,r,p * 2 + 1,mid + 1,cr);
    }
    ST(int n) {
        this->n = n;
        tree = new LL[4 * n + 1];
        lazy = new LL[4 * n + 1];
    }
    ~ST() {
        delete []tree; delete []lazy;
    }
};