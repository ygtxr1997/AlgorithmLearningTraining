class Solution {
public:
    bool isUnique(string astr) {
        int bit = 0;
        for (const char c : astr) {
            if (bit & (1 << (c - 'a'))) return false;
            bit += (1 << (c - 'a'));
        }
        return true;
    }
};