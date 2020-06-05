class Solution {
public:
    vector<int> masterMind(string solution, string guess) {
        int a = 0, b = 0;
        int s[26] = { 0 }, g[26] = { 0 };
        for (int i = 0; i < solution.size(); ++i) {
            if (solution[i] == guess[i]) a++;
            s[solution[i] - 'A']++;
            g[guess[i] - 'A']++;
        }
        for (int i = 0; i < 26; ++i) {
            if (s[i] && g[i]) b += min(s[i], g[i]);
        }
        return {a, b - a};
    }
};