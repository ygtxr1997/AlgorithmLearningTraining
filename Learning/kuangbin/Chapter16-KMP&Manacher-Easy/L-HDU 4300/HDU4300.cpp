#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace::std;
const int maxn = 100100;

int T;
char encode[27]; // 加密表
char decode[27]; // 解密表
char txt[2 * maxn];
char tmp[2 * maxn];
int nxt[2 * maxn];
void Decode(void) { // 部分解密
    int len = strlen(tmp);
    for (int i = 0; i < len / 2; ++i) { // 前一半一定是密文
        tmp[i] = decode[tmp[i] - 'a'];
    }
}
void getnxt(void) {
    int len = strlen(tmp);
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || tmp[j] == tmp[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
void getall() {
    int len = strlen(txt);
    int left = nxt[len]; // 左边加密部分的长度
    if (left > len / 2) left = len / 2; // 最短是一半
    left = len - left; // 若为奇数, 取较大的那个值
    for (int i = 0; i < left; ++i) printf("%c", txt[i]);
    for (int i = 0; i < left; ++i) printf("%c", decode[txt[i] - 'a']);
    printf("\n");
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", encode);
        for (int i = 0; i < 26; ++i) decode[encode[i] - 'a'] = i + 'a';
        scanf("%s", txt);
        memcpy(tmp, txt, sizeof(txt));
        Decode();
        getnxt();
        getall();
    }
    return 0;
}