#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace::std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
const int dir[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

// 比较简单的BFS问题，另设一个save保存经过的每个节点到起点的最短距离
// 得到最短距离后，再从终点反向寻找起点
int maze[5][5];
int save[5][5];
vector<pii> res;
void getAns(void) {
    int step = save[4][4];
    int x = 4, y = 4;
    while (step >= 0) {
        res.push_back(pii(x, y));
        for (int op = 0; op < 4; ++op) {
            int n_x = x + dir[op][0], n_y = y + dir[op][1];
            if (n_x >= 0 && n_x < 5 && n_y >= 0 && n_y < 5 
                && save[n_x][n_y] == step - 1) {
                    x = n_x;
                    y = n_y;
                    break;
                }
        }
        step--;
    }
}

void bfs(void) {
    queue<piii> qu;
    qu.push(piii(pii(0, 0), 0));
    save[0][0] = 0;
    while (!qu.empty()) {
        int x = qu.front().first.first, y = qu.front().first.second;
        int step = qu.front().second;
        for (int op = 0; op < 4; ++op) {
            int n_x = x + dir[op][0], n_y = y + dir[op][1];
            if (n_x >= 0 && n_x < 5 && n_y >= 0 && n_y < 5 && maze[n_x][n_y] == 0
                && save[n_x][n_y] == INT_MAX) {
                qu.push(piii(pii(n_x, n_y), step + 1));
                save[n_x][n_y] = step + 1;
                if (n_x == 4 && n_y == 4) return; // finded
            }
        }
        qu.pop();
    }
}

int main(void) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> maze[i][j];
            save[i][j] = INT_MAX;
        }
    }
    bfs();
    getAns();
    for (int i = res.size() - 1; i >= 0; --i) {
        printf("(%d, %d)\n", res[i].first, res[i].second);
    }
    return 0;
}