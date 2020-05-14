class Solution {
public:
    typedef pair<int, int> pii; // <state, step>
    int flipLights(int n, int m) {
        if (n == 0) return 0;
        else if (n == 1) return (m > 0) + 1;
        else if (n == 2) return (m > 1) + (m > 0) * 2 + 1;
        if (m == 0) return 1;
        else if (m == 1) return 4;
        else if (m == 2) return 7;
        return 8;
    }
};