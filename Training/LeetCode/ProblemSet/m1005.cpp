class Solution {
public:
    int findString(vector<string>& words, string s) {
        int left = 0, right = words.size() - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            while (mid <= right && words[mid].empty()) mid++;
            if (mid > right) right = (left + right) / 2 - 1;
            else {
                if (words[mid] > s) right = (left + right) / 2 - 1;
                else if (words[mid] < s) left = mid + 1;
                else return mid;
            }
        }
        return -1;
    }
};