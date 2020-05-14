class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        if (nums.size() <= 2) return true;
        int n = nums.size();
        int inc = 0, dec = n - 1; // 递增序列终点, 递减序列终点
        while (inc < n - 1 && nums[inc] <= nums[inc + 1]) inc++;
        if (inc >= n - 2) return true;
        while (dec > 0 && nums[dec] >= nums[dec - 1]) dec--;
        if (dec <= 1) return true;
        if (dec - inc <= 2 && nums[dec] >= nums[inc]) return true;
        if (dec - inc == 1) return nums[inc - 1] <= nums[dec] || nums[inc] <= nums[dec + 1];
        return false; 
    }
};