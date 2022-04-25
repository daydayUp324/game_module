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
        int mini_v = 0;// 依情况而定
        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int x,y;
        for(int i = 0;i < edges.size();i ++) {
            x = edges[i][0] , y = edges[i][1];
            if(fp(x) == fp(y)) continue;
            unite(x,y); mini_v += edges[i][2];
        }
        return mini_v;
    }
    int Prim(int root,vector<vector<int>>& g) {
        // g[x][y] = dis : x->y
        vector<int> dis(n,INT_MAX);
        vector<bool> visited(n,false);
        visited[root] = true; dis[root] = 0;
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
            if(minid == -1) return INT_MAX;// 此时说明不能生成一个树
            mini_v += minp;
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