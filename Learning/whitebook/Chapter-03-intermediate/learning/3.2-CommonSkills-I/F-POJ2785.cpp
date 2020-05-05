// ---------------------------------------------------------------------
// 题目描述:
// 给定四个元素个数均为 n 的数列 A, B, C, D,
// 从每个数列取一个数, 使四个数的和为0.
// 求出这样的组合的个数, 当一个数列有多个相同的数字时, 把它们当作不同数字看待.
// ---------------------------------------------------------------------
// 思路:
// 普通暴力枚举的时间是O(n^4), 会超时
// 用折半的思想, 先求出 A 和 B 之和的所有可能情况, O(n^2),
// 再求 C 和 D 之和的所有可能情况, O(n^2),
// 对于 A+B 的每一个值 S1, 在排序后的 C+D 中进行二分查找 -S1.
// 总时间复杂度是 O(n^2logn).
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 4010;

int N;
int A[maxn], B[maxn], C[maxn], D[maxn];
int CD[maxn * maxn];

void solve(void) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            CD[i * N + j] = C[i] + D[j];
        }
    }
    sort(CD, CD + N * N);
    long long res = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; ++j) {
            int cd = -(A[i] + B[j]);
            // 二分查找所有等于cd的元素个数
            res += upper_bound(CD, CD + N * N, cd) - lower_bound(CD, CD + N * N, cd);
        }
    }
    printf("%lld\n", res);
}

int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
        }
        solve();
    }
    return 0;
}