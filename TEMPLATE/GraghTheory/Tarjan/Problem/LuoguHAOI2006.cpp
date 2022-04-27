#include <bits/stdc++.h>
using namespace std;
// [P2341 [USACO03FALL / HAOI2006] 受欢迎的牛 G](https://www.luogu.com.cn/problem/P2341)
// 找 强连通分量 (SCC)
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
        n = n_ , timeStamp = 1 , scc_cnt = 1 , top = 0;
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
int main() {
    int n,m;
    scanf("%d %d",&n,&m);
    int a,b;
    vector<vector<int>> g(n + 1);// 有向图
    vector<vector<int>> edges;// 保存边集
    for(int i = 0;i < m;i ++) {
        scanf("%d %d",&a,&b);
        if(a == b) continue;
        edges.push_back({a,b});
        g[a].push_back(b);
    }
    tarjan h(n);
    for(int i = 1;i <= n;i ++) {
        if(!h.dfn[i]) {
            h.dfs(i,g);
        }
    }
    vector<int> ind(n + 1,0);
    for(int i = 0;i < edges.size();i ++) {
        a = edges[i][0] , b = edges[i][1];
        // cout<<a<<" , "<<b<<"\n";
        a = h.scc_idx[a] , b = h.scc_idx[b];
        // 建立反向边
        // cout<<a<<" , "<<b<<"\n";
        if(a != b) ind[a] ++;// 入度 + 1
    }
    int res = 0;
    // ind[x] = 0 的 scc 点就是被大家都喜欢的奶牛 如果有多个说明不存在该奶牛
    // cout<<h.scc_cnt<<"\n";
    for(int i = 1;i < h.scc_cnt;i ++) {
        // cout<<i<<" = "<<ind[i]<<"\n";
        if(ind[i] == 0) {
            if(!res) res = i;
            else {
                printf("0\n"); return 0;
            }
        }
    }
    if(res == 0) {
        printf("0\n"); return 0;
    }
    printf("%d\n",h.Size[res]);
    return 0;
}