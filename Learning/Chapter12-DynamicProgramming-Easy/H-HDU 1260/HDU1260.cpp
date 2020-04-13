#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxk = 2010;
const int INF = 0x3f3f3f3f;

// dp[i] = min{ dp[i-1] + One[i], dp[i-2] + Two[i]}
int N;
int K;
int One[maxk] = { 0 };
int Two[maxk] = { 0 };
int dp[maxk]; // dp[i]:前i个人花费的最少时间, 单位:秒
void solve(void) {
    dp[1] = One[1];
    for (int i = 2; i <= K; ++i) {
        dp[i] = min(dp[i - 1] + One[i], dp[i - 2] + Two[i]);
    }
}
void printAns(void) {
    int h, m, s;
    h = dp[K] / 3600;
    m = (dp[K] - 3600 * h) / 60;
    s = (dp[K] - 3600 * h - 60 * m);
    char cm = (h + 8) >= 12 ? 'p' : 'a';
    h = (h + 8) % 12;
    printf("%02d:%02d:%02d %cm\n", h, m, s, cm);
}

int main(void) {
    scanf("%d", &N);
    while (N--) {
        memset(dp, 0, sizeof(dp));
        scanf("%d", &K);
        for (int i = 1; i <= K; ++i) {
            scanf("%d", &One[i]);
        }
        for (int i = 2; i <= K; ++i) {
            scanf("%d", &Two[i]);
        }
        solve();
        printAns();
    }
    return 0;
}