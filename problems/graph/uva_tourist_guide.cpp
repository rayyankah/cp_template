//uva = tourist guide..


signed main()
{
    fast;

    int kase = 1;
    while (true)
    {
        int n, r;
        cin >> n >> r;
        if (n == 0 && r == 0)
            break;
        vv<int> matrix(n + 1, v<int>(n + 1, 0));
        for (int i = 0; i < r; i++)
        {
            int c1, c2, p;
            cin >> c1 >> c2 >> p;
            matrix[c1][c2] = p;
            matrix[c2][c1] = p;
        }
        int s, d, t;
        cin >> s >> d >> t;
        // floyd warshall for max min capacity
        for (int k = 1; k <= n; k++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    matrix[i][j] = max(matrix[i][j], min(matrix[i][k], matrix[k][j]));
                }
            }
        }
        int cap = matrix[s][d];
        int denom = cap - 1;
        int trips = t / denom;
        if (t % denom != 0)
            trips++;
        cout << "Scenario #" << kase << nl;
        cout << "Minimum Number of Trips = " << trips << nl;
        cout << nl;
        kase++;
    }
}
