#include <iostream>
#include <cstring>
#include <cmath>
using namespace::std;
const int INF = 0x3f3f3f;
const int maxn = 1010;
const int maxm = 300100; // 300100

// 并查集入门题
// 每修一台电脑就遍历更新并查集,
// 每次查询电脑就直接利用并查集的find的结果
int UnionSet[maxn]; // 并查集数组
// 并查集的递归查询写法
int FindUnion(int com) {
    if (UnionSet[com] == -1) return -1; // 电脑还未修复
    if (UnionSet[com] != com) {
        UnionSet[com] = FindUnion(UnionSet[com]);
    }
    return UnionSet[com];
}
void JoinUnion(int com1, int com2) {
    int root1 = FindUnion(com1);
    int root2 = FindUnion(com2);
    if (root1 != root2) UnionSet[root1] = root2;
}

int N, D; // N computers, D max distance, 1<=N<=1001, 0<=D<=20000
int X[maxn], Y[maxn]; // coordinates
typedef struct Op {
    char type;
    int comA, comB;
} Op;
Op Ops[maxm];
int op_num = 1;

void solve(void) {
    for (int i = 1; i <= op_num; ++i) {
        int type = Ops[i].type, comA = Ops[i].comA, comB = Ops[i].comB;
        if (type == 'O') {
            if (UnionSet[comA] == -1) UnionSet[comA] = comA;
            for (int comB = 1; comB <= N; comB++) { // 遍历所有修好的计算机，更新并查集
                if (FindUnion(comB) == -1) continue; // 未修好的计算机
                double dist = sqrt((double)(X[comA] - X[comB]) * (X[comA] - X[comB])
                                + (Y[comA] - Y[comB]) * (Y[comA] - Y[comB]));
                if (dist <= D) JoinUnion(comA, comB);
            }
        } else if (type == 'S') {
            bool bSuccess = 0;
            if (FindUnion(comA) == -1 || FindUnion(comB) == -1) bSuccess = 0;
            else if (FindUnion(comA) == FindUnion(comB)) bSuccess = 1;
            else bSuccess = 0;
            if (bSuccess) printf("SUCCESS\n");
            else printf("FAIL\n");
        }
    }
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    memset(UnionSet, -1, sizeof UnionSet);
    scanf("%d%d", &N, &D);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &X[i], &Y[i]);
    }
    do {
        getchar(); // 换行
        if (scanf("%c", &Ops[op_num].type) == EOF) break;
        if (Ops[op_num].type == 'O') {
            if (scanf("%d", &Ops[op_num].comA) == EOF) break;
        } else if (Ops[op_num].type == 'S') {
            if (scanf("%d %d", &Ops[op_num].comA, &Ops[op_num].comB) == EOF) break;
        }
        op_num++;
    } while (1);
    solve();
    return 0;
}