#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 503;
const int maxm = 2010;
const int INF = 0x3f3f3f3f;

int N, M; // N children, M rounds
int UnionSet[maxn];
int dist[maxn];
int vecA[maxm], vecB[maxm], vecD[maxm]; // 因为数组范围开小导致WA了
int Find(int i) {
    if (i != UnionSet[i]) {
        int old_root = UnionSet[i];
        UnionSet[i] = Find(UnionSet[i]);
        dist[i] = (((dist[i] + dist[old_root] + 3) % 3) + 3) % 3;
    }
    return UnionSet[i];
}

int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        int ans = 0, judge_res = 0, judge_count = 0; // 最少次数, 已经确定的法官编号, 已经确定的法官个数
        for (int i = 1; i <= M; ++i) {
            int A, B, D;
            char res;
            scanf("%d%c%d", &A, &res, &B);
            if (res == '>') D = 1;
            else if (res == '=') D = 0;
            else if (res == '<') D = 2;
            vecA[i] = A, vecB[i] = B, vecD[i] = D;
        }
        for (int judge = 0; judge < N; ++judge) { // 枚举所有可能是法官的人
            for (int i = 0; i < N; ++i) UnionSet[i] = i; // 初始化并查集
            memset(dist, 0, sizeof(dist));
            int bValid = 1; // 假设法官为judge时, 是否出现不可能出现的情况
            for (int i = 1; i <= M; ++i) {
                int A = vecA[i], B = vecB[i], D = vecD[i];
                if (A == judge || B == judge) continue; // 法官不加入并查集
                int r1 = Find(A), r2 = Find(B);
                if (r1 != r2) {
                    UnionSet[r1] = r2;
                    dist[r1] = (((dist[B] - dist[A] + D) % 3) + 3) % 3;
                } else { // 已经在并查集中, 需要验证
                    if (D != ((dist[A] - dist[B] + 3) % 3 + 3) % 3) { // 出现矛盾
                        bValid = 0; // 除了judge还有其他法官
                        ans = max(ans, i); // 取最大的那一行条件才充分
                        break;
                    }
                }
            }
            if (bValid) judge_res = judge, judge_count++;
        }
        if (M == 0) {
            if (N == 1) ans = 0, judge_res = 0, judge_count = 1;
        }
        if (judge_count > 1) printf("Can not determine\n");
        else if (judge_count == 0) printf("Impossible\n");
        else printf("Player %d can be determined to be the judge after %d lines\n", judge_res, ans);
    }
    return 0;
}