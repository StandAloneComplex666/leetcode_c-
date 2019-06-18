class Solution {
public:
    bool detectCapitalUse(string word) {
        int capCnt = count_if(word.begin(), word.end(), [](char c){return c <= 'Z';});
        return !capCnt || capCnt == word.size() || (capCnt == 1 && word[0] <= 'Z');
    }
};