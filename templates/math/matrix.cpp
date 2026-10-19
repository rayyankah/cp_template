// matrix power mod MOD: linear recurrences with n up to 1e18. Mat = vector<vi>
typedef vector<vi> Mat;
Mat matMul(const Mat &A, const Mat &B, int m = MOD)
{
    int n = A.size(), k = B.size(), p = B[0].size();
    Mat C(n, vi(p, 0));
    rep(i, 0, n) rep(t, 0, k) if (A[i][t])
        rep(j, 0, p) C[i][j] = (C[i][j] + A[i][t] * B[t][j]) % m;
    return C;
}
Mat matPow(Mat A, int e, int m = MOD)
{
    int n = A.size();
    Mat R(n, vi(n, 0));
    rep(i, 0, n) R[i][i] = 1 % m;
    while (e) { if (e & 1) R = matMul(R, A, m); A = matMul(A, A, m); e >>= 1; }
    return R;
}
// fibonacci: F(n) = matPow({{1, 1}, {1, 0}}, n)[0][1]
