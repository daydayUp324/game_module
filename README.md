# 说明

主要参考链接 : [OI Wiki](https://oi-wiki.org/)

## TEMPLATE

主要放置 对应的 **"算法模板"** :

- [树状数组 (Binary_Indexed_Tree , BIT)](./TEMPLATE/Binary_Indexed_Tree)
  - ✅`单点更新` : 主要为 `arr[]` 下标从 `0,1` 的开始的两个版本
  - ❌`区间更新` (TODO) 用 : `差分数组` 来实现
- [并查集 (Disjoint_Set_Union , DSU)](./TEMPLATE/Disjoint_Set_Union)
  - ✅`普通并查集`
  - ❌`三维并查集` (TODO)
- ✅[区间操作 (RangeModule)](./TEMPLATE/RangeModule) : `Map` + `multiset` 模拟
  - ✅`单点更新`
  - ✅`区间管理`
- ✅[字符串哈希 (StringHash)](./TEMPLATE/StringHash) : 给出了定义 `pair<int,int>` 的 `hashPII()`
- ✅[离散化 (Discretize)](./TEMPLATE/Discretize/) : 主要给出 `概念` 和 `相关的操作`
- ✅[随机数生成 (GenRandom)](./TEMPLATE/GenRandom) : `int` 和 `double` 类型
- ✅[马拉车算法 (Manacher)](./TEMPLATE/Manacher) : 给出求 `奇数` 和 `偶数` 长度的方案
- ✅[KMP 算法](./TEMPLATE/KMP) : 主串和模式串下标都是从 `0` 开始
  - ✅`Z Algorithm` ( `扩展 KMP 算法` )
- ✅[DIY_umap_map](./TEMPLATE/DIY_umap_map) : 自定义 `Node` 的 `unordered_map` 和 `map` 的写法
- ✅[线段树 (SegmentTree)](./TEMPLATE/SegmentTree) (其中 `单点赋值` 和 `单点更新` 可以被 `区间赋值` 和 `区间更新` 所实现)
  - ✅`区间赋值(Sum,Max)`
  - ✅`区间更新(Sum,Max)`
  - ✅`动态开点线段树`
- ✅[字典树 (WordTrie)](./TEMPLATE/WordTrie)
- ✅[单调队列 (MonotonicQ)](./TEMPLATE/MonotonicQ)
- ✅[倍增法 (Binary_Liftingd)](./TEMPLATE/Binary_Liftingd)
  - ✅`Least-Common-Ancestors (LCA)` 最近公共祖先
  - ✅`Kth-ancestor-of-a-tree-node` 树的第k祖先
  - ✅`ST 表 (Sparse Table)`
- [数学相关 (MathRelated)](./TEMPLATE/MathRelated)
  - ✅[质数筛 MakePrimeNumber](./TEMPLATE/MathRelated/MakePrimeNumber)
  - ✅`矩阵的相关性质` : `Rect.md` , `Rect.h` (求矩阵的 重合面积 和 重合部分矩阵)
  - ✅`三角形的相关性质` : `triangle.h`
  - ✅`字符串的最小化表示` : `Minimal_string.md` , `Minimal_string.h`
  - ✅`组合数` : `comb_num.md`
    - ✅`递推式求解组合数`
    - ✅`放球问题分析`
  - ✅`求逆元` : `inv_num.md`
    - ✅`费马小定理求逆元`
    - ✅`线性求逆元`
    - ✅`扩展欧几里得求逆元`
    - ✅`求阶乘逆元`
  - ❌`欧拉函数` (TODO)
  - ✅`全排列` : `Full_nextPermutation.md`
  - ✅`下一个排列` : `Next_Permutation.md`
  - ✅[容斥定理 Principle Of Inclusion Exclusion.md](./TEMPLATE/MathRelated/Principle_Of_Inclusion_Exclusion)
    - ✅`不定方程非负整数解计数`
    - ✅`错位排列计数`
    - ✅`最大公约数为 k 的数对个数`
    - ❌`推导欧拉函数`(TODO 和 `欧拉函数` 一起进行复习)
  - ✅`二维前缀和`
    - ✅`int` 等普通数据类型 : `Bipre.h`
    - ✅`pair<>` 的自定义 `+` 的二维前缀和 `BiprePII.h`
  - ❌`博弈论` (TODO)
  - ❌`斯特林数` (TODO)
  - ❌`表达式求值` (TODO)
  - ❌`母函数` (TODO)
- [图论相关 GraghTheory](./TEMPLATE/GraghTheory)
  - ✅`图的相关概念`
  - ✅`点是否被多边形包围` (`is_point_in_path`)
  - ✅`最短路`
    - ✅`Dijstra`
    - ✅`Folyd`
    - ✅`Bellman_ford`
    - ✅`SPFA`
  - ❌`最长路` (TODO)
  - ✅`内向基环树求环` (`BaseRingInwardTree`) 求环的个数和最大环的大小
  - `连通性相关概念` (TODO)
    - ✅`强连通分量`
    - ❌`双连通分量`
    - ✅`割点和桥`
    - ❌`圆方树`
  - ✅[二分图](./TEMPLATE/GraghTheory/BipartiteGraph)
    - ✅`二分图最大匹配`
    - ✅`二分图最大权匹配`
      - ✅`Kuhn_Munkers_bfs`
      - ✅`Kuhn_Munkers_dfs`
  - ✅[Tarjan](./TEMPLATE/GraghTheory/Tarjan)
    - ✅`求割点`
    - ✅`求桥`
    - ✅`求SCC`
    - ✅`求LCA`
  - ❌`欧拉回路` (TODO)
  - ❌`凸包问题` (TODO)
  - ✅[树的相关性质 (Trie)](./TEMPLATE/GraghTheory/Trie)
    - ✅`树的重心` : `tree-centroid.md`
    - ✅`树的直径` : `tree-diameter.md`
      - ✅`BFS求解`
      - ✅`树形DP求解`
    - ✅[最小生成树 (MST)](./TEMPLATE/GraghTheory/Trie/MST)
      - ✅`Kruskal`
      - ✅`Prim`
      - ✅`次小生成树`
        - ✅`非严格次小生成树`
        - ✅`严格次小生成树`
- ✅`模拟退火` : `Simulate_Anneal`
- ✅`逆序对` : `Inversions`
  - ✅`归并排序`
  - ✅`树状数组`
- ❌最优化求解 (TODO)
  - ❌`梯度下降法`
  - ❌`爬山法`
  - ❌`三分法`
- ❌经典排序算法 (TODO)
- `经典动态规划算法总结` : `DynamicProgram`
  - ✅`最长递增子序列`
  - ✅`最长回文子序列`
  - ✅`Trie上DP`
- 💡`经典模型问题` : `ClassicProblems`
  - ✅`第 k 大的子集和` : `Find-the-K-sum-of-an-array`
  - ✅`从子集和还原数组` : `Find-array-given-subset-sums`

## HEAD

主要放置竞赛的一些 __"头"__ —— __ACwin CodeForce LeetCode__

## CODE

- __LCCode__ : 用于 __LeetCode Competition__ 使用
- __CFCode__ : 用于 __CodeForce Competition__ 使用 (用脚本编译链接运行 输入数据放置在 __data.txt__ 中)
- __ACWCode__ : 用于 __ACwin Competition__ 使用 (用脚本编译链接运行 输入数据放置在 __data.txt__ 中)
- 其中 __CFCode__ 和 __ACWCode__ 可供笔试作为模板使用
