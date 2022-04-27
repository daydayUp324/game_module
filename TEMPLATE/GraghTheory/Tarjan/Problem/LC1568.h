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
                if(!iscut && low[v] >= dfn[u]) {// 割点判定
                    cut_P.push_back(u); iscut = true;
                }
            } else {// 回边
                low[u] = min(low[u],dfn[v]);
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
const int dir[4][2] = {
    {0,1},{0,-1},{1,0},{-1,0}
};
class Solution {
public:
    int n,m;
    int minDays(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        vector<vector<int>> g(n*m);
        vector<int> roots;// 保存每一个 1 的区域
        for(int i = 0;i < n;i ++) {
            for(int j = 0;j < m;j ++) {
                if(grid[i][j]) {
                    roots.push_back(i * m + j);
                    for(int d = 0;d < 4;d ++) {
                        int ni = i + dir[d][0];
                        int nj = j + dir[d][1];
                        if(ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj]) {
                            g[i * m + j].push_back(ni * m + nj);
                        }
                    }
                }
            }
        }
        if(roots.size() < 2) return roots.size();
        tarjan h(n * m);
        h.FindCutPE(roots[0],g);
        for(auto& root : roots) {
            // 本身就是分离的情况
            if(!h.dfn[root] && grid[root / m][root % m]) return 0;
        }
        return h.cut_P.size() ? 1 : 2;
    }
};