#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace::std;
const int maxm = 32;
const int maxn = 27;

int R, C;
int N;
char grid[maxm][maxm];
int under[maxm][maxm];
int vis[maxn];
bool check(char letter) {
    int tmp[maxm][maxm];
    memcpy(tmp, under, sizeof(tmp));
    for (int i = R - 1; i >= 0; --i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == letter) {
                if (tmp[i][j] == 0) continue;
                return false;
            }
        }
    }
    return true;
}
void solve(void) {
    for (int i = 0; i < R; ++i) {
        fill(under[i], under[i] + C, R - i - 1);
    }
    memset(vis, -1, sizeof(vis));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) vis[grid[i][j] - 'A'] = 0;
    }
    N = 0;
    for (int i = 0; i < maxn; ++i) if (vis[i] == 0) N++;
    int col[maxn] = { 0 }; // col[k]:第j列字母k有多少个
    for (int j = 0; j < C; ++j) {
        memset(col, 0, sizeof(col));
        for (int i = R - 1; i >= 0; --i) {
            char ch = grid[i][j];
            under[i][j] -= col[ch - 'A'];
            col[ch - 'A']++;
        }
    }
    for (int i = 0; i < N; ++i) { // 轮数
        bool find = 0;
        for (int j = 0; j < maxn; ++j) { // 枚举所有未访问的
            if (vis[j] == 0) {
                char letter = 'A' + j;
                if (check(letter)) {
                    find = 1;
                    vis[j] = i + 1;
                    for (int jj = 0; jj < C; ++jj) { // 列
                        int sum = 0;
                        for (int ii = R - 1; ii >= 0; --ii) { // 行
                            if (grid[ii][jj] == letter) sum++;
                            else under[ii][jj] -= sum;
                        }
                    }
                    int test = 0;
                }
            }
            if (find) break;
        }
        if (!find) {
            printf("-1\n");
            return;
        }
    }
    char ans[maxn] = { 0 };
    for (int i = 0; i < maxn; ++i) {
        if (vis[i] > 0) {
            ans[vis[i] - 1] = 'A' + i;
        }
    }
    printf("%s\n", ans);
}
int main(void) {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &R, &C);
        getchar();
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                grid[i][j] = getchar();
            }
            getchar();
        }
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}