class Solution {
public:
    int maximum(int a, int b) {
        unsigned long long x = (long long)a - (long long)b;
        x >>= 63;
        return x ? b : a;
    }
};