#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int INF = 1e9 + 3, dr[4] = {0, 0, -1, 1}, dc[4] = {-1, 1, 0, 0};

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n, m;
    cin >> n >> m;
	vector <vector <int>> a(n, vector <int>(m)), d(n, vector <int>(m, INF));
	char ch;
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            cin >> ch;
            a[r][c] = (int) (ch - '0');
        }
    }
	queue <pair <int, int>> q;
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            if (a[r][c] == 1){
				d[r][c] = 0;
                q.emplace(r, c);
            }
        }
    }

	auto valid = [&](int r, int c){
		return (r >= 0) && (r < n) && (c >= 0) & (c < m) && (a[r][c] == 0);
	};

    while (!q.empty()){
        auto[r, c] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++){
            if (valid(r + dr[k], c + dc[k]) && d[r + dr[k]][c + dc[k]] > d[r][c] + 1){
                q.emplace(r + dr[k], c + dc[k]);
                d[r + dr[k]][c + dc[k]] = min(d[r + dr[k]][c + dc[k]], d[r][c] + 1);
            }
        }
    }
    for (int r = 0; r < n; r++){
        for (int c = 0; c < m; c++){
            cout << d[r][c] << " ";
        }
        cout << "\n";
    }

    return 0;
}
