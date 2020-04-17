#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 2010;

int T;
int n, m; // n bugs, m interactions
int UnionSet[maxn];
int dist[maxn];
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        dist[i] ^= dist[old_root];
    }
    return UnionSet[i];
}

int main(void) {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        memset(dist, 0, sizeof(dist));
        bool bFound = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) UnionSet[i] = i; // 初始化
        for (int i = 1; i <= m; ++i) {
            int A, B;
            scanf("%d%d", &A, &B);
            int r1 = Find(A), r2 = Find(B);
            if (r1 != r2) {
                UnionSet[r1] = r2;
                dist[r1] = dist[B] ^ dist[A] ^ 1;
            } else {
                if (1 != (dist[A] ^ dist[B])) bFound = 1;
            }
        }

        printf("Scenario #%d:\n", t);
        if (bFound) printf("Suspicious bugs found!\n\n");
        else printf("No suspicious bugs found!\n\n");
    }
    return 0;
}