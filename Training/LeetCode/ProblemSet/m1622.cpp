class Solution {
public:
    enum DIR {
        L = 0, U = 1, R = 2, D = 3
    };
    char letter[5] = "LURD";
    int go[4][2] = {0, -1, -1, 0, 0, 1, 1, 0};
    vector<string> printKMoves(int K) {
        int lastX = 0, lastY = 0, dir = DIR::R;
        int mxLeft = 0, mxTop = 0, mxRight = 0, mxBottom = 0;
        const int offset = 2500;
        char G[5000][5000];
        memset(G, '_', sizeof(G));
        while (K--) {
            if (G[lastX + offset][lastY + offset] == '_') {
                G[lastX + offset][lastY + offset] = 'X';
                dir = (dir + 1) % 4;
            } else {
                G[lastX + offset][lastY + offset] = '_';
                dir = (dir + 3) % 4;
            }
            lastX += go[dir][0], lastY += go[dir][1];
            mxLeft = min(mxLeft, lastY);
            mxRight = max(mxRight, lastY);
            mxTop = min(mxTop, lastX);
            mxBottom = max(mxBottom, lastX);
        }
        vector<string> ret;
        for (int i = mxTop; i <= mxBottom; ++i) {
            string cur;
            for (int j = mxLeft; j <= mxRight; ++j) {
                cur.push_back(G[i + offset][j + offset]);
            }
            ret.push_back(cur);
        }
        ret[lastX - mxTop][lastY - mxLeft] = letter[dir];
        return ret;
    }
};