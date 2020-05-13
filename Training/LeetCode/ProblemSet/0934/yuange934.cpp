class Solution {
public:
    typedef pair<int, int> pii;
    typedef pair<pii, int> piii;
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    int shortestBridge(vector<vector<int>>& A) {
        int m = A.size(), n = A[0].size();
        pii start;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][j] == 1) {
                    start = pii(i, j);
                    break;
                }
            }
        }
        queue<pii> qu1; // 标记第一个岛的所有点
        qu1.push(start);
        A[start.first][start.second] = -1;
        while (!qu1.empty()) {
            int x = qu1.front().first, y = qu1.front().second;
            qu1.pop();
            for (int op = 0; op < 4; ++op) {
                int nx = x + dir[op][0], ny = y + dir[op][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && A[nx][ny] == 1) {
                    A[nx][ny] = -1;
                    qu1.push(pii(nx, ny));
                }
            }
        }
        queue<piii> qu2; // 多起点BFS
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (A[i][j] == -1) {
                    qu2.push(piii(pii(i, j), 0));
                }
            }
        }
        while (!qu2.empty()) {
            int x = qu2.front().first.first, y = qu2.front().first.second, step = qu2.front().second;
            qu2.pop();
            for (int op = 0; op < 4; ++op) {
                int nx = x + dir[op][0], ny = y + dir[op][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && A[nx][ny] != -1) {
                    if (A[nx][ny] == 1) return step;
                    A[nx][ny] = -1;
                    qu2.push(piii(pii(nx, ny), step + 1));
                }
            }
        }
        return -1;
    }
};