#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 110;
const int maxm = 110;

int T;
int n;
char strs[maxn][maxm];
int nxt[maxm];
void getnxt(int len, char* mode) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || mode[j] == mode[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
bool kmp(char* str, char* mode, int l2) {
    int l1 = strlen(str);
    int i = 0, j = 0;
    while (i < l1) {
        if (j == -1 || mode[j] == str[i]) {
            i++, j++;
        } else j = nxt[j];
        if (j >= l2) return 1;
    }
    return 0;
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", strs[i]);
        }
        // 从长到短枚举
        int l2 = strlen(strs[0]);
        int ans = 0;
        for (int l = l2; l >= 1; --l) { // 长度
            bool bAllSame = 0;
            for (int i = 0; i + l - 1 < l2; ++i) { // 首位置
                getnxt(l, strs[0] + i);
                bAllSame = 1;
                for (int j = 1; j < n && bAllSame; ++j) { // 剩余的n-1个字符串
                    bool bSame = 0;
                    bSame |= kmp(strs[j], strs[0] + i, l);
                    reverse(strs[j], strs[j] + strlen(strs[j]));
                    bSame |= kmp(strs[j], strs[0] + i, l);
                    bAllSame &= bSame;
                }
                if (bAllSame) { ans = l; break; }
            }
            if (bAllSame) break;
        }
        printf("%d\n", ans);
    }
    return 0;
}