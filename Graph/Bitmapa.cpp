//VI OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int maxn = 183, INF = 1e9 + 3, dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

int n, m;
int a[maxn][maxn], dist[maxn][maxn];

queue <int> qx, qy;

void min_self(int &a, int b){
    a = min(a, b);
}

bool valid(int i, int j){
    return i >= 0 && i < n && j >= 0 && j < m && !a[i][j];
}

void BFS(){
    int cx, cy;
    while (!qx.empty()){
        cx = qx.front(), cy = qy.front();
        qx.pop(), qy.pop();
        for (int k = 0; k < 4; k++){
            if (valid(cx + dx[k], cy + dy[k]) && dist[cx + dx[k]][cy + dy[k]] > dist[cx][cy] + 1){
                qx.push(cx + dx[k]);
                qy.push(cy + dy[k]);
                min_self(dist[cx + dx[k]][cy + dy[k]], dist[cx][cy] + 1);
            }
        }
    }
}

void solve(){
    char c;
    cin >> n >> m;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> c;
            a[i][j] = (int) (c - '0');
            if (a[i][j] == 1){
                dist[i][j] = 0;
            }
            else{
                dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == 1){
                qx.push(i);
                qy.push(j);
            }
        }
    }

    BFS();

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << dist[i][j] << " ";
        }
        cout << "\n";
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
