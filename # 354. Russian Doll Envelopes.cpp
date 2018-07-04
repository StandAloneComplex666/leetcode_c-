class Solution {
public:
    int maxEnvelopes(vector<pair<int, int>>& envelopes) {
        auto cmp = [](pair<int, int> a, pair<int, int> b) 
        { return a.first==b.first?a.second>b.second:a.first<b.first; };
        sort(envelopes.begin(), envelopes.end(), cmp);
        vector<int> dp;
        for(auto val: envelopes)
        {
            if(dp.size()==0 || val.second>dp.back()) dp.push_back(val.second);
            else 
            {
                int left = 0, right = dp.size()-1;
                while(left <= right)
                {
                    int mid = (left+right)/2;
                    if(dp[mid] < val.second) left = mid+1;
                    else right = mid-1;
                }
                dp[left] = val.second;
            }
        }
        return dp.size();
    }
};