/**
 * @author: daydayUppp
 * @brief: 树的序列化 以下代码以「二叉树」的序列化为例，用一个「三元祖」来表示一棵树
 *         如果是「n叉树」 那么用「n + 1 元祖」来表示一棵树即可。
 */
class Solution {
public:
    int dfs(TreeNode* node) {
        // 返回的是树的序号
        if (!node) return 0;
        auto tri = tuple{
            node->val, dfs(node->left), dfs(node->right)
        };
        if (mp.count(tri)) {
            // 如果该子树存在
            repeat.insert(mp[tri].first); // 用 mp[tri] 的开头来进行添加，因为即使相同的节点其地址也是不一样的，节点也不同
            return mp[tri].second;
        }
        // 否则标记该子数
        mp[tri] = {node, ++ idx}; // 分配一个序号
        return idx;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        dfs(root);
        return {repeat.begin(), repeat.end()};
    }
private:
    // 三元组的哈希函数
    static constexpr auto tri_hash = [fn = hash<int>()](const tuple<int, int, int>& o) -> size_t {
        auto&& [x, y, z] = o;
        return (fn(x) << 24) ^ (fn(y) << 8) ^ fn(z);
    };
    unordered_map<tuple<int, int, int>, pair<TreeNode*, int>, decltype(tri_hash)> mp{1, tri_hash}; // {bucket, hash_func}
    unordered_set<TreeNode*> repeat; // 保存重复的树结构的根节点
    int idx = 0;
};