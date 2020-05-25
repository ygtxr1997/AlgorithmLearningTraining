class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        unordered_map<char, int> dic;
        for (const char& c : s1) dic[c]++;
        for (const char& c : s2) dic[c]--;
        for (auto pci : dic) if (pci.second != 0) return false;
        return true;
    }
};