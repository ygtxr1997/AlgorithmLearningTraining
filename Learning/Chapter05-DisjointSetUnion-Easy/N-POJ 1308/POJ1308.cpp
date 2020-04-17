#include <iostream>
#include <cstring>
#include <algorithm>
using namespace::std;
const int maxn = 100010;

int UnionSet[maxn];
bool Room[maxn];
int Find(int i) {
    if (i != UnionSet[i]) {
        UnionSet[i] = Find(UnionSet[i]);
    }
    return UnionSet[i];
}

int main(void) {
    int A, B;
    int t = 1;
    while (scanf("%d%d", &A, &B) && A + B != -2) {
        if (A == 0 && B == 0) { // 坑爹
            printf("Case %d is a tree.\n", t++);
            continue;
        }
        memset(Room, 0, sizeof(Room));
        for (int i = 1; i < maxn; ++i) UnionSet[i] = i;
        int bFlag = 1; // 是树
        do {
            Room[A] = Room[B] = 1;
            int r1 = Find(A), r2 = Find(B);
            if (r1 == r2) bFlag = 0; // 已经连通了
            else {
                UnionSet[r1] = r2;
            }
        } while (scanf("%d%d", &A, &B) && A + B != 0);
        int root = -1;
        for (int i = 1; i < maxn; ++i) {
            if (Room[i]) {
                if (root == -1) root = Find(i);
                else if (root != Find(i)) {
                    bFlag = 0;
                    break;
                }
            }
        }
        if (bFlag) printf("Case %d is a tree.\n", t++);
        else printf("Case %d is not a tree.\n", t++); 
    }
    return 0;
}