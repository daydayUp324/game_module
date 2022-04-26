#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
class MST
{
    /**
     * @author daydayUppp
     * @brief Minimum Spanning Tree (MST) Kruskal 算法
     * 图模型用 邻接表的形式来进行存储
     */
public:
    int n;
    vector<int> fa;
    int count;// 连通块的个数
    int fp(int x) { return fa[x] < 0 ? x : fa[x] = fp(fa[x]); }
    void unite(int x,int y) {
        x = fp(x) , y = fp(y); if(x == y) return ;
        if(fa[x] < fa[y]) swap(x,y);
        fa[x] += fa[y]; fa[y] = x;
    }
    int Kruskal(vector<vector<int>>& edges) {
        // edges = {{x,y,v}}
        fa.resize(n); count = n;// 初始每一个点单独为一个连通分量
        for(int i = 0;i < n;i ++) fa[i] = -1;
        int mini_v = 0;// 依情况而定
        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int x,y;
        for(int i = 0;i < edges.size();i ++) {
            x = edges[i][0] , y = edges[i][1];
            if(fp(x) == fp(y)) continue;
            unite(x,y); mini_v += edges[i][2]; count --;
        }
        if(count > 1) return INT_MAX;
        return mini_v;
    }
    MST(int n_) {
        n = n_;
    }
};