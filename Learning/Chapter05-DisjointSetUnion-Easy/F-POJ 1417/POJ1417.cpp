#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;
const int maxp = 403;

int n, p1, p2;
int UnionSet[2 * maxp]; // 有逻辑关系的人在同一集合中
int Same[2 * maxp]; // 以根为i的并查集中与根节点距离为0(同类)的人数
int Diff[2 * maxp]; // 以根为i的并查集中与根节点距离为1(异类)的人数
int Dist[2 * maxp]; // 第i个人与根节点的距离
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        Dist[i] ^= Dist[old_root]; // 0:相同, 1:不同
    }
    return UnionSet[i];
}
// 已经获取所有人员关系, dp确认有效信息是否足够
int Set[2 * maxp][3]; // Set[i][0]:第i个集合与根节点相同的人数, 
                      // Set[i][1]:第i个集合与根不同的人数,
                      // Set[i][2]:第i个集合的根节点
int tot; // 并查集总个数
int dp[2 * maxp][2 * maxp]; // dp[i][j]:前i个集合好人为j个的可能情况数
int cho[2 * maxp][2 * maxp]; // cho[i][j]:dp中第i个集合满足dp[i][j]的该集合选0或选1, 保存路径
int pre[2 * maxp][2 * maxp]; // pre[i][j]:dp中第i个集合满足dp[i][j]的前一个集合的j值, 保存路径
int ans[2 * maxp]; // 最终结果
int ans_cnt;
// 回溯升序打印结果, i:第几个集合, j:和为多少
void printAns(int i, int j) {
    if (i >= 1) {
        for (int x = 1; x <= p1 + p2; ++x) { // 把第i个集合的所有元素加入ans[]
            if (UnionSet[x] == Set[i][2] && Dist[x] == cho[i][j]) {
                ans[++ans_cnt] = x;
            }
        }
        printAns(i - 1, pre[i][j]);
    }
    else {
        sort(ans + 1, ans + 1 + ans_cnt); // 排序后再打印
        for (int x = 1; x <= ans_cnt; ++x)
            printf("%d\n", ans[x]);
    }
}
void solve(void) {
    memset(dp, 0, sizeof(dp));
    memset(cho, -1, sizeof(cho));
    memset(pre, 0, sizeof(pre));
    tot = 0;
    for (int i = 1; i <= p1 + p2; ++i) {
        // 再次路径压缩
        if (Find(i) == i) { // 找到各个并查集的根节点
            Set[++tot][0] = Same[i];
            Set[tot][1] = Diff[i];
            Set[tot][2] = i;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= tot; ++i) {
        int A = Set[i][0], B = Set[i][1];
        for (int j = 0; j <= p1; ++j) { // j要从0开始统计!!!WA!!!
            bool choA = 0, choB = 0; // 这一步选择的是A类(0类)或者B类(1类)
            if (j >= A && dp[i - 1][j - A]) { 
                dp[i][j] += dp[i - 1][j - A]; 
                choA = (dp[i - 1][j - A] == 1) ? 1 : 0; 
            }
            if (j >= B && dp[i - 1][j - B]) { 
                dp[i][j] += dp[i - 1][j - B]; 
                choB = (dp[i - 1][j - B] == 1) ? 1 : 0; 
            }
            if (dp[i][j] == 1) {
                cho[i][j] = (choA == 1) ? 0 : 1;
                if (choA) pre[i][j] = j - A;
                else pre[i][j] = j - B;
            }
        }
    }
    if (dp[tot][p1] != 1) { // 不存在这种情况或有多种可能
        printf("no\n"); return;
    } else { // 只有一种可能, 条件充分
        memset(ans, 0, sizeof(ans));
        ans_cnt = 0;
        printAns(tot, p1);
        printf("end\n");
    }
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &p1, &p2) && n + p1 + p2 != 0) {
        memset(Dist, 0, sizeof(Dist));
        for (int i = 1; i <= p1 + p2; ++i) {
            UnionSet[i] = i;
            Same[i] = 1;
            Diff[i] = 0;
        }
        int x, y;
        char a[10];
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%s", &x, &y, a);
            int r1 = Find(x), r2 = Find(y); // 总是让r1指向r2
            // 如果r1==r2, 说明之前已经确定过x和y的关系, 不用重复确认
            if (r1 == r2) continue;
            if (a[0] == 'y') { // x, y 同种
                UnionSet[r1] = r2;
                Dist[r1] = Dist[y] ^ Dist[x] ^ 0;
            } else if (a[0] == 'n') { // x, y 异种
                UnionSet[r1] = r2;
                Dist[r1] = Dist[y] ^ Dist[x] ^ 1;
            }
            if (Dist[r1] == 0) { // r1, r2相同
                Same[r2] += Same[r1];
                Diff[r2] += Diff[r1];
            }
            else { // r1, r2 不同
                Same[r2] += Diff[r1];
                Diff[r2] += Same[r1];
            }
        }
        solve();
    }
    return 0;
}