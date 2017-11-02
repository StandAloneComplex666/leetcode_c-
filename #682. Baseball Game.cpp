class Solution{
public:
    int calPoints(vector<string>& ops){
        vector<int> r{};
        for (string& op : ops){
            if      (op=="C"){ r.pop_back(); }
            else if (op=="D"){ r.push_back(2*r.back()); }
            else if (op=="+"){ r.push_back(r.end()[-2]+r.end()[-1]); }
            else             { r.push_back(stoi(op)); }
        }
        return accumulate(r.begin(), r.end(), 0);
    }
};
