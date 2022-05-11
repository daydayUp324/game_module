/*
 * bfs 版本 : 时间复杂度 : O(n^3)
 * 
 * 1. 顶点序号从 1 开始
 * 2. 因为存在负权边 所以对于没有的边 , 设置边权为 : -INF
 *
 * 针对 DFS 的改进 , 因为每一次都失败后都需要从头广增 所以开销会比较大
 * 所以改进为 BFS 版本
 *
 * 最大的权匹配值为 : sum{lx[i] + ly[i]} (标号和)
 * 匹配方案为 : match[i] = j , 表示 左部j 匹配右部 i
 * */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int N = 505;// 最大的节点个数
int matchy[N];// 右部的匹配数组
int matchx[N];// 左部的匹配数组
bool vix[N] , viy[N];// 左右部的访问数组
LL slack[N];// 松弛数组
LL lx[N] , ly[N];// 左右部的顶点序号
LL es[N][N];// 图的邻接矩阵形式
int pre[N];// pre[i] = j , 表示右部节点 i 的前驱节点为 左部节点 j
class KM {
    public:
        int n;// 两部图的左右部的顶点数
        void Aug(int v) {
            // v 是新增的点
            // v 的前驱是 pre[v]
            while(v != -1) {
                int u = pre[v];
                int t = matchx[u];// 本身 u 的匹配点 -1 表示到了根节点
                matchx[u] = v , matchy[v] = u;
                v = t;
            }
        }
        void bfs(int v) {
            // 从 v 开始往下 BFS 来查找增广路
            for(int i = 1;i <= n;i ++) vix[i] = viy[i] = false , slack[i] = INF;
            queue<int> q;
            q.push(v);
            while(true) {
                // 一直找到增广路为止
                // 因为 BFS 核心在于每一条边访问一次
                // 所以当 lx[t] + ly[i] - es[t][i] < slack[i] 时
                // 用于判断该条边可以加入 和 确定 pre[]
                while(!q.empty()) {
                    int t = q.front(); q.pop();
                    // 找 t 的一个增广路
                    vix[t] = true;
                    for(int i = 1;i <= n;i ++) {
                        if(!viy[i]) {
                            if(lx[t] + ly[i] - es[t][i] < slack[i]) {
                                slack[i] = lx[t] + ly[i] - es[t][i];
                                pre[i] = t;// 可能的前驱
                                if(slack[i] == 0) { // 该边加入
                                    viy[i] = true;
                                    if(matchy[i] == -1) { // 找到一条增广路
                                        Aug(i); return ;// 直接返回
                                    } else { // 否则从 match[i] 继续往下
                                        q.push(matchy[i]);
                                    }
                                }
                            }
                        }
                    }
                }
                // 否则说明队列为空了 且没有找到增广路 说明需要更新 slack[] 了
                LL d = INF;
                for(int i = 1;i <= n;i ++) if(!viy[i]) d = min(d,slack[i]);
                for(int i = 1;i <= n;i ++) {
                    if(vix[i]) lx[i] -= d;
                    if(viy[i]) ly[i] += d;
                    else slack[i] -= d;// 需要减 , 因为后续需要需要用 slack[] 来加入新的点
                }
                for(int i = 1;i <= n;i ++) {
                    if(!viy[i] && !slack[i]) {
                        viy[i] = true;
                        if(matchy[i] == -1) {
                            // 找到增广路了 这是比 DFS 快的核心 不用从头进行
                            Aug(i); return ;
                        } else {
                            q.push(matchy[i]);// 加入它的匹配点继续往下匹配
                        }
                    }
                }
            }
        }
        void init() {
            // 首先初始化 lx[] 和 ly[]
            // lx[i] 为与之相连的边权的最大值 因为后续调整会变小
            for(int i = 1;i <= n;i ++) lx[i] = -INF , ly[i] = 0 , matchx[i] = matchy[i] = -1;
            for(int i = 1;i <= n;i ++) {
                for(int j = 1;j <= n;j ++) {
                    lx[i] = max(lx[i],es[i][j]);
                }
            }
            for(int i = 1;i <= n;i ++) {
                bfs(i);
            }
        }
        KM(int n_) {
            // para n,m : 左右部顶点数
            this->n = n_;
            init();
        }
};
