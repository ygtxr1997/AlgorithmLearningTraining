#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 1e5 + 10;

// 2-种类并查集
int T;
int N, M; // 人数, 信息数
int UnionSet[maxn]; // 已经确定关系的放在同一个集合中
int dist[maxn]; // 节点i到根节点的距离
int Find(int i) {
    if (UnionSet[i] != i) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        dist[i] ^= dist[old_root];
    }
    return UnionSet[i];
}
int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        // 初始化并查集
        for (int i = 0; i < N; ++i) UnionSet[i] = i;
        memset(dist, 0, sizeof(dist));
        for (int i = 0; i < M; ++i) {
            char ch;
            int a, b, ra, rb;
            getchar();
            ch = getchar();
            scanf("%d%d", &a, &b);
            ra = Find(a), rb = Find(b);
            if (ch == 'A' && N == 2) printf("In different gangs.\n");
            else if (ch == 'A') { // 询问a和b
                if (ra != rb) printf("Not sure yet.\n");
                else if (0 == (dist[a] ^ dist[b])) printf("In the same gang.\n");
                else printf("In different gangs.\n");
            } else if (ch == 'D') { // a和b不同, 合并并查集
                if (ra == rb) continue; // 这里容易WA!!!
                UnionSet[ra] = rb;
                dist[ra] = dist[b] ^ (dist[a] ^ 1); // dab = 1
            }
        }
    }
    return 0;
}