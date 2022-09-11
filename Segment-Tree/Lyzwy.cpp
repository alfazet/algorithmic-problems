//XVI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Node{
    lli sum, pre, inf, suf;

    void print(){
        cout << "{" << sum << ", " << pre << ", " << inf << ", " << suf << "}";
    }
};

struct Seg_tree{
    const int INF_INT = 1e9 + 3;
    const lli INF_LL = 1e18 + 3;
    int base;
    vector <Node> st;

    Node op(Node a, Node b){ //max, min, sum, xor, gcd...
        return {a.sum + b.sum, max(a.sum + b.pre, a.pre), max({a.inf, b.inf, a.suf + b.pre}), max(a.suf + b.sum, b.suf)};
    }

    void init(int n){
        base = 1;
        while (base < n){
            base *= 2;
        }
        st.assign(2 * base, {0, 0, 0, 0});
    }

    Node query(){
        return st[1];
    }

    void update(int ui, lli val){
        int si = base + ui;
        st[si].sum += val;
        st[si].pre = st[si].inf = st[si].suf = max(st[si].sum, 0LL);
        while (si > 1){
            si /= 2;
            st[si] = op(st[2 * si], st[2 * si + 1]);
        }
    }
};

void solve(){
    int n, q;
    lli k, d, r, x;
    cin >> n >> q >> k >> d;
    Seg_tree st;
    st.init(n - d + 1);
    for (int i = 0; i < n - d; i++){
        st.update(i, -k);
    }
    while (q--){
        cin >> r >> x;
        st.update(r - 1, x);
        cout << (st.query().inf <= d * k ? "TAK\n" : "NIE\n");
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
