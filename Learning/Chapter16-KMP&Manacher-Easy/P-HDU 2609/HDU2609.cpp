#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
using namespace::std;
const int maxn = 10010;
const int maxl = 110;

int n;
char necks[maxn][maxl];
set<string> Set;
// 最小表示
int getmin(char* str, int len) {
    int i = 0, j = 1, k = 0;
    while (i < len && j < len && k < len) {
        int t = str[(i + k) % len] - str[(j + k) % len];
        if (t == 0) k++;
        else {
            if (t > 0) i += k + 1; // j位置不变
            else j += k + 1; // i位置不变
            if (i == j) j++;
            k = 0; // k重置为0
        }
    }
    return min(i, j);
}
int main(void) {
    while (scanf("%d", &n) != EOF) {
        memset(necks, 0, sizeof(necks));
        Set.clear();
        char tmp[maxl];
        for (int i = 0; i < n; ++i) {
            scanf("%s", tmp);
            int len = strlen(tmp);
            int ismall = getmin(tmp, len);
            memcpy(necks[i], tmp + ismall, (len - ismall) * sizeof(char));
            memcpy(necks[i] + len - ismall, tmp, ismall * sizeof(char));
            Set.insert(necks[i]);
        }
        printf("%d\n", Set.size());
    }
    return 0;
}