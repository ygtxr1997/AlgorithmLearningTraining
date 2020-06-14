class Solution {
public:
    vector<string> findLongestSubarray(vector<string>& array) {
        if (array.empty()) return vector<string>();
        vector<int> sum(array.size());
        sum[0] = (array[0][0] >= '0' && array[0][0] <= '9') ? 1 : -1;
        for (int i = 1; i < array.size(); ++i) sum[i] = sum[i - 1] + ((array[i][0] >= '0' && array[i][0] <= '9') ? 1 : -1);
        unordered_map<int, int> hash;
        hash[0] = -1;
        int len = 0, start = 0;
        for (int i = 0; i < sum.size(); ++i) {
            if (hash.count(sum[i])) {
                if (i - hash[sum[i]] > len) {
                    len = i - hash[sum[i]];
                    start = hash[sum[i]] + 1;
                }
            } else hash[sum[i]] = i;
            //printf("sum[%d]=%d | start=%d, len=%d\n", i, sum[i], start, len);
        }
        return vector<string>(array.begin() + start, array.begin() + start + len);
    }
};