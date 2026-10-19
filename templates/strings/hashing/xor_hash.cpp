// hashing sets and multisets. give every value a random 64-bit number val(x)
// xor of val over a range: every value appears an even number of times <=> 0 (with high probability)
// sum of val over a range: equal multisets <=> equal sums. sets {1..k}: compare with prefix sums of val(1..k)
mt19937_64 hrng(chrono::steady_clock::now().time_since_epoch().count());
map<int, unsigned long long> hval;
unsigned long long val(int x)
{
    auto it = hval.find(x);
    if (it != hval.end()) return it->second;
    return hval[x] = hrng();
}
