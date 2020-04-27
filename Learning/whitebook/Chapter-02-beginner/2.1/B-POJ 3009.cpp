#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 23;
const int INF = 0x7f7f7f7f;
typedef pair<int, int> pii;
const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int w, h;
int M[maxn][maxn];
pii start, goal;
int step;
int ans;
void dfs(int i, int j) {
    if (step > 10) return;
    for (int op = 0; op < 4; ++op) {
        int n_i = i + dir[op][0], n_j = j + dir[op][1];
        bool bCanMove = 0; // 必须添加该变量，因为如果开局被石头包围就无法移动并且相邻的石头无法击碎
        while (n_i >= 1 && n_i <= h && n_j >= 1 && n_j <= w && M[n_i][n_j] != 1) {
            bCanMove = 1;
            if (n_i == goal.first && n_j == goal.second) break;
            n_i += dir[op][0];
            n_j += dir[op][1];
        }
        if (n_i == goal.first && n_j == goal.second) ans = min(ans, step);
        if (M[n_i][n_j] == 1 && bCanMove) { // 必须沿该直线找到石头才行
            step++;
            M[n_i][n_j] = 0;
            dfs(n_i - dir[op][0], n_j - dir[op][1]);
            M[n_i][n_j] = 1;
            step--;
        }
    }
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &w, &h) && w + h != 0) {
        memset(M, 0, sizeof(M)); // 一定要初始化, 否则边界可能判定有石头
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; ++j) {
                scanf("%d", &M[i][j]);
                if (M[i][j] == 2) start = pii(i, j);
                else if (M[i][j] == 3) goal = pii(i, j);
            }
        }
        step = 1, ans = INF;
        dfs(start.first, start.second);
        printf("%d\n", ans == INF ? -1 : ans);
    }
    return 0;
}