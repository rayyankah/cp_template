//polynomial rolling hash
ll getHash(string &key){
    ll value = 0;
    ll p = 31;
    ll p_power =1;
    for(char c : key){
        value = (value + (c - 'a' + 1) * p_power)%MOD;
        p_power = (p_power * p)%MOD;
    }
    return value;
}


//substring hash
int pref[N];
int inv_pref[N];
void compute_pref_hash(string &s, int p = 31){
    ll p_power = 1;
    inv_pref[0] = 1;
    pref[0] = (s[0] - 'a' + 1);
    for(int i=1; i<s.size(); i++){
        p_power= (binMul(p_power, p, MOD));
        pref[i] = (pref[i-1] +( s[i]-'a'+1)*p_power)%MOD;
        inv_pref[i] = binExp(p_power, MOD-2);
    }

}
ll substringHash(int l, int r, int p = 31){
    if(l==0) return pref[r];
    ll hash_value = (pref[r]-pref[l-1]);
    hash_value%=MOD;
    if(hash_value<0) hash_value+=MOD;
    hash_value = binMul(hash_value, inv_pref[l], MOD);
    return hash_value;

}


//
