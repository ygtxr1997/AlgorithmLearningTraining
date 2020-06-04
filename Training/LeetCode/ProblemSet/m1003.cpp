class Solution {
public:
    int search(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (arr[left] < arr[mid]) { // 左边区间升序
                if (arr[left] <= target && arr[mid] >= target) right = mid;
                else left = mid + 1;
            } else if (arr[left] > arr[mid]) { // 左边区间断开
                if (arr[mid] <= target && arr[right] >= target && arr[left] != arr[right]) left = mid;
                else right = mid - 1;
            } else { // 找到目标, 或者是重复值
                if (arr[left] != target) left++;
                else right = left;
            }
        }
        return arr[left] == target ? left : -1;
    }
};