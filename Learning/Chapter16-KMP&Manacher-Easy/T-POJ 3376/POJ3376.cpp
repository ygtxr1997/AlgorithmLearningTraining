// 扩展KMP+trie树
// 先写个扩展KMP吧...
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;

void getnxt(char* mode, int len, char* nxt) {
    // 计算nxt[1]
    int i = 0;
    while (i + 1 < len && mode[i] == mode[i + 1]) i++;
    nxt[1] = i;
    int po = 1;
    for (i = 2; i < len; ++i) {
        if (i + nxt[i - po] < po + nxt[po])
            nxt[i] = nxt[i - po];
        else {
            int j = po + nxt[po] - i;
            if (j < 0) j = 0;
            while (i + j < len && mode[i + j] == mode[j]) j++;
            nxt[i] = j;
            po = i;
        }
    }
}
void exkmp(char* str, char* mode, int* ex, int* nxt) {
    int l1 = strlen(str), l2 = strlen(mode);
    // 计算ex[0]
    int i = 0, po = 1;
    while (i < l1 && i < l2 && str[i] == mode[i]) i++;
    ex[0] = i;
    for (i = 1; i < l1; ++i) {
        if (i + nxt[i - po] < po + ex[po])
            ex[i] = nxt[i - po];
        else {
            int j = po + ex[po] - i;
            if (j < 0) j = 0;
            while (i + j < l1 && j < l2 && str[i] == mode[j]) j++;
            ex[i] = j;
            po = i;
        }
    }
}