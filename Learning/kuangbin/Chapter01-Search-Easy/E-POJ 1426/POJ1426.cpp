#include <iostream>
#include <cstring>
#include <stack>
using namespace::std;

// 从0位向最高位dfs搜索，每位要么取0，要么取1
// 并且保存搜索到当前节点算出的余数ans，基数base
// 如果该位为1，那么ans=ans+base; 如果该位为0，那么ans=ans不变
int n; // 1 <= n <= 200
bool m[101]; // 用来表示大数m
bool bOne; // 排除全0的情况
bool solve(int pos, int base, int ans) {
    if (pos >= 100) {
        return ans == 0 && bOne;
    }
    if (solve(pos + 1, (base * 10) % n, ans)) return true;
    m[pos] = 1; bOne = true;
    if (solve(pos + 1, (base * 10) % n, (ans + base) % n)) return true;
    m[pos] = 0;
    return false;
}

int main(void) {
    while ((cin >> n) && n != 0) {
        memset(m, 0, sizeof(bool) * 101);
        bOne = false;
        solve(0, 1, 0);
        int i = 100;
        while (m[i] == 0) --i;
        while (i >= 0) cout << m[i--];
        cout << endl;
    }
    return 0;
}