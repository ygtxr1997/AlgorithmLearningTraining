#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
const int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                        {0, -1}, {0, 1},
                        {1, -1}, {1, 0}, {1, 1} };

// 简单的老题，BFS
int m, n;
char grid[101][101];
int bfs() {
    bool visited[101][101] = { 0 };
    int count = 0;
    queue<pii> qu;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '@' && visited[i][j] == 0) {
                visited[i][j] = 1;
                qu.push(pii(i, j));
                while (!qu.empty()) {
                    int x = qu.front().first, y = qu.front().second;
                    for (int op = 0; op < 8; ++op) {
                        int n_x = x + dir[op][0], n_y = y + dir[op][1];
                        if (n_x >= 0 && n_x < m && n_y >= 0 && n_y < n 
                            && visited[n_x][n_y] == 0 && grid[n_x][n_y] == '@') {
                                visited[n_x][n_y] = 1;
                                qu.push(pii(n_x, n_y));
                            }
                    }
                    qu.pop();
                }
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    while ((cin >> m >> n) && m != 0 && n!= 0) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        cout << bfs() << endl;
    }
    return 0;
}