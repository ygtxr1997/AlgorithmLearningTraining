#include <iostream>
#include <cstring>
#define TES
using namespace::std;
const int maxn = 20;
const int INF = 0x3f3f3f3f;

// 状态压缩DP, 用比特位保存状态, 这样每个状态可以保存更多的信息(不需要非常多维的数组)
// 题中的原始状态为课程的不同排列方式, 而n!种排列方式对应的状态数太多了,
// 所以把完成的k个课程看作一个集合即对应一种状态, 相当于把k!种状态全部压缩为1种状态,
// 并且用比特位保存状态, 第b位为1代表该门课程已完成, 第b位为0代表该门课程未完成.
// 例如假设有5门课程, 11111代表课程全部完成, 01111, 10111, 11011, 11101, 11110都代表还差一门课程全部完成,
// dp[i]:达到状态i所需的最小扣分, time[i]:达到状态i的总耗时, pre[i]:能达到状态i最小扣分的最后那门课程
// dp[i] = min{ dp[last_state] + (time[j] + Cost[j] - Deadline[j]) }
//                 last_state = i - (1 << j)
int N; // N courses
char S[maxn][110]; // course name
int D[maxn]; // deadline
int C[maxn]; // cost
int dp[1 << maxn]; // dp[i] = least reduced to state i
int time[1 << maxn]; // time[i] = total cost to state i
int pre[1 << maxn]; // pre[i] = last course to state i

void printAns(int state) {
    if (state == 0) return;
    printAns(state - (1 << pre[state]));
    printf("%s\n", S[pre[state]]);
}

int solve(void) {
    memset(dp, 0x7f, sizeof(dp));
    memset(time, 0, sizeof(time));
    memset(pre, -1, sizeof(pre));
    dp[0] = 0;
    for (int state = 1; state <= (1 << N) - 1; ++state) {
        for (int j = N - 1; j >= 0; --j) { // 枚举N-1 ~ 0课程
            if (state & (1 << j)) { // 如果状态state包括课程j, 才可通过完成课程j得到state
                int last_state = state - (1 << j); // 上个状态
                int reduce = time[last_state] + C[j] - D[j];
                if (reduce < 0) reduce = 0; // 新扣的分数最低为0
                if (dp[state] > dp[last_state] + reduce) {
                    dp[state] = dp[last_state] + reduce;
                    time[state] = time[last_state] + C[j];
                    pre[state] = j; 
                }
            }
        }
    }
    return dp[(1 << N) - 1]; // 111...11
}

int main(void) {
    #ifdef TEST
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        memset(S, 0, sizeof(S));
        for (int i = 0; i < N; ++i) {
            scanf("%s%d%d", &S[i], &D[i], &C[i]);
        }
        printf("%d\n", solve());
        printAns((1 << N) - 1);
    }
    return 0;
}