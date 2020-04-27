#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 2010;
const long long INF = 0x3f3f3f3f3f3f3f3f;
typedef long long ll;
ll Hash[maxn]; // 把各个高度从小到大重新映射

// 使用滚动数组优化内存, 进一步优化至1个dp数组
int N;
ll vec[maxn];
ll dp[maxn]; // 本行的dp数组, dp[j]:从第1块路到当前路, 且当前路调整至高为Hash[j]的最低总消耗
ll solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    ll ans = INF;
    for (int j = 1; j <= N; ++j) dp[j] = abs(vec[1] - Hash[j]);
    for (int i = 2; i <= N; ++i) {
        ll last_cost = dp[1]; // 前一块路高度调整至小于Hash[j]的高度所需的最小cost
        for (int j = 1; j <= N; ++j) {
            last_cost = min(last_cost, dp[j]);
            dp[j] = abs(vec[i] - Hash[j]) + last_cost;
        }
    }
    for (int j = 1; j <= N; ++j) ans = min(ans, dp[j]);
    return ans;
}

int main(void) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &vec[i]);
        Hash[i] = vec[i];
    }
    // 把各个高度映射至路的下标
    sort(Hash + 1, Hash + N + 1);
    ll increase = solve(); // 上升序列
    reverse(vec + 1, vec + N + 1);
    ll decrease = solve(); // 下降序列
    printf("%lld\n", min(increase, decrease));
    return 0;
}