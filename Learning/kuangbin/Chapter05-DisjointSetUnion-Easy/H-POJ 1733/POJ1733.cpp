#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace::std;
const int maxn = 80010;

int N, M;
int UnionSet[maxn]; // 已验证的关系加入至同一个并查集
int Dist[maxn];
map<int, int> Hash; // 数字映射至从小到大的次序
int tot = 0;
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        Dist[i] ^= Dist[old_root];
    }
    return UnionSet[i];
}

int main(void) {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= maxn - 1; ++i) UnionSet[i] = i; // 这里初始化越界, 疯狂RE
    memset(Dist, 0, sizeof(int) * maxn);
    int ans = 0, bValid = 1;
    for (int i = 1; i <= M; ++i) {
        int A, B, D;
        char str[10];
        scanf("%d%d%s", &A, &B, str);
        if (!Hash[A - 1]) Hash[A - 1] = ++tot;
        if (!Hash[B]) Hash[B] = ++tot;
        D = (str[0] == 'o') ? 1 : 0;
        int iA = Hash[A - 1], iB = Hash[B];
        int r1 = Find(iA), r2 = Find(iB);
        if (r1 != r2) {
            UnionSet[r1] = r2;
            Dist[r1] = Dist[iA] ^ Dist[iB] ^ D;
        } else {
            if (D == (Dist[iA] ^ Dist[iB])) ; // 符合
            else if (bValid) bValid = 0, ans = i - 1;
        }
    }
    printf("%d\n", bValid ? M : ans);
    return 0;
}