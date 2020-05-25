class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int M = matrix.size(), N = matrix[0].size();
        vector<bool> Row(M, 0); // 行是否清零
        vector<bool> Col(N, 0); // 列是否清零
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == 0) Row[i] = Col[j] = 1;
            }
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (Row[i] || Col[j]) matrix[i][j] = 0;
            }
        }
    }
};