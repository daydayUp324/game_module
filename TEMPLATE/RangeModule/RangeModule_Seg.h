#include <bits/stdc++.h>
using PII = pair<int,int>;
class RangeModule_Seg
{
    /***
     * 适用范围 : 
     * 1. 用于区间 [l:r] 的 add 和 remove 
     * 2. 区间管理
     * 
     * 题目链接 : [715. Range 模块](https://leetcode-cn.com/problems/range-module/)
    */
private:
    multiset<int> mst;// 每一段区间长度
    map<int,int> mp;// mp[r] = l 存储每一段区间
public:
    void erase(int l,int r) {// 删除 [l:r] 的区间
        // 
    }
    void add(int l,int r) {// 加入区间 [l:r]
        if(r < l) return ;
        mst.insert(r - l + 1) , mp[r] = {l,q};
    }
    int getMaxRLen() {// 返回区间的最大值
        return *mst.rbegin();
    }
    int getRange(int pos) {// 得到 pos 的所属区间的右端点
        return mp.lower_bound(pos)->first;
    }
    RangeModule_Seg() {};
};