/*
腾讯笔试题 :

题目描述 :

作为程序员的小Q，他的数列和其他人的不太一样，他有 2^n 个数。

共 m 次查询 :

每次给出一个整数 q
要求小Q把这些数每 2^q 分为一组，然后把每组进行翻转

输出 每次操作后 整个序列中的逆序对 个数

对于序列1 3 4 2，逆序对有(4, 2),(3, 2),总数量为2。
当 q = 2 时 , 翻转 4 个

翻转之后为2 4 3 1，逆序对有(2, 1),(4, 3), (4, 1), (3, 1),总数量为4。

数据范围 : 

1 <= n <= 20

1 <= nums[i] <= 1e9

1 <= m <= 1e6

0 <= q <= n
*/

/*

思路分析 :

设 : 

f1[i] 表示 长度为 2^i 长度的子数组的全部逆序对数量
f2[i] 表示 长度为 2^i 长度的子数组的全部正序对数量

当翻转 q 长度时 , 小的也同时会被翻转 , 即 也同时翻转 [1:q) 长度的即可

那么进行模拟即可 , 因为最多只有 20 个不同大小的子数组

*/
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 7;
int temp[N];// 临时数组
int n,num;
long long f1[25];
long long f2[25];
long long f3[25];
template<typename T>
class MergeSort_v
{
    /**
     * @author daydayUp
     * @brief 归并排序求逆(正)序对
     * 与树状数组相比
     * 优势 : 在于当对于 nums[] 存在负数 或 过大数 时 树状数组需要进行下标转化
     * 劣势 : 在计算逆序对时整个数组同时也进行了排序 和 temp[] 数组的额外开销
     */
public:
    vector<int>& nums;
    T merge(int l1,int r1,int l2,int r2,const bool inv) { // 将 nums[l1:r1] 和 nums[l2:r2] 进行合并
        // para : inv = true 求逆序对 , false 求正序对
        T res = 0;
        int o = 0;
        int i,j;
        i = l1 , j = l2;
        if(inv) { // 逆序对
            while(i <= r1 && j <= r2) {
                if(nums[i] <= nums[j]) {
                    temp[o ++] = nums[i ++];
                } else { // nums[i] > nums[j]
                    // 说明 nums[i : r1] 都是比 nums[j] 大的 这些都是逆序对
                    temp[o ++] = nums[j ++];
                    res += r1 - i + 1;
                }
            }
        } else { // 正序对
            while(i <= r1 && j <= r2) {
                if(nums[i] >= nums[j]) {
                    temp[o ++] = nums[j ++];
                } else { // nums[i] < nums[j]
                    // 说明 nums[j : r2] 都是比 nums[i] 大的 这些都是逆序对
                    temp[o ++] = nums[i ++];
                    res += r2 - j + 1;
                }
            }
        }
        while(i <= r1) temp[o ++] = nums[i ++];
        while(j <= r2) temp[o ++] = nums[j ++];
        for(int i = l1 , j = 0;i <= r2;i ++ , j ++) nums[i] = temp[j];
        return res;
    }
    T countInversions(int left,int right,const bool inv,int v) { // 计算 nums[left:right] 中的逆序对情况
        // para : inv = true 求逆序对 , false 求正序对
        if(left >= right) return 0;// 一个的时候没有逆序对
        int mid = (left + right) / 2;
        T res = 0;
        res = 
        countInversions(left,mid,inv,v - 1) + 
        countInversions(mid + 1,right,inv,v - 1) + 
        merge(left,mid,mid + 1,right,inv);
        if(inv) f1[v] += res;
        else f2[v] += res;
        return res;
    }
    MergeSort_v(vector<int>& nums_)  : nums(nums_) {}
    ~MergeSort_v() {}
};
void solve() {
    cin >> n;
    int num = 1 << n;// 数组大小
    vector<int> w(num,0);
    vector<int> wt(num,0);
    for(int i = 0;i < num;i ++) {
        cin >> w[i];
        wt[i] = w[i];
    }
    for(int i = 0;i < 25;i ++) f1[i] = f2[i] = 0;
    MergeSort_v<long long> h1(w);
    MergeSort_v<long long> h2(wt);
    h1.countInversions(0,num - 1,true,n);
    h2.countInversions(0,num - 1,false,n);
    for(int i = 0;i < 25;i ++) f3[i] = f1[i];
    int m,q;
    cin >> m;
    long long cur = f1[n];
    while(m --) {
        cin >> q;
        long long d = (f1[q] + f2[q] - f3[q] * 2);// 产生的变化
        // 向下传递
        for(int i = 1;i <= q;i ++) {
            f3[i] = (f1[i] + f2[i] - f3[i]);// 下面的每一个也都发生改变
        }
        // 向上传递
        for(int i = q + 1;i <= n;i ++) {
            f3[i] += d;
        }
        cout<<f3[n]<<"\n";
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    solve();
    return 0;
}

