#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class SPFA
{
    /**
     * @brief Bellamn_ford 的优化版
     * g : 邻接表的形似给出
     * 顶点序号从 1 开始
     */
public:
    LL* dis;
    bool* vi;
    int n,s;
    vector<int> path;
    void Print_path(int v) {
        // 从 s->v 的最短路径
        vector<int> res;
        while(v) {
            res.push_back(v);
            v = path[v];
        }
        // res[] : {}  从 v->s 的一条最短路径
    }
    void Cal_path(vector<vector<PII>>& g) {
        path.resize(n + 1,0);
        path[s] = 0;
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        int u;
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            vi[u] = false;
            auto v = dis[u];
            for(auto& next : g[u]) {
                if(dis[next.first] > v + next.second) {
                    dis[next.first] = v + next.second;
                    path[next.first] = u;// 路径标识
                    if(!vi[next.first]) q.push(next.first);
                }
            }
        }
    }
    void Do(vector<vector<PII>>& g) {
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        int u;
        while(!q.empty()) {
            auto u = q.front(); q.pop();
            vi[u] = false;
            auto v = dis[u];
            for(auto& next : g[u]) {
                if(dis[next.first] > v + next.second) {
                    dis[next.first] = v + next.second;
                    if(!vi[next.first]) q.push(next.first);
                }
            }
        }
    }
    SPFA(vector<vector<PII>>& g,int n_,int start_) {
        // para g : 图模型 g[i] = {...{u,v}} 表示 i->u 有一条 v  的边
        // n_ : 顶点数 , start_ : 起始源点
        this->n = n_ , this->s = start_;
        dis = new LL[n + 1];
        vi = new bool[n + 1];
        for(int i = 0;i <= n;i ++) {
            dis[i] = INF;// INF 表示不可达
            vi[i] = false;
        }
        Do(g);
    }
    ~SPFA() {
        delete []dis;
        delete []vi;
    }
};