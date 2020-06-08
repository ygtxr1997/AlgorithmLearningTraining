class Solution {
public:
    int add(int a, int b) {
        unsigned int aa = a, bb = b;
        while (bb) {
            // 保存所有进位
            unsigned int c = (unsigned int)(aa & bb) << 1;
            aa ^= bb;
            bb = c;
        }
        return aa;
    }
};