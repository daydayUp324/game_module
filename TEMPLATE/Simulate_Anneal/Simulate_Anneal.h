#include <bits/stdc++.h>
using namespace std;
template<typename T>
class Simulate_Anneal {
    /*
     * 模拟退火 算法 :
     * 一个可以尽量达到全局最优的算法
     * 
     * 每次随机交换序列中的两个位置 来判断当前的序列是否可以比原始序列更优
     * 
     *      1. 若比原始序列更优,则保留交换
     *      2. 否则按一定概率保留交换 (这样才有机会达到全局最优)
     * 
     * 注意 : 为了始终等价于求最小值 , 当求最大值的时候可以通过取负数来实现，最后返回 -1 * res 即可
     * 
     * */
    public:
        int n;
        int res;// 最后返回的值
        int Cal(vector<T>& w) { // 计算当前的性质值
            int o = 0;
            /* 根据不同题目来制定 相关变量可以放在全局变量*/
            res = min(res,o);
            return o;
        }
        void Do(vector<T> w) { // 模拟退火
            random_shuffle(w.begin(),w.end());// 初始化一个序列
            for(double t = 1.0;t > 1e-5;t *= 0.99) {
                // 模拟退火的过程 t 为温度参数 整体慢慢下降
                // 越到后面整个状态要趋于稳定
                // 即 : 当 t 越低 要更趋向于保持原状态
                int i = rand() % n;
                int j = rand() % n;
                int old_v = Cal(w);
                swap(w[i],w[j]);
                int new_v = Cal(w);
                int delta = new_v - old_v;
                // 对于这个交换是否选择保留
                // 因为是求最小值 所以当变大的时候早期更大概率保留
                if(delta > 0 && (double) rand() / RAND_MAX > t) { // 当 new_v > old_v 时 一定概率保留这次操作
                    swap(w[i],w[j]);// 交换表示不保留
                }
            }
        }
        Simulate_Anneal(vector<T>& w,int times = 20) {
            srand((unsigned)time(NULL));
            n = w.size();
            res = 1e9;// 初始设为最大值
            for(int i = 0;i < times;i ++) {
                Do(w);
            }
        }
};
