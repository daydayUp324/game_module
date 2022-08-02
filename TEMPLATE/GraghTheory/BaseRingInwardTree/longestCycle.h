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
