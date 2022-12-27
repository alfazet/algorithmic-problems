// EJOI 2017
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int A[2] = {100'003, 100'019}, MOD[2] = {1'000'000'007, 1'000'000'009};

lli madd(lli a, lli b, int q = 0){
    return (a + b) % MOD[q];
}

lli mmul(lli a, lli b, int q = 0){
    return (a * b) % MOD[q];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    map <char, int> freq_s, id;
    for (char c : s){
        freq_s[c]++;
    }
    int k = 0;
    for (char c : s){
        if (freq_s[c] > 0 && id.find(c) == id.end()){
            id[c] = ++k;
        }
    }

    vector <int> a(n);
    for (int i = 0; i < n; i++){
        a[i] = id[s[i]];
    }

    vector <int> freq(k + 1);
    vector <lli> dp(n); // dp[i] = number of magic strings ending at i
    map <pair <lli, lli>, lli> mp; // hash of frequency vector -> previous index where it occured 
    mp[{0, 0}] = 0;
    for (int i = 0; i < n; i++){
        freq[a[i]]++;
        int min_freq = *min_element(freq.begin() + 1, freq.end()); // [1,1,3] and [0,0,2] must give the same hash for this to work

        pair <lli, lli> h = {0, 0}, p = {1, 1};
        for (int j = 1; j <= k; j++){
            h.ff = madd(h.ff, mmul(p.ff, freq[j] - min_freq, 0), 0);
            h.ss = madd(h.ss, mmul(p.ss, freq[j] - min_freq, 1), 1);
            p.ff = mmul(p.ff, A[0], 0);
            p.ss = mmul(p.ss, A[1], 1);
        }

        auto it = mp.find(h);
        if (it != mp.end()){
            dp[i] = madd(dp[it->ss], 1);
            mp.erase(it);
        }
        mp[h] = i;
    }

    lli ans = 0;
    for (int i = 0; i < n; i++){
        ans = madd(ans, dp[i]);
    }
    cout << ans << "\n";

    return 0;
}
