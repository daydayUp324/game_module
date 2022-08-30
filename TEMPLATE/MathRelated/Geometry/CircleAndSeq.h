#ifndef MyGeometry_h
#define MyGeometry_h
using namespace std;
const double EPS = 1e-8; // 精度范围
const double PI = 3.1415926; // π
#ifndef Seq_Cir_h
#define Seq_Cir_h
//
//  Seq.h 线段类
//  参考 :
//  [二维计算几何基础](https://oi-wiki.org/geometry/2d/)
//  [向量叉乘](https://www.cnblogs.com/tuyang1129/p/9390376.html)
//  [题目:蚂蚁爬行](https://leetcode.cn/contest/autox2023/problems/TcdlJS/)
//  Created by daydayUppp
template<typename T, typename LD> // TD 表示数据类型 double 或者 long long
class Seq {
public:
    T x1, y1, x2, y2;
    Seq() : x1(0), y1(0), x2(0), y2(0) {};
    Seq(T x1_, T y1_, T x2_, T y2_) : x1(x1_), y1(y1_), x2(x2_), y2(y2_) {};
    T get_maxX() const {
        return x1 > x2 ? x1 : x2;
    }
    T get_minX() const {
        return x1 < x2 ? x1 : x2;
    }
    T get_maxY() const {
        return y1 > y2 ? y1 : y2;
    }
    T get_minY() const {
        return y1 < y2 ? y1 : y2;
    }
    LD calCross(T a, T b, T c, T d) {
        // (a, b) x (c, d)
        return (LD) a * d - (LD) b * c;
    }
    bool is_intersect(const Seq<T, LD>& other) {
        // 判断两条线段是否相交
        // 主要分为两个阶段:
        // 1. 快速排斥
        // 判断在 x, y 轴上的投影是否有相交 如果没有则说明肯定不会相交
        if (this->get_maxX() < other.get_minX() ||
            this->get_minX() > other.get_maxX() ||
            this->get_maxY() < other.get_minY() ||
            this->get_minY() > other.get_maxY() ) return false;
        // 2. 跨立判断
        // 用叉乘来进行判断
        // 叉乘 (a, b) x (c, d) = a * d - b * c
        // AB x AD < 0 说明 AD 向量在向量 AB 的顺时针方向 否则就是逆时针方向
        // 如果两线段 a, b 相交则:
        // b 的两个端点一定分布在 a 的两端
        // a 的两个端点也一定分布在 b 的两端
        // 所以如果 (AB x AC) * (AB x AD) < 0 说明存在跨立现象
        // 由于共线但是不相交的情况也能通过跨立实验 所以还是需要先进行快速排斥
        // 向量 AB = (a, b)
        T a = this->x2 - this->x1, b = this->y2 - this->y1;
        // 向量 CD = (c, d)
        T c = other.x2 - other.x1, d = other.y2 - other.y1;
        LD v1 = this->calCross(a, b, other.x1 - this->x1, other.y1 - this->y1); // AB x AC
        LD v2 = this->calCross(a, b, other.x2 - this->x1, other.y2 - this->y1); // AB * AD
        if (v1 * v2 > 0) return false;
        LD v3 = this->calCross(c, d, this->x1 - other.x1, this->y1 - other.y1); // CD x CA
        LD v4 = this->calCross(c, d, this->x2 - other.x1, this->y2 - other.y1); // CD * CB
        if (v3 * v4 > 0) return false;
        return true; // 通过两个实验
    }
};

