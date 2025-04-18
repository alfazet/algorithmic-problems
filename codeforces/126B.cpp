#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();

    vector <int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; i++){
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]){
            k = p[k - 1];
        }
        if (s[i] == s[k]){
            k++;
        }
        p[i] = k;
    }

    vector <int> prefsuf_lengths, cnt(n + 1);
    int j = p[n - 1];
    while (j > 0){
        prefsuf_lengths.push_back(j);
        j = p[j - 1];
    }
    for (int i = n; i >= 1; i--){
        cnt[i]++;
        cnt[p[i - 1]] += cnt[i];
    }

    for (int l : prefsuf_lengths){
        if (cnt[l] > 2){
            cout << s.substr(0, l) << "\n";
            return 0;
        }
    }
    cout << "Just a legend\n";

    return 0;
}
