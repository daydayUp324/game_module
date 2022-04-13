#

## Binar_Indexed_Tree

### [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)

[![qq0Ezq.png](https://s1.ax1x.com/2022/04/04/qq0Ezq.png)](https://imgtu.com/i/qq0Ezq)

#### CODE_1

```cpp
template<typename T>
class BIT
{
public:
    int n;
    T* tree;
    T* arr;
    BIT(int sz) {
        this->n = sz + 1;
        tree = new T[n + 1];
        arr = new T[n + 1];
        for(int i = 1;i < n;i ++) tree[i] = 0;
    };
    int lowbit(int x) { return x & (-x); }
    void update(int index,T d) {
        index ++;
        while(index < n) {
            tree[index] += d;
            index += lowbit(index);
        }
    }
    T query(int index) {
        T res = 0;
        index ++;
        while(index) {
            res += tree[index];
            index -= lowbit(index);
        }
        return res;
    }
    ~BIT() {
        delete []tree; delete []arr;
    }
};
class NumArray {
public:
    BIT<int>* h;
    int n;
    NumArray(vector<int>& nums) {
        n = nums.size();
        h = new BIT<int>(n);
        for(int i = 0;i < n;i ++) {
            h->arr[i] = nums[i];
            h->update(i,nums[i]);
        }
    }
    
    void update(int index, int val) {
        h->update(index,val - h->arr[index]);
        h->arr[index] = val;
    }
    
    int sumRange(int left, int right) {
        if(!left) return h->query(right);
        return h->query(right) - h->query(left - 1);
    }
};
```

### [315. 计算右侧小于当前元素的个数](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/)

[![qq0awD.png](https://s1.ax1x.com/2022/04/04/qq0awD.png)](https://imgtu.com/i/qq0awD)

#### CODE_2

```cpp
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
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,0);
        int Base = 1e4 + 3;
        BIT<int> h(2 * Base);
        h.update(nums.back() + Base,1);
        for(int i = n - 2;i >= 0;i --) {
            res[i] = h.query(nums[i] + Base - 1);
            h.update(nums[i] + Base,1);
        }
        return res;
    }
};
```
