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


//
