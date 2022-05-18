#

## SegmentTree

用一个 `T tree[i]` 来维护某一个区间 $[l,r]$ 的某一个 **"性质"** , 核心的思想在于 `T lazy[i]`(懒标记) 的应用 , 即 **延迟更新,到需要更新的时候才进行更新**

**线段树**主要分为**四**个主要模块 (以 **维护区间和** 为例进行说明) :

1. `bulid()` 初始化 **线段树**
   - **时间复杂度** : $O(n)$ 只和节点数有关

    ```cpp
    // 节点 1 对应的节点为 [1,n]
    // 然后递归构建剩下节点
    void build(int l,int r,int p) {
        // 构建线段树
        if(l == r) {
            tree[p] = arr[l];
            return ;
        }
        int mid = (l + r) / 2;
        build(l,mid,p * 2);
        build(mid + 1,r,p * 2 + 1);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
        return ;
    }
    ```

2. `update(l,r,op)` **更新某一个区间的"性质"**
   - **时间复杂度** : $O(logn)$

    ```cpp
    void update(int l,int r,int p,int cl,int cr,int d) {
        // update Seg : [l : r] , cur_Seg : (p) [cl : cr]
        // d : update info
        if(l > cr || r < cl) return ;// 1. [l : r] 与 [cl : cr] 无交集
        if(l <= cl && r >= cr) {// 2. [cl : cr] 是 [l : r] 的子集
            tree[p] += (LL) d * (cr - cl + 1);
            if(cl < cr) lazy[p] += d;
            else arr[p] = tree[p];
            return ;
        }
        if(lazy[p]) push_down(p,cl,cr);// 3. [l : r] 与 [cl : cr] 有交集
        int mid = (cl + cr) / 2;
        update(l,r,p * 2,cl,mid,d) , update(l,r,p * 2 + 1,mid + 1,cr,d);
        tree[p] = tree[p * 2] + tree[p * 2 + 1];
    }
    ```

3. `query(l,r)` **查询某一个区间的"性质"**
   - **时间复杂度** : $O(logn)$

    ```cpp
    LL query(int l,int r,int p,int cl,int cr) {
        // 求 [l : r] 区间的和
        if(cr < l || cl > r) return 0;// 求和的情况是 0
        if(cl >= l && cr <= r) return tree[p];
        if(lazy[p]) push_down(p,cl,cr);// lazy 标记下传
        int mid = (cl + cr) / 2;
        return query(l,r,p * 2,cl,mid) + query(l,r,p * 2 + 1,mid + 1,cr);
    }
    ```

4. `push_down` 将 **懒标记下传**
   - **时间复杂度** : $O(logn)$

    ```cpp
    void push_down(int p,int l,int r) {
        int mid = (l + r) / 2;
        lazy[p * 2] += lazy[p];
        lazy[p * 2 + 1] += lazy[p];
        // 更新 tree[] 的值
        tree[p * 2] += lazy[p] * (mid - l + 1);
        tree[p * 2 + 1] += lazy[p] * (r - mid);
        // 重置 lazy[p]
        lazy[p] = 0;
    }
    ```
