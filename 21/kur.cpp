#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int BASE = (1 << 19); 

struct Leader{
    int val, k; // {value, how many more times does this one appear compared to the next most frequent value}

    Leader(int val_ = 0, int k_ = 0) : val(val_), k(k_) {};

    Leader op(Leader other){
        if (val == other.val){
            return Leader(val, k + other.k);
        }
        if (k > other.k){
            return Leader(val, k - other.k);
        }
        else{
            return Leader(other.val, other.k - k);
        }
    }
};

Leader st[2 * BASE + 3];

Leader query(int l, int r){
    l += BASE;
    r += BASE;
    Leader ans = st[l];
    if (l != r){
        ans = ans.op(st[r]);
    }
    while (l / 2 != r / 2){
        if (l % 2 == 0){
            ans = ans.op(st[l + 1]);
        }
        if (r % 2 == 1){
            ans = ans.op(st[r - 1]);
        }
        l /= 2;
        r /= 2;
    }
    return ans;
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, l, r;
    cin >> n >> q;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 0; i < n; i++){
        st[BASE + i] = {a[i], 1};
    }
    for (int i = BASE - 1; i >= 1; i--){
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    vector <int> cand(q), ans(q), len(q);
    vector <vector <int>> start(n), finish(n);
    for (int i = 0; i < q; i++){
        cin >> l >> r;
        l--, r--;
        len[i] = r - l + 1;
        cand[i] = query(l, r).val; 
        start[l].push_back(i);
        finish[r].push_back(i);
    }
    vector <int> freq(n + 1);
    for (int i = 0; i < n; i++){
        for (int x : start[i]){
            ans[x] = freq[cand[x]];
        }
        freq[a[i]]++;
        for (int x : finish[i]){
            ans[x] = freq[cand[x]] - ans[x];
        }
    }
    for (int i = 0; i < q; i++){
        cout << (ans[i] > len[i] / 2 ? cand[i] : 0) << "\n";
    }

    return 0;
}
