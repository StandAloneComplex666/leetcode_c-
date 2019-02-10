class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n==0)return(1);
        if(n<0)return(0);        
        int A[2];        
        A[0]=10;
        if(n==1)return(A[0]);
        A[1]=9*9; A[0]+=A[1];
        if(n==2)return(A[0]);
        for(int k=3;k<=n&&k<11;k++){
            A[1]*=11-k; A[0]+=A[1];
        }
        return(A[0]);
    }
};