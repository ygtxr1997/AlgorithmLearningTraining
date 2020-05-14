class Solution {
public:
    bool robot(string command, vector<vector<int>>& obstacles, int x, int y) {
        bool path[1003][1003] = { 0 }; // 第一个周期访问的路径
        int sy = 0, sx = 0; // 起点
        for (int i = 0; i < command.size(); ++i) {
            if (command[i] == 'U') sy++;
            else sx++;
            path[sx][sy] = 1;
        }
        int Tn = sx, Tm = sy;
        int offsetX = 0, offsetY = 0;
        if (command[0] == 'U') Tn++, offsetY--;
        else Tm++, offsetX--;
        for (int i = 0; i < obstacles.size(); ++i) {
            int nx = obstacles[i][0], ny = obstacles[i][1];
            if (nx > x || ny > y) continue; // 比(x,y)大的点不做考虑
            if (command[0] == 'U') nx += (ny + offsetY) / Tm; // 修正nx和ny
            else ny += (nx + offsetX) / Tn;
            if ((nx + offsetX) / Tn != (ny + offsetY) / Tm) continue;
            if (path[((nx + offsetX) % Tn) - offsetX][((ny + offsetY) % Tm) - offsetY]) {
                printf("i=%d, nx=%d, ny=%d\n", i, nx, ny);
                return false; // 先遇到障碍物
            } 
        }
        if (command[0] == 'U') x += (y + offsetY) / Tm; // 修正x和y
        else y += (x + offsetX) / Tn;
        if ((x + offsetX) / Tn != (y + offsetY) / Tm) return false;
        return path[((x + offsetX) % Tn) - offsetX][((y + offsetY) % Tm) - offsetY]; // 会来到终点
    }
};