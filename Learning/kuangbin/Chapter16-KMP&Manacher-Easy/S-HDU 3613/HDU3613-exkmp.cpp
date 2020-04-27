#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 500010;

// 用扩展KMP求回文串
int t;
int v[27];
char S[maxn], T[maxn];
int sum[maxn]; // sum[i] = S[0~i]前缀和
int nxt[maxn];
int ex1[maxn], ex2[maxn];
void getnxt(char mode[], int len) {
    memset(nxt, 0, sizeof(nxt));
    nxt[0] = len; // 用不上
    int i = 0;
    while (i + 1 < len && mode[i] == mode[i + 1]) i++;
    nxt[1] = i; // 计算nxt[1]
    int po = 1;
    for (i = 2; i < len; ++i) {
        if (i + nxt[i - po] < po + nxt[po])
            nxt[i] = nxt[i - po];
        else {
            int j = po + nxt[po] - i;
            if (j < 0) j = 0;
            while (i + j < len && mode[j] == mode[i + j]) j++;
            nxt[i] = j;
            po = i; // 更新po
        }
    }
}
void exkmp(char str[], char mode[], int ex[]) {
    int l1 = strlen(str), l2 = strlen(mode);
    getnxt(mode, l2);
    memset(ex, 0, sizeof(ex1));
    int i = 0, po = 1;
    while (str[i] == mode[i] && i < l1 && i < l2) i++;
    ex[0] = i; // 计算ex[0]
    for (i = 1; i < l1; i++) {
        if (i + nxt[i - po] < po + ex[po])
            ex[i] = nxt[i - po];
        else {
            int j = po + ex[po] - i;
            if (j < 0) j = 0;
            while (i + j < l1 && j < l2 && str[i + j] == mode[j]) j++;
            ex[i] = j;
            po = i; // 更新po
        }
    }
}
int main(void) {
    scanf("%d", &t);
    while (t--) {
        for (int i = 0; i < 26; ++i) scanf("%d", &v[i]);
        scanf("%s", S);
        int len = strlen(S);
        memset(T, 0, sizeof(T));
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < len; ++i) {
            T[i] = S[len - i - 1]; // 翻转
            if (i == 0) sum[i] = v[S[i] - 'a']; // 前缀和
            else sum[i] = sum[i - 1] + v[S[i] - 'a'];
        }
        exkmp(T, S, ex1); // 母串T的后缀为回文
        exkmp(S, T, ex2); // 母串S的后缀为回文
        int ans = -INF;
        for (int i = 1; i < len; ++i) { // 枚举前缀长度
            int sc = 0;
            if (ex1[len - i] + len - i == len) sc += sum[i - 1];
            if (ex2[i] + i == len) sc += sum[len - 1] - sum[i - 1];
            ans = max(ans, sc);
        }
        printf("%d\n", ans);
    }
}