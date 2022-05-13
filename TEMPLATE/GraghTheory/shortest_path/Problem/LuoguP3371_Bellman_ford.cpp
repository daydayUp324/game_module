// 题目链接 : 
// [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
// [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
using PII = pair<LL,int>;
const LL INF = 0x3f3f3f3f3f3f3f3f;
class Bellman_ford
{
    /**
     * @brief 弱化版 SPFA 可以判负环
     * 顶点序号从 1 开始
     * 时间复杂度 : O(VE)
     */
public:
    int n,s;
    LL* dis;
    bool Do(vector<vector<int>>& g) {
        dis[s] = 0;
        for(int i = 1;i <= n;i ++) {
            bool ok = true;
            for(auto& e : g) {
                // 枚举每一条边
                if(dis[e[1]] > dis[e[0]] + e[2]) {
                    dis[e[1]] = dis[e[0]] + e[2];
                    ok = false;
                }
            }
            if(ok) break;
        }
        for(auto& e : g) {
            if(dis[e[1]] > dis[e[0]] + e[2]) {
                return false;// 存在负权环
            }
        }
        return true;
    }
    Bellman_ford(vector<vector<int>>& g,int n_,int start_) {
        // para g : 图模型 g[i] = {...{x,y,v}} 表示 x->y 有一条 v  的边
        // n_ : 顶点数 , start_ : 起始源点
        this->n = n_ , this->s = start_;
        dis = new LL[n + 1];
        for(int i = 0;i <= n;i ++) {
            dis[i] = INF;// INF 表示不可达
        }
        Do(g);
    }
    ~Bellman_ford() {
        delete []dis;
    }
};
int main() {
    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<int>> g;
    int a,b,c;
    for(int i = 0;i < m;i ++) {
        cin >> a >> b >> c;
        g.push_back({a,b,c});
    }
    Bellman_ford h(g,n,s);
    for(int i = 1;i <= n;i ++) {
        if(h.dis[i] == INF) cout<<INT_MAX<<" ";
        else cout<<h.dis[i]<<" ";
    }
    cout<<"\n";
    return 0;
}