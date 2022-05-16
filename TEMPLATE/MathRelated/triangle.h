#include <bits/stdc++.h>
using namespace std;
class Triangle {
    public:
        bool Is_Tri(int a,int b,int c) { // 以 a,b,c 为三条边的三角形是否存在
            /*
             * 方法 :
             * 找到最长边 判断剩余两个之和是否大于它
             *
             * 扩展 :
             * 对于给定两条边 a,b : a.length <= b.length
             * 那么当第三条边为最大边时 , 第三条边 c 的长度范围为 :
             * b.length <= c.length < a.length + b.length
             *
             * 那么给定一个可用的边长数组 arr[] , 那么求可以组成合法三角形的边组合方案数做法 :
             * 1. 枚举 a,b
             * 2. 二分 c
             * 整体的时间复杂度为 : O(logn*n^2)
             * */
            if(a > c) swap(a,c);
            if(b > c) swap(b,c);
            return a + b > c;
        }
        double Cal_area(vector<int>& A,vector<int>& B,vector<int>& C) { // 计算 三角形 面积
            /*
             * 利用行列式来计算面积 (同理对于四边形也可以拆分成两个三角形来计算) :
             *
             *           | x1 y1 1 |
             * S = 1/2 * | x2 y2 1 | = 1/2 * abs(x1*y2 + x2*y3 + x3*y1 - x1*y3 - x2*y1 - x3*y2)
             *           | x3 y3 1 |
             * */
            double res = 0;
            res = abs(
                    A[0] * B[1] + B[0] * C[1] + C[0] * A[1] - A[0] * C[1] - B[0] * A[1] - C[0] * B[1]
                    );
            return res/2.0;
        }
        Triangle() {
        }
        ~Triangle() {
        }
};
