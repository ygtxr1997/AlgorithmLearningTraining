class Solution {
public:
    int maxAliveYear(vector<int>& birth, vector<int>& death) {
        int n = birth.size();
        vector<int> cnt(2500);
        for (int i = 0; i < n; ++i) { // 只关注起点和终点, 代表该年净增人口, 然后统计前缀和即来到该年的总人数
            cnt[birth[i]]++;
            cnt[death[i] + 1]--;
        }
        vector<int> sum(2500);
        int ans = 0, year = -1;
        for (int i = 1900; i <= 2000; i++) {
            sum[i] = sum[i - 1] + cnt[i];
            if (sum[i] > ans) {
                ans = sum[i];
                year = i;
            }
        }
        return year;
    }
};