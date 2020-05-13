class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        int sum = 0;
        for (int i = 0; i < k; ++i) sum += arr[i];
        int ans = 0;
        if (sum >= k * threshold) ans++;
        for (int i = 1; i + k - 1 < arr.size(); ++i) {
            sum -= arr[i - 1];
            sum += arr[i + k - 1];
            if (sum >= k * threshold) ans++;
        }
        return ans;
    }
};