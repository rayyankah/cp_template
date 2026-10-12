//footman -horseman cf ceasar
int n1, n2, k1, k2;
ll dp[101][101][11][11];
ll mod = 100000000;
ll go(int t1, int t2, int c1, int c2) {
    if (t1+t2 == n1+n2) return 1;
    if (~dp[t1][t2][c1][c2]) return dp[t1][t2][c1][c2];
    ll ch1 = 0, ch2 = 0;
    if (t1+1 <= n1 && c1+1 <= k1) ch1 = go(t1+1, t2, c1+1, 0);
    if (t2+1 <= n2 && c2+1 <= k2) ch2 = go(t1, t2+1, 0, c2+1);
    return dp[t1][t2][c1][c2] = (ch1+ch2)%mod;
}
void testcases(){
    cin >> n1 >> n2 >> k1 >> k2;
    memset(dp, -1, sizeof(dp));
    cout << go(0, 0, 0, 0) << endl;
}
