class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> maxCol(n, 0);
        vector<int> maxRow(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                maxCol[i] = max(maxCol[i], grid[i][j]);
                maxRow[i] = max(maxRow[i], grid[j][i]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans += min(maxCol[i], maxRow[j]) - grid[i][j];
            }
        }
        return ans;
    }
};