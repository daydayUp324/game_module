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