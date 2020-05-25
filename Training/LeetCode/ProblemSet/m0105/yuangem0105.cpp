class Solution {
public:
    bool oneEditAway(string first, string second) {
        if (abs((int)first.size() - (int)second.size()) > 1) return false;
        string& lon = first.size() > second.size() ? first : second;
        string& sho = first.size() > second.size() ? second : first;
        bool bsame = (lon.size() == sho.size());
        int i = 0, j = 0, step = 0;
        while (i < sho.size() && step <= 1) {
            if (lon[j] == sho[i]) i++, j++;
            else {
                if (!bsame) {
                    j++;
                    step++;
                } else {
                    i++, j++;
                    step++;
                }
            }
        }
        return step <= 1;
    }
};