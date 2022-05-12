// 题目链接 : [P1894 [USACO4.2]完美的牛栏The Perfect Stall](https://www.luogu.com.cn/problem/P1894)
#include <bits/stdc++.h>
using namespace std;
class Hungarian {
    /*
       『定理一』: 最大匹配数 = 最小点覆盖数（这是 Konig 定理）
       『定理二』: 最大匹配数 = 顶点数 - 最大独立数
       『定理三』: 最小路径覆盖数 = 顶点数 - 最大匹配数
    */
    public:
        int* match;// match[i] = j : 节点 i 匹配 j
        bool* vi;// 标记是否访问
        int count;// 最大匹配数
        int n;// 顶点数
        queue<int> q;
        void Aug(vector<int>& pre,int v,int u) {
            // u 是找到的未匹配的点 v 是上一个点
            // 迭代更新路径上的信息
            while(true) {
                int t = match[v];// 找到上一个匹配点 v 的匹配点
                match[v] = u , match[u] = v;
                u = t;
                if(u == -1) return ;
                v = pre[u];
            }
        }
        void bfs(vector<vector<int>>& g) { // BFS 计算最大匹配
            bool flag;// 用于标记是否找到一条增广路
            vector<int> pre(n + 1,-1);// pre[i] = j , 表示一棵匈牙利树 i 节点的前驱节点是 j
            for(int i = 0;i <= n;i ++) {
                if(match[i] == -1) {
                    flag = false;
                    while(!q.empty()) q.pop();// 清空队列
                    memset(vi,false,n + 1);
                    q.push(i);
                    vi[i] = true;
                    while(!q.empty() && !flag) {
                        auto v = q.front(); q.pop();
                        for(auto& u : g[v]) {
                            if(vi[u]) continue;
                            vi[u] = true;
                            if(match[u] == -1) { // 非匹配点
                                flag = true;
                                count ++;// 匹配边 + 1
                                // 更新匹配的情况
                                Aug(pre,v,u);
                                break;
                            } else { // 匹配点
                                pre[u] = v;
                                q.push(match[u]);
                            }
                        }
                    }
                }
            }
        }
        bool dfs(vector<vector<int>>& g,int v) {
            // 从 v 出发 找一条增广路
            vi[v] = true;
            for(auto& u : g[v]) {
                if(vi[u]) continue;
                if(match[u] == -1) {
                    match[u] = v , match[v] = u;
                    count ++;// 匹配 + 1
                    return true;
                } else {
                    if(!vi[match[u]] && dfs(g,match[u])) {
                        // 相当于后面出现了增广路
                        match[u] = v , match[v] = u;
                        return true;
                    }
                }
            }
            return false;
        }
        void init_dfs(vector<vector<int>>& g) {
            for(int i = 0;i <= n;i ++) { // 枚举每一个未匹配点
                if(match[i] == -1) {
                    memset(vi,false,n + 1);
                    bool t = dfs(g,i);
                }
            }
        }
        Hungarian(vector<vector<int>>& g,int n_) {
            // para : n 为顶点数
            this->n = n_;
            match = new int[n + 1];
            for(int i = 0;i <= n;i ++) match[i] = -1;// 表示未匹配
            vi = new bool[n + 1];
            count = 0;// 匹配数为 0
            // init_dfs(g);
            bfs(g);
        }
        ~Hungarian() {
            delete []match;
            delete []vi;
        }
};
int main() {
    int n,a,b,c,m;
    cin >> n >> m;
    // 每一个牛棚的序号为 1 + n
    vector<vector<int>> g(n + m + 1);
    for(int i = 1;i <= n;i ++) {
        cin >> a;
        while(a --) {
            cin >> b;
            b += n;
            g[i].push_back(b);
            g[b].push_back(i);
        }
    }
    if(!n || !m) {
        cout<<"0\n";
        return 0;
    }
    Hungarian h(g,n + m);
    cout<<h.count<<"\n";
    return 0;
}


