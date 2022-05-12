// 题目链接 : [P1285 队员分组](https://www.luogu.com.cn/problem/P1285)
#include <bits/stdc++.h>
using namespace std;
int n;
bool vi[105];// dfs 的访问标记数组
bool es[105][105];// 初始图的邻接矩阵
int color[105];// 每一个点的颜色
vector<int> mp[105][2];// 存每一个连通块的对应位置的节点
bool dp[105][105];// dp[i][j] 表示 到 j 行时 , A 组容量为 i 是否可能
int path[105][105];// 0/1 背包的转移的路径方案
void Fail() {
    cout<<"No solution\n";
}
void Suc(int v,int m) {
    // 最终的容量是 v
    vector<int> A;
    vector<int> B;
    while(v) {
        if(!path[v][m]) {
            for(auto& i : mp[m][0]) A.push_back(i);
            for(auto& i : mp[m][1]) B.push_back(i);
            v -= mp[m][0].size();
        } else {
            for(auto& i : mp[m][1]) A.push_back(i);
            for(auto& i : mp[m][0]) B.push_back(i);
            v -= mp[m][1].size();
        }
        m --;
    }
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    cout<<A.size()<<" ";
    for(auto& i : A) cout<<i<<" ";
    cout<<"\n";
    cout<<B.size()<<" ";
    for(auto& i : B) cout<<i<<" ";
    cout<<"\n";
}
// 染色过程
bool dfs(vector<vector<int>>& g,int v,int c,const int& idx) {
    // c 是 color
    // 0 : A , 1 : B
    vi[v] = true; color[v] = c;
    mp[idx][c].push_back(v);
    for(auto& u : g[v]) {
        if(!vi[u]) {
            if(!dfs(g,u,c^1,idx)) return false;
        } else if(color[u] == color[v]) return false;// 矛盾了
    }
    return true;
}
int main() {
    int n,a,b,c;
    cin >> n;
    for(int i = 1;i <= n;i ++) {
        vi[i] = false;
        color[i] = -1;// 0 A , 1 B
        for(int j = 1;j <= n;j ++) {
            es[i][j] = false;
        }
    }
    vector<vector<int>> g(n + 1);// 无向图 , 如果有边相连表示两两并不是相互认识
    /*
    题目等价于 : 在 g 中将 点分为两类 , A , B
    A,B 中的点没有边相连
    */
    for(int i = 1;i <= n;i ++) {
        while(cin >> a && a) {
            es[i][a] = true;
        }
    }
    for(int i = 1;i <= n;i ++) {
        for(int j = i + 1;j <= n;j ++) {
            if(!es[i][j] || !es[j][i]) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    vector<vector<int>> h;// 存每一个连通块的 A,B 的个数
    for(int i = 1;i <= n;i ++) {
        if(vi[i]) continue;
        int idx = h.size();
        if(!dfs(g,i,0,idx)) {
            Fail(); return 0;
        }
        h.push_back({mp[idx][0].size() , mp[idx][1].size()});
    }
    // 现在相当于 h[] 中的每一个 first , second 进行分组
    // bool dp[105][105];// dp[i][j] 表示 到 j 行时 , A 组容量为 i 是否可能
    // h[i] = {x,y}
    for(int i = 0;i <= n;i ++) dp[i][0] = false;
    dp[h[0][0]][0] = true; path[h[0][0]][0] = 0;
    dp[h[0][1]][0] = true; path[h[0][1]][0] = 1;
    for(int j = 1;j < h.size();j ++) { // 枚举行
        int a,b;
        a = h[j][0] , b = h[j][1];
        for(int i = 0;i <= n;i ++) dp[i][j] = false;
        for(int i = min(a,b);i <= n;i ++) {
            if(i > a && dp[i - a][j - 1]) dp[i][j] = true , path[i][j] = 0;
            if(i > b && dp[i - b][j - 1]) dp[i][j] = true , path[i][j] = 1;
        }
    }
    for(int i = n / 2;i >= 0;i --) {
        if(dp[i][h.size() - 1]) {
            Suc(i,h.size() - 1); break;
        }
    }
    return 0;
}

