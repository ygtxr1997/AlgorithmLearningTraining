#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 10010;

int n;
int UnionSet[maxn];
// 并查集的递归写法, 
// 把已经使用的天加入并查集中, 并查集的根代表该天往前第一个未占用的天
int Find(int i) {
    if (UnionSet[i] == -1) return i;
    else return UnionSet[i] = Find(UnionSet[i]);
}
typedef struct Node {
    Node(){}
    Node(int x1, int x2) : p(x1), d(x2) {}
    bool operator<(const Node& n2) const { return p > n2.p; }
    int p, d;
} Node;
Node products[maxn];

int main(void) {
    while (scanf("%d", &n) != EOF) {
        memset(UnionSet, -1, sizeof(UnionSet));
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &products[i].p, &products[i].d);
        }
        sort(products + 1, products + 1 + n); // 每件商品尽可能晚卖
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int root = Find(products[i].d); // UnionSet[i]=-1代表该天可用
            if (root > 0) {
                ans += products[i].p;
                UnionSet[root] = root - 1; // 该天被用了, 链接到前一天
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}