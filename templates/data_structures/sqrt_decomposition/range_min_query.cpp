//range minimum query
int getMin(int l, int r)
{
    int LB = l / BLK;
    int RB = r / BLK;
    int mn = INT_MAX;

    if (LB == RB)
        for (int i = l; i <= r; i++)
            mn = min(ar[i], mn);
    else
    {
        for (int i = l; i < (LB + 1) * BLK; i++)
            mn = min(mn, ar[i]);

        for (int i = LB + 1; i < RB; i++)
            mn = min(mn, F[i]);

        for (int i = RB * BLK; i <= r; i++)
            mn = min(mn, ar[i]);
    }

    return mn;
}
