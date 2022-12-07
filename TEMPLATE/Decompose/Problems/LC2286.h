const int N = 1e5 + 7;
int arr[N]; // 原始数组
int n, m; // 数组的长度
long long hS[N];
int hMa[N]; // 维护的信息 “和” 或者 “最大值”
int cap, sz; // cap 每一块的大小 size 总共块数
/*
@author: daydayUppp
@brief: 
    1. idx 块对应的原数组中的序号为 [idx * cap, idx * cap + cap)
    2. 一般对应长度为 n 为数组分块的大小为 sqrt(n)
    3. 每当一个块中的元素发生了改变，则对块维护的信息需要进行更新处理
*/
void ini() {
    // 初始化的各种操作
    cap = sqrt(n);
    sz = (n + cap - 1) / cap;
    n = cap * sz;
    for (int i = 0; i < n; ++i) arr[i] = m;
    for (int i = 0; i < sz; ++i) hS[i] = (long long) cap * m, hMa[i] = m;
}
vector<int> fun1(int l, int r, int k) {
    /*
    写对应的功能：对区间 [l: r] 的操作

    找到第一个位置 p 使得 arr[p] >= k
    */
    ++ r;
    // 主要遍历操作
    int idx = l / cap; // 对应的块
    int t = l;
    if (t != idx * cap) {
        int x = min(r, idx * cap + cap);
        while (t < x) {
            if (arr[t] >= k) {
                int a = t, b = m - arr[t];
                arr[t] -= k, hS[idx] -= k;
                hMa[idx] = *max_element(arr + idx * cap, arr + idx * cap + cap);
                return {a, b};
            }
            ++ t;
        }
        ++ idx;
    }
    while (t + cap <= r) {
        // 每一个块进行遍历 对每一个块进行一块操作
        if (hMa[idx] >= k) {
            while (arr[t] < k) ++ t;
            int a = t, b = m - arr[t];
            arr[t] -= k, hS[idx] -= k;
            hMa[idx] = *max_element(arr + idx * cap, arr + idx * cap + cap);
            return {a, b};
        }
        ++ idx;
        t += cap;
    }
    // 剩下的部分进行处理
    while (t < r) {
        if (arr[t] < k) ++ t;
        else {
            int a = t, b = m - arr[t];
            arr[t] -= k, hS[idx] -= k;
            hMa[idx] = *max_element(arr + idx * cap, arr + idx * cap + cap);
            return {a, b};
        }
    }
    return {};
}
int fun2(int l, int r, int k) {
    /*
    写对应的功能：对区间 [l: r] 的操作

    判断 [l: r] 中的元素和能否 -k 如果能则剪
    */
    ++ r;
    // 主要遍历操作
    int idx = l / cap; // 对应的块
    int t = l;
    if (t != idx * cap) {
        int x = min(r, idx * cap + cap);
        while (t < x) {
            if (arr[t] >= k) {
                arr[t] -= k, hS[idx] -= k;
                hMa[idx] = *max_element(arr + t, arr + idx * cap + cap);
                return t;
            }
            k -= arr[t ++];
        }
        ++ idx;
    }
    while (t + cap <= r) {
        // 每一个块进行遍历 对每一个块进行一块操作
        if (hS[idx] >= k) {
            hS[idx] -= k;
            while (arr[t] <= k) {
                k -= arr[t ++];
            }
            arr[t] -= k;
            hMa[idx] = *max_element(arr + t, arr + idx * cap + cap);
            return t;
        }
        k -= hS[idx ++];
        t += cap;
    }
    // 剩下的部分进行处理
    while (t < r) {
        if (arr[t] < k) k -= arr[t];
        else {
            arr[t] -= k, hS[idx] -= k;
            hMa[idx] = *max_element(arr + t, arr + idx * cap + cap);
            return t;
        }
        ++ t;
    }
    return -1;
}
class BookMyShow {
public:
    int bo;
    BookMyShow(int n_, int m_) {
        n = n_, m = m_, bo = 0;
        ini();
    }
    
    vector<int> gather(int k, int maxRow) {
        if (maxRow < bo) return {};
        return fun1(bo, maxRow, k);
    }
    
    bool scatter(int k, int maxRow) {
        if (maxRow < bo) return false;
        int t = fun2(bo, maxRow, k);
        if (t == -1) return false;
        bo = t;
        return true;
    }
};