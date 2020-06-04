class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int len = A.size();
        int iA = m - 1, iB = n - 1;
        int i = len - 1;
        for (; i >= 0 && iA >= 0 && iB >= 0; i--) {
            if (A[iA] > B[iB]) A[i] = A[iA--];
            else A[i] = B[iB--];
        }
        if (iA == -1) {
            while (iB >= 0) {
                A[i--] = B[iB--];
            }
        }
        return;
    }
};