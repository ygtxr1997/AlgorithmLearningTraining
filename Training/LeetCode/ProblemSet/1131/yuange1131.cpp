// 枚举, 通过枚举去绝对值
class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        const int dir[8][3] = {{1,1,1}, {1,1,-1}, {1,-1,1}, {1,-1,-1}, {-1,1,1}, {-1,1,-1}, {-1,-1,1}, {-1,-1,-1}};
        const int INF = 0x3f3f3f3f;
        int n = arr1.size();
        vector<int> mx(8, -INF);
        for (int op = 0; op < 8; ++op) {
            for (int i = 0; i < n; ++i) {
                mx[op] = max(mx[op], arr1[i] * dir[op][0] + arr2[i] * dir[op][1] + i * dir[op][2]);
            }
        }
        int ans = -INF;
        for (int op = 0; op < 8; ++op) {
            for (int j = 0; j < n; ++j) {
                ans = max(ans, mx[op] - (arr1[j] * dir[op][0] + arr2[j] * dir[op][1] + j * dir[op][2]));
            }
        }
        return ans;
    }
};