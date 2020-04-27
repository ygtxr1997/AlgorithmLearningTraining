#include <iostream>
#include <vector>

using namespace ::std;

// 类似八皇后问题，用一个数组保存已经不能再放棋子的行，从第0列开始dfs
void dfs(vector<string>& matrix, int j, vector<bool>& row, int k, int& ans) {
    if (k <= 0) { ans++; return; }
    if (j >= matrix.size()) return;
    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][j] == '#' && row[i] == 0) {
            row[i] = 1;
            dfs(matrix, j + 1, row, k - 1, ans);
            row[i] = 0;
        }
    }
    // 这里很容易漏！
    dfs(matrix, j + 1, row, k, ans);
}

int main(void) {
    int n = 0, k = 0;
    while ((cin >> n >> k)) {
        if (n == -1 && k == -1) break;
        vector<string> matrix(n);
        for (int i = 0; i < n; ++i) {
            cin >> matrix[i];
        }
        int ans = 0;
        vector<bool> row(n, 0);
        // 从第0列开始放棋子
        dfs(matrix, 0, row, k, ans);
        cout << ans << endl;
    }
    return 0;
}