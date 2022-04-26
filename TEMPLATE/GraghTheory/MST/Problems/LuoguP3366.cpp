#include <bits/stdc++.h>
using namespace std;
// 最小生成树 [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
class MST
{
    /**
     * @author daydayUppp
     * @brief Minimum Spanning Tree (MST)
     * 图模型用 邻接表的形式来进行存储
     */
public:
    int n;
    vector<int> fa;
    int count;
    int fp(int x) { return fa[x] < 0 ? x : fa[x] = fp(fa[x]); }
    void unite(int x,int y) {
        x = fp(x) , y = fp(y); if(x == y) return ;
        if(fa[x] < fa[y]) swap(x,y);
        fa[x] += fa[y]; fa[y] = x;
    }
    long long Kruskal(vector<vector<int>>& edges,vector<vector<int>>& E,vector<vector<int>>& RE) {
        // edges = {{x,y,v}}
        fa.resize(n);
        for(int i = 0;i < n;i ++) fa[i] = -1;
        long long mini_v = 0;// 依情况而定
        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int x,y;
        for(int i = 0;i < edges.size();i ++) {
            x = edges[i][0] , y = edges[i][1];
            if(fp(x) == fp(y)) {
                RE.push_back(edges[i]); continue;
            } 
            E.push_back(edges[i]);
            unite(x,y); mini_v += edges[i][2]; count --;
        }
        return mini_v;
    }
    MST(int n_) {
        n = n_; count = n - 1;
    }
};
int main() {
    int n,m,a,b,c;
    scanf("%d %d",&n,&m);
    vector<vector<vector<int>>> g(n + 1);
    vector<vector<int>> edges;// 边集
    for(int i = 0;i < m;i ++) {
        scanf("%d %d %d",&a,&b,&c);
        edges.push_back({a,b,c});
    }
    vector<vector<int>> E;// 组成最小生成树的边集
    vector<vector<int>> RE;// 剩下不用边的边集
    MST h(n + 1);
    long long o = h.Kruskal(edges,E,RE);// 最小生成树的边集 E 和 权和 o
    if(h.count == 1) cout<<o<<"\n";
    else cout<<"orz\n";
    return 0;
}