#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct P{
    int x, y, typ;

    bool operator < (P p1){
        if (x == p1.x){
            if (typ == p1.typ){
                return y < p1.y;
            }
            return typ < p1.typ;
        }
        return x < p1.x;
    }
};

const int MAXN = 15003, ST_SZ = (1 << 18), MAX_COORD = 70003;

P points[2 * MAXN];
int st[ST_SZ], lazy[ST_SZ];

void propagate(int si, int left, int right){
    st[left] += lazy[si];
    st[right] += lazy[si];
    lazy[left] += lazy[si];
    lazy[right] += lazy[si];
    lazy[si] = 0;
}

void update(int si, int ss, int se, int us, int ue, int val){
    if (se < us || ss > ue){
        return;
    }
    if (ss >= us && se <= ue){
        st[si] += val;
        lazy[si] += val;
        return;
    }

    int left = 2 * si, right = 2 * si + 1, mid = (ss + se) / 2;
    propagate(si, left, right);
    update(left, ss, mid, us, ue, val);
    update(right, mid + 1, se, us, ue, val);
    st[si] = max(st[left], st[right]);
}

int query(){
    return st[1];
}

void solve(){
    int s, w, n;
    cin >> s >> w;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
        points[i].x += 30000;
        points[i].y += 30000;
        points[i].typ = 1;

        points[i + n].x = points[i].x + s + 1;
        points[i + n].y = points[i].y;
        points[i + n].typ = -1;
    }
    sort(points, points + 2 * n);
    int ans = 0;
    for (int i = 0; i < 2 * n; i++){
        update(1, 1, MAX_COORD, points[i].y, points[i].y + w, points[i].typ);
        ans = max(ans, query());
    }
    cout << ans << "\n";
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
