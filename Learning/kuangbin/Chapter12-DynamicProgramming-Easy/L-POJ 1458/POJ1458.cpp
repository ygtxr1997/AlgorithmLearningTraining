#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

char A[maxn];
char B[maxn];
int last[maxn]; // 上一行, 滚动数组压缩存储
int dp[maxn]; // 本行

int solve(void) {
    int lA = strlen(A), lB = strlen(B);
    memset(last, 0, sizeof(dp));
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= lA; i++) {
        for (int j = 1; j <= lB; ++j) {
            if (A[i - 1] == B[j - 1]) {
                dp[j] = last[j - 1] + 1;
            } else {
                dp[j] = max(last[j], dp[j - 1]);
            }
        }
        memcpy(last, dp, sizeof(last));
        memset(dp, 0, sizeof(dp));
    }
    return last[lB];
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while (scanf("%s%s", A, B) != EOF) {
        printf("%d\n", solve());
    }
    return 0;
}