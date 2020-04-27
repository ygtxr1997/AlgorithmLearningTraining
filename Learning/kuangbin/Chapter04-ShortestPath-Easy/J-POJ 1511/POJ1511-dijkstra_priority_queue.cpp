#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace::std;
typedef long long ll;
//typedef pair<ll, ll> pll;
typedef struct pll {
    pll(ll x1, ll x2) : first(x1), second(x2) {}
    bool operator<(pll p2) const {return first < p2.first;}
    bool operator>(pll p2) const {return first > p2.first;}
    ll first, second;
} pll;
const ll maxp = 1000010; // todo : 1000010
typedef struct Node {
    Node(){}
    Node(ll x1, ll x2) : point(x1), cost(x2) {next = -1;}
    ll point;
    ll cost;
    ll next; // 存放序号，而不是指针
} Node, *PNode;

// 邻接矩阵会超出内存限制，选择存边
// 朴素dijkstra会超时，考虑优先队列优化
// 优先队列优化后，并优化邻接矩阵，还是超时
// 把cin改成scanf就好了，抽象啊抽象，算法本身没问题
int N; // N cases
ll P, Q; // P stops, Q paths, 1<=P,Q<=1000000, CCS是1号
ll StartIndex[maxp]; // 起点编号, 存放起点邻接的最后一条边在StartEdges[]中的序号
ll EndIndex[maxp];  // 终点编号, 存放终点邻接的最后一条边在EndEdges[]中的序号
Node StartEdges[maxp]; // 头插法更新邻接表
Node EndEdges[maxp]; 
ll leaveCCS[maxp]; // 以CCS为起点的最短距离
ll goCCS[maxp]; // 以CCS为终点的最短距离
bool visited[maxp];
// x->y = dxy
void addNode(ll x, ll y, ll dxy, ll edge_count) {
    StartEdges[edge_count].point = y;
    StartEdges[edge_count].cost = dxy;
    StartEdges[edge_count].next = StartIndex[x]; // 头插
    StartIndex[x] = edge_count;

    EndEdges[edge_count].point = x;
    EndEdges[edge_count].cost = dxy;
    EndEdges[edge_count].next = EndIndex[y]; // 头插
    EndIndex[y] = edge_count;
}
ll dijkstra(void) {
    memset(visited, 0, sizeof(visited));
    // 先算CCS到所有点的最短距离
    priority_queue<pll> pqu; // cost|point,要取最小的cost
    pqu.push(pll(0, 1));
    while (!pqu.empty()) {
        ll costv = -pqu.top().first, pointv = pqu.top().second;
        pqu.pop();
        if (visited[pointv]) continue;
        visited[pointv] = 1;
        leaveCCS[pointv] = costv;
        // llNode: 边表的序号
        for (ll llNode = StartIndex[pointv]; llNode != -1; llNode = StartEdges[llNode].next) {
            ll costvx = StartEdges[llNode].cost, pointx = StartEdges[llNode].point;
            if (!visited[pointx] && costvx + leaveCCS[pointv] < leaveCCS[pointx]) {
                ll newcost = costvx + leaveCCS[pointv];
                pqu.push(pll(-newcost, pointx));
            }
        }
    }

    // 再算所有点到CCS的最短距离
    memset(visited, 0, sizeof(visited));
    pqu.push(pll(0, 1));
    while (!pqu.empty()) {
        ll costv = -pqu.top().first, pointv = pqu.top().second;
        pqu.pop();
        if (visited[pointv]) continue;
        visited[pointv] = 1;
        goCCS[pointv] = costv;
        // llNode: 边表的序号
        for (ll llNode = EndIndex[pointv]; llNode != -1; llNode = EndEdges[llNode].next) {
            ll costvx = EndEdges[llNode].cost, pointx = EndEdges[llNode].point;
            if (!visited[pointx] && costvx + goCCS[pointv] < goCCS[pointx]) {
                ll newcost = costvx + goCCS[pointv];
                pqu.push(pll(-newcost, pointx));
            }
        }
    }

    // 统计总和
    ll ans = 0;
    for (ll i = 1; i <= P; ++i) {
        ans += leaveCCS[i] + goCCS[i];
    }
    return ans;
}

int main(void) {
    cin >> N;
    while (N--) {
        cin >> P >> Q;
        memset(StartIndex, -1, sizeof(StartIndex));
        memset(EndIndex, -1, sizeof(EndIndex));
        memset(leaveCCS, 0x7f, sizeof(leaveCCS));
        memset(goCCS, 0x7f, sizeof(goCCS));
        for (ll i = 1; i <= Q; ++i) {
            ll x, y, dxy;
            scanf("%lld%lld%lld", &x, &y, &dxy);
            addNode(x, y, dxy, i);
        }
        cout << dijkstra() << endl;
    }
    return 0;
}