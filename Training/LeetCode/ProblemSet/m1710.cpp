class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if (nums.empty()) return -1;
        int cho = nums[0], cnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (cnt == 0) {
                cho = nums[i];
            }
            if (nums[i] != cho) cnt--;
            else cnt++;
        }
        return cnt > 0 ? cho : -1;
    }
};