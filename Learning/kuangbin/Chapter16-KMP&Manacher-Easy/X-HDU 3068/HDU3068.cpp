#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 110000;

char str[maxn * 2];
int p[maxn * 2];
int manacher(void) {
    int ans = -1;
    int len = strlen(str);
    for (int i = len; i >= 0; --i) {
        str[2 * i + 1] = '#';
        str[2 * i + 2] = str[i];
    }
    str[0] = '$';
    int id, mx = 0;
    for (int i = 1; i < len * 2 + 1; ++i) {
        if (mx > 0) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        if (p[i] == 0) p[i] = 1;
        while (str[i - p[i]] == str[i + p[i]]) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        ans = max(ans, p[i]);
    }
    return ans - 1;
}

int main(void) {
    while (scanf("%s", str) != EOF) {
        getchar(); // 换行
        printf("%d\n", manacher());
    }
    return 0;
}