#

## 树相关知识总结

---

### 树的重心

__参考链接 :__ [树的重心](https://oi-wiki.org/graph/tree-centroid/)

#### 定义_1

> 对于树上的每一个点，计算其所有子树中最大的子树节点数，这个值最小的点就是这棵树的重心。

#### 性质_1

1. 以 __树的重心__ 为根时 , 所有子树的大小都不超过整棵树大小的一半
2. 树中所有点到某个点的距离和中，到 __重心__ 的 __距离和__ 是最小的；如果有两个 __重心__ ，那么到它们的距离和一样。
3. 把两棵树通过一条边相连得到一棵新的树，那么新的树的 __重心__ 在连接原来两棵树的重心的路径上。
4. 在一棵树上添加或删除一个叶子，那么它的 __重心__ 最多只移动一条边的距离。

#### 求重心 CODE

利用 上述 `性质 1` + `DFS` 可以求得 :

1. 对于某一个 `节点 i` 我们判断它的 `DFS` 方向的子树大小是否都不超过整颗树的一半
2. 然后因为是树 , 所以 `节点 i` 最多只有一个 `父节点` 而树的 `总节点数 n` 是确定的 , 所以用 `n` 减去 `DFS` 方向上的全部子树大小和 `节点 i` 本身 即可。

```cpp
// n 为节点总数
// m 为总结点一半 : m = n / 2
vector<int> res;// 重心的点
vector<vector<int>> g;// 树的无向图表达
int n,m;
int dfs(int cur,int pre) {
    int sz = 1;
    bool f = true;
    for(auto& next : g[cur]) {
        if(next == pre) continue;
        int t = dfs(next,cur);
        sz += t;
        if(t > m) f = false;
    }
    if(f && n - sz > m) f = false;
    if(f) res.push_back(cur);
    return sz;
}
```

---

### 树的直径

__参考链接 :__ [树的直径](https://oi-wiki.org/graph/tree-diameter/)

#### 定义_2

> 树上任意两节点之间最长的简单路径即为树的「直径」。
> 一棵树可以有多条直径，他们的长度相等。

#### 性质_2

> 若树上所有边边权均为正，则树的所有直径中点重合

#### 求直径方法_BFS

1. 从任意一个点 `i` 出发 `bfs` 找到任意距离它最远的点 `z`
2. 然后从 `z` 出发 `bfs` 找到距离它最远的点 `u`
3. 那么 `z->u` 的简单路径就是 `树的直径`

不过该方法对于 `负权边` 并不生效 , 且需要求全部直径的时候复杂度会比较高 (需要先求出全部的 `z` 然后对 `z_i` 分别 `bfs` 求 `u_i`)

__简单证明 :__

> 反证法 :
> 假设 `z` 不是 `直径` 的某一个端点 , `v` 是本来直径的某一个端点 , 且 `d(v->i)` < `d(z->i)`。
> 那么 :
>
> 1. 直径包含点 `i` : 那么直径就是 `v->i->u` 长度小于 `z->i->u`。与直径的定义矛盾
> 2. 直径不包含点 `i` : 取直径上任意一个点 `x` 那么根据 `z` 是离 `i` 最远的点的前提 , `i->x->v` 一定小于 `i->z` 即 : `x->v` 小于 `x->i->z` 所以 `z` 一定是比 `v` 更优的一个端点

##### CODE_BFS

```cpp
using PII = pair<int,int>;
vector<vector<int>> g;// 树的无向图表达形式
int bfs(int root) {
    queue<PII> q;
    int last;
    q.push({root,-1});
    while(!q.empty()) {
        int len = q.size();
        last = q.front().first;
        while(len --) {
            auto t = q.front(); q.pop(); 
            for(auto& next : g[t.first]) {
                if(next == t.second) continue;
                q.push({next,t.first});
            }
        }
    }
    return last;
}
int main() {
    // 初始化 g
    // ...
    int a,b;
    a = bfs(0);
    b = bfs(a);
    // a-b 即为其中一条直径
}
```

#### 求直径方法_树形DP

从任意节点 `i` 出发 `DFS` 来计算每一个点的往下能延展的最大距离和次大距离。 (优势 : 可以处理负权边的情况)

__简单证明 :__

>
> 从 `root` DFS 向下 , 树的直径的两个端点 `u` , `v` 只有可能是两种情况
>
> 1. `u` 和 `v` 分别在 `root` 的两棵子树上 (即 : 此时直径经过 `root` )
> 2. `u` 和 `v` 在 `root` 的某一个子树上
>
> 那么从 `root` 向下 DFS 的过程中我们用 `dp1[i]` 来记录在 `节点 i` 的向下的 __最长__ 的延伸距离。`dp2[i]` 来记录 `节点 i` 的向下的 __次长__ 的延伸距离。那么直径长度就是 `max{dp1[i] + dp2[i]}`

##### CODE_树形DP

```cpp
// 以 边权 都为 1 为例
int d;
int dp1[N] , dp2[N];
void dfs(int root,int f) {
    dp1[root] = dp2[root] = 0;
    for(auto& next : g[root]) {
        if(next == f) continue;
        dfs(next,root);
        int t = dp1[next] + 1;
        if(t > dp1[root]) dp2[root] = dp1[root] , dp1[root] = t;
        else dp2[root] = max(dp2[root],t);
    }
    d = max(d,dp1[root] + dp2[root]);
}
```
