//double hashing..
const int N = 1e6 + 10;
int pref[N];
int inv_pref[N];

// --- NEW: second hash arrays (ULL) ---
unsigned long long pref2[N];
unsigned long long pow2_ull[N];

// tiny hash combiner for pair
struct pair_hash {
    size_t operator()(const pair<ll, unsigned long long> &p) const noexcept {
        uint64_t a = (uint64_t)p.first;
        uint64_t b = (uint64_t)p.second;
        return (size_t)(a ^ (b + 0x9e3779b97f4a7c15ULL + (a<<6) + (a>>2)));
    }
};

// compute both modular prefix hash (with inv powers) and ULL prefix/powers
void compute_pref_hash(string &s, int p = 31)
{
    // modular part (existing)
    ll p_power = 1;
    inv_pref[0] = 1;
    pref[0] = (s[0] - 'a' + 1);

    // ull part
    const unsigned long long B2 = 1315423911ULL; // base for ull hash
    pow2_ull[0] = 1;
    pref2[0] = (unsigned long long)(s[0] - 'a' + 1);

    for (int i = 1; i < (int)s.size(); i++)
    {
        p_power = (binMul(p_power, p, MOD));
        pref[i] = (pref[i - 1] + (s[i] - 'a' + 1) * p_power) % MOD;
        inv_pref[i] = binExp(p_power, MOD - 2);

        // ull updates
        pow2_ull[i] = pow2_ull[i - 1] * B2;
        pref2[i] = pref2[i - 1] * B2 + (unsigned long long)(s[i] - 'a' + 1);
    }
}

// modular substring hash as before
ll substringHash(int l, int r, int p = 31)
{
    if (l == 0)
        return pref[r];
    ll hash_value = (pref[r] - pref[l - 1]);
    hash_value %= MOD;
    if (hash_value < 0)
        hash_value += MOD;
    hash_value = binMul(hash_value, inv_pref[l], MOD);
    return hash_value;
}

// --- NEW: ull substring hash (no mod) ---
unsigned long long substringHash2(int l, int r)
{
    if (l == 0) return pref2[r];
    int len = r - l + 1;
    return pref2[r] - pref2[l - 1] * pow2_ull[len];
}
