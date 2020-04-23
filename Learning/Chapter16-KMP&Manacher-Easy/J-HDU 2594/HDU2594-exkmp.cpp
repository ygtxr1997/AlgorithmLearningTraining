#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 50010;

char s1[maxn]; // 子串
char s2[maxn]; // 母串
int nxt[maxn]; // 扩展kmp专用, 子串后缀[j~m-1]与子串前缀的最长公共长度
int ex[maxn]; // 扩展kmp专用, 母串[i~n-1]与子串前缀的最长公共长度
// 扩展kmp算法, 求母串S的每一个后缀与子串T的最长公共前缀
void getnxt(void) {
    memset(nxt, 0, sizeof(nxt));
    int l1 = strlen(s1);
    int i = 0;
    nxt[0] = l1; // nxt[0]=子串长度
    while (i + 1 < l1 && s1[i] == s1[i + 1]) i++; // 计算nxt[1]
    nxt[1] = i;
    int po = 1; // 前面匹配达到的最远位置
    for (i = 2; i < l1; ++i) {
        if (nxt[i - po] + i < nxt[po] + po) // 情况1:可以直接得到nxt[i]
            nxt[i] = nxt[i - po];
        else { // 情况2:要继续往后匹配才能得到nxt[i]
            int j = nxt[po] + po - i;
            if (j < 0) j = 0; // 从头开始匹配
            while (i + j < l1 && s1[j] == s1[i + j]) j++; // 继续往后
            nxt[i] = j;
            po = i; // 更新po的位置
        }
    }
}
void exkmp(void) {
    int l1 = strlen(s1), l2 = strlen(s2);
    getnxt();
    memset(ex, 0, sizeof(ex));
    int i = 0, po = 0;
    while (s2[i] == s1[i] && i < l1 && i < l2) i++; // 计算nx[0]
    ex[0] = i;
    for (i = 1; i < l2; i++) {
        if (nxt[i - po] + i < ex[po] + po) // 情况1:可以直接得到ex[i]
            ex[i] = nxt[i - po];
        else {
            int j = ex[po] + po - i; // 子串开始匹配的位置
            if (j < 0) j = 0; // 从头开始匹配
            while (i + j < l2 && j < l1 && s1[j] == s2[j + i]) j++; // 继续往后
            ex[i] = j;
            po = i; // 更新po的位置
        }
    }
}

int main(void) {
    while (scanf("%s", s1) != EOF) {
        scanf("%s", s2);
        exkmp();
        int l2 = strlen(s2);
        int max_val = 0, max_index = 0;
        for (int i = 0; i < l2; ++i) { // 找到最大的匹配长度
            if (ex[i] > max_val && ex[i] + i == l2) { // 母串后缀的匹配长度必须到底
                max_val = ex[i];
                max_index = i;
            }
        }
        if (max_val) printf("%s %d\n", s2 + max_index, max_val);
        else printf("0\n");
    }
    return 0;
}