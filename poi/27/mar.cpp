#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

// max. ans = 17 (since the De Bruijn sequence for n = 17 has length >= 10^5)
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, q, i;
    cin >> n >> q;
    string s;
    cin >> s;

    vector<unordered_map <int, int>> hashes(17); 
    vector <int> cnt(17);

    auto get_hash = [&](string s){
        lli h = 0;
        for (int i = 0; i < (int) s.size(); i++){
            if (s[i] == '1'){
                h += (1 << i);
            }
        }
        return h;
    };

    auto add = [&](int k, int flag){
        int first = max(0, k - 15), last = min(n - 1, k + 15);
        for (int l = 1; l <= 16; l++){
            for (int i = first; i <= last; i++){
                if (i + l - 1 > last){
                    break;
                }

                lli h = get_hash(s.substr(i, l));
                hashes[l][h] += flag;
                if (flag == -1 && hashes[l][h] == 0) cnt[l]--;
                else if (flag == 1 && hashes[l][h] == 1) cnt[l]++;
            }
        }
    };

    auto query = [&](){
        for (int i = 1; i <= 16; i++){
            if (cnt[i] < (1 << i)){
                return i;
            }
        }
        return 17;
    };

    for (int i = 0; i < n; i++){
        for (int l = 1; l <= 16; l++){
            if (i + l > n){
                break;
            }
            lli h = get_hash(s.substr(i, l));
            hashes[l][h]++;
            if (hashes[l][h] == 1) cnt[l]++;
        }
    }
    cout << query() << "\n";
    while (q--){
        cin >> i;
        i--;
        add(i, -1);
        s[i] = (s[i] == '0' ? '1' : '0');
        add(i, 1);
        cout << query() << "\n";
    }

    return 0;
}   
