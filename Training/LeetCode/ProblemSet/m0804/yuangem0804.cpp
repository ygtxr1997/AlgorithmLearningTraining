class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ret;
        int n = nums.size();
        int S = (1 << n) - 1;
        for (int op = 0; op <= S; ++op) {
            int cur = op, bit = 0;
            vector<int> res;
            while (cur) {
                if (cur & 1) res.push_back(nums[bit]);
                cur >>= 1;
                bit++;
            }
            ret.push_back(res);
        }
        return ret;
    }
};