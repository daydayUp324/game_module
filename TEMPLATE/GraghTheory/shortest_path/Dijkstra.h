#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class Dijkstra
{
    /**
     * @brief 加堆优化的 Dijkstra
     * 顶点序号都从 1 开始
     * 时间复杂度 : O(nlogn)
     */
public:
    LL* dis;
    bool* vi;
    vector<int> path;
    int n,s;
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
        priority_queue<PII,vector<PII>,greater<PII>> q;
        q.push({0,s});
        int u;
        LL v;
        while(!q.empty()) {
            auto t = q.top(); q.pop();
            u = t.second , v = t.first;
            if(vi[u]) continue;// 冗余点
            vi[u] = true;
            for(auto& next : g[u]) {
                if(!vi[next.first] && dis[next.first] > v + next.second) {
                    dis[next.first] = v + next.second;
                    path[next.first] = v;// 路径标识
                    q.push({dis[next.first],next.first});
                }
            }
        }
    }
    void Do(vector<vector<PII>>& g) {
        dis[s] = 0;
        priority_queue<PII,vector<PII>,greater<PII>> q;
        q.push({0,s});// {val,node}
        int u;
        LL v;
        while(!q.empty()) {
            auto t = q.top(); q.pop();
            u = t.second , v = t.first;// (u,v) -> (node,vals)
            if(vi[u]) continue;// 冗余点
            vi[u] = true;
            for(auto& next : g[u]) {
                if(!vi[next.first] && dis[next.first] > v + next.second) {
                    dis[next.first] = v + next.second;
                    q.push({dis[next.first],next.first});
                }
            }
        }
    }
    Dijkstra(vector<vector<PII>>& g,int n_,int start_) {
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
    ~Dijkstra() {
        delete []dis;
        delete []vi;
    }
};