class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int ans = arr[0], cnt = 1;
        for (int i = 1; i < arr.size(); ++i) {
            if (arr[i] == ans) cnt++;
            else cnt = 1, ans = arr[i];
            if (cnt * 4 > arr.size()) break;
        }
        return ans;
    }
};