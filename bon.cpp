//XIX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

int mx;
lli cust_no = 1;
bool bon[MAXN], bought[MAXN];
vector <lli> res;
int last_bought[MAXN];

void query(int q){
    lli done = 0;
    for (int i = last_bought[q] + q; i <= mx && done < q; i += q){
        if (!bought[i]){
            bought[i] = true;
            last_bought[q] = i;
            if (bon[i]){
                res.push_back(cust_no + done);
            }
            done++;
        }
    }
}

void solve(){
    int n, x, q;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x;
        mx = max(mx, x);
        bon[x] = true;
    }
    cin >> q;
    for (int i = 0; i < q; i++){
        cin >> x;
        query(x);
        cust_no += x;
    }
    cout << res.size() << "\n";
    for (lli k : res){
        cout << k << "\n";
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
