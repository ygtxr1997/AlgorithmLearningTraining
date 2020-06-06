class Solution {
public:
    int dir[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
    int n, m;
    typedef pair<int, int> pii;
    int bfs(vector<vector<int>>& G, int i, int j) {
        int cnt = 0;
        queue<pii> qu;
        qu.push(pii(i, j));
        G[i][j] = 1;
        while (!qu.empty()) {
            int x = qu.front().first, y = qu.front().second;
            cnt++;
            qu.pop();
            for (int op = 0; op < 8; ++op) {
                int nx = x + dir[op][0], ny = y + dir[op][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !G[nx][ny]) {
                    G[nx][ny] = 1;
                    qu.push(pii(nx, ny));
                }
            }
        }
        return cnt;
    }
    vector<int> pondSizes(vector<vector<int>>& land) {
        vector<int> ret;
        n = land.size(), m = land[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (land[i][j]) continue;
                int ans = bfs(land, i, j);
                if (ans) ret.push_back(ans);
            }
        }
        sort(ret.begin(), ret.end());
        return ret;
    }
};