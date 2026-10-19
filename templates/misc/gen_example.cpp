// random test generator for stress.sh (seed from argv[1])
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv)
{
    mt19937 rng(atoi(argv[1]));
    auto rnd = [&](int l, int r) { return (int)(rng() % (r - l + 1)) + l; };
    int n = rnd(1, 8);
    cout << n << "\n";
    for (int i = 0; i < n; i++) cout << rnd(1, 10) << " \n"[i == n - 1];
}
