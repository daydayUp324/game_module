#include <bits/stdc++.h>
using namespace std;
/*
 * 参考链接 : [Even–odd rule](https://en.m.wikipedia.org/wiki/Even-odd_rule)
 * para :
 * 1. 给定点 P(x,y)
 * 2. 给定多边形 {(x0,y0),...,(xn,yn)}
 * 当点P 在多边形上或者在多边形内部时，返回 True 否则返回 False
 * */

const double EPS = 1e-15;
class Solution {
public:
    bool f(double a,double b) { // 判断 a,b 是否相等 (浮点数的判断)
        return a > b - EPS && a < b + EPS;
    }
    bool isPointInPolygon(double x, double y, vector<double>& s) {
        // s 是多边形的各个点的集合 {x0,y0,x1,y1....xn,yn} 其中 x0 = xn , y0 = yn
        vector<vector<double>> poly;
        for(int i = 0;i < s.size();i += 2) {
            poly.push_back({s[i],s[i + 1]});
        }
        int num = poly.size();
        int j = num - 1;
        bool c = false;
        for(int i = 0;i < num;i ++) {
            if(f(x,poly[i][0]) && f(y,poly[i][1])) return true;// 在 corner 上
            if((poly[i][1] > y) != (poly[j][1] > y)) {
                double slope = (x - poly[i][0]) * (poly[j][1] - poly[i][1]) - (poly[j][0] - poly[i][0]) * (y - poly[i][1]);
                if(fabs(slope) < EPS) return true;// 在边界上
                if((slope < 0) != (poly[j][1] < poly[i][1])) {
                    if(c) c = false;
                    else c = true;
                }
            }
            j = i;
        }
        return c;
    }
};
