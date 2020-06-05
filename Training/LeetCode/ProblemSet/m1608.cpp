class Solution {
public:
    string numberToWords(int num) {
        if (!num) return "Zero";
        string res;
        int cnt = 2;
        int factors[4] = {1000000000, 1000000, 1000, 1};
        for (int i = 0; i < 4; i ++) {
            res += helper(num / factors[i]);
            if (num / factors[i]) res += " " + gens[i] + " ";
            num %= factors[i];
        }
        while (res.size() && res.back() == ' ') res.pop_back();
        return res;
    }

private:
    string ones[21] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                       "Nine", "Ten", "Eleven","Twelve", "Thirteen", "Fourteen", "Fifteen",
                       "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    string tens[10] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    string gens[4] = {"Billion", "Million", "Thousand", ""};
    
    string helper(int num) {
        // 1000;
        if (num < 20) return ones[num];
        if (num < 100) {
            string ans = tens[num / 10];
            if (num % 10) ans += " " + ones[num % 10];
            return ans;
        }
        string ans = ones[num / 100] + " Hundred";
        if (num % 100) ans += " " + helper(num % 100);
        return ans;
    }
};