//XX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, k;
    string s;
	cin >> n >> k;
    vector <int> pref(n + 1);
    pref[0] = 0;
    cin >> s;
    stack <int> st, ans;
    int ptr = 1;
    for (int i = 0; i < n; i++){
        if (s[i] == 'b') pref[ptr] = -1;
        else pref[ptr] = k;
        pref[ptr] += pref[ptr - 1]; 
        st.push(i + 1);
        if (ptr >= k + 1 && pref[ptr] == pref[ptr - k - 1]){
            for (int j = 0; j < k + 1; j++){
                ans.push(st.top());
                st.pop();
            }
            ptr -= k + 1;
        }
        ptr++;
    }
    for (int i = 0; i < n; i++){
        cout << ans.top() << " ";
        ans.pop();
        if ((i + 1) % (k + 1) == 0){
            cout << "\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}   
