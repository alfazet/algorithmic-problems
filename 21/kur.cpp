#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int BASE = (1 << 19);

struct Leader{
    int val, stack_sz;

    Leader(int val_ = 0, int stack_sz_ = 0) : val(val_), stack_sz(stack_sz_) {};

    Leader op(Leader other){
        if (val == other.val){
            return Leader(val, stack_sz + other.stack_sz);
        }
        else if (stack_sz > other.stack_sz){
            return Leader(val, stack_sz - other.stack_sz);
        }
        else{
            return Leader(other.val, other.stack_sz - stack_sz);
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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, q, l, r;
    cin >> n >> q;
    vector <int> a(n);

    for (int i = 0; i < n; i++){
        cin >> a[i];
        st[i + BASE] = Leader(a[i], 1);
    }
    for (int i = BASE - 1; i >= 1; i--){
        st[i] = st[2 * i].op(st[2 * i + 1]);
    }

    vector <int> cand(q), len(q), freq(n + 1), freq_of_cand(q), freq_of_cand_at_start(q);
    vector <vector <int>> starts(n), ends(n);
    for (int i = 0; i < q; i++){
        cin >> l >> r;
        l--, r--;
        len[i] = r - l + 1;
        starts[l].push_back(i);
        ends[r].push_back(i);
        cand[i] = query(l, r).val;
    }
    for (int i = 0; i < n; i++){
        for (int s : starts[i]){
            freq_of_cand_at_start[s] = freq[cand[s]];
        }
        freq[a[i]]++;
        for (int e : ends[i]){
            freq_of_cand[e] = freq[cand[e]] - freq_of_cand_at_start[e];
        }
    }

    for (int i = 0; i < q; i++){
        cout << (freq_of_cand[i] > len[i] / 2 ? cand[i] : 0) << "\n";
    }

    return 0;
}
