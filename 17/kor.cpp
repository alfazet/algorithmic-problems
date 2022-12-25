#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e5 + 3, A[2] = {79, 97}, MOD[2] = {777'777'799, 999'999'797};

lli p[MAXN][2];

lli madd(lli a, lli b, int q){
    return (a + b) % MOD[q];
}

lli msub(lli a, lli b, int q){
    return ((a - b) % MOD[q] + MOD[q]) % MOD[q];
}

lli mmul(lli a, lli b, int q){
    return (a * b) % MOD[q];
}

vector <lli> get_hash(const vector <int> &a, int q){
    lli h = 0;
    vector <lli> v;
    for (int i = 0; i < (int) a.size(); i++){
        h = madd(h, mmul(a[i], p[i][q], q), q);
        v.push_back(h);
    }
    return v;
}

lli get_substr_hash(const vector <lli> &h, int l, int r, int q){ // hash of [l..r], normalized
    return mmul(msub(h[r], (l == 0 ? 0 : h[l - 1]), q), p[(int) h.size() - r - 1][q], q);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    p[0][0] = p[0][1] = 1;
    for (int i = 1; i < n; i++){
        for (int q = 0; q < 2; q++){
            p[i][q] = mmul(p[i - 1][q], A[q], q);
        }
    }

    vector <lli> h1 = get_hash(a, 0);
    vector <lli> h2 = get_hash(a, 1);
    reverse(a.begin(), a.end());
    vector <lli> rh1 = get_hash(a, 0);
    vector <lli> rh2 = get_hash(a, 1);
    reverse(a.begin(), a.end());

    vector <int> ans(n + 1);
    for (int k = 1; k <= n; k++){
        set <pair <lli, lli>> st;
        for (int j = 0; j <= n - k; j += k){
            st.insert({min(get_substr_hash(h1, j, j + k - 1, 0), get_substr_hash(rh1, n - j - k + 1 - 1, n - j - 1, 0)), min(get_substr_hash(h2, j, j + k - 1, 1), get_substr_hash(rh2, n - j - k + 1 - 1, n - j - 1, 1))});
        }
        ans[k] = st.size();
    }

    int best = *max_element(ans.begin(), ans.end());
    cout << best << " " << count(ans.begin(), ans.end(), best) << "\n";
    for (int k = 1; k <= n; k++){
        if (ans[k] == best){
            cout << k << " ";
        }
    }
    cout << "\n";

    return 0;
}   
