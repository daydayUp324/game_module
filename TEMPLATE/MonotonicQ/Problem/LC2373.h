// 题目链接：[2373. 矩阵中的局部最大值](https://leetcode.cn/problems/largest-local-values-in-a-matrix/)
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
    void clear() { // 清空队列
        while (!q.empty()) q.pop_back();
    }
    MonotonicQ(int size = INT_MAX, bool less_f = true) : sz(size), less_f(less_f) {
    }
};
class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& nums, int n = 3) {
        int a = nums.size(), b = nums[0].size();
        vector<vector<int>> large(a - n + 1, vector<int>(b - n + 1));
        for (int i = 0; i < a; i++) {
            MonotonicQ<int> q1(n); // 升序
            for (int j = 0; j < n; j++) {
                q1.push(nums[i][j], j);
            }
            nums[i][n - 1] = q1.get_front();
            for (int j = n; j < b; j++) {
                q1.push(nums[i][j], j);
                nums[i][j] = q1.get_front();
            }
        }
        for (int j = n - 1; j < b; j++) {
            MonotonicQ<int> q1(n); // 升序
            for (int i = 0; i < n; i++) {
                q1.push(nums[i][j], i);
            }
            large[0][j - n + 1] = q1.get_front();
            for (int i = n; i < a; i++) {
                q1.push(nums[i][j], i);
                large[i - n + 1][j - n + 1] = q1.get_front();
            }
        }
        return large;
    }
};