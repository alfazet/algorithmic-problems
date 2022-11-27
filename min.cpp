//IX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

void solve(){
    int n;
    cin >> n;
    char last, next;
    cin >> last;
    cout << last;
    for (int i = 0; i < n - 2; i++){
        cin >> next;
        if (next != last){
            if (next == '+'){
                cout << '(';
            }
            else{
                cout << ')';
            }
        }
        cout << '-';
        last = next;
    }
    if (last == '+'){
        cout << ')';
    }
    cout << "\n";
}

int main (){
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
