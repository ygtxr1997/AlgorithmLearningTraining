class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        // 奇数放峰, 偶数放谷
        for (int i = 1; i < nums.size(); ++i) {
            if ((i & 1) && nums[i] < nums[i - 1]) swap(nums[i], nums[i - 1]);
            else if (!(i & 1) && nums[i] > nums[i - 1]) swap(nums[i], nums[i - 1]);
        }
    }
};