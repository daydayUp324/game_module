#include <bits/stdc++.h>
using namespace std;
using LL = long long;
/**
 * author : daydayUppp
 *
 * 动态开点线段树（维护性质为区间 min/max）
 * 
 * 功能 :
 * 1. 区间更新 (Add) : [l,r,v] , 区间 val([l:r]) += v
 * 2. 区间查询 : [l,r] , 区间 [l:r] 的某种性质
 * 3. 用 int root = build_subTree() 来进行线段树的初始化
 *
 * */
#define INF INT_MIN 
// 标记最值（如果维护的是最小值 INF = INT_MAX，否则 INF = INT_MIN）
#define OP max 
// 设置操作
const static int SZ = (int) 7e6;
using SMT = int; // 注意需要与 MT 对应
// 分配的节点空间
struct Node {
    int l, r; // 表示 [l:r] 区间
    bool lazy; // 懒标记
    SMT val; // 当前区间的懒标记对应的值
    SMT tree; // 当前区间某一种性质
    int lson, rson; // 左右子树的序号 0 表示空
} tn[SZ]; // tree node
template<typename MT>
class DST_ADD_M {
public:
    int root_id; // 根节点ID
    int ori_l, ori_r; // [] 原始区间
    int cur_idx; // 每次从 cur_idx 开始分配子树序号

    bool is_intersect(const int cl, const int cr, const int& tl, const int&  tr) { 
        // 判断 [cl,cr] 与 [tl,tr] 是否有重合
        if (cl > tr || cr < tl) return false;
        return true;
    }

    int build_subTree(int l_, int r_, bool lazy_ = false, MT val_ = 0) { // 分配一个子树
        tn[cur_idx].l = l_, tn[cur_idx].r = r_;
        tn[cur_idx].lson = 0, tn[cur_idx].rson = 0;
        tn[cur_idx].lazy = lazy_;
        tn[cur_idx].val = val_;
        tn[cur_idx].tree = val_;
        return cur_idx ++;
    }

    void push_down(Node& root) { // 从当前节点往下传递信息
        root.lazy = false;
        if (!root.lson) {
            root.lson = build_subTree(root.l, (root.l + root.r) / 2, true, root.val);
        } else {
            tn[root.lson].val += root.val;
            tn[root.lson].tree += root.val;
            tn[root.lson].lazy = true;
        }
        if (!root.rson) {
            root.rson = build_subTree((root.l + root.r) / 2 + 1, root.r, true, root.val);
        } else {
            tn[root.rson].val += root.val;
            tn[root.rson].tree += root.val;
            tn[root.rson].lazy = true;
        }
        root.val = 0;
    }

    void push_up(Node& root) { // 两棵子树往上传递信息
        if (root.lson) root.tree = OP(root.tree, tn[root.lson].tree);
        if (root.rson) root.tree = OP(root.tree, tn[root.rson].tree);
    }

    void update(int l, int r, int v = 1) { // 对区间 [l, r] 中的数全部加上 v（默认为 1）
        dst_update(root_id, l, r, v);
    }

    MT query(int l, int r) { // 查询区间 [l, r]
        return dst_query(root_id, l, r);
    }

    void dst_update(int root, const int tl, const int tr, const int v) { // 更新区间 [tl,tr] -> +v
        Node& temp = tn[root];
        if (temp.l > tr || temp.r < tl) return ;// 无交集
        if (temp.l >= tl && temp.r <= tr) { // 被包含
            temp.val += v;
            temp.tree += v;
            if(temp.r > temp.l) temp.lazy = true;
            return ;
        }
        int mid = (temp.l + temp.r) / 2;
        if (temp.lazy) {
            push_down(temp);
        } else {
            if (!temp.lson && is_intersect(temp.l, mid, tl, tr)) {
                temp.lson = build_subTree(temp.l, mid, true, temp.val);
            }
            if (!temp.rson && is_intersect(mid + 1, temp.r, tl, tr)) {
                temp.rson = build_subTree(mid + 1, temp.r, true, temp.val);
            }
        }
        if (temp.lson) dst_update(temp.lson, tl, tr, v);
        if (temp.rson) dst_update(temp.rson, tl, tr, v);
        push_up(temp);
    }

    MT dst_query(int root, const int tl, const int tr) { // 查询 [tl,tr] 区间性质
        Node& temp = tn[root];
        if (temp.l > tr || temp.r < tl) return 0;// 无交集
        if (temp.l >= tl && temp.r <= tr) { // 被包含
            return temp.tree;
        }
        if (temp.lazy) push_down(temp);
        MT res = INF;
        if (temp.lson) res = OP(res, dst_query(temp.lson, tl, tr));
        if (temp.rson) res = OP(res, dst_query(temp.rson, tl, tr));
        return res;
    }

    DST_ADD_M(int l_, int r_) : ori_l(l_), ori_r(r_), cur_idx(1) {
        root_id = this->build_subTree(l_, r_); // 创建初始节点
    }

    ~DST_ADD_M() {
    }
};
class MyCalendarThree {
public:
    DST_ADD_M<int>* h;
    MyCalendarThree() {
        h = new DST_ADD_M<int>(0, 1e9 + 7);
    }
    
    int book(int startTime, int endTime) {
        h->update(startTime, endTime - 1);
        return h->query(0, 1e9 + 7);
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */