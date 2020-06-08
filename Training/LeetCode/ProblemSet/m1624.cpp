class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int l = 0, r = nums.size() - 1;
        vector<vector<int>> ret;
        while (l < r) {
            if (nums[l] + nums[r] > target) r--;
            else if (nums[l] + nums[r] < target) l++;
            else ret.push_back({nums[l++], nums[r--]});
        }
        return ret;
    }
};