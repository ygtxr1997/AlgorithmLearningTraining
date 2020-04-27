#include <iostream>
#include <cstring>
using namespace::std;
const int maxn = 30010;
const int maxm = 503;

int UnionSet[maxn];
int Size[maxn]; // 该节点及其所有子节点的个数
int Find(int i) {
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
    int r1 = Find(a);
    int r2 = Find(b);
    if (r1 != r2) { // 两个节点不属于同一集合
        if (Size[r1] < Size[r2]) { // 秩较大的根作为合并后的根
            UnionSet[r1] = r2;
            Size[r2] += Size[r1];
        } else {
            UnionSet[r2] = r1;
            Size[r1] += Size[r2];
        }
    }
}
int n, m;
int k;
int g, p; // 队长, 队员

int main(void) {
    while(scanf("%d%d", &n, &m) && n + m != 0) {
        memset(UnionSet, -1, sizeof(UnionSet));
        memset(Size, 0, sizeof(Size));
        UnionSet[0] = 0; Size[0] = 1;
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &k);
            scanf("%d", &g);
            if (UnionSet[g] == -1) {
                UnionSet[g] = g;
                Size[g] = 1;
            }
            for (int j = 1; j < k; ++j) {
                scanf("%d", &p);
                if (UnionSet[p] == -1) {
                    UnionSet[p] = p;
                    Size[p] = 1;
                }
                Join(g, p);
            }
        }
        printf("%d\n", Size[Find(0)]);
    }
    return 0;
}