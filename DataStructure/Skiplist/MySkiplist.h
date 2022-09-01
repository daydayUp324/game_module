//
//  MySkiplist.h 跳表类
//
#ifndef MySkiplist_h
#define MySkiplist_h
constexpr int MAX_LEVEL = 32; // 最大的层数
constexpr double P_FACTOR = 0.25; // 概率参数
template <typename T>
struct SkiplistNode { // 每一个跳表节点
    T val;
    vector<SkiplistNode *> forward; // forward[i] 表示该节点在第 i 层往后的第一个节点
    SkiplistNode(T _val, int _maxLevel = MAX_LEVEL) : val(_val), forward(_maxLevel, nullptr) {}
};
template <typename T>
class MySkiplist {
private:
    SkiplistNode<T>* head; // 头节点
    int level; // 当前跳表的最大层数 空的跳表层数标记为 0
    // 随机数生成器
    mt19937 gen{random_device{}()};
    uniform_real_distribution<double> dis;
public:
    MySkiplist(): head(new SkiplistNode<T>(-1)), level(0), dis(0, 1) {}
    
    bool search(T target) {
        // 查找 target 是否在跳表中
        SkiplistNode<T>* cur = this->head;
        for (int i = this->level - 1; i >= 0; i--) {
            // 查找第 i 层小于且最接近 target 的元素
            // 首先从最高层往下层进行查询
            while (cur->forward[i] && cur->forward[i]->val < target) {
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0]; // 最底层的下一个节点
        if (cur && cur->val == target) {
            return true;
        }
        return false;
    }
    
    void add(T num) {
        // 增加节点 num
        // 首先找到跳表中最底层中 num 节点后的第一个节点 after
        // 然后在 after 节点后增加该 num 节点
        SkiplistNode<T>* cur = this->head;
        vector<SkiplistNode<T>*> update(MAX_LEVEL, this->head); // update[i] 表示如果我要在某层 i 添加 num 节点时，num 节点在 update[i] 节点之后
        for (int i = this->level - 1; i >= 0; i--) {
            while (cur->forward[i] && num > cur->forward[i]->val) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        int lv = randomLevel();
        this->level = max(this->level, lv);
        SkiplistNode<T>* newNode = new SkiplistNode<T>(num, lv); // 只需要 lv 层的传递即可
        for (int i = 0; i < lv; i++) {
            // 更新 [0, lv) 层的节点
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool erase(T num) {
        // 删除节点 num 如果存在则返回 True 否则 False
        // 首先查找是否有 num 节点
        vector<SkiplistNode<T>*> update(MAX_LEVEL, nullptr); // 删除后该节点在每层上的对应节点需要删除，然后更新该层的信息
        SkiplistNode<T>* cur = this->head;
        for (int i = this->level - 1; i >= 0; i--) {
            while (cur->forward[i] && num > cur->forward[i]->val) {
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];
        if (!cur || cur->val != num) return false; // 说明此时该节点不存在
        for (int i = 0; i < cur->forward.size(); i++) {
            update[i]->forward[i] = cur->forward[i];
        }
        delete cur; // 删除该节点
        // 更新现在跳表的层数 this->level
        while (this->level && !head->forward[this->level - 1]) {
            this->level --;
        }
        return true;
    }
    
    int randomLevel() {
        // 获得从底层往上能到的一个层数
        // 最后加入的节点更新的层数为 [0, lv)
        int lv = 1;
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
            lv ++;
        }
        return lv;
    }
};

#endif /* MySkiplist_h */
