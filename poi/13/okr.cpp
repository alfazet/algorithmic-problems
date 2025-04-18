#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector <int> p(n);
    for (int i = 1; i < n; i++){
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]){
            k = p[k - 1];
        }
        p[i] = k;
        if (s[i] == s[p[i]]){
            p[i]++;
        }
    }

    vector <int> min_prefsuf(n); // longest period of s = s - min prefsuf of s  
    min_prefsuf[0] = 1;
    for (int i = 1; i < n; i++){
        min_prefsuf[i] = (p[i] == 0 ? i + 1 : p[i]);
    }

    lli ans = 0;
    for (int i = 1; i < n; i++){
        min_prefsuf[i] = min(min_prefsuf[i], min_prefsuf[min_prefsuf[i] - 1]);
        ans += i + 1 - min_prefsuf[i];
    }
    cout << ans << "\n";

    return 0;
}
