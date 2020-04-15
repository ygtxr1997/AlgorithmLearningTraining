#include <iostream>
#include <cstring>
#include <algorithm>
const int maxn = 50010;

// 在(mod 3)加法的定义下,
// A->B=1, B->C=1, C->A=1, 食用关系等价于向量值为"正1"
// A->A=0, B->B=0, C->C=0, 相等关系等价于向量值为"0"
// 带权并查集
int N, K;
int UnionSet[maxn]; // 已经作为真话的点
int dist[maxn]; // 节点到根的距离, 可能为负数
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        dist[i] += dist[old_root];
    }
    return UnionSet[i];
}

int main(void) {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; ++i) UnionSet[i] = i;
    memset(dist, 0, sizeof(dist));
    int ans = 0;
    for (int i = 1; i <= K; ++i) {
        int D, X, Y; // D=1:X和Y同类, X->Y=0; D=2:X吃Y, X->Y=1.
        scanf("%d%d%d", &D, &X, &Y);
        if (X > N || Y > N ) { ans++; continue; }
        int r1 = Find(X), r2 = Find(Y);
        if (r1 != r2) { // 有新加入的点, 不用验证
            UnionSet[r1] = r2;
            dist[r1] = dist[Y] - (dist[X] - (D - 1));
            continue;
        } else { // X和Y都已经出现过, 需要验证这句话
            if (D - 1 != ((dist[X] - dist[Y]) % 3 + 3) % 3)
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}