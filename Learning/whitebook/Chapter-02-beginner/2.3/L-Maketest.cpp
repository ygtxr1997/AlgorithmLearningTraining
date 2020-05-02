#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace::std;
const int maxk = 400;
const int maxh = 100;
const int maxc = 10;
const int maxa = 40000;

int main(void) {
    freopen("input.txt", "w", stdout);
    srand((unsigned)time(NULL));
    for (int t = 1; t <= 300; t++) {
        int K = (rand() % (maxk - 1)) + 1;
        int mod = maxh;
        printf("%d\n", K);
        for (int i = 0; i < K; ++i) {
            int h, a, c;
            h = (rand() % (maxh - 1)) + 1;
            a = (rand() % (mod - 1)) + 1;
            mod = (mod * 3) % (maxa - 1);
            c = (rand() % (maxc - 1)) + 1;
            printf("%d %d %d\n", h, a, c);
        }
        printf("\n");
    }
    int K = 400;
    printf("%d\n", K);
    for (int i = 0; i < K; ++i) {
        int h = 100, a = 40000, c = 10;
        printf("%d %d %d\n", h, a, c);
    }
    return 0;
}