#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace::std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll maxp = 1000001; // todo : 1000001
const ll maxmax = 1000000001;
typedef struct Edge {
    Edge(){}
    Edge(ll x1, ll x2, ll x3) : from(x1), to(x2), cost(x3) {}
    Edge(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost;}
    Edge& operator=(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost; return *this; }
    ll from, to;
    ll cost;
} Edge;
typedef struct Node {
    Node(ll x1, ll x2) : point(x1), cost(x2) {next = NULL; tail = NULL;}
    ~Node() {
        if (next) { next = NULL; delete next; }
        if (tail) { tail = NULL; delete tail; }
    }
    ll point;
    ll cost;
    Node* next;
    Node* tail;
} Node, *PNode;

// 邻接矩阵会超出内存限制，选择存边
// 朴素dijkstra会超时，考虑优先队列优化
int N; // N cases
ll P, Q; // P stops, Q paths, 1<=P,Q<=1000000, CCS是1号
PNode StartEdges[maxp]; 
PNode EndEdges[maxp]; 
ll leaveCCS[maxp]; // 以CCS为起点的最短距离
ll goCCS[maxp]; // 以CCS为终点的最短距离
bool visited[maxp];
void addNode(int x, int y, int dxy) {
    if (StartEdges[x] == NULL) {
        StartEdges[x] = new Node(y, dxy);
        StartEdges[x]->tail = StartEdges[x];
    } else {
        StartEdges[x]->tail->next = new Node(y, dxy);
        StartEdges[x]->tail = StartEdges[x]->tail->next;
    }
    if (EndEdges[y] == NULL) {
        EndEdges[y] = new Node(x, dxy);
        EndEdges[y]->tail = EndEdges[y];
    } else {
        EndEdges[y]->tail->next = new Node(x, dxy);
        EndEdges[y]->tail = EndEdges[y]->tail->next;
    }
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
        for (PNode pNode = StartEdges[pointv]; pNode != NULL; pNode = pNode->next) {
            ll costvx = pNode->cost, pointx = pNode->point;
            ll newcost = min(leaveCCS[pointx], costvx + leaveCCS[pointv]);
            pqu.push(pll(-newcost, pointx));
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
        for (PNode pNode = EndEdges[pointv]; pNode != NULL; pNode = pNode->next) {
            ll costvx = pNode->cost, pointx = pNode->point;
            ll newcost = min(goCCS[pointx], costvx + goCCS[pointv]);
            pqu.push(pll(-newcost, pointx));
        }
    }

    // 统计总和
    ll ans = 0;
    for (ll i = 1; i <= P; ++i) {
        ans += leaveCCS[i] + goCCS[i];
        cout << leaveCCS[i] << " " << goCCS[i]<< endl;
    }
    return ans;
}

int main(void) {
    cin >> N;
    while (N--) {
        cin >> P >> Q;
        memset(StartEdges, 0, sizeof(StartEdges));
        memset(EndEdges, 0, sizeof(EndEdges));
        memset(leaveCCS, 0x3f, sizeof(leaveCCS));
        memset(goCCS, 0x3f, sizeof(goCCS));
        for (ll i = 1; i <= Q; ++i) {
            ll x, y, dxy;
            cin >> x >> y >> dxy;
            addNode(x, y, dxy);
        }
        cout << dijkstra() << endl;
    }
    return 9;
}