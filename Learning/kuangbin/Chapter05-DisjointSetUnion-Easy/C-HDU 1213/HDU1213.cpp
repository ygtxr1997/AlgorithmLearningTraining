#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1010;

// 获取并查集的个数
int T;
int N, M;
int UnionSet[maxn];
int Find(int i) {
    if (UnionSet[i] == -1) return UnionSet[i] = i;
    int cur = i;
    while (i != UnionSet[i]) i = UnionSet[i];
    while (cur != i) {
        int next = UnionSet[cur];
        UnionSet[cur] = i;
        cur = next;
    }
    return i;
}
void Join(int a, int b) {
    int r1 = Find(a), r2 = Find(b);
    if (r1 != r2) UnionSet[r1] = r2;
}

int main(void) {
    scanf("%d", &T);
    while (T--) {
        memset(UnionSet, -1, sizeof(UnionSet));
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= M; ++i) {
            int A, B;
            scanf("%d%d", &A, &B);
            Join(A, B);
        }
        int ans = 0;
        for (int i = 1; i <= N; ++i) 
            if (UnionSet[i] == i || UnionSet[i] == -1) ans++;
        printf("%d\n", ans);
    }
    return 0;
}