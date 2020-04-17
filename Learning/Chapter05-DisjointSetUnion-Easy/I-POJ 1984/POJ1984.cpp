#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 40010;
const int maxm = 40010;
const int maxk = 10010;
typedef struct dist {
    dist() : x(0), y(0) {}
    dist(int a, int b) : x(a), y(b) {}
    dist operator-(const dist& d2) { return dist(x - d2.x, y - d2.y); }
    int x, y;
} dist;
dist Dists[maxn];
typedef struct que {
    que(){}
    bool operator<(const que& q2) const { return I < q2.I; }
    int A, B, I; // 查询的A, 查询的B, 查询的I
    int index; // 输入顺序
} que;
que Queries[maxk];

int N, M;
int UnionSet[maxn];
int vecA[maxn], vecB[maxn], vecD[maxn];
char vecDir[maxn];
int K;
int ans[maxk];
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        Dists[i].x += Dists[old_root].x;
        Dists[i].y += Dists[old_root].y;
    }
    return UnionSet[i];
}


int main(void) {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) UnionSet[i] = i;
    for (int i = 1; i <= M; ++i) {
        char blank;
        scanf("%d%d%d%c%c", &vecA[i], &vecB[i], &vecD[i], &blank, &vecDir[i]);
    }
    scanf("%d", &K);
    for (int i = 1; i <= K; ++i) {
        scanf("%d%d%d", &Queries[i].A, &Queries[i].B, &Queries[i].I);
        Queries[i].index = i;
    }
    sort(Queries + 1, Queries + K + 1);
    for (int i = 1, j = 1; j <= K; ) {
        int A = vecA[i], B = vecB[i], D = vecD[i], cDir = vecDir[i];
        dist dAB;
        if (cDir == 'N') dAB.y = D;
        else if (cDir == 'E') dAB.x = D;
        else if (cDir == 'S') dAB.y = -D;
        else if (cDir == 'W') dAB.x = -D;
        int r1 = Find(A), r2 = Find(B);
        if (r1 != r2) { // 有新来的
            UnionSet[r1] = r2;
            Dists[r1] = Dists[B] - (Dists[A] - dAB);
        }
        // 检验结果
        if (i == Queries[j].I) {
            int qA = Queries[j].A, qB = Queries[j].B, qIndex = Queries[j].index;
            int rA = Find(qA), rB = Find(qB);
            if (rA != rB) { // qA和qB关系不确定
                ans[qIndex] = -1;
            } else {
                dist res = Dists[qA] - Dists[qB];
                ans[qIndex] = abs(res.x) + abs(res.y); // 曼哈顿距离
            }
            j++;
        }
        else if (i <= M) i++; // 不用检查结果
    }
    for (int k = 1; k <= K; ++k)
        printf("%d\n", ans[k]);
    return 0;
}