#include <iostream>
#include <cstring>
using namespace::std;
const int maxn = 30100; // 30100
const int maxm = 150100; // 150100
typedef struct Node {
    Node(){}
    Node(int x1, int x2) : point(x1), dist(x2) { next = -1;}
    int point, dist, next;
} Node;
int Index[maxn]; // 最后一条邻接边的索引
Node Edges[maxm]; // 数据量不小，考虑用优化的邻接表存储

// 直接用deque会超时，考虑用自定义双端队列
int N, M; // N kids, M entries, N<=30000, M<=150000
int least[maxn]; // x到1的最大距离
bool visited[maxn]; // 是否在队列中
int myDeque[maxn]; // myDeque[0]:size
void addEdge(int x, int y, int dxy, int edge_num) {
    Edges[edge_num].point = y;
    Edges[edge_num].dist = dxy;
    Edges[edge_num].next = Index[x];
    Index[x] = edge_num;
}
// spfa+slf: 加入新点x时，如果least[x]>least[deque.front()], 就加至队首，否则加至队尾
int spfa(void) {
    int front = maxn - 1, back = 2, size = 1; // front和back都指向下一个插入的位置
    myDeque[1] = 1;
    least[1] = 0;
    while (size > 0) {
        int pointv = myDeque[front + 1 >= maxn ? 1 : front + 1];
        front = front + 1 >= maxn ? 1 : front + 1; // pop_front()
        size--;
        visited[pointv] = 0;
        for (int iNode = Index[pointv]; iNode != -1; iNode = Edges[iNode].next) {
            int pointx = Edges[iNode].point, dist = Edges[iNode].dist;
            if (least[pointv] + dist < least[pointx]) { // 这里的更新条件要想清楚
                least[pointx] = least[pointv] + dist;
                if (!visited[pointx]) {
                    // push_front()
                    if (size > 0 && least[pointx] > least[myDeque[front + 1 >= maxn ? 1 : front + 1]]) {
                        myDeque[front] = pointx;
                        front = front == 1 ? maxn - 1: front - 1;
                    }
                    // push_back()
                    else { 
                        myDeque[back] = pointx; 
                        back = back + 1 >= maxn ? 1 : back + 1; 
                    }
                    size++;
                    visited[pointx] = 1;
                }
            }
        }
    }
    return least[N];
}
int main(void) {
    while (scanf("%d%d", &N, &M) != EOF) {
        memset(Index, -1, sizeof(Index));
        memset(least, 0x7f, sizeof(least));
        memset(visited, 0, sizeof(visited));
        memset(myDeque, 0, sizeof(myDeque));
        for (int m = 1; m <= M; ++m) {
            int x, y, dxy; // y - x <= dxy
            scanf("%d%d%d", &x, &y, &dxy);
            addEdge(x, y, dxy, m);
        }
        printf("%d\n", spfa());
    }
    return 0;
}