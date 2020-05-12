class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        if (nums.empty()) return 0;
        int n = nums.size();
        unordered_map<int, int> hash; // <cnt, pos>, 保存相同前缀和出现的第一个位置
        hash[0] = -1;
        int ans = 0, sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += (nums[i] == 0) ? -1 : 1; // 前缀和
            auto ite = hash.find(sum);
            if (ite == hash.end()) {
                hash[sum] = i;
            } else {
                ans = max(ans, i - hash[sum]);
            }
        }
        return ans;
    }
};