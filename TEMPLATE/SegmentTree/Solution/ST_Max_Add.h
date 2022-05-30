#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class ST
{
    /**
     * @author : daydayUppp
     * 
     * 单点修改的线段树  (维护的区间性质为 max)
     * 
     * (l,r,v) : 将 : [l:r] 区间都加上 v
     * query(l,r) : 求 [l:r] 区间的最大值
     * 
     * 注意初始化时 : 需要把原始的区间参数传入 (seq_l,seq_r)
     */
public:
    LL* arr;// 原数组下标从 1 开始
    LL* tree;// 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1节点 表示区间 [1,n]
    LL* lazy;// "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n;// 数组的长度
    int seq_l,seq_r;// 初始区间
    void build(int l,int r,int p) {
        // 构建线段树 以 维护区间和 为例进行说明
        lazy[p] = 0;// FLAG
        if(l == r) {
            tree[p] = arr[l];// FLAG
            return ;
        }
        int mid = (l + r) / 2;
        build(l,mid,p * 2);
        build(mid + 1,r,p * 2 + 1);
        tree[p] = max(tree[p * 2] , tree[p * 2 + 1]);// FLAG
    }
    void push_down(int p,int l,int r) {// FLAG
        int mid = (l + r) / 2;
        // update lazy[]
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        // update tree[]
        tree[p * 2] += lazy[p];
        tree[p * 2 + 1] += lazy[p];
        // reset lazy[p]
        lazy[p] = 0;
    }
    void update(int l,int r,int d) {// FLAG
        return help_update(l,r,1,seq_l,seq_r,d);
    }
    void help_update(int l,int r,int p,int cl,int cr,LL d) {
        // update Seg : [l : r] , cur_Seg : (p) [cl : cr]
        // d : update info
        if(l > cr || r < cl) return ;// 1. [l : r] 与 [cl : cr] 无交集
        if(l <= cl && r >= cr) {// 2. [cl : cr] 是 [l : r] 的子集
            tree[p] += d;// FLAG
            if(cl < cr) lazy[p] += d;// FLAG
            else arr[l] = tree[p];
            return ;
        }
        if(lazy[p]) push_down(p,cl,cr);// 3. [l : r] 与 [cl : cr] 有交集
        int mid = (cl + cr) / 2;
        help_update(l,r,p * 2,cl,mid,d) , help_update(l,r,p * 2 + 1,mid + 1,cr,d);
        tree[p] = max(tree[p * 2] , tree[p * 2 + 1]);// FLAG
    }
    LL query(int l,int r) {// 查询 [l:r] 区间的性质
        return help_query(l,r,1,seq_l,seq_r);
    }
    LL help_query(int l,int r,int p,int cl,int cr) {// FLAG
        // 求 [l : r] 区间的和
        if(cr < l || cl > r) return 0;// 原则 : 不会该改变 [l : r] 的性质
        if(cl >= l && cr <= r) return tree[p];
        if(lazy[p]) push_down(p,cl,cr);// lazy 标记下传
        int mid = (cl + cr) / 2;
        return max(help_query(l,r,p * 2,cl,mid) , help_query(l,r,p * 2 + 1,mid + 1,cr));
    }
    ST(int l,int r) {
        this->n = r - l + 1;// 区间的个数
        this->seq_l = l;
        this->seq_r = r;
        arr = new LL[n + 1];
        tree = new LL[4 * n + 1];
        lazy = new LL[4 * n + 1];
    }
    ~ST() {
        delete []arr; delete []tree; delete []lazy;
    }
};
