#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxm = 1010;
const int INF = 0x7f7f7f7f;

int N, M, R;
typedef struct Node {
    Node(){}
    bool operator<(const Node& n2) {
        if (s == n2.s) return e < n2.e; // 按照开始时间排序
        return s < n2.s;
    }
    int s, e, v; // start, end, milk
} Node;
Node inter[maxm];
int dp[maxm] = { 0 }; // dp[i]:以第i段为最后一段的最大产量
int solve(void) {
    sort(inter + 1, inter + M + 1);
    int ans = 0;
    for (int i = 1; i <= M; ++i) {
        dp[i] = inter[i].v;
        for (int j = 1; j < i; ++j) {
            if (inter[j].e + R <= inter[i].s) { // j段结束后还要休息R时间
                dp[i] = max(dp[i], dp[j] + inter[i].v);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}

int main(void) {
    scanf("%d%d%d", &N, &M, &R);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d", &inter[i].s, &inter[i].e, &inter[i].v);
    }
    printf("%d\n", solve());
    return 0;
}