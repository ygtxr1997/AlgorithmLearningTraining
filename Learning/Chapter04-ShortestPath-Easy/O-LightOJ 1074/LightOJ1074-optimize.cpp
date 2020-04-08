#include <iostream>
#include <cstring>
using namespace::std;
const int maxn = 202;
const int maxm = 80010; // 最大边数
const int INF = 0x3f3f3f3f;
typedef struct Node {
    int point, cost, next;
} Node;
Node Edges[maxm]; // 边表
int head[maxn]; // head[px]=该点邻接的最后一条边在边表中的索引

int T; // T 组数据
int n, m, q; // n 个交叉, m 条路, q 个查询
int mark[maxn]; // 交叉路的评分
int least[maxn]; // 得分越高越好, 从交叉路1出发到达各交叉路口的评分
bool visited[maxn]; // 是否在栈中
int stack[maxn]; // 自定义栈
int count[maxn]; // 节点更新次数
bool circle[maxn]; // 是否在负环中

void addEdge(int from, int to, int edge_num) {
    Edges[edge_num].point = to;
    Edges[edge_num].cost = (mark[to] - mark[from]) 
                    * (mark[to] - mark[from]) 
                    * (mark[to] - mark[from]);
    Edges[edge_num].next = head[from]; // 头插法
    head[from] = edge_num;
}

// 考虑用栈优化的spfa, 会超时, 试试用邻接表存边，不用邻接矩阵
// 如果spfa中的节点更新次数超过n次说明在负环中, 不判负环会超时
void spfa(void) {
    memset(visited, 0, sizeof(visited));
    memset(stack, 0, sizeof(stack));
    memset(count, 0, sizeof(count));
    memset(circle, 0, sizeof(circle));
    int top = 0; // 栈顶元素位置, 初始是0
    stack[++top] = 1; // 起点
    least[1] = 0;
    while (top > 0) {
        int pv = stack[top--]; // 出栈
        visited[pv] = 0;
        if (count[pv] > n) {
            circle[pv] = 1;
            continue;
        }
        for (int iNode = head[pv]; iNode != -1; iNode = Edges[iNode].next) {
            int px = Edges[iNode].point, cost = Edges[iNode].cost;
            if (least[px] > least[pv] + cost
                && circle[px] == 0) {
                least[px] = least[pv] + cost;
                if (!visited[px]) {
                    visited[px] = 1;
                    stack[++top] = px; // 入栈
                    count[px]++;
                }
            }
        }
    }
}

int main(void) {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        memset(head, -1, sizeof(head)); // 初始化索引为-1
        memset(mark, 0, sizeof(mark));
        memset(least, 0x3f, sizeof(least));
        getchar();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            int mark_point;
            scanf("%d", &mark_point);
            mark[i] = mark_point;
        }

        scanf("%d", &m);
        for (int i = 1; i <= m; ++i) {
            int from, to;
            scanf("%d%d", &from, &to);
            addEdge(from, to, i);
        }

        scanf("%d", &q);
        printf("Case %d:\n", t);
        spfa();
        for (int i = 1; i <= q; ++i) {
            int target;
            scanf("%d", &target);
            int ans = least[target];
            if (ans < 3 || least[target] == INF) printf("?\n");
            else printf("%d\n", ans);
        }
    }
    return 0;
}