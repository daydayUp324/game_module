#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 2e5 + 7;
const int INF = 0x3f3f3f3f;
LL n,m,a,b;
class Solution {
public:
    vector<int> longestRepeating(string s, string p, vector<int>& q) {
        n = q.size();
        vector<int> res(n,0);
        if(n == 1) {
            for(int i = 0;i < n;i ++) res[i] = 1;
            return res;
        }
        m = s.size();
        multiset<int> mst;// 存每一个长度
        map<int,int> mp;// mp[r] = l;// 表示区间 [l:r]
        for(int i = 0;i < m;i ++) {
            int len = 1;
            int l = i;
            while(i + 1 < m && s[i + 1] == s[i]) len ++ , i++;
            mst.insert(len);
            mp[i] = l;
        }
        int idx = 0;
        for(auto& pos : q) {
            if(s[pos] == p[idx]) {// 不改变区间
                res[idx] = *mst.rbegin();
            } else {
                // 区间
                auto r = mp.lower_bound(pos)->first;// 找到 右端点
                // [l,r] 是对应的区间
                int l = mp[r];
                int len = r - l + 1;
                if(len == 1) {
                    mst.erase(mst.find(1));// 删除当前区间
                    if(pos && pos < n - 1) {
                        // 在中间的情况
                        // 等于左边和右边
                        if(p[idx] == s[pos + 1] && p[idx] == s[pos - 1]) {
                            auto rr = mp.lower_bound(pos + 1)->first;
                            mst.erase(mst.find(rr - mp[rr] + 1));
                            mst.erase(mst.find(r - mp[pos - 1]));
                            int t = mp[pos - 1];
                            mst.insert(rr - t + 1);
                            mp[rr] = t;
                            mp.erase(r);
                            mp.erase(r - 1);
                        }
                        // 等于左边
                        else if(p[idx] == s[pos - 1]) {
                            int t = mp[l -1];
                            mst.erase(mst.find(l - t));
                            mst.insert(l - t + 1);
                            mp.erase(l - 1);
                            mp[r] = t;
                        }
                        // 等于右边
                        else if(p[idx] == s[pos + 1]) {
                            mp.erase(r);
                            auto rr = mp.lower_bound(pos + 1)->first;

                            mst.erase(rr - mp[rr] + 1);
                            mst.insert(rr - r + 1);

                            mp[rr] = r;
                        }
                        // 都不是
                        else {
                            mp[r] = r;
                            mst.insert(1);
                        }
                    } else if(!pos) {
                        if(p[idx] == s[pos + 1]) {
                            mp.erase(r);
                            auto rr = mp.lower_bound(pos + 1)->first;

                            mst.erase(rr - mp[rr] + 1);
                            mst.insert(rr - r + 1);

                            mp[rr] = r;
                        } else {
                            mp[r] = r;
                            mst.insert(1);
                        }
                    } else if(pos == n - 1) {
                        if(p[idx] == s[pos - 1]) {
                            int t = mp[l -1];
                            mst.erase(mst.find(l - t));
                            mst.insert(l - t + 1);
                            mp.erase(l - 1);
                            mp[r] = t;
                        } else {
                            mp[r] = r;
                            mst.insert(1);
                        }
                    }
                    res[idx] = *mst.rbegin();
                    s[pos] = p[idx ++];
                    continue;
                }
                mst.erase(mst.find(len));// 删除当前区间
                if(pos > l && pos < r) {
                    // 区间分割
                    // [pos + 1,r]  [l,pos - 1] [pos,pos]
                    mp[r] = pos + 1;
                    mp[pos - 1] = l;
                    mp[pos] = pos;
                    mst.insert(r - pos);
                    mst.insert(pos - l);
                    mst.insert(1);
                } else if(pos == l) {
                    // 区间左端点
                    if(l) {
                        // 不是 0 端点 且和前面的一样
                        if(p[idx] == s[l - 1]) {
                            int t = mp[l -1];
                            mst.erase(mst.find(l - t));
                            mst.insert(l - t + 1);
                            mp.erase(l - 1);
                            mp[l] = t;
                            mp[r] = l + 1;
                            mst.insert(len - 1);
                        } else {
                            // 和前面不一样
                            mp[l] = l;
                            mst.insert(1);
                            mst.insert(len - 1);
                            mp[r] = l + 1;
                        }
                    } else {
                        mp[l] = l;
                        mst.insert(1);
                        mst.insert(len - 1);
                        mp[r] = l + 1;
                    }
                } else if(pos == r) {
                    // 不是最右端点
                    if(r != n - 1) {
                        // 不是 n - 1 端点 且和后面的一样
                        if(p[idx] == s[r + 1]) {
                            auto rr = mp.lower_bound(r + 1)->first;

                            mst.erase(rr - mp[rr] + 1);
                            mst.insert(rr - r + 1);

                            mp[rr] = r;

                            mst.insert(len - 1);
                            mp[r - 1] = l;
                        } else {
                            // 和后面不一样
                            mp[r] = r;
                            mst.insert(len - 1);
                            mst.insert(1);
                            mp[r - 1] = l;
                        }
                    } else {
                        mp[r] = r;
                        mst.insert(len - 1);
                        mst.insert(1);
                        mp[r - 1] = l;
                    }
                }
                res[idx] = *mst.rbegin();
            }
            s[pos] = p[idx ++];
        }
        return res;
    }
};
