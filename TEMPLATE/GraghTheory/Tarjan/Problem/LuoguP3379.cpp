#include <bits/stdc++.h>
using namespace std;
// [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
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
int main() {
    int n,m,root;
    scanf("%d %d %d",&n,&m,&root);
    int a,b;
    vector<vector<int>> g(n + 1);// 无向图
    for(int i = 1;i < n;i ++) {
        scanf("%d %d",&a,&b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<vector<PII>> Q(n + 1);
    for(int i = 0;i < m;i ++) {
        scanf("%d %d",&a,&b);
        Q[a].push_back({b,i});
        Q[b].push_back({a,i});
    }
    tarjan_lca h(n,m);
    h.dfs(root,root,g,Q);
    for(int i = 0;i < m;i ++) {
        printf("%d\n",h.qans[i]);
    }
    return 0;
}