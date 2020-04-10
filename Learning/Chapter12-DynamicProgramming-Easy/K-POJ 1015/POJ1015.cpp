#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 210;
const int maxm = 810;
const int offset = 400;

// dp[j][k]:选j个人, 且差为k的方案中, 和最大的那个方案的和
// dp[j][k] = max{ dp[j-1][x] + (D[i]+P[i]) | x+(D[i]-P[i]) == k }
int n, m; // n candidates, m jury members, 1<=n<=200, 1<=m<=20
int D[maxn], P[maxn];
int valD, valP; // D方总和, P方总和
int dp[maxn][maxm]; // dp[j][k]:选j个人, 且差为k的方案中, 和最大的那个方案的和
int path[maxn][maxm]; // path[j][k] = dp[j][k]选的最后那个人的编号
int minSub; // 最小差值
int ans[maxn]; // 候选人结果

// 判断dp[j][x]方案是否包含候选人i
bool isSelected(int j, int x, int i) {
    while (j > 0 && path[j][x] != i) {
        x -= D[path[j][x]] - P[path[j][x]];
        j--;
    }
    return j ? 1 : 0;
}

int solve(void) {
    dp[0][offset] = 0;
    for (int j = 1; j <= m; ++j) {
        for (int x = 0; x <= 2 * offset; ++x) { // 从最低-400到最高400
            if (dp[j - 1][x] >= 0) { // 若更新过记录
                for (int i = 1; i <= n; ++i) { // 找到符合更新dp[j][k]条件的那个i值
                    if (dp[j][x + (D[i] - P[i])] < dp[j - 1][x] + (D[i] + P[i])) {
                        if (!isSelected(j - 1, x, i)) { // dp[j-1][x]不包含候选人i
                            dp[j][x + (D[i] - P[i])] = dp[j - 1][x] + (D[i] + P[i]);
                            path[j][x + (D[i] - P[i])] = i; // 记录路径, 最后一次选的是i
                        }
                    }
                }
            }
        }
    }
    int k;
    for (k = 0; k <= offset; ++k) { // 从中间向两边找到第一个不为-1的值即最小差D-P
        if (dp[m][offset - k] >= 0 || dp[m][offset + k] >= 0) break;
    }
    int minSub = dp[m][offset - k] > dp[m][offset + k] ? offset - k : offset + k; // 取较大和
    valD = (dp[m][minSub] - minSub + offset) / 2; // D+P - (D-P) = 2P
    valP = (dp[m][minSub] + minSub - offset) / 2; // D+P + (D-P) = 2D
    return minSub;
}

// 升序打印候选人编号
void printAns(void) {
    for (int i = 0, j = m, k = minSub; i < m; ++i) {
        ans[i] = path[j][k];
        k -= D[ans[i]] - P[ans[i]];
        j--;
    }
    sort(ans, ans + m);
    for (int i = 0; i < m; ++i) printf(" %d", ans[i]);
    printf("\n");
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int T = 0;
    while (scanf("%d%d", &n, &m) && (n + m) != 0) {
        T++;
        memset(dp, -1, sizeof(dp));
        memset(path, 0, sizeof(path));
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &D[i], &P[i]);
        }
        minSub = solve();
        printf("Jury #%d \n", T);
        printf("Best jury has value %d ", valP);
        printf("for prosecution and value %d for defence:\n", valD);
        printAns();
        printf("\n");
    }
    return 0;
}