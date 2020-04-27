#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 4010;
const int maxl = 210;

int N;
char strs[maxn][maxl];
int nxt[maxl];
void getnxt(char* mode, int l2) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < l2) {
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
    while (scanf("%d", &N) && N != 0) {
        for (int i = 0; i < N; ++i) {
            scanf("%s", strs[i]);
        }
        int l2 = strlen(strs[0]);
        char ans[maxl] = "~";
        for (int l = l2; l >= 1; --l) { // 枚举长度
            ans[0] = '~';
            bool bAllSame = 0;
            for (int i = 0; i + l - 1 < l2; ++i) { // 枚举起点
                getnxt(strs[0] + i, l);
                bAllSame = 1;
                for (int j = 1; j < N && bAllSame; ++j) { // 剩余N-1个字符串
                    bAllSame = kmp(strs[j], strs[0] + i, l);
                }
                if (bAllSame) { // 是公共串
                    char tmp[maxl] = { 0 };
                    memcpy(tmp, strs[0] + i, l * sizeof(char));
                    if (strcmp(tmp, ans) < 0) memcpy(ans, tmp, sizeof(tmp)); // 相同长度选字典序小的
                }
            }
            if (ans[0] != '~') break; // 该长度找到了公共串, 无需再找, 这里容易WA
        }
        if (ans[0] == '~') printf("IDENTITY LOST\n"); // 未找到公共串
        else printf("%s\n", ans);
    }
}
