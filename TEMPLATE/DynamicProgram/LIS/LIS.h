class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp;
        for (auto& i : nums) {
            if (dp.empty() || i > dp.back()) dp.push_back(i);
            else {
                auto idx = lower_bound(dp.begin(), dp.end(), i) - dp.begin();
                dp[idx] = i;
            }
        }
        /*
        如果不是严格递增的情况
        for (auto& i : nums) {
            if (dp.empty() || i >= dp.back()) dp.push_back(i);
            else {
                auto idx = upper_bound(dp.begin(), dp.end(), i) - dp.begin();
                dp[idx] = i;
            }
        }
        */
        return dp.size();
    }
};