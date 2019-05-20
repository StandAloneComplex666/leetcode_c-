class Solution {
public:
string licenseKeyFormatting (string S, int K) {
vector<char> formatted;
  for (auto x : S) {
    if (x == '-') continue;
    if (x > 96) formatted.push_back (x - 32);
    else formatted.push_back (x);
  }
  std::reverse (formatted.begin(), formatted.end());
  string result = "";
  int i = 0;
  for (int j = 0; j < formatted.size(); j++){
    if ((i + 1) % (K + 1) == 0) {
    result.push_back('-');
    result.push_back(formatted[j]);
    i = i + 2;
    }
    else {
    result.push_back(formatted[j]);
    i++;
    }
  }
  std::reverse (result.begin(), result.end());
  return result;
}
};
