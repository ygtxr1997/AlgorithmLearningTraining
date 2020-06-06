class Solution {
public:
    vector<int> findSwapValues(vector<int>& array1, vector<int>& array2) {
        int sum1 = 0, sum2 = 0;
        for (int num : array1) sum1 += num;
        for (int num : array2) sum2 += num;
        int dif = sum1 - sum2;
        if (((dif % 2) + 2) % 2) return {}; // 相差为奇数不可能
        int target = dif / 2;
        sort(array2.begin(), array2.end());
        for (int a : array1) {
            if (binary_search(array2.begin(), array2.end(), a - target))
                return {a, a - target};
        }
        return {};
    }
};