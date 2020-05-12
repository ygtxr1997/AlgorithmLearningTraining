class Solution {
public:
    inline int min4(int a, int b, int c, int d) {
        return min((a < b ? a : b), (c < d ? c : d));
    }
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>> grid(N, vector<int>(N, 1));
        for (int i = 0; i < mines.size(); ++i) grid[mines[i][0]][mines[i][1]] = 0;
        // 四个方向的最长连续1的个数
        vector<vector<int>> up(N, vector<int>(N, 0));
        vector<vector<int>> down(N, vector<int>(N, 0));
        vector<vector<int>> left(N, vector<int>(N, 0));
        vector<vector<int>> right(N, vector<int>(N, 0));
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j < N; ++j) {
                if (grid[j - 1][i] == 1) up[j][i] = up[j - 1][i] + 1;
                else up[j][i] = 0;
                if (grid[N - j][i] == 1) down[N - j - 1][i] = down[N - j][i] + 1;
                else down[N - j - 1][i] = 0;
                if (grid[i][j - 1] == 1) left[i][j] = left[i][j - 1] + 1;
                else left[i][j] = 0;
                if (grid[i][N - j] == 1) right[i][N - j - 1] = right[i][N - j] + 1;
                else right[i][N - j - 1] = 0;
            }
        }
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == 1) {
                    ans = max(ans, 1 + min4(up[i][j], down[i][j], left[i][j], right[i][j]));
                }
            }
        }
        return ans;
    }
};