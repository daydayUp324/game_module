#

## DST

### 概念

并查集是一种 **树型** 的数据结构，用于处理一些不相交集合的合并及查询问题。并查集的思想是用一个数组表示了整片森林（parent），树的根节点唯一标识了一个集合，我们只要找到了某个元素的的树根，就能确定它在哪个集合里。

#### [947. 移除最多的同行或同列石头](https://leetcode-cn.com/problems/most-stones-removed-with-same-row-or-column/)

[![qLtp7j.png](https://s1.ax1x.com/2022/04/05/qLtp7j.png)](https://imgtu.com/i/qLtp7j)

#### 解题思路_1

把 $line_i$ 和 $row_i$ 看成单独的元素 , 那么 每一个 $stone_i = (x,y)$ 都将 $x,y$ 进行合并。那么最后当该 **行** 或 **列** 没有 **父节点** 时 说明该节点不能移除。

又因为 $x,y$ 的范围重复 , 所以需要 $x' = x + 10^4$ 使 $x'$ 与 $y$ 范围不重叠。

#### CODE_1

```cpp
class DSU {
    /**
     * @author : daydayUppp
     * 1. fp(int x) 查找 x 的连通块的代表
     * 2. con(int x, int y) x, y 是否联通
     * 3. ut(int x, int y) 连接 x,y 返回是否连接成功
     * 4. Size(int x) 区域 x 对应的大小
     */
public:
    vector<int> fa;
    int n, count;
    DSU(int n) : n(n), count(n), fa(n + 1, -1) {}
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    bool con(int x, int y) {
        return fp(x) == fp(y);
    }
    bool ut(int x, int y) {
        // 连接 x 和 y
        x = fp(x), y = fp(y);
        if (x == y) return false;
        count --;
        // 按秩合并 fa[x] 越小表示这棵树越长
        if (fa[x] < fa[y]) swap(x, y);
        fa[x] += fa[y], fa[y] = x;
        return true;
    }
    int Size(int x) {
        // 返回区域 p 的大小
        return -fa[fp(x)];
    }
    ~DSU() {}
};
const int N = 1e4 + 5;
class Solution {
public:
    int removeStones(vector<vector<int>>& s) {
        DSU h(2 * N);
        for(auto& i : s) {
            h.ut(i[0] + N,i[1]);
        } 
        int res = s.size();
        for(int i = 0;i < 2 * N;i ++) {
            if(h.fa[i] < -1) res --;
        } 
        return res;
    }
};
```

#### [2092. 找出知晓秘密的所有专家](https://leetcode-cn.com/problems/find-all-people-with-secret/)

[![qLtVjU.png](https://s1.ax1x.com/2022/04/05/qLtVjU.png)](https://imgtu.com/i/qLtVjU)

#### 解题思路_2

1. 因为题目是根据时间来进行的 , 所以首先对 `meets[]` 按照 `meets[i][2]` 进行升序排序
2. 然后对于同一时间的我们先进行连接 , 因为最后如果不是知晓秘密的连通区域 , 那么全部还原成原来的状态即可
3. 最后统计根节点不是自己的连通区域数量即可 (令 `n节点` 为知晓秘密的连通块的根节点)

#### CODE_2

```cpp
class DSU {
    /**
     * @author : daydayUppp
     * 1. fp(int x) 查找 x 的连通块的代表
     * 2. con(int x, int y) x, y 是否联通
     * 3. ut(int x, int y) 连接 x,y 返回是否连接成功
     * 4. Size(int x) 区域 x 对应的大小
     */
public:
    vector<int> fa;
    int n, count;
    DSU(int n) : n(n), count(n), fa(n + 1, -1) {}
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    bool con(int x, int y) {
        return fp(x) == fp(y);
    }
    bool ut(int x, int y) {
        // 连接 x 和 y
        x = fp(x), y = fp(y);
        if (x == y) return false;
        count --;
        // 按秩合并 fa[x] 越小表示这棵树越长
        if (fa[x] < fa[y]) swap(x, y);
        fa[x] += fa[y], fa[y] = x;
        return true;
    }
    int Size(int x) {
        // 返回区域 p 的大小
        return -fa[fp(x)];
    }
    ~DSU() {}
};
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& ms, int fp) {
        sort(ms.begin(),ms.end(),[](vector<int>& a,vector<int>& b) {
            return a[2] < b[2];
        });
        DSU h(n);
        h.ut(0, fp);
        vector<int> res;
        for(int i = 0;i < ms.size();) {
            int j = i;
            // 首先尝试进行连接
            for(;j < ms.size() && ms[j][2] == ms[i][2];j ++) {
                h.ut(ms[j][0],ms[j][1]);
            }
            h.fa[h.fp(0)] = n , h.fa[n] = -1;// 使 n 节点为知晓秘密的根节点 , 那么最后根节点不是 n 的就是非知晓秘密的连通区域
            while(i < j) {
                if(h.fp(ms[i][0]) != n) {
                    h.fa[ms[i][0]] = h.fa[ms[i][1]] = -1;
                }
                i ++;
            }
        } 
        for(int i = 0;i < n;i ++) if(h.fa[i] >= 0) res.push_back(i);
        return res;
    }
};
```

#### [打砖块](https://leetcode-cn.com/problems/bricks-falling-when-hit/)

#### 解题思路_3

正向来模拟的话会比较麻烦 , 打掉一个 `砖块` 还需要 `dfs` 来 **判断 并且 更新** 周围的连通区域是否从 "稳定" 到 "非稳定" 的撞状态 , 即 `hits[i]` 会对 `hits[j]` , `i < j` 产生影响。

所以我们考虑 **逆向思考** , 先把要打的区域全部 "打掉" , 然后从最后往前进行放置 `砖块`。当放置了 `砖块` 后 , 它周围存在 **连通区域** 从 `不稳定` -> `稳定`。那么这块 **连通区域** 就是打掉这块 `砖块` 后掉落的 `砖块区域`。而从后往前，当一块区域变 `稳定` 后 , 就不会再变成 `非稳定` , 有利于状态的更新。

1. 所以先把全部要打掉的 `砖块` 都先打掉
2. 然后加入一个 `超级根节点 root` 使得 所以有 `root` 的连通区域都是稳定的 , 并把 顶上的砖块 与 `root` 相连。
3. 然后初始化 `grid` 中的初始连通区域
4. 最后从逆向开始放置 `砖块` , 并判断是否有区域从 `不稳定` -> `稳定` , 并更新 `res` 即可

#### CODE

```cpp
class DSU {
    /**
     * @author : daydayUppp
     * 1. fp(int x) 查找 x 的连通块的代表
     * 2. con(int x, int y) x, y 是否联通
     * 3. ut(int x, int y) 连接 x,y 返回是否连接成功
     * 4. Size(int x) 区域 x 对应的大小
     */
public:
    vector<int> fa;
    int n, count;
    DSU(int n) : n(n), count(n), fa(n + 1, -1) {}
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    bool con(int x, int y) {
        return fp(x) == fp(y);
    }
    bool ut(int x, int y) {
        // 连接 x 和 y
        x = fp(x), y = fp(y);
        if (x == y) return false;
        count --;
        // 按秩合并 fa[x] 越小表示这棵树越长
        if (fa[x] < fa[y]) swap(x, y);
        fa[x] += fa[y], fa[y] = x;
        return true;
    }
    int Size(int x) {
        // 返回区域 p 的大小
        return -fa[fp(x)];
    }
    ~DSU() {}
};
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
class Solution {
public:
    int n,m;
    int root;
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        n = grid.size() , m = grid[0].size();// (i,j) -> i * m + j
        root = n * m;// 稳定的根节点
        DSU h(root);
        vector<int> res(hits.size(),0);
        // 逆序进行操作
        vector<vector<int>> s = grid;
        for(auto& i : hits) {
            s[i[0]][i[1]] = 0;
        }
        // 对初始连通区域进行初始化
        for(int i = 0;i < n;i ++) {
            for(int j = 0;j < m;j ++) {
                if(s[i][j]) {
                    int o = i * m + j;
                    for(int d = 0;d < 4;d ++) {
                        int nx,ny;
                        nx = i + dir[d][0] , ny = j + dir[d][1];
                        if(nx >= 0 && nx < n && ny >= 0 && ny < m && s[nx][ny]) {
                            h.ut(o,nx * m + ny);
                        }
                    }
                }
            }
        }
        for(int j = 0;j < m;j ++) {
            if(s[0][j]) {
                h.ut(j,root);// 稳定的区域
            }
        }
        for(int i = hits.size() - 1;i >= 0;i --) {
            int x,y;
            x = hits[i][0] , y = hits[i][1];
            if(grid[x][y]) {
                // 有掉落的情况 : (i,j) 周围的连通区域本来是不稳定的 加入 (i,j) 后变得稳定了
                int o = 0;
                for(int d = 0;d < 4;d ++) {
                    int nx,ny;
                    nx = x + dir[d][0] , ny = y + dir[d][1];
                    if(nx >= 0 && nx < n && ny >= 0 && ny < m && s[nx][ny]) {
                        if(!h.con(x * m + y,nx * m + ny) && !h.con(root,nx * m + ny))
                            o -= h.fa[h.fp(nx * m + ny)];
                        h.ut(x * m + y,nx * m + ny);
                    }
                }
                if(!x) h.ut(x * m + y , root);// 如果加入后是顶端需要和 root 相连
                if(h.con(x * m + y, root)) res[i] = o;
                s[x][y] = 1;
            }
        }
        return res;
    }
};
```
