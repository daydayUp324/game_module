#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
// 求 LCA
class tarjan_lca
{
public:
    int n,m;// n 为点的个数 , m 为查询的个数
    int* fa;// 并查集
    bool* vi;// 某一个点是否处理过
    int* qans;// 每一个查询的答案
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    void dfs(int u,int v,vector<vector<int>>& g,vector<vector<PII>>& Q) {
        // u 为当前点 v 为 u 的父节点
        vi[u] = true;
        for(auto& next : g[u]) {
            if(next == v) continue;
            dfs(next,u,g,Q);
        }
        for(auto& q : Q[u]) {// 查询有关 u 的询问
            if(vi[q.first]) {
                qans[q.second] = fp(q.first);
            }
        }
        fa[u] = fp(v);
    }
    tarjan_lca(int n_,int m_) {
        n = n_ , m = m_;
        fa = new int[n + 1]; memset(fa,-1,4 * n + 4);
        vi = new bool[n + 1]; memset(vi,false,n + 1);
        qans = new int[m + 1];
    }
    ~tarjan_lca() {
        delete []qans;
        delete []fa;
        delete []vi;
    }
};