// 题目链接 : [剑指 Offer 51. 数组中的逆序对](https://leetcode.cn/problems/shu-zu-zhong-de-ni-xu-dui-lcof/)
#include <bits/stdc++.h>
using namespace std;
template<typename T>
class BIT_v {
    /**
     * @author daydayUp
     * @brief 树状数组求逆序对
     */
    public:
        int n,m;// n 为 nums[] 的大小 , m 为 mp[] 的大小
        T* tree;
        vector<int>& nums;
        vector<int> mp;// 大小映射
        int lowbit(int x) { return x & (-x); }
        int getIndex(int target) {
            return lower_bound(mp.begin(),mp.begin() + m,target) - mp.begin();
        }
        void update(int index) {
            // 更新 arr[index] -> 负责的节点为 tree[index]
            while(index < n) {
                tree[index] ++;
                index += lowbit(index);
            }
        }
        T query(int index) {
            // 查询 [1:index]
            T res = 0;
            while(index) {
                res += tree[index];
                index -= lowbit(index);
            }
            return res;
        }
        T countInversions(int left,int right) { // 计算 nums[left:right] 中的逆序对情况
            T res = 0;
            for(int i = left;i <= right;i ++) {
                int idx = getIndex(nums[i]) + 1;
                update(idx);
                res += i - left + 1 - query(idx);
            }
            return res;
        }
        BIT_v(vector<int>& nums_) : nums(nums_) {
            n = nums.size() + 1;// 因为假定下标从 1 开始
            tree = new T[n];
            memset(tree,0,sizeof(T) * n);
            mp = nums;
            sort(mp.begin(),mp.end());
            m = unique(mp.begin(),mp.end()) - mp.begin();
        }
        ~BIT_v() {
            delete []tree;
        };
};
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        BIT_v<long long> h(nums);
        return h.countInversions(0,nums.size() - 1);
    }
};