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