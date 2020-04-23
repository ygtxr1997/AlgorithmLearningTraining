#include <iostream>
#include <algorithm>
#include <cstring>
using namespace::std;
const int maxn = 1000010;

char S[maxn];
char small[maxn];
char big[maxn];
int nxt[maxn];

// 同构字符串的最大最小表示法, 
// 最小:通过循环左移, 字典序最小的那个同构字符串
// 最大:通过循环左移, 字典序最大的那个同构字符串
int getmin(char* str, int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = str[(i + k) % len] - str[(j + k) % len];
        if (t == 0) k++; // 相等, 继续往后
        else {
            if (t > 0) i += k + 1; // str[i+k]较大, 移动i
            else j += k + 1; // str[j+k]较大, 移动j
            if (i == j) j++; // 如果相同, 默认让j往后移动
            k = 0; // k重置为0
        }
    }
    return min(i, j);
}
int getmax(char* str, int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = str[(i + k) % len] - str[(j + k) % len];
        if (t == 0) k++;
        else {
            if (t > 0) j += k + 1; // str[j+k]较小, 移动j
            else i += k + 1; // str[i+k]较小, 移动i
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j);
}
void getnxt(char* str, int len) {
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || str[j] == str[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
int main(void) {
    while (scanf("%s", S) != EOF) {
        memset(small, 0, sizeof(small));
        memset(big, 0, sizeof(big));
        int len = strlen(S);
        int ismall = getmin(S, len), ibig = getmax(S, len);
        memcpy(small + len - ismall, S, ismall * sizeof(char));
        memcpy(small, S + ismall, (len - ismall) * sizeof(char));
        memcpy(big + len - ibig, S, ibig * sizeof(char));
        memcpy(big, S + ibig, (len - ibig) * sizeof(char));
        getnxt(small, len);
        int cyc = len - nxt[len];
        int time;
        if (cyc == len) time = 1;
        else if (len % cyc == 0) time = len / cyc;
        else time = 1;
        printf("%d %d %d %d\n", ismall + 1, time, ibig + 1, time);
    }
    return 0;
}