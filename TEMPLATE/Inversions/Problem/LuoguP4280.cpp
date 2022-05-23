// 题目链接 : 
// [P4280 [AHOI2008]逆序对](https://www.luogu.com.cn/problem/P4280)
/* 
题目描述 : 
    假设这串数字由 n 个正整数组成，其中任一数字 x 均在 1～m 之间，数字串中一部分数字被“-1”替代后
    如：4 2 -1 -1 3 , m = 4 
    那么这串数字，可能是4 2 1 3 3，也可能是4 2 4 4 3，也可能是别的样子。
    你要做的就是根据已知的数字，推断出这串数字里最少能有多少个逆序对。
解题思路 :
    对于两个 i,j , 有 nums[i] = nums[j] = -1 , i < j
    则 : 如果 交换 nums[i] 和 nums[j] ,  nums[:i-1] 和 nums[j + 1:] 对于 nums[i] 和 nums[j] 贡献的逆序对是不会发生改变的 那么使得 nums[i] <= nums[j] 一定是最优的

    所以前面 不确定的数(-1) 是单调不减的 , 所以它们之间是不会有贡献产生的

    设 dp[i][j] 表示 : 第 i 个 -1 的位置 放置为 j 的逆序对个数贡献为 : 

    contribution = dp[i-1][p] + L({j + 1,m}) + R({1:j - 1}) , 1 <= p <= j , 其中 L 表示左边在范围 [j+1:m] 的数字个数 R 表示右边在范围 [1:j-1] 的数字个数 那么从左到右进行遍历然后 用两个树状数组来维护即可

    1 <= n <= 1e4
    1 <= m <= 100
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 7;
const int INF = 0x3f3f3f3f;
template<typename T>
class BIT
{
    /**
     * @author : daydayUppp
     * 适用范围 : 
     * 1. arr[] 从下标 1 开始 则 : tree[index] 负责 arr[index]
     * 2. 单点更新 每次 + 1
     * 3. 区间 [1:p] 查询 -> query(p)
     * 4. 对于区间 [l:r] 查询 -> query(r) - query(l - 1) 对于 l == 1 特判
     */
public:
    int n;
    T* tree;
    BIT(int sz) {
        this->n = sz + 1;
        tree = new T[n];
        for(int i = 1;i < n;i ++) tree[i] = 0;
    };
    int lowbit(int x) { return x & (-x); }
    void update(int index,T d) {
        // 更新 arr[index] -> 负责的节点为 tree[index]
        while(index < n) {
            tree[index] += d;
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
    ~BIT() {
        delete []tree;
    }
};
int n,m;
int nums[N];
int dp[N][105];
int main() {
    cin >> n >> m;
    BIT<int> L(m);
    BIT<int> R(m);
    vector<int> h;// 存不确定的数的位置
    int cur = 0;// 初始的逆序对的个数
    h.push_back(-1);
    for(int i = 1;i <= n;i ++) {
        cin >> nums[i];
        if(nums[i] != -1) {
            R.update(nums[i],1);
            cur += R.query(m) - R.query(nums[i]);
        } else {
            h.push_back(i);
        }
    } 
    if(h.size() == 1) {
        cout<<cur<<"\n"; return 0;
    }
    for(int i = 1;i <= m;i ++) dp[0][i] = 0;// 初始的情况设为 0
    for(int i = 1 , j = 1;i <= n;i ++) {
        if(nums[i] != -1) {
            R.update(nums[i],-1);
            L.update(nums[i],1);
        } else {
            // 枚举 [1:m]
            // 非优化版 :
            // for(int k = 1;k <= m;k ++) {
            //     // 对于某一个 j 产生的贡献为
            //     // 要找 dp[i-1][p] 的最小值 1 <= p <= k
            //     dp[j][k] = INF;
            //     int add = L.query(m) - L.query(k) + R.query(k-1);
            //     for(int p = 1;p <= k;p ++) {
            //         dp[j][k] = min(dp[j][k] , 
            //             dp[j-1][p]
            //         );
            //     }
            //     dp[j][k] += add;
            // }

            // 优化版 : 省略一个 for 循环
            int mm = INF;
            for(int k = 1;k <= m;k ++) {
                // 对于某一个 j 产生的贡献
                // 要找 dp[i-1][p] 的最小值 1 <= p <= k
                mm = min(mm,dp[j-1][k]);
                dp[j][k] = mm + L.query(m) - L.query(k) + R.query(k-1);
            }
            j ++;
        }
    }
    int res = INF;
    int idx = h.size() - 1;
    for(int j = 1;j <= m;j ++) {
        res = min(res,dp[idx][j]);
    }
    cout<<res + cur<<"\n";
    return 0;
}