//  Circle.h 圆类
//  Created by daydayUppp
template<typename T, typename LD> // TD 表示数据类型 double 或者 long long
class Circle {
public:
    T x, y, r;
    Circle() : x(0), y(0), r(1) {};
    Circle(T x_, T y_, T r_) : x(x_), y(y_), r(r_) {};
    double Area() {
        // 计算圆的面积
        return PI * this->r * this->r;
    }
    bool is_intersects_hollow(const Circle<T, LD>& other) {
        // 判断两个空心圆是否相交 （仅判断外围是否有交点，包含的情况不算相交情况）
        T d_r = this->r + other.r;
        T d_x = this->x - other.x;
        T d_y = this->y - other.y;
        
        LD d_dis = (LD) d_x * d_x + (LD) d_y * d_y; // 两个圆心之间的距离平方
        
        if (d_dis > (LD) d_r * d_r) return false; // 两个圆不相交
        
        T max_r = max(this->r, other.r);
        T min_r = min(this->r, other.r);
        
        double d_c = sqrt(d_dis); // 两圆心之间的距离
        
        d_c += min_r;
        
        if (d_c + EPS < (double) max_r) return false;
        
        return true;
    }
    bool is_intersects_solid(const Circle<T, LD>& other) {
        // 判断两个实心圆是否相交 （包含的情况也算相交）
        T d_r = this->r + other.r;
        T d_x = this->x - other.x;
        T d_y = this->y - other.y;
        
        LD d_dis = (LD) d_x * d_x + (LD) d_y * d_y;
        
        if (d_dis > (LD) d_r * d_r) return false;
        
        return true;
    }
};

#endif /* Seq_Cir_h */
template<typename T, typename LD, typename U>
bool is_intersects_seqAndhollowCircle(const Seq<T, LD>& sq, const Circle<T, LD>& c) {
    // 判断空心圆 sq 和 线段 AB 是否相交
    // 此时为有点相交即为相交情况 (线段端点也包含其中)
    bool AinCir = true, BinCir = true;
    
    U d1 = (U) (sq.x1 - c.x) * (sq.x1 - c.x) + (U) (sq.y1 - c.y) * (sq.y1 - c.y);
    if (d1 < EPS) return true; // 点在圆上的情况
    d1 = sqrt(d1);
    if (d1 > c.r) AinCir = false; // 不在圆内
    
    U d2 = (U) (sq.x2 - c.x) * (sq.x2 - c.x) + (U) (sq.y2 - c.y) * (sq.y2 - c.y);
    if (d2 < EPS) return true; // 点在圆上的情况
    d2 = sqrt(d2);
    if (d2 > c.r) BinCir = false; // 不在圆内
    
    if (AinCir && BinCir) return false; // 都在圆内
    
    if ( (AinCir && !BinCir) || (BinCir && !AinCir)) return true; // 一个在内一个在外
    
    // 线段用 Ax + By + C = 0 来表示 -> (y1 - y2)x + (x2 - x1)y + x1*y2 - y1*x2 = 0
    
    U A, B, C, dis1, dis2;
    
    if (sq.x1 == sq.x2) {
        A = 1, B = 0, C = -sq.x1;
    } else if(sq.y1 == sq.y2) {
        A = 0, B = 1, C = -sq.y1;
    } else {
        A = sq.y1 - sq.y2;
        B = sq.x2 - sq.x1;
        C = (U) sq.x1 * sq.y2 - (U) sq.y1 * sq.x2;
    }
    
    // 圆心到线段的距离 d_cs = |Ax + By + C| / sqrt(A*A + B*B) <= 半径 r 才是相交
    
    dis1 = abs(A * c.x + B * c.y + C);
    dis2 = sqrt(A * A + B * B) * c.r;
    
    if (dis1 > dis2 + EPS) return false;
    
    // 然后判断 OAB 和 OBA 两个角是否是锐角 O 表示圆心
    // 可以用预先相似度来判断 : AO 点乘 AB = |OA| * |AB| * Cos<OA, AB>，点乘的正负和 cos<OA, AB> 相关
    
    double angle1 = (U) (c.x - sq.x1) * (sq.x2 - sq.x1) + (U) (c.y - sq.y1) * (sq.y2 - sq.y1); // AO 点乘 AB
    double angle2 = (U) (c.x - sq.x2) * (sq.x1 - sq.x2) + (U) (c.y - sq.y2) * (sq.y1 - sq.y2); // BO 点乘 BA
    
    if (angle1 > EPS && angle2 > EPS) return true; // 两个角为锐角说明存在相交
    
    return false;
}

#endif /* MyGeometry_h */
