#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, u, v, z;
	cin >> n;
	vector <int> l(n + 1), r(n + 1), par(n + 1), level(n + 1);
	for (int i = 1; i <= n; i++){
		cin >> l[i] >> r[i];
	}

	queue <int> q;
	q.push(1);
	while (!q.empty()){
		v = q.front();
		q.pop();
		if (l[v] != 0){
			q.push(l[v]);
			par[l[v]] = v;
			level[l[v]] = (level[v] == 0 ? 0 : level[v] + 1);
		}
		if (r[v] != 0){
			q.push(r[v]);
			par[r[v]] = v;
			level[r[v]] = level[v] + 1; 
		}
	}

	auto path = [&](int v){
		string s;
		while (level[v] > 0){
			s += (v == l[par[v]] ? '0' : '1');
			v = par[v];
		}
		reverse(s.begin(), s.end());
		return s;
	};

	cin >> z;
	while (z--){
		cin >> u >> v;
		if (level[u] != level[v]){
			cout << (level[u] > level[v] ? "TAK\n" : "NIE\n");
		}
		else{
			cout << (path(u) >= path(v) ? "TAK\n" : "NIE\n");
		}
	}

    return 0;
}   
