#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, c, len = 0;
    cin >> n >> m;
    vector <int> temp(m), need(n + 1), freq(n + 1), a(n);
    vector <bool> ok(n + 1); // do we have just enough of this color
    set <int> colors;
    for (int i = 0; i < m; i++){
        cin >> temp[i];
        len += temp[i];
    }
    for (int i = 0; i < m; i++){
        cin >> c;
        need[c] = temp[i];
    }
    for (int i = 0; i < n; i++){
        cin >> a[i];
        colors.insert(a[i]);
    }

    if (len > n){
        cout << "0\n";
        return 0;
    }

    int satisfied = 0;
    for (int x : colors){
        if (need[x] == 0){
            ok[x] = true;
            satisfied++;
        }
    }

    for (int i = 0; i < len; i++){
        freq[a[i]]++;
        if (freq[a[i]] == need[a[i]] && !ok[a[i]]){
            ok[a[i]] = true;
            satisfied++;
        }
        else if (freq[a[i]] > need[a[i]] && ok[a[i]]){
            ok[a[i]] = false;
            satisfied--;
        }
    }

    int ans = (satisfied == (int) colors.size());
    for (int i = len; i < n; i++){
        freq[a[i - len]]--;
        freq[a[i]]++;
        if (freq[a[i - len]] == need[a[i - len]] && !ok[a[i - len]]){
            ok[a[i - len]] = true;
            satisfied++;
        }
        else if (freq[a[i - len]] < need[a[i - len]] && ok[a[i - len]]){
            ok[a[i - len]] = false;
            satisfied--;
        }
        if (freq[a[i]] == need[a[i]] && !ok[a[i]]){
            ok[a[i]] = true;
            satisfied++;
        }
        else if (freq[a[i]] > need[a[i]] && ok[a[i]]){
            ok[a[i]] = false;
            satisfied--;
        }

        ans += (satisfied == (int) colors.size());
    }
    cout << ans << "\n";

    return 0;
}   
