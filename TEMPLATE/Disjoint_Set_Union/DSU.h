class DSU {
    /**
     * @author : daydayUppp
     * fp(int x) 查找 x 的连通块的代表
     */
public:
    int* fa;
    int n,count;// count 连通分量的数量
    DSU(int n_) {
        n = n_ , count = n_;
        fa = new int[n_ + 1];
    }
    int fp(int x) {
        return fa[x] < 0 ? x : fa[x] = fp(fa[x]);
    }
    bool unite(int x,int y) {
        // 连接 x 和 y
        x = fp(x) , y = fp(y);
        if(x == y) return false;// 已经是一个连通分量
        count --;
        // 按秩合并 
        if(fa[x] > fa[y]) y ^= x , x ^= y , y ^= x;
        fa[x] += fa[y] , fa[y] = x;
        return true;
    }
};