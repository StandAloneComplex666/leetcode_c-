// 540. Single Element in a Sorted Array
//other's fastest version
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ret = 0;
        for(auto i:nums){
            ret ^=i;
        }
        return ret;
    }
};
//my version
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
    int l = 0;
    int r = nums.size();
    while (l < r){
        const int m = (l + r)/2;
        const int n = m^1;
        if (nums[n] == nums[m]){
            l = m+1;        
        }
        else{
            r = m;
        }
    }
    return nums[l];
    }
};