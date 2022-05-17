#

## 二分图 (Bipartite Graph)

> 参考链接 :
>
> 1. [二分图的最大匹配](https://blog.csdn.net/qq_41996523/article/details/113245137)
> 2. [二分图 OI WiKi](https://oi-wiki.org/graph/bi-graph/)

---

### 二分图定义

二分图又称作二部图，是图论中的一种特殊模型。
设G=(V,E)是一个无向图，如果顶点V可分割为两个互不相交的子集(A,B)，并且图中的每条边（i，j）所关联的两个顶点i和j分别属于这两个不同的顶点集(i in A,j in B)，则称图G为一个二分图。简而言之，就是顶点集V可分割为两个互不相交的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。

等价定义 : **一个不含奇数条边的环**

---

#### 验证二分图

验证一个图是否是 `二分图` 可以用 `染色法` 来 `DFS` 或者 `BFS` 求解。

**参考题目 :** [785. 判断二分图](https://leetcode-cn.com/problems/is-graph-bipartite/)

```cpp
// 输入的是一个无向图 每两对点可能并不是连通的
// 深搜染色法如下
const int N = 105;
class Solution {
public:
    int colors[N];// 用于标记每一个点的颜色
    bool dfs(vector<vector<int>>& g,int cur) {
        for(auto& next : g[cur]) {
            if(!colors[next]) {
                colors[next] = colors[cur] ^ 3; 
                if(!dfs(g,next)) return false;
            } else {
                if(colors[next] == colors[cur]) return false;
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& g) {
        int n = g.size();
        memset(colors,0,4 * n);
        for(int i = 0;i < n;i ++) {
            if(!colors[i]) {
                colors[i] = 1;// 1,2 染色
                if(!dfs(g,i)) return false;
            }
        }
        return true;
    }
};
```

---

#### 匹配

> 在一个图中 , 一个 『匹配』 是一个边的集合 , 其中**任意两条边都没有公共顶点。** 比如下方的 , `图 3` , `图 4` 就是 `图 2` 的一个匹配。

[![LyWQg0.png](https://s1.ax1x.com/2022/04/21/LyWQg0.png)](https://imgtu.com/i/LyWQg0)

先定义四个概念 : 『匹配点』 , 『匹配边』 , 『未匹配点』 , 『非匹配边』 , 其含义顾名思义不做解释。

补充定义和定理 :

---

**定义**

1. 『最大匹配数』: 最大匹配的匹配边的数目
2. 『最小点覆盖』: 选取最少的点，使任意一条边至少有一个端点被选择
3. 『最大独立数』: 选取最多的点，使任意所选两点均不相连
4. 『最小路径覆盖数』: 对于一个 `DAG（有向无环图）`，选取最少条路径，使得每个顶点属于且仅属于一条路径。路径长可以为 0（即单个点）。

---

**定理**

『定理一』: 最大匹配数 = 最小点覆盖数（这是 Konig 定理）
    - 简单证明 : 首先易得 『最小点覆盖数』中的点不会存在两个点是一条最终情况下的 『匹配边』上的两个点。因此 『最小点覆盖数』中的每一个点一定是某一条『匹配边』中的某一个端点。

『定理二』: 最大匹配数 = 顶点数 - 最大独立数
    - 简单证明 : 因为只选择 『最大匹配』的每一条『匹配边』的一个点，那么一定是一个『独立点集』。然后除了 『最大匹配』 中的点 , 其余的任意两个点肯定也不存在边相连 —— 若存在 , 则该边也应该被包含在 『最大匹配』中。

『定理三』: 最小路径覆盖数 = 顶点数 - 最大匹配数
    - 简单证明 : 首先易得 : 『最大匹配数』 * 2 等于此时图中『匹配点』 的个数。那么对于每一个匹配点我们都需要选择一条边。且每一个『未匹配点』 都需要一条路径。即 : 『最小路径覆盖数』= `x＋y` , 『顶点数』 = `2x + y` , 其中 `x` 是 『最大匹配数』 , `y` 是 『未匹配点数』 , 即 『最小路径覆盖数』 = 『顶点数』 - 『最大匹配数』。

---

##### 最大匹配

> 一个图的所有匹配中 , 所含 `匹配边数` 最多的匹配 , 称为这个图的最大匹配。

##### 匈牙利算法

###### 基本概念

[![Ly4w2n.png](https://s1.ax1x.com/2022/04/21/Ly4w2n.png)](https://imgtu.com/i/Ly4w2n)

1. 『交替路』 : 从一个未匹配点出发，依次经过非匹配边、匹配边、非匹配边…形成的路径叫交替路。
2. 『增广路』 : 从一个未匹配点出发，走交替路，如果途径另一个未匹配点（出发的点不算），则这条交替路称为增广路（agumenting path）。例如，图 5 中的一条增广路如图 6 所示（图中的匹配点均用红色标出）：

    [![Ly4sbT.png](https://s1.ax1x.com/2022/04/21/Ly4sbT.png)](https://imgtu.com/i/Ly4sbT)

    『增广路』 有一个重要特点：『非匹配边』 比 『匹配边』 多一条。因此，研究增广路的意义是改进匹配。只要把增广路中的匹配边和非匹配边的身份交换即可。由于中间的匹配节点不存在其他相连的匹配边，所以这样做不会破坏匹配的性质。交换后，图中的匹配边数目比原来多了 1 条。所以我们可以通过不停地找增广路来增加匹配中的匹配边和匹配点。找不到增广路时，达到最大匹配（这是增广路定理）。

3. 『匈牙利树』 : 一般用 `BFS` 构造。从一个未匹配点出发运行 `BFS` (唯一的限制是 必须要走交替路) ， 直到不能再扩展为止。（由下图所示 , 由 `Fig.7` 可以得到 `Fig.8` 的一棵 `BFS 树`）但是 『匈牙利树』要求所有的叶子节点均为『匹配点』，所以这不是一棵『匈牙利树』。如果原图中没有 `节点 7` ，则最后生成的就是一棵 『匈牙利树』。同时，我们可以看到 ，从 `节点 2` 到 `节点 7` 显然是一条 『增广路』。即 ：沿着这条增广路扩充后将会新增一个匹配。

[![O8aZ7j.png](https://s1.ax1x.com/2022/05/09/O8aZ7j.png)](https://imgtu.com/i/O8aZ7j)

因此 ： 『匈牙利算法（Hungarian）』 的核心就是从每一个未匹配的点出发寻找 『增广路』。

算法流程主要如下：

1. 从左边第 1 个顶点开始，挑选未匹配点进行搜索，寻找增广路。

- 如果经过一个未匹配点，说明寻找成功。更新路径信息，匹配边数 +1，停止搜索。
- 如果一直没有找到增广路，则不再从这个点开始搜索。事实上，此时搜索后会形成一棵匈牙利树。我们可以永久性地把它从图中删去，而不影响结果。

代码看 `./Solution/Augment_path.h` (`DFS` 和 `BFS` 两个版本)

**时间复杂度 :** $O(VE)$

---

##### 完美匹配

> 如果一个图的某个匹配中，所有的顶点都是匹配点，那么它就是一个完美匹配。显然，图 4 是一个完美匹配。完美匹配一定是最大匹配（完美匹配的任何一个点都已经匹配，添加一条新的匹配边一定会与已有的匹配边冲突）。但并非每个图都存在完美匹配。

[![LyWxMV.png](https://s1.ax1x.com/2022/04/21/LyWxMV.png)](https://imgtu.com/i/LyWxMVi)

---

##### 完备匹配

> 匹配了二分图较小集合（二分图X，Y中小的那个）的所有点的匹配。

---

##### 最小路径覆盖

参考链接 : [最小路径覆盖](https://blog.csdn.net/qq_39627843/article/details/82012572)

###### DAG的最小不相交路径覆盖

算法 : 把原图的每个点 `V` 拆成 `Vx` 和 `Vy` 两个点，如果有一条有向边 `A->B`，那么就加边 `Ax−>By`。这样就得到了一个 『二分图』。 那么最小路径覆盖 = 原图的结点数 - 新图的最大匹配数。 (**拆点** 的运用)

---

##### 二分图带权最优匹配求解

参考链接 :

1. [OI Wiki二分图最大权匹配](https://oi-wiki.org/graph/graph-matching/bigraph-weight-match/)
2. [匈牙利算法](https://blog.csdn.net/qq_41996523/article/details/113245137)
3. [二分图最大权匹配——KM算法](https://blog.csdn.net/weixin_30727835/article/details/99364230)

**问题描述**

> 对于二分图的每条边都有一个权（非负），要求一种完备匹配方案，使得所有匹配边的权和最大，记做最优完备匹配。（特殊的，当所有边的权为1时，就是最大完备匹配问题）
> 二分图的带权匹配就是求出一个匹配集合，使得集合中边的权值之和最大或最小。
>
> 使用 `Kuhn-Munkers` 算法实现求二分图的最优匹配。`Kuhn-Munkers` 算法可以实现为 $O(N^3)$ 的时间复杂度。

###### Kuhn-Munkers 算法

KM算法用来求一类特殊二分图的最大权完美匹配。这个特殊指 :

1. **每对** 左右部点间都有边
2. 左右部的节点数量相同。

其实没有关系。我们只要这样做，就可以推至普适情况：

1. 原来没有边的左右部点间连权值为 0 / −inf 的边（通常直接用邻接矩阵实现。连 0 还是连 -inf 取决于是否要求一定要完美匹配）。
2. 往少的那一部补一些点使之相等。

**定义 :**

1. **顶标** : 我们给每个节点设置一个 “顶标”。为了方便，左部节点的顶标叫做 $lx_i$ , 右部节点的顶标叫做 $ly_i$。
    - 性质 : 对于图中的任意一条边 $(u,v,w)$ 满足 : $lx_u + ly_v >= w$
2. **相等子图** : 『相等子图』 包括原二分图中的所有节点（即一个生成子图），而边集却是原图中满足 $lx_u + ly_v = w$  的边 $(u,v,w)$ 构成的。也就是把那些的边搞出来的一个生成子图。
    - 性质1 : 相等子图若存在完美匹配，则完美匹配的权和就是顶标和。
    - 性质2 : 相等子图若存在完美匹配，则同时也是原图的最大权完美匹配。(即 我们只要增广一个 『相等子图』，使之具有完美匹配即可)

**算法流程 :**

1. 赋予一个顶标初始值，比如 $lx_u = \max\{w|(u,v,w)\}$ , $ly_i = 0$
2. 选一个未匹配点，从它那里开始在 『相等子图』 中增广。
3. 调整顶标，给在交错树中的左部的节点减去一个值，给在交错树中的右部的节点加上一个值。这是为了让更多的节点加进相等子图。

---

**调整顶标**

比如我们要进行调整的变化值为 $\text{a}$，即让所有在交错树中的点的 $lx_u$ 减 $\text{a}$ ，$ly_v$ 加 $\text{a}$。

若假设 `u,v`  分别是交错树上任意的两个左、右部点 ，`u',v'` 分别是交错树外任意的两个左、右节点。则有如下性质 :

1. `(u,v)` 仍在交错树上
2. `(u',v')` 仍不在交错树上
3. `(u,v')` 由于顶标和的减小 , **有可能** 进入相等子图
4. `(u',v)` 由于顶标和增加 , 更 **不可能** 进入相等子图

因此 : 所以我们要增广，关键看第3种情况。

为了维护顶标的性质，并且让第3种情况的边加入， $\text{a}$ 值应选择为：

$$a = \min\{ (lx_u + ly_{v}' - w) |\forall (u,v',w)\}$$

代码 : 具体看 `./Solution/Kuhn_Munkers_bfs.h` 和 `./Solution/Kuhn_Munkers_dfs.h`

###### Kuhn-Munkers 算法的几种变形应用

1.**Kuhn-Munkers 算法** 是求最大权完备匹配，如果要求最小权完备匹配怎么办？方法很简单，只需将所有的边权值取其相反数，求最大权完备匹配，匹配的值再取相反数即可。
2.**Kuhn-Munkers 算法** 的运行要求是必须存在一个 『完备匹配』，如果求一个最大权匹配(不一定完备)该如何办？依然很简单，把不存在的边权值赋为0。
3.**Kuhn-Munkers 算法** 求得的最大权匹配是边权值和最大，如果我想要边权之积最大，又怎样转化？还是不难办到，每条边权取自然对数，然后求最大和权匹配，求得的结果a再算出e^a就是最大积匹配。