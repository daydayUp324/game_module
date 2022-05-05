#include <bits/stdc++.h>
using namespace std;
// 题目 : [P2504 [HAOI2006]聪明的猴子](https://www.luogu.com.cn/problem/P2504)
#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
class MST
{
    /**
     * @author daydayUppp
     * @brief Minimum Spanning Tree (MST)
     * 图模型用 邻接表的形式来进行存储
     * 
     * 适用情景 : 处理 n 个节点 , 使 n 个节点成为连通图的最小开销
     * 
     * 给出两种方法 :
     * 1. Kruskal 算法
     * 2. Prim 算法
     */
public:
    int n;
    vector<int> fa;
    int fp(int x) { return fa[x] < 0 ? x : fa[x] = fp(fa[x]); }
    void unite(int x,int y) {
        x = fp(x) , y = fp(y);
        if(x == y) return ;
        if(fa[x] < fa[y]) swap(x,y);
        fa[x] += fa[y]; fa[y] = x;
    }
    int Kruskal(vector<vector<int>>& edges) {
        // edges = {{x,y,v}}
        fa.resize(n);
        for(int i = 0;i < n;i ++) fa[i] = -1;
        int mini_v = 0;
        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int x,y;
        for(int i = 0;i < edges.size();i ++) {
            x = edges[i][0] , y = edges[i][1];
            if(fp(x) == fp(y)) continue;
            unite(x,y); mini_v = max(mini_v,edges[i][2]);
        }
        return mini_v;
    }
    int Prim(int root,vector<vector<int>>& g) {
        // g[x][y] = dis : x->y
        vector<int> dis(n,INT_MAX);
        vector<bool> visited(n,false);
        visited[root] = true;
        dis[root] = 0;
        int mini_v = 0;
        // 初始化
        for(int i = 0;i < n;i++) dis[i] = g[root][i];
        for(int i = 1;i < n;i++) {
            int minp = INT_MAX;
            int minid = -1;
            for(int j = 0;j < n;j++) {
                if(!visited[j] && dis[j] < minp) {
                    minp = dis[j];
                    minid = j;
                }
            }// 找到与连通区域距离最近的点
            mini_v = max(minp,mini_v);
            visited[minid] = true;
            for(int j = 0;j < n;j++) {
                if(!visited[j]) {
                    dis[j] = min(g[minid][j],dis[j]);
                }
            }
        }// 总共要加n-1条边构成环
        return mini_v;
    }
    MST(int n_) {
        n = n_;
    }
};
int n,m;
int w[505];
int tx[1005];
int ty[1005];
int Cal_dis(int a,int b,int c,int d) {
    return (a - c) * (a - c) + (b - d) * (b - d);
}
int solve1(MST& h) {
    // Kruskal
    vector<vector<int>> edges;
    for(int i = 0;i < m;i ++) {
        for(int j = i + 1;j < m;j ++) {
            int d = Cal_dis(tx[i],ty[i],tx[j],ty[j]);
            edges.push_back({i,j,d});
        }
    }
    return h.Kruskal(edges);
}
int solve2(MST& h) {
    // Prim
    vector<vector<int>> g(m,vector<int>(m,INT_MAX));
    for(int i = 0;i < m;i ++) {
        for(int j = i + 1;j < m;j ++) {
            int d = Cal_dis(tx[i],ty[i],tx[j],ty[j]);
            g[i][j] = g[j][i] = d;
        }
    }
    return h.Prim(0,g);
}
int main() {
    cin >> n;
    for(int i = 0;i < n;i ++) {
        cin >> w[i]; w[i] *= w[i];
    }
    cin >> m;
    for(int i = 0;i < m;i ++) {
        cin >> tx[i] >> ty[i];
    }
    MST h(m);
    int o = solve1(h);// Kruskal
    // int o = solve2(h);// Prim
    // cout<<"min_v = "<<h.mini_v<<"\n";
    int ans = 0;
    for(int i = 0;i < n;i ++) if(w[i] >= o) ans ++;
    cout<<ans<<"\n";
    return 0;
}