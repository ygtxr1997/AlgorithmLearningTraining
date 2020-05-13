class Solution {
public:
    bool check(vector<int>& nums, vector<int>& res, int state) {
        int i = 0;
        while (state > 0) {
            if (state & 1) res.push_back(nums[i]);
            i++;
            state /= 2;
        }
        if (res.size() < 2) res.resize(0);
        for (int i = 1; i < res.size(); ++i) {
            if (res[i] < res[i - 1]) return false;
        }
        return res.size() >= 2;
    }
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> ret; // 用set保存
        if (nums.empty()) return vector<vector<int>>(ret.begin(), ret.end());
        int n = nums.size();
        int S = (1 << n) - 1;
        for (int i = 3; i <= S; ++i) {
            vector<int> tmp;
            if (check(nums, tmp, i)) ret.insert(tmp);
        }
        return vector<vector<int>>(ret.begin(), ret.end());
    }
};