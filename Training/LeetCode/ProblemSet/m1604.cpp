// 如果遇到O则加1, 如果遇到X则减1
class Solution {
public:
    string tictactoe(vector<string>& board) {
        int N = board.size();
        vector<int> row(N);
        vector<int> col(N);
        int dia1 = 0, dia2 = 0; // 主副对角线
        bool pending = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int offset = 0;
                if (board[i][j] == 'O') offset = 1;
                else if (board[i][j] == 'X') offset = -1;
                else pending = 1; // 有空位
                row[i] += offset;
                col[j] += offset;
                if (i == j) dia1 += offset;
                if (i + j == N - 1) dia2 += offset;
            }
        }
        if (dia1 == N || dia2 == N) return "O";
        if (dia1 == -N || dia2 == -N) return "X";
        for (int k = 0; k < N; ++k) {
            if (row[k] == N || col[k] == N ) return "O";
            else if (row[k] == -N || col[k] == -N) return "X";
        }
        if (!pending) return "Draw";
        else return "Pending";
    }
};