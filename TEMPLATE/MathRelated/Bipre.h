#include <bits/stdc++.h>
using namespace std;
template<class T1,class T2>
inline pair<T1,T2> operator+(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    pair<T1, T2> ret; ret.first = p1.first + p2.first; ret.second = p1.second + p2.second;
    return ret;
}
template<class T1,class T2>
inline pair<T1,T2> operator-(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    pair<T1, T2> ret; ret.first = p1.first - p2.first; ret.second = p1.second - p2.second;
    return ret;
}
template<class T1,class T2>
inline void operator+=(pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    p1.first += p2.first; p1.second += p2.second;
}
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