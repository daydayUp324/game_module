#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
class RangeModule_Point
{
    /***
     * @author : daydayUppp
     * 适用范围 : 
     * 1. 每一段小区间左右端点合并在一起是一段完整的区间
     * 2. 单点更新
     * 
     * 题目链接 : [6030. 由单个字符重复的最长子字符串](https://leetcode-cn.com/problems/longest-substring-of-one-repeating-character/submissions/)
    */
private:
    multiset<int> mst;// 每一段区间长度
    map<int,PII> mp;// mp[r] = {l,quality}
    int l_,r_;// 总区间的范围 [l_,r_]
public:
    void erase(int r) {// 删除端点 r 的区间
        mst.erase(mst.find(r - mp[r].first + 1)) , mp.erase(r);
    }
    void add(int l,int r,int q) {// 加入区间 [l:r]
        if(r < l) return ;
        mst.insert(r - l + 1) , mp[r] = {l,q};
    }
    int getMaxRLen() {// 返回区间的最大长度
        return *mst.rbegin();
    }
    int findR(int pos) {// 得到 pos 的所属区间的右端点
        return mp.lower_bound(pos)->first;
    }
    int getQ(int pos) {// 获得位置 pos 的性质
        return mp.lower_bound(pos)->second.second;
    }
    void update(int pos,int nq) {// 将位置 pos 的属性改为 nq
        // 需要判断 pos 在所属区间 [l:r]
        int r = findR(pos) , l = mp[r].first , q = mp[r].second;
        if(q == nq) return ;// 该点的属性不变
        // 然后判断 pos 在 [l:r] 的方位

        if(r == l && l > l_ && l < r_ && mp[l - 1].second == nq) {// 取左右两个区间判断是否能合并
            auto rr = findR(r + 1);// 右边的区间的右端点
            if(mp[rr].second == nq) {
                // [mp[l-1].first,l-1] + [l,r] + [r+1,rr] -> [mp[l-1].first,rr]
                int ll = mp[l-1].first;
                erase(l-1) , erase(r) , erase(rr);
                add(ll,rr,nq);
                return ;
            }
        }
        if(pos > l && pos < r) {
            // [l,r] -> [l,pos - 1] [pos,pos] [pos + 1,r] 前后两个区间的属性不变
            erase(r) , add(l,pos - 1,q) , add(pos,pos,nq) , add(pos + 1,r,q);
            return ;
        }
        if(pos == l) {
            // 判断是否和左边的区间属性相同
            if(pos == l_) {// 已经是最左边的区间了
                // [l,r] -> [l,l] + [l + 1,r] 
                erase(r);
                add(l,l,nq) , add(l + 1,r,q);
            } else {
                if(mp[l-1].second == nq) {
                    // [mp[l-1].first,l-1] + [l:r] -> [mp[l-1].first,l] + [l+1,r]
                    int ll = mp[l - 1].first;
                    erase(r) , erase(l - 1);
                    add(ll,l,nq) , add(l + 1,r,q);
                    return ;
                } else {
                    // [l,r] -> [l,l] + [l + 1,r] 
                    erase(r);
                    add(l,l,nq) , add(l + 1,r,q);
                }
            }
        }
        if(pos == r) {
            // 判断是否和右边的区间属性相同
            if(r == r_) {// 已经是最右边的区间
                // [l,r] -> [l,r - 1] + [r,r] 
                erase(r);
                add(r,r,nq) , add(l,r - 1,q);
            } else {
                int rr = findR(r + 1);
                if(mp[rr].second == nq) {
                    // [l,r] + [mp[rr].first,rr] -> [l,r - 1] + [r,rr]
                    erase(r) , erase(rr);
                    add(l,r - 1,q) , add(r,rr,nq);
                } else {
                    // [l,r] -> [l,r - 1] + [r,r] 
                    erase(r);
                    add(r,r,nq) , add(l,r - 1,q);
                }
            }
        }
    }
    RangeModule_Point(int _l,int _r) {
        l_ = _l , r_ = _r;
    };
};
