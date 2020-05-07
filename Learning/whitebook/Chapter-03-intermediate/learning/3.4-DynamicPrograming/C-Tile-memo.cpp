// ---------------------------------------------------------------------
// 题目描述:
// 给定 n*m 的格子, 每个格子被染成了黑色或者白色.
// 现要用 1*2 的砖块覆盖这些格子, 要求块与块之间不重叠, 且覆盖所有白色格子.
// 不能覆盖黑色格子.
// 求一共有多少种覆盖方法, 输出方案数对 M 取模后的结果.
// 1 <= n <= 15
// 1 <= m <= 15
// 2 <= M <= 10^9
// ---------------------------------------------------------------------
// 思路一:
// 朴素 DFS
// 每次从最左上方的空格开始放置, 并用一个bool数组维护已经被覆盖过的格子.
// 时间复杂度O(n*m*2^(n*m)), 显然会超时.
// ---------------------------------------------------------------------
const int M = 1e9 + 7;

// input
int n, m;
bool color[maxn][maxm]; // 0:白, 1:黑

// 现在查看的格子是(i,j), used表示那些格子已经被覆盖
int rec(int i, int j, bool used[maxn][maxm]) {
    if (j == m) return rec(i + 1, 0, used); // 去下一行
    if (i == n) return 1; // 已经完全覆盖, 方案数+1
    if (used[i][j] || color[i][j]) return rec(i, j + 1, used); // 不需要放砖块, 向右寻找
    int res = 0;
    used[i][j] = true;
    // 横着放
    if (j + 1 < m && !used[i][j + 1] && !color[i][j + 1]) {
        used[i][j + 1] = true;
        res += rec(i, j + 1, used); // 继续向右递归
        used[i][j + 1] = false;
    }
    // 竖着放
    if (i + 1 < n && !used[i][j + 1] && !color[i + 1][j]) {
        used[i + 1][j] = true;
        res += rec(i, j + 1, used); // 继续向右递归
        used[i + 1][j] = false;
    }

    used[i][j] = false;
    return res % M;
}

void solve(void) {
    bool used[maxn][maxm];
    memset(used, 0, sizeof(used));
    printf("%d\n", rec(0, 0, used));
}