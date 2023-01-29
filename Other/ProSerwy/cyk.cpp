#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const double EPS = 1e-4, INF = 1e9 + 3;
const int MAXN = 103;

bool adj[MAXN][MAXN];
double w[MAXN][MAXN], d[MAXN][MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, m, a, b, weight;
    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> weight;
        adj[a][b] = true;
        w[a][b] = -weight;
    }

    auto check = [&](double x){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                if (adj[i][j]) d[i][j] = w[i][j] - x;
                else d[i][j] = INF;
            }
        }
        
        for (int k = 1; k <= n; k++){
            for (int i = 1; i <= n; i++){
                for (int j = 1; j <= n; j++){
                    if (d[i][k] + d[k][j] < d[i][j]){
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }

        for (int i = 1; i <= n; i++){
            if (d[i][i] < 0) return true;
        }
        return false;
    };

    double l = -(1e6), r = 0, mid, ans = r;
    for (int rep = 0; rep < 50; rep++){ // a set number of iterations to avoid comparing doubles, here we need only 1e-4 so 50 is enough
        mid = (l + r) / 2.0;
        if (check(mid)){
            ans = min(ans, mid);
            r = mid - EPS;
        }
        else{
            l = mid + EPS;
        }
    }
    cout << fixed << setprecision(4) << -ans << "\n";

    return 0;
}   
