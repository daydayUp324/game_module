#include <bits/stdc++.h>
using namespace std;
#ifndef __DIJKSTRA__H_
#define __DIJKSTRA__H_
class Dijkstra {
public:
    /**
     * @brief 堆优化的 Dijkstra
     * 顶点序号从 0 开始
     * 时间复杂度 : O(nlogn)
     * 使用说明 : 
     * 1. 构造函数传入邻接图 g[i] = {{node, val}}
     */
    vector<long long> dis;
    vector<bool> vi;
    vector<vector<pair<int, int>>>& g; // g[i] = {{ne, v}}，边 i->ne 的距离为 v
    int n; // 顶点数
    void Cal_shortestPath(int start, int INF = 0x3f3f3f3f) { // 从 start 开始跑最短路
        dis.resize(n, INF); // 设置为最大值
        vi.resize(n, false);
        dis[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        q.push({0, start}); // {val,node}
        int u;
        long long v;
        while (!q.empty()) {
            auto t = q.top(); q.pop();
            u = t.second , v = t.first;// (u,v) -> (node,vals)
            if (vi[u]) continue;// 冗余点
            vi[u] = true;
            for (auto& next : g[u]) {
                int vv = next.second; // 改边的权值
                if (!vi[next.first] && dis[next.first] > v + vv) { // 松弛操作
                    dis[next.first] = v + vv;
                    q.push({dis[next.first], next.first});
                }
            }
        }
    }
    Dijkstra(vector<vector<pair<int, int>>>& g_) : g(g_) {
        n = g.size();
    }
};
#endif