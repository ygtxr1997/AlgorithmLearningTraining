class Solution {
public:
    vector<int> subSort(vector<int>& array) {
        if (array.size() <= 1) return {-1, -1};
        int mx = INT_MIN, mi = INT_MAX, n = array.size();
        int left = -1, right = -1;
        for (int i = 0; i < n; ++i) {
            if (array[i] >= mx) mx = array[i]; // 从左向右更新最大值
            else right = i;
            int j = n - 1 - i;
            if (array[j] <= mi) mi = array[j]; // 从右向左更新最小值
            else left = j;
        }
        return {left, right};
    }
};