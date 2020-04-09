#include <iostream>
#include <cstring>
using namespace::std;
const int maxn = 10010;
const int INF = 0x3f3f3f3f;
// 边数较少, 用邻接表
typedef struct Node {
    int point, cost, next;
} Node;
Node Edges[2 * maxn]; // 有向边表

int T; // T cases
int N, M, C; // N points, M edges, C layer cost


int main(void) {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &N, &M, &C);
        
    }
    return 0;
}