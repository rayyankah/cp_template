//cf- powerful array
void add(int pos){
    int pref = freq[ar[pos]];
    int currf = ++freq[ar[pos]];
    power-=pref*pref*ar[pos];
    power+=currf*currf*ar[pos];
}
void remove(int pos){
    int pref = freq[ar[pos]];
    int currf = --freq[ar[pos]];
    power-=pref*pref*ar[pos];
    power+=currf*currf*ar[pos];
}
