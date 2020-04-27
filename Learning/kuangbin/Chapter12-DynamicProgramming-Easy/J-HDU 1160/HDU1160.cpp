#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int INF = 0x3f3f3f3f;

typedef struct Mouse {
    Mouse() {}
    Mouse(int x1, int x2, int x3) : w(x1), s(x2), id(x3) {}
    bool operator<(Mouse m2) const {
        if (w < m2.w) return true;
        else if (w == m2.w) return s > m2.s; 
        return false; 
    }
    int w, s, id;
} Mouse;
Mouse M[maxn];
int dp[maxn]; // dp[i]:以第i只老鼠结尾的最长递增子序列
int pre[maxn];
int tail;
int n;
int maxLen;
void printAns(int index) {
    if (index == -1) return;
    printAns(pre[index]);
    printf("%d\n", M[index].id);
}

void solve(void) {
    memset(dp, 0, sizeof(dp));
    memset(pre, -1, sizeof(pre));
    M[0].w = -INF, M[0].s = INF;
    maxLen = 1;
    dp[1] = 1; tail = 1;
    sort(M + 1, M + n + 1);
    for (int i = 2; i <= n; ++i) {
        dp[i] = 1; // 最少是1, 这里易漏
        for (int j = 1; j < i; ++j) {
            if (M[j].w < M[i].w && M[j].s > M[i].s) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                    if (dp[i] > maxLen) {
                        maxLen = dp[i];
                        tail = i;
                    }
                }
            }
        }
    }
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int i = 1;
    while (scanf("%d%d", &M[i].w, &M[i].s) != EOF) {
        M[i].id = i;
        i++;
    }
    n = i - 1;
    solve();
    printf("%d\n", maxLen);
    printAns(tail);
    return 0;
}