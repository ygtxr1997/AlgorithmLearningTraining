#include <iostream>
#include <cstring>
#include <queue>
using namespace::std;
const int INF = 0x3f3f3f3f;
const int maxn = 1003;
const int maxm = 10010;
typedef struct node {
    node(){next = -1;}
    node(int x, int y) : point(x), cost(y) {}
    int point, cost, next;
} node;
node Edges[2 * maxm];
int head[maxn];
int edge_num;
void addEdge(int from, int to, int cost) {
    Edges[edge_num].point = to;
    Edges[edge_num].cost = cost;
    Edges[edge_num].next = head[from];
    head[from] = edge_num++;
}

// 差分约束转化为最短路径, 多个约束同时生效, 所以每次要取约束最严格的那个点(least[]最小)逐步松弛, least[n]即最大距离
// 题目说A牛认为B牛的距离xxxx, A牛始终是在B牛前面的, 不可能在后面, 假设数轴是从左向右递增
// 题中有两种约束 1.B-A<=D, 对应有向边cost(A->B)=D
//               2.B-A>=D, 转化为A-B<=-D, 对应负权有向边cost(B->A)=-D
// 有负权边, 肯定得用spfa了, 如果图中出现负圈, 说明圈中存在不可能同时符合所有约束的点
int N, ML, MD; // N cows, 2<=N<=1000, 1<=ML<=10000, 1<=MD<=10000
bool visited[maxn]; // 是否在队列中
int least[maxn]; // 最短距离
int update[maxn]; // 点i的更新次数

int spfa(void) {
    memset(visited, 0, sizeof visited);
    memset(least, 0x3f, sizeof least);
    memset(update, 0, sizeof update);
    bool bNegCir = false; // 是否存在负圈
    least[1] = 0;
    queue<int> qu;
    qu.push(1);
    while (!qu.empty()) {
        int pv = qu.front();
        qu.pop();
        visited[pv] = 0;
        if (update[pv] > N) { bNegCir = 1; break; } // 存在负圈
        for (int iNode = head[pv]; iNode != -1; iNode = Edges[iNode].next) {
            int px = Edges[iNode].point, cost = Edges[iNode].cost;
            if (least[px] > least[pv] + cost) {
                least[px] = least[pv] + cost;
                update[px]++;
                if (!visited[px]) {
                    qu.push(px);
                    visited[px] = 1;
                }
            }
        }
    }

    if (bNegCir) return -1; // 无解
    return least[N] == INF ? -2 : least[N]; // 任意远;有效约束值
}

int main(void) {
    edge_num = 0;
    memset(head, -1, sizeof head);
    scanf("%d%d%d", &N, &ML, &MD);
    for (int i = 1; i <= ML; ++i) {
        int A, B, D;
        scanf("%d%d%d", &A, &B, &D);
        addEdge(A, B, D);
    }
    for (int i = 1; i <= MD; ++i) {
        int A, B, D;
        scanf("%d%d%d", &A, &B, &D);
        addEdge(B, A, -D);
    }
    printf("%d\n", spfa());
    return 0;
}