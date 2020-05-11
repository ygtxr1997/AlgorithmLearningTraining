class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return vector<int>();
        int M = matrix.size(), N = matrix[0].size();
        int i = 0, j = 0;
        int dir = 0; // 0:右上, 1:左下
        vector<int> ret;
        while (1) {
            if (i == M - 1 && j == N - 1) {
                ret.push_back(matrix[i][j]);
                break;
            }
            if (dir == 0) {
                while (i >= 0 && j <= N - 1) {
                    ret.push_back(matrix[i][j]);
                    i--, j++;
                }
                if (i == -1 && j <= N - 1) i = 0;
                else if (j == N) i += 2, j = N - 1;
            } else {
                while (i <= M - 1 && j >= 0) {
                    ret.push_back(matrix[i][j]);
                    i++, j--;
                }
                if (j == -1 && i <= M - 1) j = 0;
                else if (i == M) j += 2, i = M - 1;
            }
            dir ^= 1;
        }
        return ret;
    }
};