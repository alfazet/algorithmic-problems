#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int SQRT = 347;

struct Q{
    int a, l, d;
    bool operator <(Q q){
        return d < q.d;
    }
};

void solve(){
	int n, q, a, l, d;
    cin >> n >> q;
    vector <int> ans(n), add(n + 1), stop(n + 1);
    vector <Q> queries;
    for (int i = 0; i < q; i++){
        cin >> a >> l >> d;
        a--;
        if (l <= SQRT){
            for (int i = 0; i < l; i++){
                ans[a + i * d]++;
            }
        }
        else{
            queries.push_back({a, l, d});
        }
    }
    sort(queries.begin(), queries.end());
    Q cur;
    q = queries.size();
    for (int i = 0; i < q; i++){
        cur = queries[i];
        add[cur.a]++;
        stop[cur.a + (cur.l - 1) * cur.d]++;
        if (i == q - 1 || queries[i + 1].d != cur.d){
            for (int j = 0; j < n; j++){
                ans[j] += add[j];
                add[j] -= stop[j];
                if (add[j] && j + cur.d <= n - 1){
                    add[j + cur.d] += add[j];
                }
                add[j] = 0;
                stop[j] = 0;
            }
        }
    }
    for (int x : ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
