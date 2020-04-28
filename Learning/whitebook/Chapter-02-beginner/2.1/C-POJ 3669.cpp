#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace::std;
typedef struct node {
    node(){}
    node(int a, int b, int c) : x(a), y(b), step(c) {}
    int x, y, step;
} node;
const int maxn = 310;
const int INF = 0x3f3f3f3f;
const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

// 把问题转化为找到迷宫中最近的INF, 并且在寻找过程中的step必须小于流星最早到达的时间
int M;
int grid[maxn][maxn];
int vis[maxn][maxn];

int bfs(void) {
    if (grid[0][0] == 0) return -1; // 起点在第0秒被炸
    memset(vis, 0, sizeof(vis));
    queue<node> qu;
    qu.push(node(0, 0, 0));
    vis[0][0] = 1;
    while (!qu.empty()) {
        int x = qu.front().x, y = qu.front().y;
        int step = qu.front().step;
        qu.pop();
        if (grid[x][y] == INF) return step; // 找到最近的
        for (int op = 0; op < 4; ++op) {
            int n_x = x + dir[op][0], n_y = y + dir[op][1];
            // 来到该点的步数小于流星来到该点的最早时间
            if (n_x >= 0 && n_y >= 0 && !vis[n_x][n_y] && step + 1 < grid[n_x][n_y]) {
                qu.push(node(n_x, n_y, step + 1));
                vis[n_x][n_y] = 1;
            }
        }
    }
    return -1; // 不存在合法路径
}

int main(void) {
    while (scanf("%d", &M) != EOF) {
        memset(grid, 0x3f, sizeof(grid));
        for (int i = 0; i < M; ++i) {
            int x, y, t;
            scanf("%d%d%d", &x, &y, &t);
            grid[x][y] = min(grid[x][y], t);
            for (int op = 0; op < 4; ++op) {
                int n_x = x + dir[op][0], n_y = y + dir[op][1];
                if (n_x >= 0 && n_y >= 0) grid[n_x][n_y] = min(grid[n_x][n_y], t); // 周围的也要被炸
            }
        }
        int ans = bfs();
        printf("%d\n", ans);
    }
    return 0;
}