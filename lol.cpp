//VII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int find_leader_cand(const vector <int> &a){
    stack <int> st;
    for (int i = 0; i < (int) a.size(); i++){
        if (!st.empty() && st.top() != a[i]){
            st.pop();
        }
        else{
            st.push(a[i]);
        }
    }
    if (st.empty()){
        return 0;
    }
    else{
        return st.top();
    }
}

void solve(){
    int n, lider = 0;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int cand = find_leader_cand(a), cnt = 0;
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
    if (!lider){ // nie ma lidera => da się
        cout << "TAK\n";
        return;
    }
    // tutaj tylko cnt == n / 2
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
    if ((smaller && bigger == 0) || (smaller == 0 && bigger)){
        cout << "TAK\n";
    }
    else{
        cout << "NIE\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    //t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
