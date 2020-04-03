#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef pair<pii, pii> piiii;
const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 搞清题目意思，两个人不能同时移动
int n, m;
char grid[201][201];
bool visited[201][201][2]; // 0:Y, 1:M
int kfcTime[201][201][2];
pii pY, pM;
int bfs() {
    int ans = INT_MAX;
    memset(visited, 0, sizeof(bool) * 201 * 201 * 2);
    for (int i = 0; i < 201; ++i) for (int j = 0; j < 201; ++j) kfcTime[i][j][0] = kfcTime[i][j][1] = INT_MAX;
    queue<piiii> qu; // <<x, y>, <person, step>>
    qu.push(piiii(pY, pii('Y', 0)));
    qu.push(piiii(pM, pii('M', 0)));
    visited[pY.first][pY.second][0] = visited[pM.first][pM.second][1] = 1;
    while (!qu.empty()) {
        int x = qu.front().first.first, y = qu.front().first.second,
            person = qu.front().second.first;
        int step = qu.front().second.second;
        if (grid[x][y] == '@') {
            if (person == 'Y') kfcTime[x][y][0] = step;
            else kfcTime[x][y][1] = step;
            if (kfcTime[x][y][0] != INT_MAX && kfcTime[x][y][1] != INT_MAX)
                ans = min(ans, kfcTime[x][y][0] + kfcTime[x][y][1]);
            //cout << kfcTime[x][y][0] << '-' << kfcTime[x][y][1] << endl;
        }
        int p = person == 'Y' ? 0 : 1;
        for (int op = 0; op < 4; ++op) {
            int n_x = x + dir[op][0], n_y = y + dir[op][1];
            if (n_x >= 0 && n_x < n && n_y >= 0 && n_y < m
                && grid[n_x][n_y] != '#' && visited[n_x][n_y][p] == 0) {
                    visited[n_x][n_y][p] = 1;
                    qu.push(piiii(pii(n_x, n_y), pii(person, step + 1)));
                }
        }
        qu.pop();
    }
    return ans;
}

int main(void) {
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == 'Y') pY = pii(i, j);
                else if (grid[i][j] == 'M') pM = pii(i, j);
            }
        }
        int ans = bfs();
        cout << ans * 11 << endl;
    }
}