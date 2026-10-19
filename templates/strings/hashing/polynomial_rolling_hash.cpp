// hash of a whole string (mod MOD). for substrings use double_hash.cpp
int getHash(const string &key, int p = 131)
{
    int value = 0;
    for (char c : key) value = (value * p + (unsigned char)c) % MOD;
    return value;
}
