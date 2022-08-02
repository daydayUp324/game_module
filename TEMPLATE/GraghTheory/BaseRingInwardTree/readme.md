#

## 基环内向树

**定义：** 每个点出度为1（因此每个环上点的子树，儿子指向父亲）

**基环内向树** 找环的操作：

1. 朴素做法就是先**拓扑排序**，然后 `dfs` 来找每一个环，并需要 `vi[]` 来进行访问标记
2. 对于 **基环内向树** 我们往往可以引入 **时间戳** 的概念来进行访问标记。而不需要 **拓扑排序** 的操作

### CODE

```cpp
// 找基环内向树的最大环/环的个数
// 题目链接 : [2360. 图中的最长环](https://leetcode.cn/problems/longest-cycle-in-a-graph/)
class Solution {
public:
    int longestCycle(vector<int> &g) {
        // g[i] 表示 节点 i 的出边的端点，-1 表示无出边
        int n = g.size();
        int res = -1;
        vector<int> time(n,0);
        int starttime = 1; // 开始的时间戳
        // int count = 0; // 环的个数
        for (int i = 0; i < n; i++) {
            if (time[i]) continue;
            int node = i;
            time[node] = starttime ++;
            while (g[node] != -1 && !time[g[node]]) {
                node = g[node];
                time[node] = starttime ++;
            }
            if (g[node] != -1 && time[g[node]] >= time[i]) {
                // 是环的条件，碰到的标记过的点的时间戳要大于 time[i]
                // count ++; // 环的个数开关
                res = max(res, time[node] - time[g[node]] + 1);
            }
        }
        return res;
    }
};
```
