#include <bits/stdc++.h>
using namespace std;
class LCA
{
    /**
     * @author : daydayUppp
     * @brief :
     * 1. 针对树模型 (有向图/无向图 , 节点idx 在 [0,n) 之间)
     * 2. 倍增法 来求树中的两个点 x,y 的最近公共祖先 (Least Common Ancestors)
     * 3. 倍增法 来求某一个节点的 Kth 祖先 如果没有的话就返回 -1
     */
public:
    vector<int> depth; // depth[i] 表示 节点 i 的深度，其中 depth[root] = 0
    vector<vector<int>> dp; // dp[i][j] 表示 节点 i 的第 1 << j 的祖先节点 -1 表示没有
    int n, maxF;// 总结点数 n，以及 (1 << maxF) < n
    void dfs(vector<vector<int>>& g, int cur, int pre) { // 初始化 dp[cur][0] 与 depth[cur]
        depth[cur] = depth[pre] + 1;
        dp[cur][0] = pre;
        for (auto& next : g[cur]) {
            if (next == pre) continue; // 无向图情况
            dfs(g, next, cur);
        }
    }
    int findKthAncestor(int x, int k) { // 计算节点 x 的往上 k 祖先节点
        // 时间复杂度 : O(logn)
        // 把 k 的二进制位的距离全部跳掉
        for (int i = 0; i < maxF && x != -1; i ++) {
            if (k >> i & 1) {
                x = dp[x][i];
            }
        }
        return x;
    }
    int calLCA(int x, int y) { // 计算节点 x, y 的最近公共祖先
        // 时间复杂度 : O(logn)
        if (depth[x] < depth[y]) { 
            swap(x,y);
        } 
        x = findKthAncestor(x, depth[x] - depth[y]); // 深度保持一致
        if (x == y) {
            return x;
        } 
        // 假设公共祖先和他们的距离为 D
        // 那么 x,y 任何往上跳 dis < D 的距离都不会跳到相同的位置
        // 所以 x,y 把 D - 1 的全部二进制位上的 1 都跳了
        // 就会跳到距离公共祖先相差距离 1 的位置
        for (int i = maxF - 1; i >= 0; i --) { // 从最大的层数开始往上进行判断
            if (dp[x][i] != dp[y][i]) x = dp[x][i] , y = dp[y][i];
        }
        return dp[x][0];
    }
    LCA(vector<vector<int>>& g, int root) : n(g.size()) {
        // 节点序号从 0 开始，若要从 1 开始则 resize(n + 1)
        maxF = 0; while((1 << maxF) <= n) maxF ++;// 确定最大层数
        depth.resize(n, 0);
        dp.resize(n, vector<int>(maxF, -1));
        // 初始化 depth[] , 时间复杂度 : O(n)
        for(auto& next : g[root]) dfs(g,next,root);
        // 初始化 dp[][] , 时间复杂度 : O(maxF * n)
        dp[root][0] = -1;
        for (int j = 1; j < maxF; j ++) { // 计算每一个节点 i 的 1 << j 祖先节点 dp[i][j] = dp[dp[i][j - 1]][j - 1]
            for (int i = 0; i < n; i ++) {
                if (dp[i][j-1] == -1) {
                    dp[i][j] = -1;
                } else {
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                } 
            }
        }
    };
};