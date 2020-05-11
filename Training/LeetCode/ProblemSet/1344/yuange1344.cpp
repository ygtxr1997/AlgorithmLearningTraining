class Solution {
public:
    double angleClock(int hour, int minutes) {
        double hAng = (hour % 12) * 30;
        double hMin = (minutes % 60) * 6;
        hAng += ((double)(minutes % 60)) / 60 * 30;
        double res = abs(hAng - hMin);
        if (res >= 180) res = 360 - res;
        return res;
    }
};