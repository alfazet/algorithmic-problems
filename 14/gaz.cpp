// this exceeds a 32MB memory limit for some reason...
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int BASE = (1 << 17);

struct P{
    int x, y, id, type;

    P(int x_ = 0, int y_ = 0, int id_ = 0, int type_ = 0) : x(x_), y(y_), id(id_), type(type_) {};

    bool operator < (P &b){
        if (x == b.x){
            return y > b.y;
        }
        return x < b.x;
    }
};

int st[2 * BASE + 3];
queue <pair <int, int>> q[BASE]; // queue of {x-coord, id} of extraction points at given y-coord

int query(int k){ // first value not less than k
    int i = k + BASE, prv = 2 * i;
    if (st[i] > 0){
        return i - BASE;
    }
    while (i > 1){
        prv = i;
        i /= 2;
        if (st[2 * i + 1] > 0 && prv == 2 * i){ // if we came from the left son
            break;
        }
    }
    i = 2 * i + 1; 
    while (i < BASE){
        i *= 2;
        if (st[i] == 0){
            i++;
        }
    }
    return i - BASE;
}

void update(int i, int val, int x = 0, int id = 0){
    if (val == 1){
        q[i].emplace(x, id);
    }
    else{
        q[i].pop();
    }
    i += BASE;
    st[i] += val;
    while (i > 1){
        i /= 2;
        st[i] = st[2 * i] + st[2 * i + 1];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    vector <P> a(2 * n);
    for (int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].id = i + 1;
        a[i].type = 0;
    }
    for (int i = 0; i < n; i++){
        cin >> a[i + n].x >> a[i + n].y;
        a[i + n].id = i + 1;
        a[i + n].type = 1;
    }
    sort(a.begin(), a.end());

    lli ans = 0;
    vector <int> match(n + 1);
    for (P p : a){
        if (p.type == 0){
            update(p.y, 1, p.x, p.id);
        }
        else{
            int v = query(p.y);
            auto[x, id] = q[v].front();
            match[id] = p.id;
            ans += v - p.y + p.x - x;
            update(v, -1);
        }
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++){
        cout << i << " " << match[i] << "\n"; 
    }

    return 0;
}
