// 题目链接 : [1334. 阈值距离内邻居最少的城市](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class Floyd
{
    /**
     * @brief 多源点的最短路算法
     * 点序号从 1 开始
     * 时间复杂度 : O(n^3)
     */
public:
    int n;
    bool is_direct;// 是否是有向图
    vector<vector<LL>> dis;
    vector<vector<int>> path;
    void Print_path(int v,int u) {
        // 输出从 v->u 的最短路
        stack<PII> st;
        st.push({v,u});

        vector<int> res;
        res.push_back(-1);// 哨兵

        while(!st.empty()) {
            auto t = st.top(); st.pop();
            int u = t.first;
            int v = t.second;
            int p = path[t.first][t.second];
            if(p == -1) {
                // 说明 u->v 输出
                if(res.back() != u) res.push_back(u);
                if(res.back() != v) res.push_back(v);
            } else {
                st.push({p,v});
                st.push({u,p});
            }
        }
        // res[1:] 就是最后的路径
    }
    void CalPath(vector<vector<int>>& es) {
        // 需要输出路径
        dis.resize(n + 1,vector<LL>(n + 1,INF));
        path.resize(n + 1,vector<int>(n + 1,-1));
        for(auto& i : es) {
            dis[i[0]][i[1]] = i[2];
            path[i[0]][i[1]] = -1;
            if(!is_direct) {
                dis[i[1]][i[0]] = i[2];
                path[i[1]][i[0]] = -1;
            } 
        }
        for(int i = 1;i <= n;i ++) {
            // 每一个点加入进行松弛
            for(int j = 1;j <= n;j ++) {
                for(int k = 1;k <= n;k ++) {
                    if(j == k) continue;
                    if(dis[j][i] + dis[i][k] < dis[j][k]) {
                        dis[j][k] = dis[j][i] + dis[i][k];
                        path[j][k] = i;
                    }
                }
            }
        }
    }
    void CalDis(vector<vector<int>>& es) {
        // 只需要计算最短路
        dis.resize(n + 1,vector<LL>(n + 1,INF));
        for(auto& i : es) {
            dis[i[0]][i[1]] = i[2];
            if(!is_direct) dis[i[1]][i[0]] = i[2];
        }
        for(int i = 1;i <= n;i ++) {
            // 每一个点加入进行松弛
            for(int j = 1;j <= n;j ++) {
                for(int k = 1;k <= n;k ++) {
                    if(j == k) continue;
                    dis[j][k] = min(
                        dis[j][k] , dis[j][i] + dis[i][k]
                    );
                }
            }
        }
    }
    Floyd(vector<vector<int>>& es,int n_,bool is_direct_) {
        // para es : 边集
        // n_ : 顶点数
        // is_direct : 是否是有向图
        this->n = n_;
        this->is_direct = is_direct_;
        CalDis(es);
        // CalPath(es);
    }
};
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        for(auto& e : edges) e[0] ++ , e[1] ++;
        Floyd h(edges,n,false);
        int res = 0;
        int o = 1e9;
        for(int i = n;i;i --) {
            int a = 0;
            for(int j = 1;j <= n;j ++) {
                if(h.dis[i][j] <= distanceThreshold) a ++;
            }
            if(a < o) o = a , res = i; 
        }
        return res - 1;
    }
};