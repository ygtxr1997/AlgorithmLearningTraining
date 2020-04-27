// 打表枚举题
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace::std;
map<string, int> fun; // <词性, 序号>
map<string, int> dic; // <字典里的单词, 词性序号>
map<string, char> str; // <短语结构, 缩写>
map<string, int> ste; // <句子形式, 无>
void init(void) {
    fun["n."] = 0;
    fun["pron."] = 1;
    fun["adj."] = 2;
    fun["adv."] = 3;
    fun["prep."] = 4;
    fun["art."] = 5;
    fun["vt."] = 6;
    fun["vi."] = 7;
    fun["v."] = 8;

    str["450"] = 'A'; // 介词短语
    str["42"] = 'A';
    str["41"] = 'A';
    str["1"] = 'S'; // 主语或宾语
    str["50"] = 'S';
    str["520"] = 'S';
    str["7"] = 'I'; // 不及物谓语
    str["37"] = 'I';
    str["6"] = 'T'; // 及物谓语
    str["36"] = 'T';
    str["8"] = 'V'; // 通用谓语
    str["38"] = 'V';

    ste["SI"] = 1; // 主+谓
    ste["SV"] = 1;
    ste["STS"] = 1; // 主+谓+宾
    ste["SVS"] = 1;
    ste["ASI"] = 1; // 介+主+谓
    ste["ASV"] = 1;
    ste["ASTS"] = 1; // 介+主+谓+宾
    ste["ASVS"] = 1;
    ste["SAI"] = 1; // 主+介+谓
    ste["SAV"] = 1;
    ste["SATS"] = 1; // 主+介+谓+宾
    ste["SAVS"] = 1;
    ste["SIA"] = 1;  // 主+谓+介
	ste["SVA"] = 1;
	ste["STAS"] = 1;  // 主+谓+介+宾
	ste["SVAS"] = 1;
	ste["STSA"] = 1;  // 主+谓+宾+介
	ste["SVSA"] = 1;
}
int n, m;
int main() {
    ios::sync_with_stdio(0);
    string a, b;
    init();
    scanf("%d%d", &n, &m);
    while (n--) {
        cin >> a >> b;
        dic[a] = fun[b];
    }
    while (m--) {
        bool flag = 0;
        b = "";
        while (cin >> a) {
            if (isupper(a[0])) a[0] = a[0] + 32; // 转为小写
            int len = a.size();
            if (a[len - 1] == '.') {
                flag = 1;
                a.erase(len - 1, 1);
            }
            if (a[len - 1] == ',') a.erase(len - 1, 1);
            b += '0' + dic[a];
            if (flag) break;
        }
        string c, d;
        c = d = "";
        for (int i = 0; i < b.size(); ++i) { // 转化为缩写结构
            c += b[i];
            if (str[c]) {
                d += str[c];
                c = "";
            }
        }
        d += c;
        if (ste[d]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}