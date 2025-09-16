///dice..
 const int N = 1e9+7;
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<int>>dp(n+2,vector<int>(target+1,0));
        vector<vector<int>>csum(n+2,vector<int>(target+1,0));
        dp[n+1][0]=csum[n+1][0]=1;
        for(int i=0; i<=target; i++){
            csum[n+1][i]=1;
        }
        //csum[i][j]=sum of dp values in ith row(dices taken upto n) from 0 to j
        for(int dice=n; dice>=1; dice--){
            dp[dice][0]=csum[dice][0]=0;
            for(int val = 1; val<=target; val++){
                //face possible -->1 to k
                //face nibo 1 to k
                //val hbe val-1 to val-k -->csum[val-1]-csum[val-k-1]
                //but val jodi k theke choto hoy
                //face nibo 1 to val
                //val hbe val-1 to 0-->csum[val-1]
                if(val-k-1<00){
                    dp[dice][val]=((dp[dice][val]%N)+(csum[dice+1][val-1]%N))%N;
                    if(dp[dice][val]<0)dp[dice][val]+=N;
                }
                else{
                    dp[dice][val]+=(csum[dice+1][val-1]-csum[dice+1][val-k-1])%N;
                    if(dp[dice][val]<0)dp[dice][val]+=N;

                }
                csum[dice][val]=((csum[dice][val-1]%N)+(dp[dice][val]%N))%N;
                if(csum[dice][val]<0)csum[dice][val]+=N;
            }
        }
        return dp[1][target];

    }








