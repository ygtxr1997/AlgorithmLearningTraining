#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <map>
using namespace::std;
typedef struct Edge {
    Edge(){}
    Edge(int x1, int x2, double x3) : from(x1), to(x2), cost(x3) {}
    Edge(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost;}
    Edge& operator=(const Edge& e2) {from = e2.from; to = e2.to; cost = e2.cost; return *this; }
    int from, to;
    double cost;
} Edge;

// 上古题目，输入有点恶心，题目也没说是否是简单图。。。
int n, m; // 1 <= n <= 30
vector<Edge> Edges;
double most[31];
vector<string> vec;
// 判断是否存在正环
bool bellman(void) {
    most[1] = 1;
    for (int time = 1; time < n; ++time) {
        for (int e = 0; e < Edges.size(); ++e) {
            int from = Edges[e].from, to = Edges[e].to;
            double cost = Edges[e].cost;
            if (most[to] < most[from] * cost) {
                most[to] = most[from] * cost;
            }
        }
    }
    for (int e = 0; e < Edges.size(); ++e) {
        int from = Edges[e].from, to = Edges[e].to;
        double cost = Edges[e].cost;
        if (most[to] < most[from] * cost) {
            return true; // 存在正环
        }
    }
    return false;
}
int getStrIndex(const string& str) {
    for (int i = 1; i < vec.size(); ++i) {
        // 这里WA了，因为strcmp当两个字符串相等时返回0，大于返回正数，小于返回负数
        if (strcmp(str.c_str(), vec[i].c_str()) == 0) return i;
    }
    return -1;
}

int main(void) {
    int t = 1;
    while ((cin >> n) && n != 0) {
        vector<Edge>().swap(Edges);
        memset(most, 0, sizeof(most));
        vec.clear();
        vec.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            char tmp[100] = { 0 };
            cin >> tmp;
            vec[i] = string(tmp);
        }
        cin >> m;
        for (int i = 1; i <= m; ++i) {
            char c1[100], c2[100];
            double r12;
            cin >> c1 >> r12 >> c2;
            Edges.push_back(Edge(getStrIndex(string(c1)), getStrIndex(string(c2)), r12));
        }
        printf("Case %d: ", t);
        if (bellman()) printf("Yes\n");
        else printf("No\n");
        t++;
    }
    return 0;
}