/**
 * 题目链接 : [10011. 以组为单位订音乐会的门票](https://leetcode.cn/problems/booking-concert-tickets-in-groups/)
 * 解题思路 :
 *
 * 用 线段树 和 树状数组 来进行维护区间的信息
 *
 * 线段树来维护 : [l,r] 的最大空座位
 * 树状数组来维护 : [l:r] 的空座位总数
 *
 * 然后用 map<int,int> 来维护每一排座位的空位置
 *
 * 然后对于 gather(int k,int maxRow) 来说 :
 *
 * 用二分来找到比 maxRow 小的最小的座位排即可
 *
 * */

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class ST
{
    /**
     * @author : daydayUppp
     * 
     * (l,r,v) : 将 : [l:r] 区间都加上 v
     * query(l,r) : 求 [l:r] 区间的和
     */
public:
    LL* arr;// 原数组下标从 1 开始
    LL* tree;// 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1节点 表示区间 [1,n]
    LL* lazy;// "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n;// 数组的长度
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
        return help_update(l,r,1,0,n-1,d);
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
        return help_query(l,r,1,0,n-1);
    }
    LL help_query(int l,int r,int p,int cl,int cr) {// FLAG
        // 求 [l : r] 区间的和
        if(cr < l || cl > r) return 0;// 原则 : 不会该改变 [l : r] 的性质
        if(cl >= l && cr <= r) return tree[p];
        if(lazy[p]) push_down(p,cl,cr);// lazy 标记下传
        int mid = (cl + cr) / 2;
        return max(help_query(l,r,p * 2,cl,mid) , help_query(l,r,p * 2 + 1,mid + 1,cr));
    }
    ST(int n) {
        this->n = n;
        arr = new LL[n + 1];
        tree = new LL[4 * n + 1];
        lazy = new LL[4 * n + 1];
    }
    ~ST() {
        delete []arr; delete []tree; delete []lazy;
    }
};

template<typename T>
class BIT
{
    /**
     * @author : daydayUppp
     * 适用范围 :
     * 1. arr[] 从下标 0 开始 则 : tree[index + 1] 负责 arr[index]
     * 2. 单点更新 每次 + 1
     * 3. 区间 [0:p] 查询 -> query(p)
     * 4. 区间 [0:r] 查询 -> query(r) - query(l - 1) 对于 l == 0 特判
     */
public:
    int n;
    T* tree;
    BIT(int sz) {
        this->n = sz + 1;
        tree = new T[n];
        for(int i = 1;i < n;i ++) tree[i] = 0;
    };
    int lowbit(int x) { return x & (-x); }
    void update(int index,T d) {
        // 更新 arr[index] -> 负责的节点为 tree[index + 1]
        index ++;
        while(index < n) {
            tree[index] += d;
            index += lowbit(index);
        }
    }
    T query(int index) {
        // 查询区间 [0:index] 的和 则 index 的负责区间仍然是 index + 1
        T res = 0;
        index ++;
        while(index) {
            res += tree[index];
            index -= lowbit(index);
        }
        return res;
    }
    ~BIT() {
        delete []tree;
    }
};


class BookMyShow {
public:
    BIT<long long>* bt;
    ST* st;
    int n,m;
    map<int,int> mp;// 每一行的空闲位置个数
    BookMyShow(int n_, int m_) {
        n = n_;
        m = m_;
        bt = new BIT<long long>(n);
        st = new ST(n);
        for(int i = 0;i < n;i ++) {
           bt->update(i,m);// 每一行的空闲的位置数 
           st->arr[i] = m;// 每一行的空闲的位置数 (维护区间的最大值)
           mp[i] = m;
        } 
        st->build(0,n-1,1);// 创建线段树 , root = 1
    }
    
    vector<int> gather(int k, int maxRow) {
        // 二分找到最左的一个区间 [l:l] 使得 mp[l] >= k
        auto t = st->query(0,maxRow);
        if(t < k) return {};
        // 说明肯定是可以的
        int l = 0;
        int r = maxRow;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(st->query(l,mid) >= k) r = mid - 1;
            else l = mid + 1;
        }
        // 最后是 r + 1 为目标座位
        r ++;
        int be = m - mp[r];
        mp[r] -= k;
        st->update(r,r,-k);
        bt->update(r,-k);
        return {r,be};
    }
    
    bool scatter(int k, int maxRow) {
        auto t = bt->query(maxRow);
        if(t < k) return false;
        // 否则进行放置
        while(k) {
            auto it = mp.begin();// {line , number}
            int line = it->first;
            int num = it->second;
            if(num <= k) {
                k -= num;
                // 更新两个树
                st->update(line,line,-num);
                bt->update(line,-num);
                mp.erase(it);
            } else {
                it->second = num - k;
                st->update(line,line,-k);
                bt->update(line,-k);
                k = 0;
            }
        }
        return true;
    }
};

/**
 * Your BookMyShow object will be instantiated and called as such:
 * BookMyShow* obj = new BookMyShow(n, m);
 * vector<int> param_1 = obj->gather(k,maxRow);
 * bool param_2 = obj->scatter(k,maxRow);
 */
