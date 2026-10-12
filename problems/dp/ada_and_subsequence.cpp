//ada and subsequece
void solve()
{
      int N, M;
    cin >> N >> M;
    vector<int> cost(26);
    for (int i = 0; i < 26; i++)
        cin >> cost[i];
    string A, B;
    cin >> A >> B;
    vector<vector<ll>> dp(N + 1, vector<ll>(M + 1, 0));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + cost[A[i - 1] - 'a'];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    // Base cases: dp[0][0] = 0, and dp[i][0] = 0 for all i, dp[0][j] = 0 for all j
    cout << dp[N][M] << nl;
}
