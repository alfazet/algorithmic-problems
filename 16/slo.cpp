#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const lli INF = 1e18 + 3;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, x;
    lli lightest_all = INF;
    cin >> n;
    vector <int> a(n + 1), nxt(n + 1);
    vector <lli> m(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> m[i];
        lightest_all = min(lightest_all, m[i]);
    }
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        cin >> x;
        nxt[a[i]] = x;
    }

    int c = 0;
    vector <int> cycle_no(n + 1);
    vector <lli> lightest(n + 1, INF), cycle_weight(n + 1), cycle_sz(n + 1);
    for (int i = 1; i <= n; i++){
        if (cycle_no[i] == 0){
            cycle_no[i] = ++c;
            int v = nxt[i];
            while (v != i){
                cycle_no[v] = c;
                v = nxt[v];
            }
        }
        lightest[cycle_no[i]] = min(lightest[cycle_no[i]], m[i]);
        cycle_weight[cycle_no[i]] += m[i];
        cycle_sz[cycle_no[i]]++;
    }

    // we can use the lightest elephants to sort their entire cycles
    // or we can use the lightest overall but then we have to move him twice
    lli ans = 0;
    for (int i = 1; i <= c; i++){
        ans += min((cycle_sz[i] - 1) * lightest[i] + cycle_weight[i] - lightest[i], 2LL * (lightest_all + lightest[i]) + (cycle_sz[i] - 1) * lightest_all + cycle_weight[i] - lightest[i]);
    }
    cout << ans << "\n";

    return 0;
}   
