class WordsFrequency {
public:
    unordered_map<string, int> hash;
    WordsFrequency(vector<string>& book) {
        for (auto str : book) hash[str]++;
    }
    
    int get(string word) {
        return hash[word];
    }
};

/**
 * Your WordsFrequency object will be instantiated and called as such:
 * WordsFrequency* obj = new WordsFrequency(book);
 * int param_1 = obj->get(word);
 */