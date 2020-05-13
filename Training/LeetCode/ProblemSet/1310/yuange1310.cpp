class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        if (arr.empty()) return vector<int>();
        int n = arr.size();
        vector<int> Xor(n, 0); // 前缀异或
        Xor[0] = arr[0];
        for (int i = 1; i < n; ++i) Xor[i] = Xor[i - 1] ^ arr[i];
        vector<int> ret;
        for (int i = 0; i < queries.size(); ++i) {
            int L = queries[i][0], R = queries[i][1];
            if (L == 0) ret.push_back(Xor[R]);
            else ret.push_back(Xor[L - 1] ^ Xor[R]);
        }
        return ret;
    }
};