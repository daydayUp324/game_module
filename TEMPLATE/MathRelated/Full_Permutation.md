#

## 全排列 (Full_Permutation)

问题描述 :

从 `n` 个不同元素中任取 `m（m≤n）` 个元素，按照一定的顺序排列起来，叫做从 `n` 个不同元素中取出 `m` 个元素的一个排列。当 `m=n` 时所有的排列情况叫全排列。

### DFS 回溯进行放置求解

**没有重复元素**

```cpp
// [46. 全排列](https://leetcode.cn/problems/permutations/)
class Solution {
public:
    vector<vector<int>> res;
    void dfs(vector<int>& nums,vector<bool>& vi,vector<int>& temp) {
        if(temp.size() == nums.size()) {
            res.push_back(temp);
            return ;
        }
        for(int i = 0;i < nums.size();i ++) {
            if(!vi[i]) {
                vi[i] = true;
                temp.push_back(nums[i]);
                dfs(nums,vi,temp);
                temp.pop_back();
                vi[i] = false;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> vi(nums.size(),false);
        vector<int> temp;
        dfs(nums,vi,temp);
        return res;
    }
};
```

**有重复元素 :** 放置的时候需要注意一个位置不应该放置相同的元素

```cpp
// [47. 全排列 II](https://leetcode.cn/problems/permutations-ii/)
class Solution {
public:
    vector<vector<int>> res;
    void dfs(vector<int>& nums,vector<bool>& vi,vector<int>& temp) {
        if(temp.size() == nums.size()) {
            res.push_back(temp);
            return ;
        }
        for(int i = 0;i < nums.size();i ++) {
            if(!vi[i]) {
                vi[i] = true;
                temp.push_back(nums[i]);
                dfs(nums,vi,temp);
                temp.pop_back();
                vi[i] = false;
                while(i + 1 < nums.size() && nums[i + 1] == nums[i]) i ++;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        return res;
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<bool> vi(nums.size(),false);
        vector<int> temp;
        dfs(nums,vi,temp);
        return res;
    }
};
```
