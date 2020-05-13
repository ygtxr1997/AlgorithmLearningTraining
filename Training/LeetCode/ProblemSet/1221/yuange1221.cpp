class Solution {
public:
    int balancedStringSplit(string s) {
        if (s.empty()) return 0;
        int n = s.size();
        int sum = 0, ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'R') sum++;
            else sum--;
            if (sum == 0) ans++;
        }
        return ans;
    }
};