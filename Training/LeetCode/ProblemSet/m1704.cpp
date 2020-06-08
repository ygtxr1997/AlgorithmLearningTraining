class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int X = nums.size();
        for (int i = 0; i < nums.size(); ++i) {
            X ^= i;
            X ^= nums[i];
        }
        return X;
    }
};