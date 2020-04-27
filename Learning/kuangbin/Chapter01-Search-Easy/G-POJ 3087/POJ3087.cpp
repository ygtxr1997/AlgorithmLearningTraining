#include <iostream>
#include <string>
#include <map>
using namespace::std;

// 水题，理解题意就好
int N, C;
string s1, s2, s12;
map<string, bool> visited; // 合并后的牌堆是否出现过
int solve() {
    int ans = 0;
    string tmp(2 * C, '0');
    while (1) {
        for (int i = 0; i < C; ++i) {
            tmp[2 * i] = s2[i];
            tmp[2 * i + 1] = s1[i];
        }
        if (visited.find(tmp) != visited.end()) return -1;
        visited[tmp] = 1;
        ans++;
        if (tmp == s12) return ans;
        s1 = tmp.substr(0, C);
        s2 = tmp.substr(C, C);
    }
    return ans;
}

int main(void) {
    while (cin >> N) {
        for (int k = 1; k <= N; ++k) {
            cin >> C >> s1 >> s2 >> s12;
            visited.clear();
            int res = solve();
            cout << k << ' ' << res << endl; 
        }
    }
    return 0;
}