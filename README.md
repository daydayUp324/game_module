# 说明

## TEMPLATE

主要放置 对应的 **"算法模板"** :

- **树状数组** `BIT`  (**单点更新**) 主要为 `arr[]` 下标从 **0,1** 的开始的两个版本
- **并查集** `DSU`
- **区间操作** `RangeModule`  (`Map` + `multiset` 模拟) **单点更新 + 区间管理** 两个版本
- **字符串哈希** `StringHash` , 给出了定义 `pair<int,int>` 的 **hashPII()** 用于保存状态
- **离散化** `Discretize` (主要给出 **概念** 和 **相关的操作**)
- **随机数生成** `GenRandom` : `int` 和 `double` 类型
- **马拉车** `Manacher` 算法 给出求 `奇数` 和 `偶数` 长度的方案
- `KMP` 算法 (主串和模式串下标都是从 **0** 开始)
  - `Z Algorithm` ( `扩展 KMP 算法` )
- **自定义** `Node` 的 `unordered_map` 和 `map` 的写法
- **线段树** `SegmentTree` (**区间更新 + 单点更新**)
- **字典树** `Trie`
- **倍增法** `Binary_Lifting`
  - `Least-Common-Ancestors (LCA)`
  - `Kth-ancestor-of-a-tree-node`
  - `ST 表 (Sparse Table)`
- **数学相关** `MathRelated`
  - `质数筛`
  - `矩阵的相关性质`
  - `组合数`
    - `递推式求解组合数`
    - `放球问题分析`
  - `求逆元`
    - `费马小定理求逆元`
    - `线性求逆元`
    - `扩展欧几里得求逆元`
    - `求阶乘逆元`
  - `欧拉函数` (TODO)
  - `博弈论` (TODO)
  - `斯特林数` (TODO)
  - `表达式求值` (TODO)
  - `母函数` (TODO)
- **图论相关** `GraghTheory` ——
  - `最短路` (TODO)
  - `二分图` (TODO)
  - `Tarjan` (TODO)
  - `欧拉回路` (TODO)
  - `凸包问题` (TODO)
  - `树的相关性质` (TODO)
    - `树的重心`
    - `最小生成树`
- **模拟退火** `Simulate_Anneal` (TODO)
- **经典排序算法** (TODO) 重点 : **归并排序**
- **经典动态规划算法总结** (TODO)

## HEAD

主要放置竞赛的一些 **"头"** —— 主要针对 **ACwin CodeForce LeetCode**

## CODE

- **LCCode** : 用于 **LeetCode Competition** 使用
- **CFCode** : 用于 **CodeForce Competition** 使用 (用脚本编译链接运行 数据放置在 **data.txt** 中)
- **ACWCode** : 用于 **ACwin Competition** 使用 (用脚本编译链接运行 数据放置在 **data.txt** 中)
- 其中 **CFCode** 和 **ACWCode** 可供笔试作为模板使用
