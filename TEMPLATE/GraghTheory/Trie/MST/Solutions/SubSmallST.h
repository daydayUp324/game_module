#include <bits/stdc++.h>
using namespace std;
// 非严格次小生成树
template<typename T>
class SubSmallST
{
public:
    int* depth;// 深度数组 depth[i] 表示 节点 i 的深度
    int** dp;// dp[i][j] 表示 节点 i 的第 1 << j 的祖先节点 -1 表示没有
    T** ws;// ws[i][j] 表示 节点 i 到第 1 << j 的祖先节点 的某一个性质 (此模板中为 路径的最大边)
    T INF_FLAG;
    int n;// 总结点数
    int maxF;// (1 << maxF) < n
    void dfs(vector<vector<vector<int>>>& g,int cur,int pre) {
        depth[cur] = depth[pre] + 1;
        dp[cur][0] = pre;
        for(auto& next : g[cur]) {
            if(next[0] == pre) continue;// 如果是无向图
            ws[next[0]][0] = next[1];
            dfs(g,next[0],cur);
        }
    }
    T calWS(int x,int y) {// 每一次查询的时间复杂度 : O(logn)
        // 首先深度保持一致
        if(depth[x] < depth[y]) swap(x,y);
        // x 的深度更深
        T res = 0;// 返回路径中的最大值
        int k = depth[x] - depth[y];
        for(int i = 0;i < maxF;i ++) {
            if(k >> i & 1) {
                res = max(res,ws[x][i]);
                x = dp[x][i];
            }
        }
        if(x == y) return res;
        for(int i = maxF - 1;i >= 0;i --) {
            if(dp[x][i] != dp[y][i]) {
                res = max(res,max(ws[x][i],ws[y][i]));
                x = dp[x][i] , y = dp[y][i];
            }
        }
        res = max(res,max(ws[x][0],ws[y][0]));
        return res;
    }
    void init(vector<vector<vector<int>>>& g,int root,T INF_FLAG_) {
        depth = new int[n + 1];
        dp = new int*[n + 1];
        ws = new T*[n + 1];
        INF_FLAG = INF_FLAG_;
        maxF = 0; while((1 << maxF) <= n) maxF ++;// 确定最大层数
        for(int i = 0;i <= n;i ++) dp[i] = new int[maxF] , ws[i] = new T[maxF];
        // 初始化 depth[] , 时间复杂度 : O(n)
        depth[root] = 0;
        for(auto& next : g[root]) {
            ws[next[0]][0] = next[1];
            dfs(g,next[0],root);
        } 
        // 初始化 dp[][] , 时间复杂度 : O(maxF * n)
        dp[0][0] = -1;// 如果 0 不是节点
        dp[root][0] = -1;
        for(int j = 1;j < maxF;j ++) {
            // 枚举每一个节点
            for(int i = 0;i < n;i ++) {
                if(dp[i][j-1] == -1) dp[i][j] = -1;
                else dp[i][j] = dp[dp[i][j - 1]][j - 1] , ws[i][j] = max(ws[i][j-1],ws[dp[i][j-1]][j-1]);
            }
        }
    }
    SubSmallST(int n_) {
        n = n_;
    };
    ~SubSmallST() {
        delete []depth;
        delete []dp;
        delete []ws;
    }
};