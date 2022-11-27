//XXI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 2e5 + 3, INF = 1e9 + 7, LOG = 18;

struct Node{
    bool aa, ar, ra, rr; // aw-aw, aw-re, re-aw, re-re
};

#define aw first // awers
#define re second // rewers

pair <int, int> a[MAXN];
Node st[(1 << (LOG + 1)) + 3];

Node merge(Node p, Node q, int rp, int lq){
    Node n;

    n.aa = (p.aa && q.aa && a[rp].aw <= a[lq].aw); // lewy i prawy syn są aw-aw
    n.aa |= (p.aa && q.ra && a[rp].aw <= a[lq].re); // lewy syn jest aw-aw, prawy jest re-aw
    n.aa |= (p.ar && q.aa && a[rp].re <= a[lq].aw); // lewy syn jest aw-re, prawy jest aw-aw
    n.aa |= (p.ar && q.ra && a[rp].re <= a[lq].re); // lewy syn jest aw-re, prawy jest re-aw

    n.ar = (p.aa && q.ar && a[rp].aw <= a[lq].aw); // lewy syn jest aw-aw, prawy jest aw-re
    n.ar |= (p.aa && q.rr && a[rp].aw <= a[lq].re); // lewy syn jest aw-aw, prawy jest re-re
    n.ar |= (p.ar && q.rr && a[rp].re <= a[lq].re); // lewy syn jest aw-re, prawy jest re-re
    n.ar |= (p.ar && q.ar && a[rp].re <= a[lq].aw); // lewy i prawy syn są aw-re

    n.ra = (p.ra && q.aa && a[rp].aw <= a[lq].aw); // lewy syn jest re-aw, prawy jest aw-aw
    n.ra |= (p.rr && q.aa && a[rp].re <= a[lq].aw);// lewy syn jest re-re, prawy jest aw-aw
    n.ra |= (p.rr && q.ra && a[rp].re <= a[lq].re);// lewy syn jest re-re, prawy jest re-aw
    n.ra |= (p.ra && q.ra && a[rp].aw <= a[lq].re);// lewy i prawy syn są re-aw

    n.rr = (p.rr && q.rr && a[rp].re <= a[lq].re); // lewy i prawy syn są re-re
    n.rr |= (p.rr && q.ar && a[rp].re <= a[lq].aw); // lewy syn jest re-re, prawy jest aw-re
    n.rr |= (p.ra && q.rr && a[rp].aw <= a[lq].re); // lewy syn jest re-aw, prawy jest re-re
    n.rr |= (p.ra && q.ar && a[rp].aw <= a[lq].aw); // lewy syn jest re-aw, prawy jest aw-re

    return n;
}

void build(int si, int ss, int se){
    if (ss == se){
        st[si] = {true, false, false, true};
        return;
    }
    int mid = (ss + se) / 2;
    build(2 * si, ss, mid);
    build(2 * si + 1, mid + 1, se);
    st[si] = merge(st[2 * si], st[2 * si + 1], mid, mid + 1);
}

void update(int si, int ss, int se, int ui){
    if (ss == se || ui < ss || ui > se){
        return;
    }
    int mid = (ss + se) / 2;
    update(2 * si, ss, mid, ui);
    update(2 * si + 1, mid + 1, se, ui);
    st[si] = merge(st[2 * si], st[2 * si + 1], mid, mid + 1);
}

void solve(){
    int n, q, x, y;
    pair <int, int> temp;
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> a[i].aw >> a[i].re;
    }
    build(1, 1, n);
    cin >> q;
    while (q--){
        cin >> x >> y;
        temp = a[x];
        a[x] = a[y];
        a[y] = temp;
        update(1, 1, n, x);
        update(1, 1, n, y);
        cout << (st[1].aa || st[1].ar || st[1].ra || st[1].rr ? "TAK\n" : "NIE\n");
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
