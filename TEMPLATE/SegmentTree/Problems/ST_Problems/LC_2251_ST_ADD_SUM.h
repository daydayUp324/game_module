/*
题目链接：https://leetcode.cn/problems/number-of-flowers-in-full-bloom/
*/
#include <bits/stdc++.h>
using namespace std;
/**
 * @author : daydayUppp
 * 
 * 区间加的线段树 (维护的区间性质为 sum)
 * 
 * (l, r, v) : 将 [l:r] 区间加上 v（nums[i] += v, l <= i <= r）
 * query(l, r) : 求 [l:r] 区间和
 * 
 * 若一个区间为 (l, r) 节点序号为 id
 * 那么该区间的左子树为 id * 2，右子树 id * 2 + 1
 * 
 * 注意初始化时 : 需要把原始的区间参数传入 (seq_l, seq_r) 或者传入原始数组 nums[] 来初始化 arr[]
 */
template<typename MT>
class ST_ADD {
public:
    int seq_l, seq_r; // 初始区间的左右边界
    MT* arr; // 原数组下标从 1 开始
    MT* tree; // 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1 节点 表示区间 [1, n]
    MT* lazy; // "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n; // 数组的长度
    void build_tree(int l, int r, int node_id) { // 构建整个线段树
        lazy[node_id] = 0;
        if (l == r) {
            tree[node_id] = arr[l];
            return ;
        }
        int mid = (l + r) / 2;
        build_tree(l, mid, node_id * 2);
        build_tree(mid + 1, r, node_id * 2 + 1);
        tree[node_id] = tree[node_id * 2] + tree[node_id * 2 + 1]; // 区间和
    }
    void update_node(int node_len, int node_id, int v) { // 对 node_id 全部加上 v
        tree[node_id] += (MT) node_len * v;
    }
    void push_down(int l, int r, int node_id) { // 节点 node_id 的懒标记下传（其中包括对其子节点信息的更新）
        int mid = (l + r) / 2, lson = node_id * 2, rson = node_id * 2 + 1;
        int v = lazy[node_id];
        lazy[lson] += v, lazy[rson] += v;
        // update tree[lson] 和 tree[rson]
        // 始终保持若修改了则对应的 tree[] 值对应修改
        update_node(mid - l + 1, lson, v);
        update_node(r - mid, rson, v);
        // reset lazy[node_id]
        lazy[node_id] = 0;
    }
    void push_up(int l, int r, int node_id) { // 节点 node_id 的子节点信息上传
        int lson = node_id * 2, rson = node_id * 2 + 1;
        tree[node_id] = tree[lson] + tree[rson];
    }
    void update(int l, int r, int v = 1) { // 区间 (l, r) 全部加上 v 默认 + 1
        help_update(l, r, seq_l, seq_r, 1, v);
    }
    MT query(int l, int r) { // 查询区间 (l, r) 的区间和
        return help_query(l, r, seq_l, seq_r, 1);
    }
    void help_update(const int tl, const int tr, int cl, int cr, int node_id, int v) {
        // (tl, tr) 为目标区间 (cl, cr) 为当前区间 node_id 为当前区间序号
        if (cr < tl || cl > tr) return ; // 与 (tl, tr) 没有交集
        if (cl >= tl && cr <= tr) { // 当前区间被包含
            update_node(cr - cl + 1, node_id, v); // 进行翻转
            lazy[node_id] += v; // 更新懒标记
            return ;
        }
        // 否则往下
        if (lazy[node_id]) { // 若存在懒标记
            push_down(cl, cr, node_id);
        }
        int mid = (cl + cr) / 2, lson = node_id * 2, rson = node_id * 2 + 1;
        help_update(tl, tr, cl, mid, lson, v);
        help_update(tl, tr, mid + 1, cr, rson, v);
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
    ST_ADD(int l_ = 0, int r_ = 0) : seq_l(l_), seq_r(r_), n(r_ - l_ + 1) {
        // arr[i] 默认为 0
        arr = new MT[n + 1];
        for (int i = 0; i <= n; ++i) {
            arr[i] = 0;
        }
        tree = new MT[4 * n + 1];
        lazy = new MT[4 * n + 1];
        build_tree(0, n - 1, 1); // 初始化线段树
    }
    ST_ADD(const vector<int>& nums) {
        n = nums.size();
        seq_l = 0, seq_r = n - 1;
        arr = new MT[n + 1];
        tree = new MT[4 * n + 1];
        lazy = new MT[4 * n + 1];
        // 用 nums 来初始化 arr[i]
        for (int i = 0; i < nums.size(); ++i) {
            arr[i] = nums[i];
        }
        build_tree(0, n - 1, 1); // 初始化线段树
    }
    ~ST_ADD() {
        delete []arr; delete []tree; delete []lazy;
    }
};
class Solution {
public:
    // 排序 + 去重
    // 注意 : 该数组会改变。 如果要求原数组不变的情况 需要先把原数组 copy 到一个辅助数组中
    vector<int> mp_nums;
    // 排序 + 去重
    // 注意 : 该数组会改变。 如果要求原数组不变的情况 需要先把原数组 copy 到一个辅助数组中
    void orderly() {
        sort(mp_nums.begin(), mp_nums.end());
        mp_nums.erase(unique(mp_nums.begin(), mp_nums.end()), mp_nums.end());
    }
    // 二分查找序号
    // 注意 : 前提需要确保该数在数组中
    int getId(int target) {
        return lower_bound(mp_nums.begin(), mp_nums.end(), target) - mp_nums.begin();
    }
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        for (auto& x : flowers) {
            mp_nums.push_back(x[0]);
            mp_nums.push_back(x[1]);
        }
        for (auto& p : people) {
            mp_nums.push_back(p);
        }
        orderly();
        ST_ADD<long long> h(0, mp_nums.size());
        for (auto& x : flowers) {
            h.update(getId(x[0]), getId(x[1]));
        }
        vector<int> res;
        for (auto& p : people) {
            int t = getId(p);
            res.push_back(h.query(t, t));
        }
        return res;
    }
};