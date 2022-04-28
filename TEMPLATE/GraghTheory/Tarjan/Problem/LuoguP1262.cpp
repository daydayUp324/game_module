#include <bits/stdc++.h>
using namespace std;
// [P1262 间谍网络](https://www.luogu.com.cn/problem/P1262)
// 找 强连通分量 (SCC)
const int INF = 0x3f3f3f3f;
class tarjan
{
public:
    int* dfn;
    int* low;
    int* st;// 模拟栈
    int top;// 栈顶标识
    int* have;// 是否在栈中标识
    int* scc_idx;// 每一个点对应的 scc 序号
    int* Size;// 每一个连通块的大小
    int scc_cnt;// scc 的个数个序号标识
    int timeStamp;
    int n;
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
        if(dfn[u] == low[u]) { // 以 u 为根节点的子树为一个强连通分量
            Size[scc_cnt] = 0;
            int v = -1;
            do {
                v = st[-- top]; scc_idx[v] = scc_cnt; have[v] = false; Size[scc_cnt] ++;
            } while(v != u);
            scc_cnt ++;
        }
    }
    tarjan(int n_) {
        // @param n 点的个数 点的序号为 [0,n)
        n = n_ , timeStamp = 1 , scc_cnt = 0 , top = 0;
        dfn = new int[n + 1];
        have = new int[n + 1];
        Size = new int[n + 1];
        for(int i = 0;i <= n;i ++) dfn[i] = 0 , have[i] = false;// 0 表示未访问
        low = new int[n + 1];
        st = new int[n + 1];
        scc_idx = new int[n + 1];
    }
    ~tarjan() {
        delete []low; delete []dfn;
        delete []st; delete []have;
        delete []scc_idx; delete []Size;
    }
};
int w[3005];// 每一个间谍的收买价格
int f[3005];// 每一个 scc 中得最小编号间谍
int c[3005];// 每一个入度为 0 的 scc 的最小开销
int ind[3005];// 每一个点的入度
int main() {
    int n,m,a,b;
    scanf("%d %d",&n,&m);
    for(int i = 0;i <= n;i ++) f[i] = INF , w[i] = INF , c[i] = INF , ind[i] = 0;
    for(int i = 1;i <= m;i ++) {
        scanf("%d %d",&a,&b);
        w[a] = b;
    } 
    scanf("%d",&m);
    vector<vector<int>> g(n + 1);// 有向图
    for(int i = 1;i <= m;i ++) {
        scanf("%d %d",&a,&b);
        g[a].push_back(b);
    }
    tarjan h(n);
    for(int i = 1;i <= n;i ++) {
        if(!h.dfn[i]) {
            h.dfs(i,g);
        }
    }
    for(int i = 1;i <= n;i ++) {
        int a = h.scc_idx[i];
        f[a] = min(f[a],i);// 每一个 scc 的最小间谍编号
        for(auto& v : g[i]) {
            b = h.scc_idx[v];
            if(a != b) ind[b] ++;
        }
    }
    // 每一个入度为 0 的 scc 的最小开销
    for(int i = 1;i <= n;i ++) {
        int o = h.scc_idx[i];
        if(ind[o] == 0) {
            c[o] = min(c[o],w[i]);
        }
    }
    int res = 0;
    for(int i = 0;i < h.scc_cnt;i ++) {
        if(ind[i] == 0) {
            if(c[i] == INF) {
                printf("NO\n");
                for(int j = 1;j <= n;j ++) {
                    int j_ = h.scc_idx[j];
                    if(ind[j_] == 0 && c[j_] == INF) {
                        printf("%d\n",j); break;
                    }
                }
                return 0;
            }
            res += c[i];
        }
    }
    printf("YES\n%d\n",res);
    return 0;
}