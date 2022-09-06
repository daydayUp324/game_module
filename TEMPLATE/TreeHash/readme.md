#

## 树的哈希（序列化）

**题目链接：** 

- [652. 寻找重复的子树](https://leetcode.cn/problems/find-duplicate-subtrees/)
- [297. 二叉树的序列化与反序列化](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/)

**参考文章：**

- [寻找重复的子树](https://leetcode.cn/problems/find-duplicate-subtrees/solutions/1798953/xun-zhao-zhong-fu-de-zi-shu-by-leetcode-zoncw/)

「序列化」的目的主要是：

- 相同的子树会被序列化成相同的子串；
- 不同的子树会被序列化成不同的子串。

### 用字符串来序列化树

一种比较直接的思路就是将树按照某一种遍历来序列化成「字符串」。比如以「前序遍历」为例，那么一棵以 `root` 为根节点的树，可以按照以下的规则来进行序列化：

```cpp
string dfs(TreeNode* root) {
    if (!root) return "()";
    return "(" + to_string(root->val) + dfs(root->left) + dfs(root->right) + ")";
}
```

这样对于某一个字符串我们也可以按照括号展开来进行反序列。

### 用 n 元组来进行序列化树

我们可以用一个「序号」来表示一棵不同的树，那么：`(root, l_idx, r_idx)` 就可以表示一棵树，其中如果要解析这棵树的时候就可以按照左右节点递归解析的方式来进行处理。这里的「序号」指的是：每当我们发现一棵新的子树，就给这棵子树一个序号，用来表示其结构。那么两棵树是重复的，当且仅当它们对应的三元组完全相同。

使用「序号」的好处在于同时减少了时间复杂度和空间复杂度。方法一的瓶颈在于生成的序列会变得非常长，而使用序号替换整个左子树和右子树的序列，可以使得每一个节点只使用常数大小的空间。

那么同样的道理，如果是 `n 叉树` 那么我们用一个 `n + 1 元祖` 来表示一棵树即可。

完整代码具体见 `TreeHash.h`
