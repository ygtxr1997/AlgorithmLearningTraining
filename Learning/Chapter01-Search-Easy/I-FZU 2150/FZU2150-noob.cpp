#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

// 选择两个不同的起点，同时BFS
// 这种方法已经不行了，不管怎么优化都会TLE
int T, n, m;
char grid[11][11];
int grass;
// 两个起点同时BFS
int bfs(int x1, int y1, int x2, int y2) {
    queue<piii> qu;
    int visited[11][11] = { 0 };
    int step = 0, burn = 0;
    qu.push(piii(pii(x1, y1), 0)); qu.push(piii(pii(x2, y2), 0));
    visited[x1][y1] = visited[x2][y2] = 1;
    while (!qu.empty()) {
        int x = qu.front().first.first, y = qu.front().first.second;
        step = qu.front().second; burn++;
        if (x + 1 < n && visited[x + 1][y] == 0 && grid[x + 1][y] == '#') { 
            visited[x + 1][y] = 1; qu.push(piii(pii(x + 1, y), step + 1)); }
        if (x - 1 <= 0 && visited[x - 1][y] == 0 && grid[x - 1][y] == '#') { 
            visited[x - 1][y] = 1; qu.push(piii(pii(x - 1, y), step + 1)); }
        if (y + 1 < m && visited[x][y + 1] == 0 && grid[x][y + 1] == '#') { 
            visited[x][y + 1] = 1; qu.push(piii(pii(x, y + 1), step + 1)); }
        if (y - 1 >= 0 && visited[x][y - 1] == 0 && grid[x][y - 1] == '#') { 
            visited[x][y - 1] = 1; qu.push(piii(pii(x, y - 1), step + 1)); }
        qu.pop();
    }
    if (burn == grass) return step;
    else return INT_MAX;
}

int main(void) {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> n >> m;
        memset(grid, 0, sizeof(char) * 121);
        grass = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == '#') grass++;
            }
        int ans = INT_MAX;
        for (int x1 = 0; x1 < n; ++x1) {
            for (int y1 = 0; y1 < m; ++y1) {
                for (int x2 = x1; x2 < n; ++x2) {
                    for (int y2 = y1; y2 < m; ++y2) {
                        if (x1 == x2 && y1 == y2) continue;
                        if (grid[x1][y1] != '#' || grid[x2][y2] != '#') continue;
                        int tmp = bfs(x1, y1, x2, y2);
                        ans = min(ans, tmp);
                    }
                }
            }
        }
        if (ans == INT_MAX) ans = -1;
        cout << "Case " << t << ": " << ans << endl;
    }
}