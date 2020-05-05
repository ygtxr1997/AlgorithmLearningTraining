// ---------------------------------------------------------------------
// 题目描述:
// FJ 搭了一间有 N 个牛舍的小屋, 牛舍排在一条线上, 第i号牛舍在 xi 的位置.
// 但是他的 M 头牛对小屋很不满意, 因此经常互相攻击.
// FJ 为了防止牛互相攻击, 因此决定把每头牛都放在离其他牛尽可能远的牛舍.
// 也就是要最大化最近的两头牛之间的距离.(最大化最小值)
// ---------------------------------------------------------------------
// 思路:
// 最大化最小值或者最小化最大值, 通常用二分搜索可以很好的解决.
// 定义 C(d):= 可以安排牛的位置使得任意两头牛距离大于等于 d
// 问题变成了求满足 C(d) 的最大的 d, 对于 C(d) 的判断用贪心即可,
// 如果第 j 头牛在位置 xj, 那么第 j+1 头牛就要放在满足 xj+d<=xk 的最小 xk 中
// ---------------------------------------------------------------------
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 100010;
const int INF = 0x3f3f3f3f;

int N, C; // 牛舍数, 牛数
int X[maxn];
// 判断两头牛最小距离为 d 时是否满足条件
bool Judge(int d) {
    int last = 0; // 第一头牛的位置在 x0
    for (int i = 1; i < C; ++i) {
        int cur = last + 1;
        while (cur < N && X[cur] - X[last] < d) cur++;
        if (cur == N) return false; // 放不下C头牛
        last = cur;
    }
    return true; // 可以放C头牛
}
int solve(void) {
    sort(X, X + N); // 先按从小到大排序
    int lb = 0, ub = INF; // 开区间
    while (ub - lb > 1) { // 因为mid不可能为小数, 所以终止条件为ub-lb==1
        int mid = (lb + ub) / 2;
        if (Judge(mid)) lb = mid;
        else ub = mid;
    }
    return lb; // 必须返回lb, 假设ub-lb=2, 如果judge(mid)为true, 那么应该返回mid
               //                         如果judge(mid)为false, 应该返回lb
}
int main(void) {
    while (scanf("%d%d", &N, &C) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &X[i]);
        printf("%d\n", solve());
    }
    return 0;
}