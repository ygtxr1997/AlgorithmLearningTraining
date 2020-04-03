#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;
const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 多个F节点和J节点同时bfs，并且F先于J入队列
int T, R, C;
char maze[1001][1001]; // 迷宫
bool visitedF[1001][1001] = { 0 }; // 保存F走过的位置
bool visitedJ[1001][1001] = { 0 }; // 保存J走过的位置
pii start; // J初始位置
vector<pii> fires; // 多个F的初始位置
int bfs(void) {
    memset(visitedF, 0, sizeof(bool) * 1001 * 1001);
    memset(visitedJ, 0, sizeof(bool) * 1001 * 1001);
    queue<piiii> qu; // <<x, y>, <type, step>>
    for (int i = 0; i < fires.size(); ++i) { 
        qu.push(piiii(fires[i], pii('F', 0))); 
        visitedF[fires[i].first][fires[i].second] = 1;
    }
    qu.push(piiii(start, pii('J', 0)));
    visitedJ[start.first][start.second] = 1;
    int step = 0;
    while (!qu.empty()) {
        int x = qu.front().first.first, y = qu.front().first.second, type = qu.front().second.first;
        step = qu.front().second.second;
        if (type == 'F') { // 该点是火
            for (int op = 0; op < 4; op++) {
                int n_x = x + dir[op][0], n_y = y + dir[op][1];
                if (n_x >= 0 && n_x < R && n_y >= 0 && n_y < C && visitedF[n_x][n_y] == 0 
                    && maze[n_x][n_y] != '#') {
                    visitedF[n_x][n_y] = 1;
                    qu.push(piiii(pii(n_x, n_y), pii('F', step + 1)));
                }
            }
        } else if (type == 'J') { // 该点J是上次走到的地方
            if (x == 0 || x == R - 1 || y == 0 || y == C - 1) return step;
            for (int op = 0; op < 4; op++) {
                int n_x = x + dir[op][0], n_y = y + dir[op][1];
                if (n_x >= 0 && n_x < R && n_y >= 0 && n_y < C && visitedF[n_x][n_y] == 0
                    && visitedJ[n_x][n_y] == 0 && maze[n_x][n_y] != '#') {
                    visitedJ[n_x][n_y] = 1;
                    qu.push(piiii(pii(n_x, n_y), pii('J', step + 1)));
                }
            }
        }
        qu.pop();
    }
    return -1;
}

int main(void) {
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> R >> C;
        memset(maze, 0, sizeof(char) * 1001 * 1001);
        fires.clear();
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                cin >> maze[i][j];
                if (maze[i][j] == 'J') start = pii(i, j);
                else if (maze[i][j] == 'F') fires.push_back(pii(i, j));
            }
        }
        int ans = bfs();
        if (ans == -1) cout << "IMPOSSIBLE" << endl;
        else cout << ans + 1 << endl;
    }
    return 0;
}