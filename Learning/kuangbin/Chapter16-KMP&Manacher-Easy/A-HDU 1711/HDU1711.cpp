#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1000100;
const int maxm = 10010;

int T;
int N, M;
int vecA[maxn], vecB[maxm];
int Next[maxm];
// 获取next数组, next[i]:[1~i]的最大前后缀匹配长度
void getNext(void) {
    memset(Next, 0, sizeof(Next));
    Next[1] = 0;
    for (int i = 2, k = 1; i <= M; ++i) { // k代表要比较的位置, 至少为1
        while (k >= 2 && vecB[k] != vecB[i])
            k = Next[k - 1] + 1; // 向前递归寻找前后缀匹配的最大长度
        if (vecB[k] == vecB[i]) k++;
        Next[i] = k - 1;
    }
}
// kmp算法本体
int kmp(void) {
    getNext();
    for (int i = 1, j = 1; i <= N; ++i) {
        while (j >= 2 && vecA[i] != vecB[j]) {
            j = Next[j - 1] + 1; 
        }
        if (vecA[i] == vecB[j]) j++;
        if (j == M + 1) return i - M + 1; // vecB匹配完毕
    }
    return -1; // vecA中找不到子串
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &vecA[i]);
        }
        for (int i = 1; i <= M; ++i) {
            scanf("%d", &vecB[i]);
        }
        printf("%d\n", kmp());
    }
    return 0;
}