//XXII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

bool inside(int &n, int &m, int i, int j){
    if (i < 0 || i >= n || j < 0 || j >= m){
        return false;
    }
    return true;
}

void solve(){
    int n, m, a, b;
    int topx, topy, newx, newy;
    cin >> n >> m >> a >> b;
    string grid[n], seal[a];
    for (int i = 0; i < n; i++){
        cin >> grid[i];
    }
    for (int i = 0; i < a; i++){
        cin >> seal[i];
    }
    bool ok = false;
    vector <pair <int, int>> trans;
    for (int i = 0; i < a; i++){
        for (int j = 0; j < b; j++){
            if (seal[i][j] == 'x' && !ok){
                ok = true;
                topx = i;
                topy = j;
            }
            if (seal[i][j] == 'x'){
                trans.push_back(make_pair(i - topx, j - topy));
            }
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (grid[i][j] == 'x'){
                for (pair <int, int> p : trans){
                    newx = i + p.first;
                    newy = j + p.second;
                    if (inside(n, m, newx, newy)){
                        //cout << "grid[i][j] = " << grid[newx][newy] << "\n";
                        if (grid[newx][newy] != 'x'){
                            cout << "NIE\n";
                            return;
                        }
                        grid[newx][newy] = '.';
                    }
                    else{
                        cout << "NIE\n";
                        return;
                    }
                }
            }
        }
    }
    cout << "TAK\n";
}

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    //t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
