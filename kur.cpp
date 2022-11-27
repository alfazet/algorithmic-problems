//XXI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = (1 << 19);

struct Node{
    int val;
    int k;
};

int a[maxn];
Node st[2 * maxn];

Node merge(Node a, Node b){
    Node n;
    if (a.val == b.val){
        n.val = a.val;
        n.k = a.k + b.k;
    }
    else if (a.k > b.k){
        n.val = a.val;
        n.k = a.k - b.k;
    }
    else{
        n.val = b.val;
        n.k = b.k - a.k;
    }
    return n;
}

void build(int si, int ss, int se){
    if (ss == se){
        st[si].val = a[ss];
        st[si].k = 1; 
        return;
    }
    int mid = (ss + se) / 2;
    build(2 * si, ss, mid);
    build(2 * si + 1, mid + 1, se);
    st[si] = merge(st[2 * si], st[2 * si + 1]);
}

Node query(int si, int ss, int se, int qs, int qe){
    if (ss > qe || se < qs){
        return {0, 0};
    }
    if (qs <= ss && qe >= se){
        return st[si];
    }
    int mid = (ss + se) / 2;
    return merge(query(2 * si, ss, mid, qs, qe), query(2 * si + 1, mid + 1, se, qs, qe)); 
}

void solve(){
    int n, q, l, r;
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    build(1, 0, n - 1);
    vector <pair <int, int>> queries(q);
    vector <int> kand(q), odp(q);
    vector <vector <int>> starty(n), konce(n);
    for (int i = 0; i < q; i++){
        cin >> l >> r;
        l--, r--;
        kand[i] = query(1, 0, n - 1, l, r).val; 
        starty[l].push_back(i);
        konce[r].push_back(i);
        queries[i] = {l, r};
    }
    vector <int> freq(n + 1);
    for (int i = 0; i < n; i++){
        for (int x : starty[i]){
            odp[x] = freq[kand[x]];
        }
        freq[a[i]]++;
        for (int x : konce[i]){
            odp[x] = freq[kand[x]] - odp[x];
        }
    }
    for (int i = 0; i < q; i++){
        cout << (odp[i] > (queries[i].second - queries[i].first + 1) / 2 ? kand[i] : 0) << "\n";
    }
}  

int main (){
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
