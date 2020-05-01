#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int maxk = 103;
typedef long long ll;
const ll mod = 1e14; 
typedef struct bigint {
    bigint(){}
    bigint(ll l, ll r) : left(l), right(r) {}
    ll left; // 十进制高14位
    ll right; // 十进制低14位
    bigint operator+(const bigint& b2) const {
        ll r = (right + b2.right) % mod;
        ll l = (left + b2.left) + (right + b2.right) / mod;
        return bigint(l, r); 
    }
    bigint operator=(const bigint& b2) {
        left = b2.left;
        right = b2.right;
        return *this;
    }
} bigint;

// 完全背包
// dp[i][j]:前i种组成价值j的总共方法数
// dp[i+1][j] = Σ(k=0, k<=j/v[i])dp[i][j-k*v[i]]
//            = Σ(k=1, k<=j/v[i])dp[i][j-k*v[i]] + dp[i][j]
//            let k' = k - 1,
//            = Σ(k'=0, k'<=(j-v[i])/v[i])dp[i][j-(k'+1)*v[i]] + dp[i][j]
//            = Σ(k=0, k<=(j-v[i])/v[i])dp[i][j-(k+1)*v[i]] + dp[i][j]      ......(1)
// while,
// dp[i+1][j-v[i]] = Σ(k=0, k<=(j-v[i])/v[i])dp[i][j-v[i]-k*v[i]]           ......(2)
// because (1),(2),
// dp[i+1][j] = dp[i+1][j-v[i]] + dp[i][j]
// 此题数据较小, 不需要滚动数组优化
// 但是数据值很大, 需要定义大整数相加
int N, K; // 总额, 商品种数
int v[maxk]; // 第i件商品的价格为i+1
bigint dp[maxk][maxn]; // dp[i][j]:前i种组成价值j的总共方法数
bigint solve(void) {
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= K; ++i) dp[i][0].right = 1;
    for (int i = 0; i < K; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (j >= v[i]) {
                dp[i + 1][j] = dp[i + 1][j - v[i]] + dp[i][j];
            } else {
                dp[i + 1][j] = dp[i][j];
            }
        }
    }
    return dp[K][N];
}
void printans(const bigint& big) {
    if (big.left > 0) printf("%lld%014lld\n", big.left, big.right);
    else printf("%lld\n", big.right);
}
int main(void) {
    for (int i = 0; i < maxk; ++i) {
        v[i] = i + 1;
    }
    while (scanf("%d%d", &N, &K) != EOF) {
        printans(solve());
    }
    return 0;
}