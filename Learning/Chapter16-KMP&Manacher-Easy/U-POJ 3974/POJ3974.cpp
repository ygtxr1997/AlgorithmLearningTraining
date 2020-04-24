#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000010; // 1000010

char S[2 * maxn];
char T[2 * maxn]; // 预处理后的字符串
int P[2 * maxn]; // 最长回文子串

// manacher求最长回文子串
int manacher(char* str, int len) {
    memset(P, 0, sizeof(P));
    int ans = -1;
    int id, mx = 0;
    for (int i = 1; i < len; ++i) {
        if (mx > 1) P[i] = min(P[2 * id - i], mx - i);
        else P[i] = 1;
        while (T[i - P[i]] == T[i + P[i]]) P[i]++;
        if (i + P[i] > mx) {
            id = i;
            mx = i + P[i];
        }
        ans = max(ans, P[i]);
    }
    return ans - 1; // 无论奇偶, 一定是P[i]-1
}

int main(void) {
    int t = 1;
    while (scanf("%s", S) && S[0] != 'E') {
        memset(T, 0, sizeof(T));
        // 预处理
        int l = strlen(S);
        T[0] = '$';
        for (int i = 0; i < l; ++i) {
            T[2 * i + 1] = '#';
            T[2 * i + 2] = S[i];
        }
        T[2 * l + 1] = '#';
        // manacher
        int len = strlen(T);
        int ans = manacher(T, len);
        printf("Case %d: %d\n", t++, ans);
    }
    return 0;
}