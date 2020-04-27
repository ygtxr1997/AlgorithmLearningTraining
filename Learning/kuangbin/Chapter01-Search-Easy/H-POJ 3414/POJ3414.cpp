#include <iostream>
#include <vector>
#include <cstring>
using namespace::std;

// 每次有6种操作方式，dfs遍历所有可能的结果，并用visited辅助保存已经访问过的状态
// 遍历过程中保存访问路径，当得到某个罐子的状态为C时，保存这条路径
// BFS也可以获得最短路径的值，但是路径的保存好像不太方便
int A, B, C; // A,B <= 100
vector<int> path; // 中间结果
vector<int> ans; // 最终结果
bool visited[101][101]; // 罐子状态是否访问过
void dfs(int i, int j) {
    if (visited[i][j]) return;
    if (i == C || j == C) { 
        if (ans.empty() || ans.size() > path.size()) ans = path;
        return; 
    }
    visited[i][j] = 1;
    for (int op = 1; op <= 6; op++) {
        path.push_back(op);
        if (op == 1 && i != A) { dfs(A, j); } // fill 1
        else if (op == 2 && j != B) { dfs(i, B); } // fill 2
        else if (op == 3 && i != 0) { dfs(0, j); } // drop 1
        else if (op == 4 && j != 0) { dfs(i, 0); } // drop 2
        else if (op == 5 && j != B && i != 0) { // pour 1 to 2
            if (i + j <= B) { dfs(0, i + j); }
            else { dfs(i + j - B, B); }
        }
        else if (op == 6 && i != A && j != 0) { // pour 2 to 1
            if (i + j <= A) { dfs(i + j, 0); }
            else { dfs(A, i + j - A); }
        }
        path.pop_back();
    }
    visited[i][j] = 0;
}

int main(void) {
    while (cin >> A >> B >> C) {
        path.clear(); ans.clear();
        memset(visited, 0, sizeof(bool) * 101 * 101);
        dfs(0, 0);
        if (ans.empty()) cout << "impossible" << endl;
        else {
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); ++i) {
                int op = ans[i];
                if (op == 1) printf("FILL(1)\n");
                else if (op == 2) printf("FILL(2)\n");
                else if (op == 3) printf("DROP(1)\n");
                else if (op == 4) printf("DROP(2)\n");
                else if (op == 5) printf("POUR(1,2)\n");
                else if (op == 6) printf("POUR(2,1)\n");
            }
        }
    }
    return 0;
}