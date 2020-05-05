// ---------------------------------------------------------------------
// 题目描述:
// 有N条绳子, 它们的长度分别为Li.
// 如果从他们中切割出K条长度相同的绳子, 这K条绳子每条最长能有多长?
// 答案保留到小数点后2位.
// ---------------------------------------------------------------------
// 思路:
// 设条件C(x):=可以得到K条长度为x的绳子
// 问题变成了求满足条件C(x)的最大的x, x的取值区间为(0, INF).
// 现在的问题是, 给定x, 能否高效地判断C(x)是否成立.
// 由于长度为Li的绳子最多可以切出floor(Li/x)条绳子, 因此:
// C(x)=(Σ(i=1,N)floor(Li/x)是否大于等于K)
// 可以在O(N)的时间内判断出来, 故通过二分的方法, 算法的复杂度为O(NlogINF)
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace::std;
const int maxn = 10010;
const int maxk = 10010;
const int maxl = 100010;
const int INF = 0x3f3f3f3f;

int N, K;
double L[maxn];
// 判断切割长度为x时, 能否至少得到K条绳子
bool C(double x) {
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
        cnt += (int)(L[i] / x);
    }
    return cnt >= K;
}
// 二分
double solve(void) {
    // 上下界
    double lb = 0, ub = INF;
    // 重复循环, 直到解的范围足够小
    for (int i = 0; i < 100; ++i) {
        double mid = (lb + ub) / 2;
        if (C(mid)) lb = mid; // 切割的段数过多, x偏小
        else ub = mid; // 切割的段数过少, x偏大
    }
    // 返回ub或者lb都可以, 因为精度已经够了
    return floor(lb * 100) / 100; // 只保留两位小数
}
int main(void) {
    while (scanf("%d%d", &N, &K) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%lf", &L[i]);
        }
        printf("%.2lf\n", solve());
    }
    return 0;
}