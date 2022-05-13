// 题目链接 : [743. 网络延迟时间](https://leetcode.cn/problems/network-delay-time/)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class Floyd
{
    /**
     * @brief 多源点的最短路算法
     * 
     * 时间复杂度 : O(n^3)
     */
public:
    int n;
    vector<vector<LL>> dis;
    Floyd(vector<vector<int>>& es,int n_) {
        // para es : 边集
        // n_ : 顶点数
        this->n = n_;
        dis.resize(n + 1,vector<LL>(n + 1,INF));
        for(auto& i : es) {
            dis[i[0]][i[1]] = i[2];
        }
        // 松弛操作
        for(int i = 1;i <= n;i ++) {
            // 每一个点加入进行松弛
            for(int j = 1;j <= n;j ++) {
                for(int k = 1;k <= n;k ++) {
                    dis[j][k] = min(
                        dis[j][k] , dis[j][i] + dis[i][k]
                    );
                }
            }
        }
    }
};
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        Floyd h(times,n);
        LL res = 0;
        h.dis[k][k] = 0;
        for(int i = 1;i <= n;i ++) {
            res = max(res,h.dis[k][i]);
        }
        return res == INF ? -1 : res;
    }
};