#include <bits/stdc++.h>
using namespace std;
// [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
class tarjan
{
public:
    int* dfn;
    int* low;
    int timeStamp;
    int n;
    vector<int> cut_P;// 割点集
    vector<vector<int>> cut_E;// 割边集
    void dfs(int u,int fa,vector<vector<int>>& g) {
        low[u] = dfn[u] = timeStamp ++;
        bool iscut = false;
        for(auto& v : g[u]) {
            if(v == fa) continue;
            if(!dfn[v]) {// 树边
                dfs(v,u,g);
                low[u] = min(low[u],low[v]);
                if(!iscut && low[v] >= dfn[u]) {// 割点判定
                    cut_P.push_back(u); iscut = true;
                }
            } else {// 回边
                low[u] = min(low[u],dfn[v]);
            }
            if(low[v] > dfn[u]) {// 割边判定
                cut_E.push_back({u,v});
            }
        }
    }
    void FindCutPE(int root,vector<vector<int>>& g) {
        // @param g 图的邻接表形式 (无向连通图)
        // @param root 图的根节点(自定义)
        int child = 0;
        // 根节点需要特判
        low[root] = dfn[root] = timeStamp ++;
        for(auto& next : g[root]) {
            if(!dfn[next]) {
                child ++;
                dfs(next,root,g);
                // 判断 (root->next) 是否是割边
                if(low[next] > dfn[root]) {
                    cut_E.push_back({root,next});
                }
            } 
        }
        if(child > 1) {
            // 说明根节点为割点
            cut_P.push_back(root);
        }
    }
    tarjan(int n_) {
        // @param n 点的个数 点的序号为 [0,n)
        n = n_ , timeStamp = 1;
        dfn = new int[n + 1];
        for(int i = 0;i <= n;i ++) dfn[i] = 0;// 0 表示未访问
        low = new int[n + 1];
    }
    ~tarjan() {
        delete []low;
        delete []dfn;
        cut_E.clear() , cut_P.clear();
    }
};
int main() {
    int n,m;
    cin >> n >> m;
    int a,b;
    vector<vector<int>> g(n + 1);
    for(int i = 0;i < m;i ++) {
        cin >> a >> b;
        if(a == b) continue;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    tarjan h(n);
    for(int i = 1;i <= n;i ++) {
        if(!h.dfn[i]) {
            h.FindCutPE(i,g);
        }
    }
    sort(h.cut_P.begin(),h.cut_P.end());
    printf("%d\n",(int)h.cut_P.size());
    if(h.cut_P.size() > 0) {
        printf("%d",h.cut_P[0]);
    }
    for(int i = 1;i < h.cut_P.size();i ++) printf(" %d",h.cut_P[i]);
    printf("\n");
    return 0;
}