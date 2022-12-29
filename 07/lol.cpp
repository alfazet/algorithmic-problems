#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n, lider = 0;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    stack <int> st;
    for (int i = 0; i < (int) a.size(); i++){
        if (!st.empty() && st.top() != a[i]){
            st.pop();
        }
        else{
            st.push(a[i]);
        }
    }
    
    int cand = (st.empty() ? 0 : st.top()), cnt = 0;
    for (int i = 0; i < n; i++){
        if (a[i] == cand){
            cnt++;
        }
    }
    if (cnt > n / 2){
        lider = cand;
    }

    if (cnt > (n + 1) / 2){
        cout << "NIE\n";
        return;
    }
    if (!lider){
        cout << "TAK\n";
        return;
    }

    int bigger = 0, smaller = 0;
    for (int x : a){
        if (x != lider){
            if (x > lider){
                bigger++;
            }
            else{
                smaller++;
            }
        }
    }
    cout << ((smaller > 0 && bigger == 0) || (smaller == 0 && bigger > 0) ? "TAK\n" : "NIE\n");
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
