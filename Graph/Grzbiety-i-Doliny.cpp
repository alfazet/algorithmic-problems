#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1003;

pair <int, int> moves[8] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

int a[MAXN][MAXN], n, valleys, ridges;
bool valley[MAXN][MAXN], ridge[MAXN][MAXN], vis[MAXN][MAXN];

bool valid(int r, int c){
    return r >= 0 && r < n && c >= 0 && c < n && !vis[r][c];
}

bool DFS(int r, int c, int typ){
    vis[r][c] = true;
    if ((typ == 0 && !valley[r][c]) || (typ == 1 && !ridge[r][c])){
        return false;
    }
    
    bool ok = true;
    for (auto [dr, dc] : moves){
        if (valid(r + dr, c + dc) && a[r + dr][c + dc] == a[r][c]){
            ok &= DFS(r + dr, c + dc, typ);
        }
    }
    return ok;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	cin >> n;
	for (int r = 0; r < n; r++){
	    for (int c = 0; c < n; c++){
	        cin >> a[r][c];
	    }
	}
	
	for (int r = 0; r < n; r++){
	    for (int c = 0; c < n; c++){
	        valley[r][c] = true;
	        ridge[r][c] = true;
	        for (auto [dr, dc] : moves){
	            if (valid(r + dr, c + dc)){
	                if (a[r][c] > a[r + dr][c + dc]){
	                    valley[r][c] = false;
	                }
	                else if (a[r][c] < a[r + dr][c + dc]){
	                    ridge[r][c] = false;
	                }
	            }
	        }
	    }
	}
	
	for (int r = 0; r < n; r++){
	    for (int c = 0; c < n; c++){
	        if (!vis[r][c]){
	            if (valley[r][c]){
	                valleys += DFS(r, c, 0);
	            }
	            if (ridge[r][c]){
	                ridges += DFS(r, c, 1);
	            }
	        }
	    }
	}
	cout << ridges << " " << valleys << "\n";
	
    return 0;
}
