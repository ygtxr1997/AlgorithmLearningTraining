// 因为这题没有括号, 优先级也仅限于加减乘除, 所以不需要符号栈, 只要数字栈就够了
class Solution {
public:
    int calculate(string s) {
        long long num = 0;
        char opt = '+';
        stack<int> st;
        for (int i = 0; i <= s.size(); ++i) {
            if (s[i] == ' ') continue;
            else if (s[i] >= '0' && s[i] <= '9') num = num * 10 + s[i] - '0';
            else {
                // 当i==s.size()时还要计算一次opt
                if (opt == '+') st.push(num);
                else if (opt == '-') st.push(-num);
                else {
                    int top = st.top();
                    st.pop();
                    if (opt == '*') st.push(num * top);
                    else if (opt == '/') st.push(top / num);
                }
                opt = s[i];
                num = 0;
            }
        }
        long long sum = 0;
        while (!st.empty()) {
            sum += st.top();
            st.pop();
        }
        return sum;
    }
};