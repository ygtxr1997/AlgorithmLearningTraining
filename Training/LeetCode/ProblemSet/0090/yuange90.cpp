class Solution {
public:
    vector<int> val;
    vector<int> cnt;
    void dfs(int i, int n, vector<int>& tmp, vector<vector<int>>& ret) {
        if (i >= n) {
            ret.push_back(tmp);
            return;
        }
        for (int k = 0; k <= cnt[i]; ++k) {
            for (int j = 0; j < k; ++j) tmp.push_back(val[i]);
            dfs(i + 1, n, tmp, ret);
            for (int j = 0; j < k; ++j) tmp.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); ++i) hash[nums[i]]++;
        for (auto pii : hash) {
            val.push_back(pii.first);
            cnt.push_back(pii.second);
        }
        int n = val.size();
        vector<vector<int>> ret;
        vector<int> tmp;
        dfs(0, n, tmp, ret);
        return ret;
    }
};