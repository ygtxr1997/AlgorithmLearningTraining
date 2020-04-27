#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 200010;
const int maxm = 40010;

//            [R2]
//           ↗ ↑ 
//          /   |
//         /    |
//        /     |
//       [R1]   |
//      ↗  ↖  |
//     /      \ |
//    /        \|
//  [A]------->[B]    [R1, R2) = [B, R2) - ([A, R1) - [A, B))
//                 即:dist[R1] = dist[B] - (dist[A] - D(A, B))
int N, M;
int UnionSet[maxn]; // 已经验证为正确答案的节点
int dist[maxn]; // 并查集中的点到根节点的距离(数轴上向右为正), 可能为负
                // 距离为左闭右开区间, 如1->10=100即[1, 11) = 100
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]); // 递归更新
        dist[i] += dist[old_root]; // 路径压缩的同时更新dist[]
    }
    return UnionSet[i];
}
int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        for (int i = 1; i <= N; ++i) UnionSet[i] = i;
        memset(dist, 0, sizeof(dist));
        int ans = 0;
        for (int i = 1; i <= M; ++i) {
            int A, B, D;
            scanf("%d%d%d", &A, &B, &D);
            B++; // [A, B + 1)
            int r1 = Find(A);
            int r2 = Find(B);
            if (r1 != r2) { // 有新的节点想加入并查集
                UnionSet[r1] = r2;
                dist[r1] = dist[B] - (dist[A] - D);
            } else { // 两个点都已经在并查集中, 需要验证给出的dist是否与并查集中一致
                if (D != dist[A] - dist[B]) ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}