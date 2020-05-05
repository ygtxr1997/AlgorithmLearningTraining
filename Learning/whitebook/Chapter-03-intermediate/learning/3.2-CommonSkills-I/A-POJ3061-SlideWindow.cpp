// ---------------------------------------------------------------------
// 题目描述:
// 给定长度为 n 的数组(数组元素均为正数)以及整数 S.
// 求出总和不小于 S 的连续子序列的长度的最小值, 如果不存在则输出0.
// ---------------------------------------------------------------------
// 思路二:
// 滑动窗口
// 设滑动窗口左边界为s, 右边界为t, 
// x x x {a[s] a[s+1] ... a[t-2] a[t-1]} a[t] x x x x x
// 若 sum[s ~ t-1] 为恰好不小于 S 的连续子序列,
// 则有 sum[s+1 ~ t-2] < sum[s ~ t-2] < S
// x x x a[s] {a[s+1] ... a[t-2] a[t-1]} a[t] x x x x x
// 设 sum[s+1 ~ t'-1] 为恰好不小于 S 的连续子序列,
// 则必然有 t <= t'
// ---------------------------------------------------------------------
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 100010;

int T;
int N, S;
int arr[maxn];

int solve(void) {
    int res = N + 1;
    int s = 0, t = 0, sum = 0;
    while (1) {
        while (t < N && sum < S) sum += arr[t++];
        if (sum < S) break; // 找不到大于等于 S 的连续子序列
        res = min(res, t - s); // 每找到一个大于等于 S 的连续子序列, 就更新 res
        sum -= arr[s++]; // 并且左边界向右移动一格
    }
    if (res > N) res = 0;
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
