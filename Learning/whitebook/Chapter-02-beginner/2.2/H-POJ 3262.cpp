#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 100100;
typedef long long ll;

// 先选牛a, 牛b的破坏是b.d * a.t * 2
// 先选牛b, 牛a的破坏是a.d * b.t * 2
// 剩下的牛的破坏都是(a.t + b.t) * other.d * 2
int N;
typedef struct node {
    bool operator<(const node& n2) { 
        return t * n2.d < n2.t * d;
    } 
    int t, d;
} node;
node costs[maxn];

int main(void) {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &costs[i].t, &costs[i].d);
        }
        sort(costs, costs + N);
        ll sum = 0, t = 0;
        for (int i = 0; i < N; ++i) {
            sum += t * costs[i].d;
            t += 2 * costs[i].t;
        }
        printf("%lld\n", sum);
    }
    return 0;
}