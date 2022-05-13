// 题目链接 : 
// [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
// [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
// 对于 标准版 SPFA 会 STL
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class SPFA
{
public:
    LL* dis;
    bool* vi;
    int n,s;
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
class Dijkstra
{
    /**
     * @brief 加堆优化的 Dijkstra
     * 时间复杂度 : O(nlogn)
     */
public:
    LL* dis;
    bool* vi;
    int n,s;
    void Do(vector<vector<PII>>& g) {
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
int main() {
    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<PII>> g(n + 1);
    int a,b,c;
    for(int i = 0;i < m;i ++) {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
    }
    Dijkstra h(g,n,s);
    for(int i = 1;i <= n;i ++) {
        if(h.dis[i] == INF) cout<<INT_MAX<<" ";
        else cout<<h.dis[i]<<" ";
    }
    cout<<"\n";
    return 0;
}