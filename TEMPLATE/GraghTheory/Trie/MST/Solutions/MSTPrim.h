#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
class MST
{
    /**
     * @author daydayUppp
     * @brief Minimum Spanning Tree (MST) Prim 算法
     * 图模型用 邻接表的形式来进行存储
     */
public:
    int n;
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