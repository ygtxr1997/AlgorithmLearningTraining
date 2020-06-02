class Solution {
	int count1(int num) {
		int cnt = 0;
		for (int i = 0; i < 32; i++) {
			if (num & (1 << i)) cnt++;
		}
		return cnt;
	}

public:
	vector<int> findClosedNumbers(int num) {
		int s = count1(num);
		vector<int> res = { -1,-1 };
		for (int i = num + 1; i <= 2147483647; i++) {
			if (count1(i) == s) {
				res[0] = i; break;
			}
		}
		for (int i = num - 1; i >= 0; i--) {
			if (count1(i) == s) {
				res[1] = i; break;
			}
		}
		return res;
	}
};