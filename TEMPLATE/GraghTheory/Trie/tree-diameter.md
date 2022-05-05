#

## 树的直径

__参考链接 :__ [树的直径](https://oi-wiki.org/graph/tree-diameter/)

### 定义

> 树上任意两节点之间最长的简单路径即为树的「直径」。
> 一棵树可以有多条直径，他们的长度相等。

### 性质

> 若树上所有边边权均为正，则树的所有直径中点重合

### 求直径方法

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

#### CODE_BFS

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

### 求直径方法_树形DP

从任意节点 `i` 出发 `DFS` 来计算每一个点的往下能延展的最大距离和次大距离。 (优势 : 可以处理负权边的情况)

__简单证明 :__

>
> 从 `root` DFS 向下 , 树的直径的两个端点 `u` , `v` 只有可能是两种情况
>
> 1. `u` 和 `v` 分别在 `root` 的两棵子树上 (即 : 此时直径经过 `root` )
> 2. `u` 和 `v` 在 `root` 的某一个子树上
>
> 那么从 `root` 向下 DFS 的过程中我们用 `dp1[i]` 来记录在 `节点 i` 的向下的 __最长__ 的延伸距离。`dp2[i]` 来记录 `节点 i` 的向下的 __次长__ 的延伸距离。那么直径长度就是 `max{dp1[i] + dp2[i]}`

#### CODE_树形DP

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

