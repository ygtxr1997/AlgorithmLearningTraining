class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        if (timeSeries.empty()) return 0;
        int n = timeSeries.size(), ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            ans += min(timeSeries[i + 1] - timeSeries[i], duration);
        }
        return ans + duration;
    }
};