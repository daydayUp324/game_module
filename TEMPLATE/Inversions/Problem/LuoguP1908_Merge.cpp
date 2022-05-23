// 题目链接 : [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 7;
int temp[N];// 临时数组
template<typename T>
class MergeSort_v
{
    /**
     * @author daydayUp
     * @brief 归并排序求逆序对
     * 与树状数组相比
     * 优势 : 在于当对于 nums[] 存在负数 或 过大数 时 树状数组需要进行下标转化
     * 劣势 : 在计算逆序对时整个数组同时也进行了排序 和 temp[] 数组的额外开销
     */
public:
    vector<int>& nums;
    T merge(int l1,int r1,int l2,int r2) { // 将 nums[l1:r1] 和 nums[l2:r2] 进行合并
        T res = 0;
        int o = 0;
        int i,j;
        i = l1 , j = l2;
        while(i <= r1 && j <= r2) {
            if(nums[i] <= nums[j]) {
                temp[o ++] = nums[i ++];
            } else { // nums[i] > nums[j]
                // 说明 nums[i : r1] 都是比 nums[j] 大的 这些都是逆序对
                temp[o ++] = nums[j ++];
                res += r1 - i + 1;
            }
        }
        while(i <= r1) temp[o ++] = nums[i ++];
        while(j <= r2) temp[o ++] = nums[j ++];
        for(int i = l1 , j = 0;i <= r2;i ++ , j ++) nums[i] = temp[j];
        return res;
    }
    T countInversions(int left,int right) { // 计算 nums[left:right] 中的逆序对情况
        if(left >= right) return 0;// 一个的时候没有逆序对
        int mid = (left + right) / 2;
        T res = 0;
        res = 
        countInversions(left,mid) + 
        countInversions(mid + 1,right) + 
        merge(left,mid,mid + 1,right);
        return res;
    }
    MergeSort_v(vector<int>& nums_)  : nums(nums_) {}
    ~MergeSort_v() {}
};
int n;
int main() {
    cin >> n;
    vector<int> nums(n,0);
    for(int i = 0;i < n;i ++) scanf("%d",&nums[i]);
    MergeSort_v<long long> h(nums);
    printf("%lld\n",h.countInversions(0,nums.size() - 1));
    return 0;
}