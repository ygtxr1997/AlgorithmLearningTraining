#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 2010;
const long long INF = 0x3f3f3f3f3f3f3f3f;
typedef long long ll;
ll Hash[maxn]; // 把各个高度从小到大重新映射, 离散化

// 做过的题
// dp[i][j]:前i块路, 且第i块路调整至高为Hash[j]的最低总消耗
// dp[i][j] = min{ dp[i-1][k] + abs(vec[i] - Hash[j]) | 0<=k<=j }
// 若 k 能满足 k<=j, 则一定也有 k<=j+1, k<=j+2, k<=j+3, ...
// 所以对 j 从小到大遍历, 用 last_cost 保存第 i-1 块路满足 k<=j 的最小消耗 dp[i-1][k]
int N;
ll vec[maxn];
ll dp[maxn][maxn]; // dp[i][j]:前i块路, 且第i块路调整至高为Hash[j]的最低总消耗
ll solve(void) {
    memset(dp, 0x3f, sizeof(dp));
    ll ans = INF;
    for (int j = 1; j <= N; ++j) dp[1][j] = abs(vec[1] - Hash[j]);
    for (int i = 2; i <= N; ++i) {
        ll last_cost = dp[i - 1][1]; // 前一块路高度调整至小于Hash[j]的高度所需的最小cost
        for (int j = 1; j <= N; ++j) {
            last_cost = min(last_cost, dp[i - 1][j]);
            dp[i][j] = abs(vec[i] - Hash[j]) + last_cost;
        }
    }
    for (int j = 1; j <= N; ++j) ans = min(ans, dp[N][j]);
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