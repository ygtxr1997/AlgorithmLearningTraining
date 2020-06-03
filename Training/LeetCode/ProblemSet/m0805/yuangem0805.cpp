class Solution {
public:
    int multiply(int A, int B) {
        if (B == 0) return 0;
        if (B == 1) return A;
        if (B == 2) return A + A;
        if (B & 1) return A + (multiply(A, B >> 1) << 1);
        else return multiply(A, B >> 1) << 1;
    }
};