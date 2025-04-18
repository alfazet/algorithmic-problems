#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

struct Max{
    pair <int, int> val;
    static constexpr pair <int, int> NEUTRAL = {-(1e9 + 3), -(1e9 + 3)};

    Max(pair <int, int> val_ = {0, 0}) : val(val_) {};

    Max op(Max other){
        return Max(max(val, other.val));
    }
};

template <typename T>
struct SegTree{
    int n;
    vector <T> st;

    void init(int n_, vector <int> a = {}){
        n = n_;
        int base = 1;
        while (base <= n){
            base *= 2;
        }
        st.resize(2 * base + 3);
        build(1, 1, n, a);
    }

    void build(int i, int s, int e, const vector <int> &a){
        if (s == e){
            st[i] = pair{a[s - 1], s - 1};
            return;
        }
        int mid = (s + e) / 2;
        build(2 * i, s, mid, a);
        build(2 * i + 1, mid + 1, e, a);
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    T query(int i, int s, int e, int l, int r){
        if (l <= s && e <= r){
            return st[i];
        }
        if (e < l || r < s){
            return T::NEUTRAL;
        }
        int mid = (s + e) / 2;
        return query(2 * i, s, mid, l, r).op(query(2 * i + 1, mid + 1, e, l, r));
    }

    T query(int l, int r){
        return query(1, 1, n, l, r);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    char c;
    vector <int> a = {0}, next_smaller(n + 1);
    next_smaller[0] = n + 2;
    for (int i = 0; i < n; i++){
        cin >> c;
        if (c == 'j'){
            a.push_back(a.back() - 1);
        }
        else{
            a.push_back(a.back() + 1);
        }
        next_smaller[i + 1] = n + 2;
    }

    stack <pair <int, int>> s;
    for (int i = 0; i <= n; i++){
        while (!s.empty() && s.top().ff > a[i]){
            next_smaller[s.top().ss] = i;
            s.pop();
        }
        s.emplace(a[i], i);
    }

    int ans = 0;
    SegTree <Max> st;
    st.init(n + 1, a); // pairs {value, index}
    for (int i = 0; i <= n; i++){
        ans = max(ans, st.query(i, next_smaller[i] - 1).val.ss - i);
    }
    cout << ans << "\n";
    
    return 0;
}
