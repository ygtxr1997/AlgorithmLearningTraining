class Solution {
public:
    unordered_map<string, int> Enc;
    unordered_map<int, string> Dec;
    string constUrl = "http://tinyurl.com/";
    int index = 0; // 根据出现先后顺序加密
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        Enc[longUrl] = index;
        Dec[index] = longUrl;
        return constUrl + to_string(index++);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int ind = stoi(shortUrl.substr(constUrl.size()));
        return Dec[ind];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));