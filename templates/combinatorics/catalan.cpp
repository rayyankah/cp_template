//catalan
vi catalan(N);
void compute_catalan()
{
    catalan[0] = 1;
    catalan[1] = 1;
    for(int i=2; i<N; i++){
        for(int j=0; j<i; j++){
            catalan[i] = (catalan[i] + (catalan[j]*catalan[i-j-1])%MOD)%MOD;    
        }
    }
}
