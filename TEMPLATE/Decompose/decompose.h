const int N = 1e5 + 7;
int arr[N]; // 原始数组
int n; // 数组的长度
int hS[N], hMa[N]; // 维护的信息 “和” 或者 “最大值”
int cap, size; // cap 每一块的大小 size 总共块数
/*
@author: daydayUppp
@brief: 
    1. idx 块对应的原数组中的序号为 [idx * cap, idx * cap + cap)
    2. 一般对应长度为 n 为数组分块的大小为 sqrt(n)
    3. 每当一个块中的元素发生了改变，则对块维护的信息需要进行更新处理
    4. 主要查询区间的信息
*/
void ini() {
    // 初始化的各种操作
    cap = sqrt(n);
    size = (n + cap - 1) / cap;
    n = cap * size;
}
int fun1(int l, int r) {
    /*
    写对应的功能：对区间 [l: r] 的操作
    */
    ++ r;
    // 主要遍历操作
    int idx = l / cap; // 对应的块
    int t = l;
    if (t != idx * cap) {
        int x = max(r, idx * cap + cap);
        while (t != x) {
            // do something
            ++ t;
        }
        ++ idx;
    }
    while (t + cap <= r) {
        // 每一个块进行遍历 对每一个块进行一块操作
        // 
        // 
        ++ idx;
        t += cap;
    }
    // 剩下的部分进行处理
    while (t < r) {
        // 
    }
    return res;
}