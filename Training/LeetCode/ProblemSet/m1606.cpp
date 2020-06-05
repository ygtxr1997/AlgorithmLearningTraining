class Solution {
public:
    typedef long long ll;
    int smallestDifference(vector<int>& a, vector<int>& b) {
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ll ans = LONG_MAX;
        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            ans = min(ans, abs((ll)a[i] - (ll)b[j]));
            if (a[i] < b[j]) i++;
            else j++;
        }
        return ans;
    }
};