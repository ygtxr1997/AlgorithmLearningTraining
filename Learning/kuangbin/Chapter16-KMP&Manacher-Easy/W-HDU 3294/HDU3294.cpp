#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 200010;

char cc;
int step;
char str[2 * maxn];
int P[2 * maxn];
int max_id, max_val;
void manacher(int len) {
    memset(P, 0, sizeof(P));
    max_id = 0, max_val = 1;
    int id, mx = 0;
    for (int i = 1; i < len; ++i) {
        if (mx > 0) P[i] = min(P[2 * id - i], mx - i);
        else P[i] = 1;
        if (P[i] == 0) P[i] = 1;
        while (str[i - P[i]] == str[i + P[i]]) P[i]++;
        if (i + P[i] > mx) {
            mx = i + P[i];
            id = i;
        }
        if (P[i] - 1 > max_val) {
            max_val = P[i] - 1;
            max_id = i;
        }
    }
}

int main(void) {
    while (scanf("%c", &cc) != EOF) {
        step = 'a' - cc;
        scanf("%s", str);
        getchar();
        // 预处理
        int l = strlen(str);
        for (int i = l; i >= 0; i--) {
            str[2 * i + 1] = '#';
            str[2 * i + 2] = str[i];
        }
        str[0] = '$';
        int len = strlen(str);
        manacher(len);
        if (max_val == 1) printf("No solution!\n");
        else {
            int left = max_id - max_val;
            int right = max_id + max_val;
            printf("%d %d\n", (left + 1) / 2 - 1, right / 2 - 1);
            for (int i = left; i <= right; ++i) {
                if (str[i] == '#') continue;
                printf("%c", 'a' + ((str[i] - 'a' + step + 26) % 26));
            }
            printf("\n");
        }
    }
    return 0;
}