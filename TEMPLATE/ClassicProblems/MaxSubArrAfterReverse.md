#

## 反转后的最大子数组和

### 题目描述

给定一个数组 $h$，我们可以选择翻转数组的一段 $h[l:r]$，然后求出数组的最大子数组和的大小，空的子数组和大小为 $0$

### 解题思路

首先明确：最后的最大子数组一定不会包含整段反转的数组，因为如果包含此时就说明翻转的效果并没有作用。那么如果我们枚举分割区间的右边界 r，那么就会得到三段数组 h[0:l-1] h[r-1:l:-1] h[r:n-1] 中间表示反转。因为我们反转了中间的部分，所以最后的最大子数组 $[x,y]$ 的区间一定落在了 :

1. $x$ 在第一段 $y$ 在第二段，且 $x$ 可以为空
2. $x$ 在第二段 $y$ 在第三段，且 $y$ 可以为空

而在遍历的过程中，第二种情况实际上在 $r$ 移动的过程中会出现在后面的第一种情况中，即两种情况是等价的，那么我们现在只考虑第2种情况即可。
如果数组中存在正数，那么最大的子数组一定是非空的，所以我们先考虑子数组非空的情况。
设 $dp[i]$ 表示以 $h[i]$ 为起点（该点一定被包含）往后能得到的最大子数组大小。
那么枚举到 $r$ 的时候最大的子数组就是 $dp[r] + leftmax$，$leftmax$ 是在 $r$ 左边的以某一个位置往后的最大子数组和

### 代码参考

```cpp
#include <bits/stdc++.h>
#include "MyGeometry.h"
#include "A.h"
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    vector<int> dp(n); // dp[i] 表示从 h[i]（包括 h[i] 本身） 往后能获得的最大的子数组和
    dp[n - 1] = h[n-1];
    for (int i = n - 2; i >= 0; i--) {
        dp[i] = h[i] + max(0, dp[i+1]);
    }
    int res = max(0, dp[0]); // 左边没有元素不能进行反转
    int left = h[0];
    int leftmax = max(0, h[0]); // 遍历过程中左边从某一个 h[l] 往后到现在遍历的数 h[r] 之前能获得的最大值
    for (int i = 0; i < n; i++) {
        res = max(res, dp[i] + leftmax); // 相当于前面找一段最大的反转然后和后面的进行拼接
        left = h[i] + max(0, left);
        leftmax = max(leftmax, left);
    }
    res = max(res, 0); // 空子数组的情况
    cout<<res<<"\n";
}
int main() {
    solve();
    return 0;
}
```
