#include<bits/stdc++.h>
using namespace std;
class Rect
{
    /**
     * @author : daydayUppp
     * @brief : 主要总结矩阵的相关性质 :
     *          1. 计算矩阵的相关信息
     *          2. 计算两个矩阵中间的相交部分面积
     *              - 可以用在 x 和 y 轴方向上的重叠大小来计算
     *              - 以 x 方向为例 : 
     *                1. 相交的矩阵部分的左边界肯定是两个矩阵左边界的最大值来决定的
     *                2. 相交的矩阵部分的右边界肯定是两个矩阵右边界的最小值来决定的
     */
public:
    int lx,ly,rx,ry;
    int Xoverlap(Rect& B) {// RectA 和 RectB 在 x 轴的相交片段
        return max(0 , min(this->rx,B.rx) - max(this->lx,B.lx) );
    }
    int Yoverlap(Rect& B) {// RectA 和 RectB 在 y 轴的相交片段
        return max(0 , min(this->ry,B.ry) - max(this->ly,B.ly) );
    }
    int area() {// 计算 RectA 面积
        return (rx - lx) * (ry - ly);
    }
    int intersect(Rect& B) {// 计算 RectA 和 RectB 相交的面积
        int ox = Xoverlap(B) , oy = Yoverlap(B);
        return ox * oy;
    }
    Rect() {}
    Rect(int lx_,int ly_,int rx_,int ry_) {
        lx = lx_ , ly_ = ly , rx = rx_ , ry = ry_;
    }
};