#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 10010;
const int INF = 0x3f3f3f3f;
typedef long long ll; // 题目说了32位整数可能不够用

int N, S;
ll C[maxn], Y[maxn];
ll solve(void) {
    ll sum = 0, min_cost = INF;
    for (int i = 0; i < N; ++i) {
        min_cost = min(min_cost, C[i]);
        sum += min_cost * Y[i];
        min_cost += S; // 每过一周, min_cost增加S
    }
    return sum;
}

int main(void) {
    while (scanf("%d%d", &N, &S) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%lld%lld", &C[i], &Y[i]);
        }
        ll ans = solve();
        printf("%lld\n", ans);
    }
    return 0;
}