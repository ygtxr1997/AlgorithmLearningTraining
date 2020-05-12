// 二分查找
class Solution {
public:
    static const int INF = 0x3f3f3f3f;
    bool C(vector<int>& arr, int target, int value) {
        int n = arr.size();
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] > value) sum += value;
            else sum += arr[i];
            if (sum >= target) return false;
        }
        return sum < target;
    }
    int findBestValue(vector<int>& arr, int target) {
        int lb = 0, ub = INF;
        for (;ub - lb > 1;) {
            int mid = (lb + ub) / 2;
            if (C(arr, target, mid)) lb = mid;
            else ub = mid;
        }
        int suml = 0, sumu = 0;
        for (int i = 0; i < arr.size(); ++i) {
            suml += (arr[i] > lb) ? lb : arr[i];
            sumu += (arr[i] > ub) ? ub : arr[i];
        }
        return abs(suml - target) <= abs(sumu - target) ? lb : ub;
    }
};