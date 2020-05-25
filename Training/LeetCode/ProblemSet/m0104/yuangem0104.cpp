class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> dic;
        for (auto c : s) dic[c]++;
        int odd = 0;
        for (auto pci : dic) if (pci.second % 2) odd++;
        return odd <= 1;
    }
};