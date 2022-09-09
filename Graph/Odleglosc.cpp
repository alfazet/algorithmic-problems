//XIX OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3, INF = 1e9 + 3;

int mx, occ1[MAXN], occ2[MAXN], lpf[MAXN], factorization[MAXN], dist_to_marked[MAXN], dist_to_other_marked[MAXN], closest_marked[MAXN], other_closest_marked[MAXN];;
vector <int> adj[MAXN];

void fill_lpf(){
	vector <int> primes;
	for (int i = 2; i <= mx; i++){
		if (lpf[i] == 0){
			lpf[i] = i;
			primes.push_back(i);
		}
		for (int j = 0; j < (int) primes.size() && primes[j] <= lpf[i] && i * primes[j] <= mx; j++){
			lpf[i * primes[j]] = primes[j];
		}
	}
}

void BFS1(){
    queue <int> q;
    for (int i = 1; i <= mx; i++){
        if (occ1[i]){
            q.push(i);
            dist_to_marked[i] = 0;
            closest_marked[i] = i;
        }
        else{
            dist_to_marked[i] = INF;
        }
		dist_to_other_marked[i] = INF;
    }
    while (!q.empty()){
        int v = q.front();
        q.pop();
        for (int child : adj[v]){
            if (dist_to_marked[child] == INF){
                dist_to_marked[child] = dist_to_marked[v] + 1;
                closest_marked[child] = closest_marked[v];
                q.push(child);
            }
            else if (dist_to_marked[v] + 1 == dist_to_marked[child] && occ1[closest_marked[child]] > occ1[closest_marked[v]]){
                closest_marked[child] = closest_marked[v];
            }
        }
    }
}

void BFS2(){
    for (int i = 1; i <= mx; i++){
        for (int child : adj[i]){
            int v = closest_marked[i], w = closest_marked[child];
            if (v != w){
                int d = dist_to_marked[i] + dist_to_marked[child] + 1;
                if (d < dist_to_other_marked[v] || (d == dist_to_other_marked[v] && occ1[w] < occ1[other_closest_marked[v]])){
                    other_closest_marked[v] = w;
                    dist_to_other_marked[v] = d;
                }
            }
        }
    }
}

void solve(){
	int n;
    cin >> n;
	vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        mx = max(mx, a[i]);
        if (!occ1[a[i]]){
            occ1[a[i]] = i + 1;
        }
        else if (!occ2[a[i]]){
            occ2[a[i]] = i + 1;
        }
    }

	fill_lpf();
	int ptr = 0, nx;
	for (int x = 1; x <= mx; x++){
		nx = x;
		ptr = 0;
		while (lpf[nx] != 0){
			if (ptr == 0 || factorization[ptr - 1] != lpf[nx]){
				factorization[ptr++] = lpf[nx];
			}
			nx /= lpf[nx];
		}
		for (int i = 0; i <= ptr - 1; i++){
			adj[x].push_back(x / factorization[i]);
			adj[x / factorization[i]].push_back(x);
		}
	}
	
    BFS1();
    BFS2();

    for (int i = 0; i < n; i++){
        if (occ2[a[i]]){
            if (occ1[a[i]] != i + 1){
                cout << occ1[a[i]] << "\n";
            }
            else{
                cout << occ2[a[i]] << "\n";
            }
        }
        else{
            cout << occ1[other_closest_marked[a[i]]] << "\n";
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    //cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
