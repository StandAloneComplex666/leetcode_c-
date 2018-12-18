// the brute force solution used recursion, whose time complexity is O(2^n)
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        return find(0,nums,S);    
    }
    int find(int p, vector<int>& nums, int sum) {
        if(p==nums.size()) return sum==0;
        return find(p+1,nums,sum+nums[p])+find(p+1,nums,sum-nums[p]);
    }
};

//O(ns) Memoization. There is redundancy in brute force. A call to find() with the same start index and target sum can be made multiple times. 
//We can use a 2d table to cache the result to avoid duplicate calls with the same state.
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int,int>> mem(nums.size());
        return find(0,nums,S,mem);    
    }
    int find(int p, vector<int>& nums, int sum, vector<unordered_map<int,int>>& mem) {
        if(p==nums.size()) return sum==0;
        auto it = mem[p].find(sum);
        if(it != mem[p].end()) return it->second;
        return mem[p][sum]=find(p+1,nums,sum+nums[p],mem)+find(p+1,nums,sum-nums[p],mem);
    }
};
// O(ns) pseudo polynomial dp, s is the target sum. Most dp problems visits continuous states and 
// this is a great example to use hashtable to visit valid states only.

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        vector<unordered_map<int,int>> dp(n+1);
        dp[0][0]=1;
        for(int i=0;i<n;i++)
            for(auto &p:dp[i]) {
                dp[i+1][p.first+nums[i]] += p.second; 
                dp[i+1][p.first-nums[i]] += p.second;
            }
        return dp[n][S];
    }
};
// O(ns) time, linear space dp.
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        unordered_map<int,int> cur({{0,1}}), nxt, *p_cur=&cur, *p_nxt=&nxt;
        for(int i=0;i<nums.size();i++) {
            for(auto &p:*p_cur) {
                (*p_nxt)[p.first+nums[i]] += p.second; 
                (*p_nxt)[p.first-nums[i]] += p.second;
            }
            swap(p_cur,p_nxt);
            p_nxt->clear();
        }
        return (*p_cur)[S];
    }
};