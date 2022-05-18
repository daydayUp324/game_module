# 

## 动态开点线段树应用

### [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)

![qqATMT.png](https://s1.ax1x.com/2022/04/04/qqATMT.png)](<https://imgtu.com/i/qqATMT>)

#### CODE_1

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = int;
class ST
{
    /**
     * @author : daydayUppp
     * 以 维护区间和 为例
     * 维护其他性质时 , 修改有关 tree[] 和 lazy[] 的对应操作即可
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
        tree[p] = tree[p * 2] + tree[p * 2 + 1];// FLAG
    }
    void push_down(int p,int l,int r) {// FLAG
        int mid = (l + r) / 2;
        // update lazy[]
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        // update tree[]
        tree[p * 2] += lazy[p] * (mid - l + 1);
        tree[p * 2 + 1] += lazy[p] * (r - mid);
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
            tree[p] += (LL) d * (cr - cl + 1);// FLAG
            if(cl < cr) lazy[p] += d;// FLAG
            else arr[l] = tree[p];
            return ;
        }
        if(lazy[p]) push_down(p,cl,cr);// 3. [l : r] 与 [cl : cr] 有交集
        int mid = (cl + cr) / 2;
        help_update(l,r,p * 2,cl,mid,d) , help_update(l,r,p * 2 + 1,mid + 1,cr,d);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];// FLAG
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
        arr = new LL[n + 1];
        tree = new LL[4 * n + 1];
        lazy = new LL[4 * n + 1];
    }
    ~ST() {
        delete arr; delete tree; delete lazy;
    }
};
class NumArray {
public:
    ST* h;
    NumArray(vector<int>& nums) {
        h = new ST(nums.size());
        for(int i = 1;i <= nums.size();i ++) {
            h->arr[i] = nums[i - 1];
        }
        h->build(1,nums.size(),1);
    }
    
    void update(int index, int val) {
        index ++;
        h->update(index,index,val - h->arr[index]);
    }
    
    int sumRange(int left, int right) {
        return h->query(left + 1,right + 1);
    }
};
```

### [699. 掉落的方块](https://leetcode-cn.com/problems/falling-squares/)

![image.png](https://i.bmp.ovh/imgs/2022/04/04/fb76b0fba6bb9215.png)

[![qqElwQ.png](https://s1.ax1x.com/2022/04/04/qqElwQ.png)](https://imgtu.com/i/qqElwQ)

#### 解题思路_2

1. 如果数据范围较小的话 , 那么直接用 **线段树** 来维护每一个 $[l,r]$ 的区间的高度 即可

2. 但是现在数据范围比较大 , 我们可以知道一个区间的最大值我们可以只记录两个端点来表示区间 , 而不考虑中间的元素。那么可以想到用 **离散化** 来处理

#### CODE_2

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
class ST
{
    /**
     * @author : daydayUppp
     * 以 维护区间和 为例
     * 维护其他性质时 , 修改有关 tree[] 和 lazy[] 的对应操作即可
     */
public:
    LL* arr;// 原数组下标从 1 开始
    LL* tree;// 线段树 tree[i] 维护 i 节点的所负责区间的某一个性质
    // 其中 1节点 表示区间 [1,n]
    LL* lazy;// "懒"标记数组 只有某一个某一个节点的性质要改变时才需要 "懒" 标记下传
    int n;// 数组的长度
    void build(int l,int r,int p) {
        // 构建线段树 以 维护区间和 为例进行说明
        lazy[p] = tree[p] = 0;// FLAG
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
        tree[p] = max(tree[p * 2] , tree[p * 2 + 1]);// FLAG
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
        return max(help_query(l,r,p * 2,cl,mid) , help_query(l,r,p * 2 + 1,mid + 1,cr));
    }
    ST(int n) {
        this->n = n;
        arr = new LL[2];
        tree = new LL[4 * n + 1];
        lazy = new LL[4 * n + 1];
    }
    ~ST() {
        delete []arr; delete []tree; delete []lazy;
    }
};
class Solution {
public:
    void orderly(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
    }
    int getIndex(vector<int>& nums,int target) {
        return lower_bound(nums.begin(),nums.end(),target) - nums.begin();
    }
    vector<int> fallingSquares(vector<vector<int>>& s) {
        // 离散化
        vector<int> ph;
        for(auto& i : s) {
            ph.push_back(i[0]);
            ph.push_back(i[0] + i[1] - 1);
        }
        orderly(ph);
        int n = ph.size();
        ST h(n); h.build(1,n,1);
        vector<int> res;
        for(auto& i : s) {
            int l = getIndex(ph,i[0]) + 1;
            int r = getIndex(ph,i[0] + i[1] - 1) + 1;
            h.update(l,r,h.query(l,r) + i[1]);
            res.push_back(h.tree[1]);
        }
        return res;
    }
};
```
