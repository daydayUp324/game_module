#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayUppp
 * 
 * 区间翻转的线段树 (维护的区间性质为 sum)
 * 
 * (l, r) : 将 [l:r] 区间翻转（nums[i] ^= 1, l <= i <= r）
 * query(l, r) : 求 [l:r] 区间和
 * 
 * 若一个区间为 (l, r) 节点序号为 id
 * 那么该区间的左子树为 id * 2，右子树 id * 2 + 1
 * 
 * 注意初始化时 : 需要把原始的区间参数传入 (seq_l, seq_r) 或者传入原始数组 nums[] 来初始化 arr[]
 */
template<typename MT>
class ST_01 {
public:
    int seq_l, seq_r; // 初始区间的左右边界
    MT* arr; // 原数组下标从 1 开始
    MT* tree; // 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1 节点 表示区间 [1, n]
    bool* lazy; // "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n; // 数组的长度
    void build_tree(int l, int r, int node_id) { // 构建整个线段树
        lazy[node_id] = false;
        if (l == r) {
            tree[node_id] = arr[l];
            return ;
        }
        int mid = (l + r) / 2;
        build_tree(l, mid, node_id * 2);
        build_tree(mid + 1, r, node_id * 2 + 1);
        tree[node_id] = tree[node_id * 2] + tree[node_id * 2 + 1]; // 区间和
    }
    void update_node(int node_len, int node_id) { // 对 node_id 进行翻转
        tree[node_id] = node_len - tree[node_id];
    }
    void push_down(int l, int r, int node_id) { // 节点 node_id 的懒标记下传（其中包括对其子节点信息的更新）
        int mid = (l + r) / 2, lson = node_id * 2, rson = node_id * 2 + 1;
        lazy[lson] ^= 1, lazy[rson] ^= 1;
        // update tree[lson] 和 tree[rson]
        // 始终保持若修改了则对应的 tree[] 值对应修改
        update_node(mid - l + 1, lson);
        update_node(r - mid, rson);
        // reset lazy[node_id]
        lazy[node_id] = 0;
    }
    void push_up(int l, int r, int node_id) { // 节点 node_id 的子节点信息上传
        int lson = node_id * 2, rson = node_id * 2 + 1;
        tree[node_id] = tree[lson] + tree[rson];
    }
    void update(int l, int r) { // 翻转区间 (l, r)
        help_update(l, r, seq_l, seq_r, 1);
    }
    MT query(int l, int r) { // 查询区间 (l, r) 的区间和
        if (r < l) return 0; // 区间不合法
        return help_query(l, r, seq_l, seq_r, 1);
    }
    void help_update(const int tl, const int tr, int cl, int cr, int node_id) {
        // (tl, tr) 为目标翻转区间 (cl, cr) 为当前区间 node_id 为当前区间序号
        if (cr < tl || cl > tr) return ; // 与 (tl, tr) 没有交集
        if (cl >= tl && cr <= tr) { // 当前区间被包含
            update_node(cr - cl + 1, node_id); // 进行翻转
            lazy[node_id] ^= 1; // 更新懒标记
            return ;
        }
        // 否则往下
        if (lazy[node_id]) { // 若存在懒标记
            push_down(cl, cr, node_id);
        }
        int mid = (cl + cr) / 2, lson = node_id * 2, rson = node_id * 2 + 1;
        help_update(tl, tr, cl, mid, lson);
        help_update(tl, tr, mid + 1, cr, rson);
        push_up(cl, cr, node_id);
    }
    MT help_query(const int tl, const int tr, int cl, int cr, int node_id) {
        // (tl, tr) 为目标查询区间 (cl, cr) 为当前区间 node_id 为当前区间序号
        if (cr < tl || cl > tr) return 0; // 与 (tl, tr) 没有交集
        if (cl >= tl && cr <= tr) { // 当前区间被包含
            return tree[node_id];
        }
        // 否则往下
        if (lazy[node_id]) { // 若存在懒标记
            push_down(cl, cr, node_id);
        }
        int mid = (cl + cr) / 2, lson = node_id * 2, rson = node_id * 2 + 1;
        return help_query(tl, tr, cl, mid, lson) + help_query(tl, tr, mid + 1, cr, rson);
    }
    ST_01(int l_ = 0, int r_ = 0) : seq_l(l_), seq_r(r_), n(r_ - l_ + 1) {
        // arr[i] 默认为 0
        arr = new MT[n + 1];
        for (int i = 0; i <= n; ++i) {
            arr[i] = 0;
        }
        tree = new MT[4 * n + 1];
        lazy = new bool[4 * n + 1];
        build_tree(0, n - 1, 1); // 初始化线段树
    }
    ST_01(const vector<int>& nums) {
        n = nums.size();
        seq_l = 0, seq_r = n - 1;
        arr = new MT[n + 1];
        tree = new MT[4 * n + 1];
        lazy = new bool[4 * n + 1];
        // 用 nums 来初始化 arr[i]
        for (int i = 0; i < nums.size(); ++i) {
            arr[i] = nums[i];
        }
        build_tree(0, n - 1, 1); // 初始化线段树
    }
    ~ST_01() {
        delete []arr; delete []tree; delete []lazy;
    }
};