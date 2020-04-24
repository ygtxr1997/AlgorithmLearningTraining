#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxl = 1000010;

// 把题意理解清楚, 其实就是前后缀匹配问题
int T;
char S[maxl];
int nxt[maxl];
int ans[maxl];
int ans_num;
void getnxt(int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || S[j] == S[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}

int main(void) {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        memset(ans, 0, sizeof(ans));
        ans_num = 0;
        scanf("%s", S);
        int len = strlen(S);
        getnxt(len);
        int j = len;
        while (j > 0) {
            ans[ans_num++] = len - nxt[j];
            j = nxt[j];
        }
        printf("Case #%d: %d\n", t, ans_num);
        for (int i = 0; i < ans_num; ++i) printf("%d%c", ans[i], 
            i == ans_num - 1 ? '\n' : ' '); // 注意格式
    }
    return 0;
}