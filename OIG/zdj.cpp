#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAX_COORD = 2e5 + 3, BASE = (1 << 19);

int st[2 * BASE + 3], lazy[2 * BASE + 3];

struct P{
    int x, y, h, type; // 0/1 - photo starts/ends
    
    P(int x_ = 0, int y_ = 0, int h_ = 0, int type_ = 0) : x(x_), y(y_), h(h_), type(type_) {};
    
    bool operator <(const P &B) const{ // sort by x so we can sweep with a vertical line
        if (x == B.x){
            if (y == B.y){
                return type < B.type; 
            }
            return y < B.y;
        }
        return x < B.x;
    }
};

void propagate(int i, int s, int e, int val){
    st[i] += val;
    if (s != e){
        lazy[2 * i] += val;
        lazy[2 * i + 1] += val;
    }
}

int query(int i, int s, int e, int l, int r){
    propagate(i, s, e, lazy[i]);
    lazy[i] = 0;
    
    if (l > e || r < s){
        return 0;
    }
    if (l <= s && e <= r){
        return st[i];
    }
    
    int mid = (s + e) / 2;
    return max(query(2 * i, s, mid, l, r), query(2 * i + 1, mid + 1, e, l, r));
}

void update(int i, int s, int e, int l, int r, int val){
    propagate(i, s, e, lazy[i]);
    lazy[i] = 0;
    
    if (l > e || r < s){
        return;
    }
    if (l <= s && e <= r){
        propagate(i, s, e, val);
        return;
    }
    
    int mid = (s + e) / 2;
    update(2 * i, s, mid, l, r, val);
    update(2 * i + 1, mid + 1, e, l, r, val);
    st[i] = max(st[2 * i], st[2 * i + 1]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x1, y1, x2, y2;
    cin >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> x1 >> y1 >> x2 >> y2;
        a[i] = P(x1 + MAX_COORD, y1 + MAX_COORD, y2 - y1, 0);
        a[i + n] = P(x2 + MAX_COORD, y2 + MAX_COORD, y2 - y1, 1); 
    }
    sort(a.begin(), a.end());
    
    int ans = 0;
    for (auto [x, y, h, type] : a){
        if (type == 0){
            update(1, 1, 2 * MAX_COORD, y, y + h, 1);
        }
        else{
            update(1, 1, 2 * MAX_COORD, y - h, y, -1);
        }
        ans = max(ans, query(1, 1, 2 * MAX_COORD, 1, 2 * MAX_COORD));
    }
    cout << ans << "\n";
    
    return 0;
}
