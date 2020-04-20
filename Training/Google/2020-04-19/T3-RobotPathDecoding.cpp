#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <stack>
using namespace::std;
const int INF = 0x7f7f7f7f;
const int mod = 1e9;
typedef long long ll;
typedef pair<int, int> pii;
typedef struct node {
    node(){}
    node(int t, ll x, ll y) : type(t), w(x), h(y) { }
    int type; // 0:数字, 1:括号, 2:坐标偏移
    ll w, h;
} node;

int T;
string str;
ll f_w, f_h;
void solve(void) {
    stack<node> sta; // type: 0:数字, 1:括号, 2:坐标偏移
    f_w = 0, f_h = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] >= '2' && str[i] <= '9') sta.push(node(0, str[i] - '0', 0));
        else if (str[i] == '(') sta.push(node(1, '(', 0));
        else if (str[i] == 'N') sta.push(node(2, 0, -1));
        else if (str[i] == 'S') sta.push(node(2, 0, 1));
        else if (str[i] == 'E') sta.push(node(2, 1, 0));
        else if (str[i] == 'W') sta.push(node(2, -1, 0));
        else if (str[i] == ')') {
            ll diff_w = 0, diff_h = 0;
            while (sta.top().type != 1) {
                diff_w += sta.top().w;
                diff_h += sta.top().h;
                sta.pop();
            }
            sta.pop(); // 左括号
            diff_w = (diff_w * sta.top().w) % mod; // 重复多次
            diff_h = (diff_h * sta.top().w) % mod;
            sta.pop(); // 数字
            sta.push(node(2, diff_w, diff_h));
        }
    }
    while (!sta.empty()) {
        f_w = (f_w + sta.top().w + mod) % mod;
        f_h = (f_h + sta.top().h + mod) % mod;
        sta.pop();
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        str.clear();
        cin >> str;
        solve();
        f_w = (f_w + 1);
        f_h = (f_h + 1);
        printf("Case #%d: %lld %lld\n", t, f_w, f_h);
    }
    return 0;
}