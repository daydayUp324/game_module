#

## 倍增法

`倍增法 (binary lifting)` 更多是一种思想 , 顾名思义就是翻倍 , 一种利用 `二进制` 来解决问题的角度。它能够使线性的处理转化为对数级的处理，大大地优化时间复杂度。比如我们常见的 `快速幂` , `快速乘` 其实都是 **倍增** 的思想。其他还有 `Least-Common-Ancestors (LCA)` , `ST(Sparse Table)表` (解决 `RMQ(Range Maxinum/Minimum Query)` 的问题) 都是 `倍增法` 的一个应用。

- `快速幂` : $a^b$ 的计算在朴素算法中是 $O(b)$ 的时间复杂度 , 而 `快速幂` 能到 $O(logb)$ 的一个时间复杂度。
- `扔鸡蛋` : 计算鸡蛋从上往下扔的最大安全距离。朴素的也是从最小高度往上扔 , 同理也是需要 $O(n)$ 一个时间复杂度。而通过 `二分` 每次排除一半的范围 , 这样也就把复杂度降到了 $O(logn)$ , 这也是 `倍增法` 的一个体现。

### 倍增法求 LCA 和 KthAncestor

参考题目链接 :

1. LCA : [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
2. KthAncestor : [1483. 树节点的第 K 个祖先](https://leetcode-cn.com/problems/kth-ancestor-of-a-tree-node/)

其实都是 `树上倍增` , 类似动态规划 , 用 `dp[i][j]` 来记录 `节点 i` 的 `1 << j` 的祖先节点 , 用 `depth[i]` 来表示 `节点 i` 的深度

- 对于 求解 某一个节点的 第 k 个祖先 `KthAncestor` , 就可以不用一步步地往上跳 , 而是把 k 的全部 `二进制` 位为 `1` 的位置来进行跳跃前进。

    ```cpp
    int findKthAncestor(int x,int k) {// 时间复杂度 : O(logn)
        // 同样把 k 的二进制位的距离全部跳掉
        for(int i = maxF;i >= 0;i --) {
            if(k >> i & 1) {
                x = dp[x][i];
                if(x == -1) return -1;
            }
        }
        return x;
    }
    ```

- 对于 `LCA` 的求解其实也是相类似 , 因为节点的祖先也是有一个单调性的 : 如果两个相同深度的节点 `x,y` , 最近的公共祖先距离 `x,y` 有 `d` 的距离 , 那么 :

  > - 对于 `d1 > d` 的 `x,y` 的祖先一定是 **相同** 的
  > - 对于 `d2 < d` 的 `x,y` 的祖先一定是 **不相同** 的

    所以和上面的求解 `KthAncestor` 相类似 , 我们只需要将 `x,y` 往上跳跃 `d - 1` 二进制位为 `1` 的步数即可。但是对于 `d - 1` 的求解并不能直接求解。但是我们可以进一步分析得到 : 如果我们从最高位往下来进行判断 , 如果 `dp[x][j] != dp[y][j]` , 那么就说明 `(1 << j)` 一定是在 `d - 1` 的一个二进制位中 , 那么进行跳跃即可。(不过上述的前提是需要 `x,y` 的深度是相同的 , 所以当 `x,y` 深度不相同的时候 , 我们还需要做一个 **预处理** : 相当于找深度更深的那个节点的第 `D` 个祖先 (`KthAncestor`) , `D` 为两者深度的差)

    ```cpp
    int calLCA(int x,int y) {// 每一次查询的时间复杂度 : O(logn)
    // 首先深度保持一致
    if(depth[x] < depth[y]) swap(x,y);
    int dis = depth[x] - depth[y];
    for(int i = 0;i < maxF;i ++) {
        if(dis >> i & 1) x = dp[x][i];
    }
    if(x == y) return x;
    // 假设公共祖先和他们的距离为 D
    // 那么 x,y 任何往上跳 dis < D 的距离都不会跳到相同的位置
    // 所以 x,y 把 D - 1 的全部二进制位上的 1 都跳了
    // 就会跳到距离公共祖先相差距离 1 的位置
    for(int i = maxF - 1;i >= 0;i --) {
        if(dp[x][i] != dp[y][i]) x = dp[x][i] , y = dp[y][i];
    }
    return dp[x][0];
    }
    ```

具体见 `./LCA.h` 和 `main.cpp` 程序代码

### ST 表

`ST 表(Sparse Table)` 主要是一种数据结构 , 主要用来解决类似 `RMQ (Maximum/Minimum Query)` 这种 **可重复贡献问题**。

> 可重复问题 : 对于运算 $opt$ 满足 `x opt x = x` 且满足 **结合律** , 则对应的区间查询就是一个 可重复贡献问题 , 比如 `最大值` , `最小值`,`最大公因数`,`最大公倍数`,`按位或/与`。可重复贡献的意义在于 , 可以对两个交集不为空的区间进行区间合并。

主要应用 **倍增** 的思想 (预处理和 `树上倍增` 相类似) , 来实现 $O(nlogn)$ 预处理 , $O(1)$ 查询。

- `RMQ (Maximum/Minimum Query)` : 以最大值为例 , 假如有一个数组 `A[]` , 给定一个区间 `[l,r]` 求 `max{A_i} , i ∈ [l,r]`

`ST 表` 使用的是一个二维数组 , 对于范围内的所有 `f[a][b]` 表示一个对于 `[a,a + 2^b)` 的查询。预处理方法如下 : (以下以查询最大值为例进行说明)

```cpp
const int N = 2e5 + 7;
int dp[N][25];// N 为最大的区间范围 , logN < 25
// 假设原数组为 A[]
for(int i = 0;i < n;i ++) dp[i][0] = A[i];
for(int i = 1;i < 25;i ++) {
    for(j = 0;j + (1 << i) <= nj ++) {
        dp[j][i] = max(dp[j][i - 1],dp[j + (1 << (i - 1))][i-1]);
    }
}
```

那么对于某一个区间 `[l,r]` 的查询就可以通过这样的方式来查询 : 找到一个 `整数 s` 将 `[l,r]` 分为两个区间 `[l,l + 2^s - 1]` 和 `[r - 2^s + 1,r]` , 并且这两个区间的并集为 : `[l,r]`。那么我们肯定是尽量的希望 第一个区间的右端点尽量的靠近 `r` (当然 第二个区间的左端点尽量靠近 `l` 也是一样的)，那么使 : $l + 2^s - 1 = r$ 此时得到 $s = \lfloor log(r + 1 - l) \rfloor$。

```cpp
// 对于区间 [l,r] 的查询
int s = Log2[r + 1 - l];
int res = max(dp[l][s],dp[r - (1 << s) + 1][s]);
```

而每次计算 `Log2p[]` 开销太大 , 我们可以对 `Log2[]` 也预处理

```cpp
Log2[1] = 0;
for(int i = 2;i < n;i ++) {
    Log2[i] = Log2[i / 2] + 1;
}
```

参考题目 : [P2880 [USACO07JAN] Balanced Lineup G](https://www.luogu.com.cn/problem/P2880)

[![LQgpHP.png](https://s1.ax1x.com/2022/04/14/LQgpHP.png)](https://imgtu.com/i/LQgpHP)

[![LQg334.png](https://s1.ax1x.com/2022/04/14/LQg334.png)](https://imgtu.com/i/LQg334)

代码具体见 : `ST.cpp`
