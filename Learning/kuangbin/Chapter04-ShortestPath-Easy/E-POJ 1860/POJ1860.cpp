#include <iostream>
#include <queue>
#include <cstring>
using namespace::std;
typedef struct Change {
    Change(void) {}
    Change(int i1, int i2, double f1, double f2) : From(i1), To(i2),
        Rab(f1), Cab(f2) {}
    Change& operator=(const Change& c2) {From = c2.From; To = c2.To; Rab = c2.Rab; Cab = c2.Cab; return *this;}
    Change(const Change& c2) {From = c2.From; To = c2.To; Rab = c2.Rab; Cab = c2.Cab;} 
    int From, To;
    double Rab, Cab; // get = (1 - C) * R * have
} Change;

// WA了半天，原来是因为float类型精度不够，换成double就好了
// 理解题意，cashB = (cashA - C) * R
int N, M, S; // N货币种类数, M交易点个数, S持有货币种类, 1 <= S <= N <= 100, 1 <= M <= 100
double V; // V持有货币额
Change dist[300]; // 存放2 * M条边
double most[101]; // 从S货币换成x货币能获得的最大钱
// 判断是否有正环
bool bellman(void) {
    most[S] = V;
    for (int i = 1; i < N; ++i) {
        for (int j = 2; j <= 2 * M + 1; ++j) {
            int a = dist[j].From, b = dist[j].To;
            double rab = dist[j].Rab, cab = dist[j].Cab;
            most[b] = max(most[b], (most[a] - cab) * rab);
        }
        int xx = 1;
    }
    for (int j = 2; j <= 2 * M + 1; ++j) {
        int a = dist[j].From, b = dist[j].To;
        double rab = dist[j].Rab, cab = dist[j].Cab;
        if (most[b] < (most[a] - cab) * rab) return true;
    }
    return false;
}

int main(void) {
    while (cin >> N >> M >> S >> V) {
        memset(dist, 0, sizeof(dist));
        memset(most, 0, sizeof(most));
        for (int m = 1; m <= M; m++) {
            int a, b;
            cin >> a >> b;
            double rab, cab, rba, cba;
            cin >> rab >> cab >> rba >> cba;
            dist[2 * m] = Change(a, b, rab, cab);
            dist[2 * m + 1] = Change(b, a, rba, cba);
        }
        if (bellman()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}