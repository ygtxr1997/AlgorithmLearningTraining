#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;

const int maxm = 12;
const int maxb = 70;
int M;
string strs[maxm];
int nxt[maxb];
void getnxt(const string& mode) {
    int len = mode.size();
    memset(nxt, -1, sizeof(nxt));
    int j = 0, k = -1;
    while (j < len) {
        if (k == -1 || nxt[j] == nxt[k]) {
            j++, k++;
            nxt[j] = k;
        } else k = nxt[k];
    }
}
bool kmp(const string& mode, const string& str) {
    int n = str.size(), m = mode.size();
    int i = 0, j = 0;
    while (i < n) {
        if (j == -1 || str[i] == mode[j]) {
            i++, j++;
        } else j = nxt[j];
        if (j >= m) return 1; // 匹配成功
    }
    return 0;
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &M);
        for (int i = 0; i < M; ++i) {
            strs[i].resize(maxb);
            scanf("%s", &strs[i][0]);
        }
        string ans(maxb, 'Z');
        for (int l = 60; l >= 3; l--) { // 枚举长度
            ans[0] = 'Z';
            for (int i = 0; i + l <= 60; i++) { // 这里的等号啊!!!
                const string& mode = strs[0].substr(i, l);
                getnxt(mode);
                // 与剩余M-1个序列逐个比较
                bool bSame = 1;
                for (int j = 1; j < M; ++j) {
                    const string& str = strs[j];
                    bSame &= kmp(mode, str);
                }
                if (bSame == 0) continue; // 并非全部包含该序列
                if (strcmp(ans.c_str(), mode.c_str()) > 0) ans = mode; // 选择字典序较小的mode串
            }
            if (ans[0] != 'Z') break; // 已经找到mode串
        }
        if (ans[0] == 'Z') printf("no significant commonalities\n");
        else printf("%s\n", ans.c_str());
    }
    return 0;
}