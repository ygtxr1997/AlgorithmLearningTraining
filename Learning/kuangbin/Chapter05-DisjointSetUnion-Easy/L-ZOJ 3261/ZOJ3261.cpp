#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
using namespace::std;
const int maxn = 10010;
const int maxm = 20010;
const int maxq = 50010;
typedef pair<int, int> pii;

// 先把要删除的边都记录下来, 那么根据战争前的边和要删除的边可以得出删除后的终态
// 再由终态反向遍历M个操作, 如果是destroy则把删除的这条边添加回去, 
// 如果是query则去判断该节点的根的power是否比自己的大。
// 并查集在合并时, 保证根节点总为power较大的那个,
// 还需要一个most[]记录每个节点在他所在的并查集的根的power值.
int N; // N planets
int P[maxn];
int UnionSet[maxn];
int most[maxn];
int M; // M connects
int vecA[maxm], vecB[maxm];
map<pii, bool> Hash;
int Q; // Q queries
typedef struct query {
    int type; // 0:query, 1:destroy
    int A, B;
} query;
query Ques[maxq];
int ans[maxq];

int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        most[i] = max(most[i], most[old_root]);
    }
    return UnionSet[i];
}
void Join(int A, int B) {
    int r1 = Find(A), r2 = Find(B);
    if (r1 == r2) return; // 已经连接
    // 把值较大的作为根, 如果值相同则把序号小的作为根
    if (most[r1] > most[r2] || (most[r1] == most[r2] && r1 < r2)) UnionSet[r2] = r1; 
    else UnionSet[r1] = r2;
}

int main(void) {
    bool bFirst = 1;
    while (scanf("%d", &N) != EOF) {
        if (bFirst) bFirst = 0;
        else printf("\n"); // 每个case换行
        for (int i = 0; i < N; ++i) scanf("%d", &P[i]);
        Hash.clear();
        for (int i = 0; i < N; ++i) UnionSet[i] = i, most[i] = P[i]; // 初始化
        scanf("%d", &M);
        for (int i = 0; i < M; ++i) {
            int A, B;
            scanf("%d%d", &A, &B);
            if (A > B) swap(A, B); // A < B
            Hash[pii(A, B)] = 1; // 所有边
        }
        scanf("%d", &Q);
        for (int i = 0; i < Q; ++i) {
            char cType[10];
            scanf("%s", cType);
            if (cType[0] == 'q') {
                scanf("%d", &Ques[i].A);
                Ques[i].type = 0;
            } else if (cType[0] == 'd') {
                int A, B;
                scanf("%d%d", &A, &B);
                if (A > B) swap(A, B);
                Ques[i].A = A;
                Ques[i].B = B;
                Ques[i].type = 1;
                Hash[pii(A, B)] = 0; // 即将破坏的边
            }
        }
        for (map<pii, bool>::iterator ite = Hash.begin(); ite != Hash.end(); ++ite) {
            if (ite->second) { // 不会被破坏的边
                Join(ite->first.first, ite->first.second);
            }
        }
        memset(ans, 0, sizeof(ans));
        int tot = 0; // 答案的元素个数
        for (int i = Q - 1; i >= 0; --i) {
            if (Ques[i].type) { // destroy
                Join(Ques[i].A, Ques[i].B);
            } else { // query
                int A = Ques[i].A;
                int r1 = Find(A);
                if (most[r1] <= P[A]) ans[tot++] = -1; // 找不到更大的
                else ans[tot++] = r1;
            }
        }
        for (int i = tot - 1; i >= 0; --i) { // 倒着打印
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}