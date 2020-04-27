#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
const int dir[8][2] = { {-1, -1}, {-1, 0}, {-1, 1},
                        {0, -1}, {0, 1},
                        {1, -1}, {1, 0}, {1, 1} };

// 再试试DFS的方法
int m, n;
char grid[101][101];
bool visited[101][101];
// 找到和(x,y)相连的所有方块
bool dfs(int x, int y) {
    if (grid[x][y] == '*' || visited[x][y] == 1) return false;
    visited[x][y] = 1;
    for (int op = 0; op < 8; ++op) {
        int n_x = x + dir[op][0], n_y = y + dir[op][1];
        if (n_x >= 0 && n_x < m && n_y >= 0 && n_y < n 
            && visited[n_x][n_y] == 0 && grid[n_x][n_y] == '@') {
            dfs(n_x, n_y);
        } 
    }
    return true;
}

int main(void) {
    while ((cin >> m >> n) && m != 0 && n!= 0) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        memset(visited, 0, sizeof(bool) * 101 * 101);
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(i, j)) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}