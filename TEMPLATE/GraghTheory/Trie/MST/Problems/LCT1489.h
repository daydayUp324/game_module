// 相关题目 : 
// [1489. 找到最小生成树里的关键边和伪关键边](https://leetcode-cn.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)
#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
class MST
{
    /**
     * @author daydayUppp
     * @brief Minimum Spanning Tree (MST)
     * 图模型用 邻接表的形式来进行存储
     */
public:
    int n;
    vector<int> fa;
    int count;// 连通块的个数
    int fp(int x) { return fa[x] < 0 ? x : fa[x] = fp(fa[x]); }
    void unite(int x,int y) {
        x = fp(x) , y = fp(y);
        if(x == y) return ;
        if(fa[x] < fa[y]) swap(x,y);
        fa[x] += fa[y]; fa[y] = x;
    }
    int Kruskal(vector<vector<int>>& edges,int erase_e,int add_e) {
        // edges = {{x,y,v}}
        fa.resize(n); count = n;// 初始每一个点单独为一个连通分量
        for(int i = 0;i < n;i ++) fa[i] = -1;
        int mini_v = 0;// 依情况而定
        if(add_e != -1) unite(edges[add_e][0],edges[add_e][1]) , mini_v += edges[add_e][2] , count --;
        int x,y;
        for(int i = 0;i < edges.size();i ++) {
            if(i == erase_e) continue;
            x = edges[i][0] , y = edges[i][1];
            if(fp(x) == fp(y)) continue;
            unite(x,y); mini_v += edges[i][2]; count --;
        }
        if(count > 1) return INT_MAX;
        return mini_v;
    }
    MST(int n_) {
        n = n_;
    }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> res(2);
        MST h(n);
        for(int i = 0;i < edges.size();i ++) {
            edges[i].push_back(i);// 加入边的序号
        }
        // 按照边权排序
        sort(edges.begin(),edges.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        int o = h.Kruskal(edges,-1,-1);
        for(int i = 0;i < edges.size();i ++) {
            // 每次删除一条边 看最后的权重和是否 < o 来判断是否是关键边
            // 每次刚开始就加入该边来判断是否是生成树边
            // 如果不是生成树边那么最后的权重一定是比 o 要大的
            int t = h.Kruskal(edges,i,-1);
            if(t > o) res[0].push_back(edges[i][3]);
            else {
                t = h.Kruskal(edges,-1,i);
                if(t == o) res[1].push_back(edges[i][3]);
            } 
        }
        return res;
    }
};