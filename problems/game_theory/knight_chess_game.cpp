//chess
int dp[16][16];
int func(int x, int y){
    
    if(x<1 || y<1 || x>15|| y>15){
        return 1;//amr jonno winning cz je dise she invalid move dise
    }
    if(dp[x][y]!=-1){
        return dp[x][y];
    }
    int ans = func(x-1,y-2)+func(x-2,y-1)+func(x-2, y+1)+func(x+1, y-2);
    if(ans<=3){
        return dp[x][y]=1;
    }
    return dp[x][y]=0;
}
//================ Code starts here ================
void solve()
{
  int x,y;

    cin >>x>>y;
    if(func(x,y)){
        cout<<"First"<<nl;
    }
    else{
        cout<<"Second"<<nl;
    }


}
