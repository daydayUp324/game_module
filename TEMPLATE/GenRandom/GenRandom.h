class GenRandom
{
    /**
     * @author : daydayUppp
     * @brief : 输入 l,r 生成 int 类型 范围在 [l,r] 的随机数
     */
private:
    mt19937 rng{random_device{}()};// 随机数生成器
    uniform_real_distribution<double> uni_double{0, 1};
public:
    int RandInt(int l, int r) {
        uniform_int_distribution<int> uni(l, r);
        return uni(rng);
    }
    double RandDouble() {
        return uni_double(rng);
    }
    GenRandom() {
        srand((unsigned)time(NULL));// 初始化随机数种子
    };
};