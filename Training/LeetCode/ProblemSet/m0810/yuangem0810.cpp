class Solution {
public:
    int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
    typedef pair<int, int> pii;
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int n = image.size(), m = image[0].size();
        int sColor = image[sr][sc];
        if (newColor == sColor) return image;
        queue<pii> qu;
        qu.push(pii(sr, sc));
        image[sr][sc] = newColor;
        while (!qu.empty()) {
            int x = qu.front().first, y = qu.front().second;
            qu.pop();
            for (int op = 0; op < 4; ++op) {
                int nx = x + dir[op][0], ny = y + dir[op][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && image[nx][ny] == sColor) {
                    image[nx][ny] = newColor;
                    qu.push(pii(nx, ny));
                }
            }
        }
        return image;
    }
};