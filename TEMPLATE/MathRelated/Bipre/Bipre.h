#include <bits/stdc++.h>
using namespace std;
template<typename BipreT>
class Bipre
{
    /**
     * @author daydayUppp
     * @brief core : sum[l][r] = sum[l][r-1] + sum[l-1][r] - sum[l-1][r-1] + g[l][r]
     * @attention
     * 1. 注意求和过后的数据范围
     * 2. 主要需要传入初始化为 "0" 的值
     */
public:
    BipreT** pre;// 记 pre[l][r] 表示 (0,0) -> (l-1,r-1) 的一个前缀和
    int n,m;// 长宽
    BipreT sumRegion(int r1, int c1, int r2, int c2) {
        // 返回 (r1,c1) 为左上角 (r2,c2) 为右下角 的子矩阵的和
        // 左上角一般不会有问题 对右下角做一个处理 (防止越界)
        r2 = min(r2,n-1) , c2 = min(c2,m-1);
        return pre[r2 + 1][c2 + 1] - pre[r1][c2 + 1] - pre[r2 + 1][c1] + pre[r1][c1];
    }
    Bipre(vector<vector<BipreT>>& g,const BipreT Init_v) {
        n = g.size() , m = g[0].size();
        pre = new BipreT*[n + 1];
        for(int i = 0;i <= n;i ++) pre[i] = new BipreT[m + 1];
        // 初始化 pre
        for(int i = 0;i <= n;i ++) pre[i][0] = Init_v;
        for(int j = 1;j <= m;j ++) pre[0][j] = Init_v;
        for(int i = 1;i <= n;i ++) {
            for(int j = 1;j <= m;j ++) {
                pre[i][j] = pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1] + g[i-1][j-1];
            }
        }
    }
    ~Bipre() {
        delete []pre;
    }
};