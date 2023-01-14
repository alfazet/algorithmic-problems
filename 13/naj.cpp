#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9 + 3;

struct P{
    lli x, y;
    
    P(lli x_ = 0, lli y_ = 0) : x(x_), y(y_) {};

    P operator - (P b){
        return P(x - b.x, y - b.y);
    }
    lli operator ^ (P b){
        return x * b.y - y * b.x;
    }

    lli sin(P b, P c){
        return (b - (*this)) ^ (c - (*this));
    }
};

istream& operator>> (istream &in, P &a){
    return in >> a.x >> a.y;
}

ostream& operator<< (ostream &out, P &a){
    return out << "(" << a.x << ", " << a.y << ")"; 
}

P refer;

bool comp(pair <P, int> &a, pair <P, int> &b){
    return refer.sin(a.ff, b.ff) > 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, m, all = 0;
    cin >> n;
    vector <P> poly(n);
    for (int i = 0; i < n; i++){
        cin >> poly[i];
    }
    reverse(poly.begin(), poly.end());
    cin >> m;
    vector <pair <P, int>> a(m);
    for (int i = 0; i < m; i++){
        cin >> a[i].ff >> a[i].ss;
        all += a[i].ss;
    }

    auto nxt = [&](int i, int d){
        return (i + d + n) % n;
    };

    vector <vector <int>> triangle(n, vector <int>(n)), halfplane(n, vector <int>(n)); // sum of values in triangle i-(j-1)-j / halfplane i-j, edge excluded 
    for (int i = 0; i < n; i++){
        refer = poly[i]; // point of reference for angle sort
        sort(a.begin(), a.end(), comp);

        int j = nxt(i, 2), k = 0;
        while (j != i){
            while (k < m && poly[i].sin(poly[j], a[k].ff) < 0){
                triangle[i][j] += a[k].ss;
                k++;
            }
            j = nxt(j, 1);
        }
    }
    for (int i = 0; i < n; i++){
        halfplane[i][i] = halfplane[i][nxt(i, -1)] = halfplane[i][nxt(i, 1)] = 0;
    }
    for (int i = 0; i < n; i++){
        for (int j = nxt(i, 2); j != i; j = nxt(j, 1)){
            halfplane[i][j] = halfplane[i][nxt(j, -1)] + triangle[i][j];
        }
    }

    int ans = -INF;
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            for (int k = j + 1; k < n; k++){
                ans = max(ans, all - halfplane[i][j] - halfplane[j][k] - halfplane[k][i]);
            }
        }
    }
    cout << ans << "\n";

    return 0;
}
