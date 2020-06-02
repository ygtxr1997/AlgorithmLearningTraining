class Solution {
public:
    int convertInteger(int A, int B) {
        unsigned int x = A ^ B, res = 0;
        while (x != 0) {
            x = x & (x - 1);
            res += 1;
        }
        return res;
    }
};