#

## 字典树辅助动态规划 DpOnTrie

**题目链接：[D2. Xor-Subsequence (hard version)](https://codeforces.com/contest/1720/problem/D2)**

### 题目描述

给你一个长为 $n$ 的整数数组 $a$，从 $0$ 开始编号。

一个长为 $m$ ，从 $0$ 开始编号的整数数组 $b$ 是数组 $a$ 的 $subsequence$，有 $0\leq b_0<b_1<\dots<b_{m-1}<n$。

若 $b$ 是 $a$ 的 $beautiful$ $subsequence$，当且仅当满足以下条件：

+ $b$ 是 $a$ 的 subsequence；
+ $\forall p\in[0,m)\cap\textbf{N},a_{b_p} \oplus b_{p+1}<a_{b_{p+1}} \oplus b_p$。

其中 $\oplus$ 表示位运算中的异或运算。

现在，你需要求出最长的 $beautiful$ $subsequence$ 有多长。

#### 输入格式

第一行一个整数 $T$，表示数据组数。

对于每组数据，第一行一个整数 $n$，表示数组 $a$ 的长度。

第二行有 $n$ 个整数，表示数组 $a$。

#### 输出格式

对于每组数据，输出一行一个数，表示最长的 $beautiful$ $subsequence$ 的长度。

#### 数据范围

$1\leq T\leq 10^5,2\leq n\leq 3\times 10^5,0\leq a_i\leq 10^9,\sum n\leq 3\times 10^5$。

#### 样例

**样例输入：**

```
3
2
1 2
5
5 2 4 3 1
10
3 8 8 2 9 1 6 2 8 3
```

**样例输出：**

```
2
3
6
```

##### 提示

In the first test case, we can pick the whole array as a beautiful subsequence because $ 1 \oplus 1 < 2 \oplus 0 $ .

In the second test case, we can pick elements with indexes $1$ , $2$ and $4$ (in $ 0 $ indexation). For this elements holds: $2 \oplus 2 < 4 \oplus 1 $ and $ 4 \oplus 4 < 1 \oplus 2$

### 思路分析

满足的条件为 $a_{b_p} \oplus b_{p+1}<a_{b_{p+1}} \oplus b_p$，即每一个数 $a_{b_{p + 1}}$ 只需要满足与前一个数 $a_{b_p}$ 有关，那么很容易联想到 `LIS(最长递增子序列)` 模型的 $n^2$ 的算法：

```cpp
// dp[i] 表示以 a[i] 结尾的最长的 "美丽" 序列的长度/
// res 为最长的 "美丽" 序列的长度
for (int i = 0; i < a.size(); i++) {
    dp[i] = 1;
    for (int j = 0; j < i; j++) {
        if (a[j] ^ i < a[i] ^ j) dp[j] = max(dp[j] + 1, dp[i]);
    }
    res = max(res, dp[i]);
}
```

而 $n^2$ 的算法是肯定会超时的，所以我们挖掘性质：因为 **异或** 的操作对于 **不等式** 是不能保持不等式的状态。那么我们从 **等号** 出发：

那么假设两个下标 $i$，$j$，$i < j$，$x = a_i \oplus i$，$y = a_j \oplus j$。如果 $x = y$，则：$x \oplus i \oplus j = y \oplus i \oplus j$，即有 $a_i \oplus j = a_j \oplus i$，所以 $a_i \oplus i = a_j \oplus j$ 和 $a_i \oplus j = a_j \oplus i$ 是 **等价** 的。因为每一个数和序号都为 $32$ 位二进制的数字，那么令 $a_i = num1[32]$ 和 $i = idx1[32]$，$a_j = num2[32]$，$j = idx2[32]$，其中 $num[]$ 和 $idx[]$ 都表示对应的一个二进制序列。所以假设 $num1[p:] \oplus idx1[p:] = num2[p:] \oplus idx2[p:]$，那么肯定有 $num1[p:] \oplus idx2[p:] = num2[p:] \oplus idx1[p:]$。所以我们可以用 $(num[32] , idx[32])$ 作为 $key$ 然后从二进制 **高位到低位** 来进行判断。那么不同的情况只有 $2$ 种情况：

$num1[p] \oplus idx1[p]$ | $num2[p] \oplus idx2[p]$ |
--- | --- |
0 | 1 |
1 | 0 |

且能满足 $num1[p] \oplus idx2[p] < num2[p] \oplus idx1[p]$ 的情况为：

$num1[p]$ | $idx1[p]$ | $num2[p]$ | $idx2[p]$ |
--- | --- | --- | --- |
0 | 0 | 1 | 0 |
1 | 1 | 0 | 1 |
0 | 1 | 0 | 0 |
1 | 0 | 1 | 1 |

那么我们只需要按照 $(num[32] \oplus idx[32])$ 来作为 $key$ 值然后记录以 $(num[32], idx[32])$ 的最长 "美丽" 序列长度。那么在遍历的过程中来维护这个 `Trie` 然后进行查询即可。具体见代码来理解。

### CODE

```cpp
// 题目链接：[D2. Xor-Subsequence (hard version)](https://codeforces.com/contest/1720/problem/D2)
#include <bits/stdc++.h>
using namespace std;
const int N = 2e7 + 7;
struct trie
{
    int val[4]; // 最长 "美丽" 序列的长度
    int ne[2]; // 下一个 0 表示无
} tr[N];
int n, m, a, add; // add 表示后面加的 trie 节点
int ne[4] = {1, 3, 0 ,2};
void insert(int num, int idx, const int& ma) {
    int root = 1;
    for (int i = 29; i >= 0; i--) {
        int t = (num >> i & 1) ^ (idx >> i & 1);
        int u = (num >> i & 1) * 2 +  (idx >> i & 1);
        if (!tr[root].ne[t]) {
            tr[root].ne[t] = add ++;
        }
        root = tr[root].ne[t];
        tr[root].val[u] = max(tr[root].val[u], ma);
    }
}
int query(int num, int idx) {
    int res = 1;
    // 0 0 -> 1
    // 0 1 -> 3
    // 1 0 -> 0
    // 1 1 -> 2
    int root = 1;
    for (int i = 29; i >= 0; i--) {
        int t = (num >> i & 1) ^ (idx >> i & 1);
        int u = (num >> i & 1) * 2 + (idx >> i & 1);
        if (tr[root].ne[!t]) {
            int o = tr[root].ne[!t];
            res = max(res, 1 + tr[o].val[ne[u]]);
        }
        if (!tr[root].ne[t]) {
            break;
        }
        root = tr[root].ne[t];
    }
    return res;
}
void solve() {
    scanf("%d", &n);
    int res = 0;
    add = 2;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        int ma = query(a, i);
        res = max(res, ma);
        insert(a, i, ma);
    }
    // 清空操作
    for (int i = 1; i < add; i++) {
        tr[i].val[0] = tr[i].val[1] = tr[i].val[2] = tr[i].val[3] = 0;
        tr[i].ne[0] = tr[i].ne[1] = 0;
    }
    printf("%d\n", res);
}
int main() {
    int T;
    cin >> T;
    while (T --) solve();
    return 0;
}
```
