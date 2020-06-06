class Solution {
public:
    int numA = 0, numB = 0;
    int firstA = -1, firstB = -1;
    bool check(const string& pat, const string& val, int lenA) {
        int len = val.size(), lenB;
        if ((len - numA * lenA) % numB) return false; // 必须整除
        lenB = (len - numA * lenA) / numB;
        string strA = val.substr(firstA * lenB, lenA);
        string strB = val.substr(firstB * lenA, lenB);
        if (strA == strB) return false; // a,b串不能相同
        int i = 0, j = 0;
        while (i < pat.size()) {
            if (pat[i] == 'a') {
                if (val.substr(j, lenA) != strA) return false;
                j += lenA;
            } else if (pat[i] == 'b') {
                if (val.substr(j, lenB) != strB) return false;
                j += lenB;
            }
            i++;
        }
        return true;
    }
    bool patternMatching(string pattern, string value) {
        for (int i = 0; i < pattern.size(); ++i) {
            char c = pattern[i];
            if (c == 'a') numA++, firstA = (firstA == -1) ? i : firstA;
            else if (c == 'b') numB++, firstB = (firstB == -1) ? i : firstB;
        }
        if (value.empty()) return numA == 0 || numB == 0;
        if (pattern.empty()) return false;
        // 如果a或b没有出现过, 那么再添加更多的a或b也不会影响结果
        if (numA == 0) firstA = pattern.size(), pattern.append(string(numB + 1, 'a')), numA += numB + 1;
        if (numB == 0) firstB = pattern.size(), pattern.append(string(numA + 1, 'b')), numB += numA + 1;
        for (int lenA = 0; lenA * numA <= value.size(); ++lenA) { // 枚举A串的长度
            if (check(pattern, value, lenA)) return true;
        }
        return false;
    }
};