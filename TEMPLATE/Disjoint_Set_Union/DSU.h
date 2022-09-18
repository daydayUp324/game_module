#define VALID (nx >= 0 && nx < n && ny >= 0 && ny < m)
const int dir[8][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,-1}, {-1,1}};
class DSU {
    /**
     * @author : daydayUppp
     * 1. fp(int x) 查找 x 的连通块的代表
     * 2. isconnect(int x,int y) 判断 x,y 是否连通
     * 3. unite(int x,int y) 连接 x,y
     * 4. getSize(int x) 区域 x 对应的大小
     */
public:
    int* fa;
    int n, count;// count 连通分量的数量
    DSU(int n_) {
        n = n_, count = n_;
        fa = new int[n_ + 1];
        memset(fa, -1, 4 * n + 4);
    }
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    bool isconnect(int x,int y) {
        return fp(x) == fp(y);
    }
    bool unite(int x, int y) {
        // 连接 x 和 y
        x = fp(x), y = fp(y);
        if (x == y) return false;
        count --;
        // 按秩合并 fa[x] 越小表示这棵树越长
        if (fa[x] < fa[y]) y ^= x, x ^= y, y ^= x;
        fa[x] += fa[y], fa[y] = x;
        return true;
    }
    int getSize(int x) {
        // 返回区域 p 的大小
        return -fa[fp(x)];
    }
    ~DSU() {
        delete []fa;
    }
};
