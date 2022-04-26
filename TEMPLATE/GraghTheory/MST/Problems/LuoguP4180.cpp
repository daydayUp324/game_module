#include <bits/stdc++.h>
using namespace std;
// [非严格次小生成树](https://www.luogu.com.cn/problem/P4180)
template<typename T>
class SubSmallST
{
public:
    int* depth;// 深度数组 depth[i] 表示 节点 i 的深度
    int** dp;// dp[i][j] 表示 节点 i 的第 1 << j 的祖先节点 -1 表示没有
    T** ws1;// ws[i][j] 表示 节点 i 到第 1 << j 的祖先节点 的某一个性质 (此模板中为 路径的最大边)
    T** ws2;// ws2[i][j] 表示 节点 i 到第 1 << j 的祖先节点 路径的次大边
    T INF_FLAG;// 次小值 无 的标记
    int n;// 总结点数
    int maxF;// (1 << maxF) < n
    void dfs(vector<vector<vector<int>>>& g,int cur,int pre) {
        depth[cur] = depth[pre] + 1;
        dp[cur][0] = pre;
        for(auto& next : g[cur]) {
            if(next[0] == pre) continue;// 如果是无向图
            ws1[next[0]][0] = next[1] , ws2[next[0]][0] = INF_FLAG;
            dfs(g,next[0],cur);
        }
    }
    void Update(int& x,int i,int& a,int& b) {
        // 从节点 x 往上跳 i 更新 a
        if(ws1[x][i] != b) a = max(a,ws1[x][i]);
        else if(ws2[x][i] != b) a = max(a,ws2[x][i]);
        x = dp[x][i];
    }
    int calWS(int x,int y,int b) {// 每一次查询的时间复杂度 : O(logn)
        // 首先深度保持一致
        if(depth[x] < depth[y]) swap(x,y);
        // x 的深度更深
        int a = INF_FLAG;
        int k = depth[x] - depth[y];
        for(int i = 0;i < maxF;i ++) {
            if(k >> i & 1) Update(x,i,a,b);
        }
        if(x == y) return a;
        for(int i = maxF - 1;i >= 0;i --) {
            if(dp[x][i] != dp[y][i]) {
                Update(x,i,a,b); Update(y,i,a,b);
            }
        }
        // 还需要跳一步
        Update(x,0,a,b); Update(y,0,a,b);
        return a;
    }
    void init(vector<vector<vector<int>>>& g,int root) {
        maxF = 0; while((1 << maxF) <= n) maxF ++;// 确定最大层数
        for(int i = 0;i < n;i ++) {
            dp[i] = new int[maxF] , ws1[i] = new T[maxF] , ws2[i] = new T[maxF];
            // dp[i][0] = -1;
        }
        dp[0][0] = -1; dp[root][0] = -1;
        // 初始化 depth[] , 时间复杂度 : O(n)
        depth[0] = 0 , depth[root] = 1;
        for(auto& next : g[root]) {
            ws1[next[0]][0] = next[1];
            ws2[next[0]][0] = INF_FLAG;// 次大值 无则进行标记
            dfs(g,next[0],root);
        } 
        // 初始化 dp[][] , 时间复杂度 : O(maxF * n)
        T a,b,c,d;
        for(int j = 1;j < maxF;j ++) {
            // 枚举每一个节点
            for(int i = 0;i < n;i ++) {
                if(dp[i][j-1] == -1) dp[i][j] = -1;// 没有意义的情况
                else {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                    a = ws1[dp[i][j-1]][j-1];
                    b = ws1[i][j-1];
                    c = ws2[dp[i][j-1]][j-1];
                    d = ws2[i][j-1];
                    // a , b 为两端路中最大的数字
                    ws1[i][j] = max(a,b);
                    if(a != b) ws2[i][j] = max(min(a,b),max(c,d));
                    else { // 最大值相同 那么用两个的次大值
                        ws2[i][j] = max(c,d);
                    }
                } 
            }
        }
    }
    SubSmallST(int n_,T INF_FLAG_) {
        n = n_ , INF_FLAG = INF_FLAG_;
        depth = new int[n]; dp = new int*[n];
        ws1 = new T*[n]; ws2 = new T*[n];
    };
    ~SubSmallST() {
        delete []depth;
        delete []dp;
        delete []ws1;
        delete []ws2;
    }
};
struct edges {
    int a,b,v;
    bool f;
};
const int N = 3e5 + 7;
edges es[N];
int n,m,a,b,c;
int fa[100005];
int fp(int x) { return fa[x] < 0 ? x : fa[x] = fp(fa[x]); }
void unite(int x,int y) {
    x = fp(x) , y = fp(y); if(x == y) return ;
    if(fa[x] < fa[y]) swap(x,y);
    fa[x] += fa[y]; fa[y] = x;
}
long long Kruskal() {
    // edges = {{x,y,v}}
    for(int i = 0;i < n;i ++) fa[i] = -1;
    long long mini_v = 0;// 依情况而定
    sort(es,es + m,[](edges& a,edges& b) {
        return a.v < b.v;
    });
    int x,y;
    for(int i = 0;i < m;i ++) {
        x = es[i].a , y = es[i].b;
        if(fp(x) == fp(y)) {
            continue;
        } 
        es[i].f = 1;
        unite(x,y); mini_v += es[i].v;
    }
    return mini_v;
}
int main() {
    scanf("%d %d",&n,&m);
    vector<vector<vector<int>>> g(n + 1);
    for(int i = 0;i < m;i ++) {
        scanf("%d %d %d",&a,&b,&c);
        es[i] = {a,b,c,0};
    }
    long long o = Kruskal();
    long long res = 1e18;
    // cout<<"mini = "<<o<<"\n";
    for(int i = 0;i < m;i ++) {
        // 边集构图
        if(!es[i].f) continue;
        int x = es[i].a , y = es[i].b , v = es[i].v;
        g[x].push_back({y,v});
        g[y].push_back({x,v});
    }
    SubSmallST<int> hh(n + 1,0);
    hh.init(g,1);
    for(int i = 0;i < m;i ++) {
        // 尝试加入
        if(es[i].f) continue;
        int x = es[i].a , y = es[i].b , v = es[i].v;
        auto t = hh.calWS(x,y,v);
        res = min(res,o + (long long) v - t);// 用 v 来代替 t
    }
    printf("%lld\n",res);
    return 0;
}