class Solution {
public:
    vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
        if (square1[0] > square2[0] || square1[0] == square2[0] && square1[1] > square2[1]) square1.swap(square2);
        double r1 = square1[2] / 2.0, r2 = square2[2] / 2.0;
        double x1 = square1[0] + r1, y1 = square1[1] + r1; // 中心
        double x2 = square2[0] + r2, y2 = square2[1] + r2;
        if (x1 == x2) return {x1, y1 - r1, x1, max(y1 + r1, y2 + r2)}; // 斜率不存在
        else {
            double k = (y2 - y1) / (x2 - x1), b = y1 - k * x1;
            if (abs(k) <= 1) { // 斜率小于45度
                double l = square1[0], r = max(x1 + r1, x2 + r2);
                return {l, k * l + b, r, k * r + b};
            } else { // 斜率大于45度
                double d = min(square1[1], square2[1]), u = max(y1 + r1, y2 + r2);
                double xd = (d - b) / k, xu = (u - b) / k;
                if (xd < xu || (xd == xu && d < u)) return {xd, d, xu, u};
                return {xu, u, xd, d};
            }
        }
    }
};