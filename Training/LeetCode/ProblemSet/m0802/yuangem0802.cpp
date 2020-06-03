class Solution {
public:
    vector<vector<int>> ret;
    int n, m;
    int dir[2][2] = {1, 0, 0, 1};
    bool finded = 0;
    void dfs(vector<vector<int>>& G, int x, int y) {
        if (x == n - 1 && y == m - 1) {
            finded = 1;
            ret.push_back(vector<int>({x, y}));
            return;
        }
        ret.push_back(vector<int>({x, y}));
        for (int op = 0; op < 2 && !finded; ++op) {
            int nx = x + dir[op][0], ny = y + dir[op][1];
            if (nx >= n || ny >= m) continue;
            if (G[nx][ny]) continue;
            G[nx][ny] = 1;
            dfs(G, nx, ny);
        }
        if (!finded) ret.pop_back();
    }
    vector<vector<int>> pathWithObstacles(vector<vector<int>>& obstacleGrid) {
        n = obstacleGrid.size(), m = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1) return ret;
        if (n == 1 && m == 1 && obstacleGrid[0][0] == 0) { ret.push_back(vector<int>(2, 0)); return ret;}
        dfs(obstacleGrid, 0, 0);
        return ret;
    }
};