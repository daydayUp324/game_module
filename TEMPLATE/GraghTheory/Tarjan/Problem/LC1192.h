#include <bits/stdc++.h>
using namespace std;
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
            } else {// 回边
                low[u] = min(low[u],dfn[v]);
            }
            if(!iscut && low[v] >= dfn[u]) {// 割点判定
                cut_P.push_back(u); iscut = true;
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
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> g(n);
        for(auto& e : connections) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        tarjan h(n);
        h.FindCutPE(0,g);
        return h.cut_E;
    }
};