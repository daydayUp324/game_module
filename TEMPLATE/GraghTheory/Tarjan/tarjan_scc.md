#

## 求 strongly connected components(SCC)

在有向图G中,如果两个顶点间至少存在一条路径,称两个顶点 `强连通(strongly connected)`,如果有向图G的每两个顶点都强连通，称G是一个 **强连通图** , 通俗的说法是 : `从图G内任意一个点出发,存在通向图G内任意一点的的一条路径`

非强连通图有向图的极大强连通子图，称为 `强连通分量(strongly connected components,SCC)`

求图强连通分量的意义是 :

> 由于强连通分量内部的节点性质相同,可以将一个强连通分量内的节点缩成一个点（重要思想）,即消除了环,这样,原图就变成了一个 `有向无环图(directed acyclic graph,DAG)`. 显然对于一个无向图,求强连通分量没有什么意义,连通即为强连通.

- **注意 :** 对于求 `SCC` 是针对的是 `有向图` , 所以在 `DFS` 时 , 若真实存在一条到 `父边` 的 "回边" , 此时是不能跳过的。(和 `tarjan` 求 **割点 和 割边** 是有区别的。)

1. 求 **割点 和 割边**

    ```cpp
    void dfs(int u,int fa,vector<vector<int>>& g) {
        low[u] = dfn[u] = timeStamp ++;
        bool iscut = false;
        for(auto& v : g[u]) {
            if(v == fa) continue;
            // .... 省略
        }
    }
    ```

2. 求 **SCC**

    ```cpp
        void dfs(int u,vector<vector<int>>& g) {
            low[u] = dfn[u] = timeStamp ++;
            st[top ++] = u , have[u] = true;// 入栈
            for(auto& v : g[u]) {
                if(!dfn[v]) {// 树边
                    dfs(v,g);
                    low[u] = min(low[u],low[v]);
                } else if(have[v]) {// 回边 且端点在栈中
                    low[u] = min(low[u],dfn[v]);
                }
            }
            // 省略
        }
    ```

---

### 算法核心

Tarjan 算法是基于 DFS 算法，每个 `强连通分量` 为 `搜索树中的一棵子树`。搜索时，把当前搜索树中未处理的节点加入一个栈，回溯时可以判断栈顶到栈中的节点是否为一个强连通分量。

与 `tarjan` 找 `割点` , `割边` 的操作都是在 **树边** `u->v` 的时候进行 `深搜` 和更新 `low[u] = min(low[u],low[v])` , 区别在于当某一条 **回边** `u->v` , `v` 在栈中时才进行更新 `low[u] = min(low[u],dfn[v])`

- 当dfn(u)=low(u)时，以 u 为根的搜索子树上所有节点是一个强连通分量。此时把元素退栈即可。

---

### CODE

具体见 `Solution/tarjan_scc.h`
