class Solution {
public:
    int N;
    vector<int> row; // 每行对应的位置, 下标从1开始
    vector<vector<string>> ret;
    vector<string> makeGrid(void) {
        vector<string> ret;
        for (int i = 0; i < N; ++i) {
            int pos = row[i];
            string str = string(pos - 1, '.') + "Q" + string(N - pos, '.');
            ret.push_back(str);
        }
        return ret;
    }
    void dfs(int r) {
        if (r > N) {
            ret.push_back(makeGrid());
            return;
        }
        for (int i = 1; i <= N; ++i) {
            if (row.empty()) {
                row.push_back(i);
                dfs(r + 1);
                row.pop_back();
            } else {
                bool enable = 1;
                for (int j = row.size() - 1; j >= 0 && enable; --j) {
                    // 同列或者在对角线上
                    if (i == row[j] || abs(i - row[j]) == r - j - 1) enable = 0;
                }
                if (!enable) continue;
                row.push_back(i);
                dfs(r + 1);
                row.pop_back();
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        N = n;
        dfs(1);
        return ret;
    }
};