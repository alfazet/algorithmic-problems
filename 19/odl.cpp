#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3, INF = 1e9 + 3;

int occ1[MAXN], occ2[MAXN], lpf[MAXN], factorization[MAXN], dist_to_marked[MAXN], dist_to_other_marked[MAXN], closest_marked[MAXN], other_closest_marked[MAXN];
vector <int> adj[MAXN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int n, mx = 0;
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

    iota(lpf + 1, lpf + mx + 1, 1);
	for (int i = 2; i * i <= mx; i++){
        if (lpf[i] == i){
            for (int j = i * i; j <= mx; j += i){
                if (lpf[j] == j){
                    lpf[j] = i;
                }
            }
        }
    }
	
    vector <int> factors;
    for (int i = 1; i <= mx; i++){
        factors.clear();
        int ni = i;
        while (ni != 1){
            if (factors.empty() || factors.back() != lpf[ni]){
                factors.push_back(lpf[ni]);
            }
            ni /= lpf[ni];
        }
        for (int f : factors){
            adj[i].push_back(i / f);
            adj[i / f].push_back(i);
        }
    }
	
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

    return 0;
}
