// ---------------------------------------------------------------------
// 题目描述:
// 给定长度为 n 的数组(数组元素均为正数)以及整数 S.
// 求出总和不小于 S 的连续子序列的长度的最小值, 如果不存在则输出0.
// ---------------------------------------------------------------------
// 思路一:
// 前缀和 + 二分搜索
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 100010;

int T;
int N, S;
int arr[maxn];
int sum[maxn]; // 前缀和
int solve(void) {
    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < N; ++i) {
        sum[i + 1] = sum[i] + arr[i];
    }
    if (sum[N] < S) return 0; // 不存在这样的连续子序列
    int res = N;
    for (int i = 0; sum[i] + S <= sum[N]; ++i) {
        int pos = lower_bound(sum + i, sum + N, sum[i] + S) - sum;
        res = min(res, pos - i);
    }
    return res;
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &S);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", solve());
    }
    return 0;
}
