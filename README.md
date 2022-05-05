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
- ✅[随机数生成 (GenRandom)](.TEMPLATE/GenRandom) : `int` 和 `double` 类型
- ✅[马拉车算法 (Manacher)](./TEMPLATE/Manacher) : 给出求 `奇数` 和 `偶数` 长度的方案
- ✅[KMP 算法](./TEMPLATE/KMP) : 主串和模式串下标都是从 `0` 开始
  - ✅`Z Algorithm` ( `扩展 KMP 算法` )
- ✅[DIY_umap_map](./TEMPLATE/DIY_umap_map) : 自定义 `Node` 的 `unordered_map` 和 `map` 的写法
- ✅[线段树 (SegmentTree)](./TEMPLATE/SegmentTree)
  - ✅`区间更新`
  - ✅`区间求和`
- ✅[字典树 (WordTrie)](./TEMPLATE/WordTrie)
- ✅[倍增法 (Binary_Liftingd)](./TEMPLATE/Binary_Liftingd)
  - ✅`Least-Common-Ancestors (LCA)`
  - ✅`Kth-ancestor-of-a-tree-node`
  - ✅`ST 表 (Sparse Table)`
- [数学相关 (MathRelated)](./TEMPLATE/MathRelated)
  - ✅[质数筛 MakePrimeNumber](./TEMPLATE/MathRelated/MakePrimeNumber)
  - ✅`矩阵的相关性质` : `Rect.md` , `Rect.h`
  - ✅`组合数` : `comb_num.md`
    - ✅`递推式求解组合数`
    - ✅`放球问题分析`
  - ✅`求逆元` : `inv_num.md`
    - ✅`费马小定理求逆元`
    - ✅`线性求逆元`
    - ✅`扩展欧几里得求逆元`
    - ✅`求阶乘逆元`
  - ❌`欧拉函数` (TODO)
  - ✅`二维前缀和`
    - ✅`int` 等普通数据类型 : `Bipre.h`
    - ✅`pair<>` 的自定义 `+` 的二维前缀和 `BiprePII.h`
  - ❌`博弈论` (TODO)
  - ❌`斯特林数` (TODO)
  - ❌`表达式求值` (TODO)
  - ❌`母函数` (TODO)
- [图论相关 GraghTheory](./TEMPLATE/GraghTheory)
  - ✅`图的相关概念`
  - ❌`最短路` (TODO)
  - ❌`最长路` (TODO)
  - `连通性相关概念` (TODO)
    - ✅`强连通分量`
    - ❌`双连通分量`
    - ✅`割点和桥`
    - ❌`圆方树`
  - ❌`二分图` (TODO)
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
- **模拟退火** `Simulate_Anneal` (TODO)
- **经典排序算法** (TODO) 重点 : **归并排序**
- **经典动态规划算法总结** (TODO)

## HEAD

主要放置竞赛的一些 **"头"** —— **ACwin CodeForce LeetCode**

## CODE

- **LCCode** : 用于 **LeetCode Competition** 使用
- **CFCode** : 用于 **CodeForce Competition** 使用 (用脚本编译链接运行 数据放置在 **data.txt** 中)
- **ACWCode** : 用于 **ACwin Competition** 使用 (用脚本编译链接运行 数据放置在 **data.txt** 中)
- 其中 **CFCode** 和 **ACWCode** 可供笔试作为模板使用
