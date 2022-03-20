#define SZ 400007
template<typename T>
class BIT
{
/*
1. arr[] 从下标 0 开始 则 : tree[index + 1] 负责 arr[index]
2. 单点更新 每次 + 1
3. 区间 [1:p] 查询 -> query(p)
4. 区间 [l:r] 查询 -> query(r) - query(l - 1) 对于 l == 0 特判
*/
private:
    int n;
    T tree[SZ];
public:
    BIT(int sz) {
        this->n = sz;
        for(int i = 1;i < sz;i ++) tree[i] = 0;
    };
    int lowbit(int x) { return x & (-x); }
    void update(int index,T d) {
        // 更新 arr[index] -> 负责的节点为 tree[index + 1]
        index ++;
        while(index <= n) {
            tree[index] += d;
            index += lowbit(index);
        }
    }
    T query(int index) {
        // 查询区间 [1:index] 的和 则 index 的负责区间仍然是 index + 1
        T res = 0;
        index ++;
        while(index) {
            res += tree[index];
            index -= lowbit(index);
        }
        return res;
    }
};
