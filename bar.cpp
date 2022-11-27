//XXI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 1e6 + 3;

int wykres[MAXN];

struct Seg_tree{
    const int INF = 1e9 + 3;
    int base;
    vector <pair <int, int>> st; //pary {val, id}

    pair <int, int> op(pair <int, int> a, pair <int, int> b){ 
        return max(a, b);
    }

    pair <int, int> neutral(){ 
        return {-INF, -INF};
    }

    void build(int n){
        for (int i = 0; i < n; i++){
            st[base + i] = {wykres[i], i};
        }
        for (int si = base - 1; si >= 1; si--){
            st[si] = op(st[2 * si], st[2 * si + 1]);
        }
    }

    void init(int n){
        base = 1;
        while (base < n){
            base *= 2;
        }
        st.assign(2 * base, neutral());
        build(n);
    }

    pair <int, int> query(int qs, int qe){
        int si_l = base + qs, si_r = base + qe;
        pair <int, int> res = st[si_l];
        if (si_l != si_r){
            res = op(res, st[si_r]);
        }
        while (si_l / 2 != si_r / 2){
            if (si_l % 2 == 0){
                res = op(res, st[si_l + 1]);
            }
            si_l /= 2;
            if (si_r % 2 == 1){
                res = op(res, st[si_r - 1]);
            }
            si_r /= 2;
        }
        return res;
    }
};


void read(string &s, int &n){
    char c;
    bool flag = false;
    for (int i = 0; i < n; i++){
        cin >> c;
        if (c == 'p'){
            s += c;
            flag = true;
        }
        else if (flag){
            s += c;
        }
    }
    while (s.back() == 'j'){
        s.pop_back();
    }
    n = s.size();
}

void solve(){
	int n;
    cin >> n;
    string s;
    read(s, n);
    
    vector <int> next_lower(n + 1);
    next_lower[n] = n;
    wykres[0] = 0;
    for (int i = 0; i < n; i++){
        wykres[i + 1] = wykres[i] + (s[i] == 'p' ? 1 : -1);
        next_lower[i] = n;
    }

    stack <pair <int, int>> sta;
    for (int i = 0; i < n; i++){
        while (!sta.empty() && sta.top().ff > wykres[i]){
            next_lower[sta.top().ss] = i;
            sta.pop();
        }
        sta.push({wykres[i], i});
    }
    
    Seg_tree st;
    st.init(n + 1);
    
    int ans = 0;
    for (int i = 0; i <= n; i++){
        if (s[i] == 'p'){
            ans = max(ans, st.query(i, next_lower[i]).ss - i);
        }
    }
    cout << ans << "\n";
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
