// 题目链接：[239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/)
template<typename  T>
class MonotonicQ {
    /**
     @author: daydayUppp
     @brief: 单调队列的实现：维护一个范围内（sz）的单调性，从队尾到队首保持一定单调性（less_f），用双端队列来实现。
     */
public:
    T val;
    bool less_f; // true 默认为保持队列升序
    deque<pair<T, int>> q;
    int sz; // 维持的单调性的范围 默认无穷大
    bool less(const T& val_) {
        return q.back().first < val_ == this->less_f;
    }
    void push(const T& val, int idx) {
        while (!q.empty() && q.front().second + sz <= idx) q.pop_front(); // 超出范围
        while (!q.empty() && less(val)) q.pop_back(); // 维护单调性
        q.push_back({val, idx}); // 加入队列
    }
    T get_front() { // 获取头元素
        return q.front().first;
    }
    MonotonicQ(int size = INT_MAX, bool less_f = true) : sz(size), less_f(less_f) {
    }
};
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int m = nums.size();
        MonotonicQ<int> q(k);
        for (int i = 0; i < k; i++) q.push(nums[i], i);
        vector<int> res;
        res.push_back(q.get_front());
        for (int i = k; i < m; i++) {
            q.push(nums[i], i);
            res.push_back(q.get_front());
        }
        return res;
    }
};