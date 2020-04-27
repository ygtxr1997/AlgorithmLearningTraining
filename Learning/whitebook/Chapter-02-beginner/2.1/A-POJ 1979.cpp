#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 25;
typedef pair<int, int> pii;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int W, H;
pii start;
char M[maxn][maxn];
int dfs(int x, int y) {
    int cnt = 1;
    for (int op = 0; op < 4; op++) {
        int n_x = x + dir[op][0], n_y = y + dir[op][1];
        if (n_x >= 0 && n_x < H && n_y >= 0 && n_y < W && M[n_x][n_y] == '.') {
            M[n_x][n_y] = '#';
            cnt += dfs(n_x, n_y);
        }
    }
    return cnt;
}

int main(void) {
    while (scanf("%d %d", &W, &H) && W + H != 0) {
        for (int i = 0; i < H; ++i) {
            scanf("%s", M[i]);
        }
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                if (M[i][j] == '@') start = pii(i, j);
            }
        }
        int ans = dfs(start.first, start.second);
        printf("%d\n", ans);
    }
    return 0;
}