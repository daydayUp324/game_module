/*
 * dfs 版本 : 时间复杂度 : O(n^4)
 * 
 * 1. 顶点序号从 1 开始
 * 2. 因为存在负权边 所以对于没有的边 , 设置边权为 : -INF
 *
 * 最大的权匹配值为 : sum{lx[i] + ly[i]} (标号和)
 * 匹配方案为 : match[i] = j , 表示 左部j 匹配右部 i
 * */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int N = 505;// 最大的节点个数
int match[N];// 右部的匹配数组
bool vix[N] , viy[N];// 左右部的访问数组
LL slack[N];// 松弛数组
LL lx[N] , ly[N];// 左右部的顶点序号
LL es[N][N];// 图的邻接矩阵形式
class KM {
    public:
        int n;// 两部图的左右部的顶点数
        bool dfs(int v) {
            vix[v] = true;
            for(int u = 1;u <= n;u ++) {
                // 枚举邻接点把符合的边加入
                if(!viy[u]) {
                    if(lx[v] + ly[u] == es[v][u]) {
                        viy[u] = true;
                        if(match[u] == -1 || dfs(match[u])) {
                            match[u] = v;
                            return true;
                        }
                    } else {
                        // 否则该点需要被 "松弛"
                        slack[u] = min(
                            slack[u] , lx[v] + ly[u] - es[v][u]
                        );
                    }
                }
            }
            return false;
        }
        void init() {
            // 首先初始化 lx[] 和 ly[]
            // lx[i] 为与之相连的边权的最大值 因为后续调整会变小
            for(int i = 1;i <= n;i ++) lx[i] = -INF , ly[i] = 0 , match[i] = -1;
            for(int i = 1;i <= n;i ++) {
                for(int j = 1;j <= n;j ++) {
                    lx[i] = max(lx[i],es[i][j]);
                }
            }
            for(int i = 1;i <= n;i ++) {
                // 从每一个点开始找增广路判断是否能形成完备匹配
                for(int j = 1;j <= n;j ++) slack[j] = INF;
                while(true) {
                    for(int j = 1;j <= n;j ++) {
                        // 初始化 vix[] viy[] slack[]
                        vix[j] = viy[j] = false;
                    }
                    if(dfs(i)) break;// 匹配成功
                    LL d = INF;
                    for(int j = 1;j <= n;j ++) {
                        if(!viy[j]) d = min(d,slack[j]);
                    }
                    // "松弛操作"
                    for(int j = 1;j <= n;j ++) {
                        if(vix[j]) lx[j] -= d;
                        if(viy[j]) ly[j] += d;
                    }
                }
            }
        }
        KM(int n_) {
            // para n,m : 左右部顶点数
            this->n = n_;
            init();
        }
};
