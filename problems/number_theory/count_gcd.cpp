//cf-count gcd
signed main(){
        ios_base::sync_with_stdio(false); cin.tie(NULL);
        int tt = 1; cin >> tt;
        while( tt-- ){
                int n,m; cin >> n >> m;
                vector<int> v(n);
                for( auto &z : v ) cin >> z;
                bool anso = 0;
                for( int i = 1 ; i < n ; i++ ) if( v[i-1] % v[i] ) anso = 1;
                if( anso ){
                        cout << 0 << '\n';
                        continue;
                }
                int x = v[0] , ans = 1;
                vector<int> fact;
                for( int i = 2 ; ( i * i ) <= x ; i++ ){
                        if( !( x % i ) ) fact.push_back(i);
                        while( !( x % i ) ) x /= i;
                }
                if( x != 1 ) fact.push_back(x);
                for( int i = 1 ; i < n ; i++ ){
                        x = v[i-1] / v[i];
                        int cnt = 0 , mx = m / v[i];
                        vector<int> pr;
                        for( auto z : fact ) if( !( x % z ) ) pr.push_back(z);
                        for( int mask = 0 ; mask < ( 1 << pr.size() ) ; mask++ ){
                                int mul = 1;
                                for( int i = 0 ; i < pr.size() ; i++ ) if( mask & ( 1 << i ) ) mul *= pr[i];
                                if( __builtin_popcount(mask) & 1 ) cnt -= ( mx / mul );
                                else cnt += ( mx / mul );
                        }
                        ans *= cnt , ans %= mod;
                }
                cout << ans << '\n';
        }
