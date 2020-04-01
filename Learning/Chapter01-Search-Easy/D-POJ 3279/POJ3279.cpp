#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
using namespace::std;

// 第i行翻转后，第i+1行的翻转位置就确定了
// 从第0行开始字典序遍历翻转位置，那么下面每一行必须按照上一行1的位置翻转
// 直到最后一行，检验最后一行是否全为0，如果是全0，就保存这个结果
int M, N;
int ans, step = 0;
int grid[16][16];
int cur[16][16];
int res[16][16];
int old_grid[16][16];
void dfs(int i) {
    if (i == 0) { // 翻转第0行
        memcpy(old_grid, grid, sizeof(int) * 16 * 16);
        for (int m = 0; m < (1 << N); m++) {
            int m_code = m;
            for (int pos = N - 1; pos >= 0; --pos) {
                if (m_code % 2 == 1) {
                    grid[0][pos] ^= 1; // self
                    grid[0][pos - 1] ^= 1; // left
                    grid[0][pos + 1] ^= 1; // right
                    grid[1][pos] ^= 1; // down
                    step++;
                    cur[0][pos] = 1;
                };
                m_code /= 2;
            }
            dfs(i + 1);
            memcpy(grid, old_grid, sizeof(int) * 16 * 16);
            memset(cur, 0, sizeof(int) * 16 * 16);
            step = 0;
        }
        return;
    }
    else if (i < M) {
        for (int pos = 0; pos < N; ++pos) {
            if (grid[i - 1][pos] == 1) { // 上一层为1的位置，就是这一层要翻转的位置
                grid[i - 1][pos] = 0; // up
                grid[i][pos] ^= 1; // self
                grid[i][pos - 1] ^= 1; // left
                grid[i][pos + 1] ^= 1; // right
                grid[i + 1][pos] ^= 1; // down
                step++;
                cur[i][pos] = 1; 
            };
        }
        dfs(i + 1);
    }
    else {
        int b = 0;
        for (int pos = 0; pos < N; ++pos) {
            if (grid[M - 1][pos] == 1) return; // 最后一层存在黑色方块
        }
        // 最后一行全白，记录此值M
        if (step < ans) {
            ans = step;
            memcpy(res, cur, sizeof(int) * 16 * 16);
        }
    }
}

int main(void) {
    while (cin >> M >> N) {
        ans = INT_MAX;
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                cin >> grid[i][j];
        dfs(0);
        if (ans == INT_MAX) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << res[i][j];
                if (j < N - 1) cout << ' ';
            }
            cout << endl;
        }
    }
    return 0;
}