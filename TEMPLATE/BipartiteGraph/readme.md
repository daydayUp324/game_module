#

## 二分图 (Bipartite Graph)

> 参考链接 :
>
> 1. [二分图的最大匹配、完美匹配和匈牙利算法](https://www.renfei.org/blog/bipartite-matching.html)
> 2. [二分图 OI WiKi](https://oi-wiki.org/graph/bi-graph/)

### 二分图定义

> 二分图又称作二部图，是图论中的一种特殊模型。
> 设G=(V,E)是一个无向图，如果顶点V可分割为两个互不相交的子集(A,B)，并且图中的每条边（i，j）所关联的两个顶点i和j分别属于这两个不同的顶点集(i in A,j in B)，则称图G为一个二分图。简而言之，就是顶点集V可分割为两个互不相交的子集，并且图中每条边依附的两个顶点都分属于这两个互不相交的子集，两个子集内的顶点不相邻。
>
> 等价定义 : **一个不含奇数条边的环**

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

#### 匹配

> 在一个图中 , 一个 `匹配` 是一个边的集合 , 其中**任意两条边都没有公共顶点。** 比如下方的 , `图 3` , `图 4` 就是 `图 2` 的一个匹配。

[![LyWQg0.png](https://s1.ax1x.com/2022/04/21/LyWQg0.png)](https://imgtu.com/i/LyWQg0)

先定义四个概念 : `匹配点` , `匹配边` , `未匹配点` , `非匹配边` , 其含义顾名思义不做解释。

##### 最大匹配

> 一个图的所有匹配中 , 所含 `匹配边数` 最多的匹配 , 称为这个图的最大匹配。

##### 匈牙利算法

###### 基本概念

[![Ly4w2n.png](https://s1.ax1x.com/2022/04/21/Ly4w2n.png)](https://imgtu.com/i/Ly4w2n)

1. `交替路` : 从一个未匹配点出发，依次经过非匹配边、匹配边、非匹配边…形成的路径叫交替路。
2. `增广路` : 从一个未匹配点出发，走交替路，如果途径另一个未匹配点（出发的点不算），则这条交替路称为增广路（agumenting path）。例如，图 5 中的一条增广路如图 6 所示（图中的匹配点均用红色标出）：

    [![Ly4sbT.png](https://s1.ax1x.com/2022/04/21/Ly4sbT.png)](https://imgtu.com/i/Ly4sbT)

    `增广路` 有一个重要特点：`非匹配边` 比 `匹配边` 多一条。因此，研究增广路的意义是改进匹配。只要把增广路中的匹配边和非匹配边的身份交换即可。由于中间的匹配节点不存在其他相连的匹配边，所以这样做不会破坏匹配的性质。交换后，图中的匹配边数目比原来多了 1 条。所以我们可以通过不停地找增广路来增加匹配中的匹配边和匹配点。找不到增广路时，达到最大匹配（这是增广路定理）。

3. `匈牙利树` : 一般用 `BFS` 构造。从一个未匹配点出发运行 `BFS` (唯一的限制是 必须要走交替路) , 直到不能再扩展为止。

##### 完美匹配

> 如果一个图的某个匹配中，所有的顶点都是匹配点，那么它就是一个完美匹配。显然，图 4 是一个完美匹配。完美匹配一定是最大匹配（完美匹配的任何一个点都已经匹配，添加一条新的匹配边一定会与已有的匹配边冲突）。但并非每个图都存在完美匹配。

[![LyWxMV.png](https://s1.ax1x.com/2022/04/21/LyWxMV.png)](https://imgtu.com/i/LyWxMV)
