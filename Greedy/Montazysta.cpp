#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 5e5 + 11;

#define ff first
#define ss second

bool take[MAXN];
pair <pair <int, int>, int> a[MAXN];

void solve(){
    int n;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> a[i].ff.ss >> a[i].ff.ff;
        a[i].ss = i + 1;
    }
    sort(a, a + n);

    int ans = 0;
    lli czas = 0;
    pair <int, int> temp;
    priority_queue <pair <int, int>> pq; 

    for (int i = 0; i < n; i++){
        if (a[i].ff.ff < a[i].ff.ss){
            continue;
        }
        if (czas + a[i].ff.ss <= a[i].ff.ff){
            ans++;
            czas += a[i].ff.ss;
            pq.push({a[i].ff.ss, i});
            take[i] = true;
        }
        else if (!pq.empty() && pq.top().first > a[i].ff.ss){
            temp = pq.top();
            take[temp.second] = false;
            pq.pop();
            czas -= (temp.first - a[i].ff.ss);
            pq.push({a[i].ff.ss, i});
            take[i] = true;
        }
    }
  
    cout << ans << "\n";
    czas = 1;

    for (int i = 0; i < n; i++){
        if (take[i]){
            cout << a[i].ss << " " << czas << "\n";
            czas += a[i].ff.ss;
        }
    }
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    tc = 1;
    //cin >> tc;
    while (tc--){
        solve();
    }
}
