#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace::std;
const int maxn = 6;
const int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

// 用set保存得到的数字
set<int> res;
int grid[maxn][maxn];
int step = 1;
void dfs(int num, int x, int y) {
    if (step > 6) { res.insert(num); return;}
    for (int op = 0; op < 4; ++op) {
        int ni = x + dir[op][0], nj = y + dir[op][1];
        if (ni >= 0 && ni < 5 && nj >= 0 && nj < 5) {
            step++;
            dfs(num * 10 + grid[ni][nj], ni, nj);
            step--;
        }
    }
}

int main(void) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            scanf("%d", &grid[i][j]);
        }
    }
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; ++j) {
            dfs(0, i, j);
        }
    int ans = res.size();
    printf("%d\n", ans);
    return 0;
}