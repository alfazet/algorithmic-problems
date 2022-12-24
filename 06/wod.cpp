#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 103, dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};

int n, m, start_h[MAXN][MAXN], water_h[MAXN][MAXN];

bool border(int r, int c){
    return r == 0 || r == n - 1 || c == 0 || c == m - 1;
}

bool valid(int r, int c){
    return r >= 0 && r <= n - 1 && c >= 0 && c <= m - 1;
}

void DFS(int r, int c, int cur_h){
    water_h[r][c] = (border(r, c) ? start_h[r][c] : cur_h); // water doesn't stay on the border
    int nr, nc;
    for (int i = 0; i < 4; i++){
        nr = r + dr[i];
        nc = c + dc[i];
        if (valid(nr, nc) && water_h[nr][nc] == 0 && start_h[nr][nc] <= cur_h){
            DFS(nr, nc, cur_h);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    cin >> n >> m;
    vector <tuple <int, int, int>> pos;
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            cin >> start_h[r][c];
            pos.emplace_back(start_h[r][c], r, c);
        }
    }
    sort(pos.begin(), pos.end());

    int nr, nc;
    bool start_here;
    for (auto[h, r, c] : pos){
        start_here = false;
        if (border(r, c)){
            start_here = true;
        }
        else{
            for (int i = 0; i < 4; i++){
                nr = r + dr[i];
                nc = c + dc[i];
                if (valid(nr, nc) && water_h[nr][nc] != 0){
                    start_here = true;
                }
            }
        }
        if (start_here){ // start DFS only if this is the border or any of the neighbors are already done
            DFS(r, c, h);
        }
    }

    int ans = 0;
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            ans += water_h[r][c] - start_h[r][c];
        }
    }
    cout << ans << "\n";

    return 0;
}   
