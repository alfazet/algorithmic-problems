#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 53, MAXM = 503;
const lli INF = 1e18 + 3;

struct P{
    lli x, y;

    P (lli x_ = 0, lli y_ = 0) : x(x_), y(y_) {};

    P operator + (P b){
        return P(x + b.x, y + b.y);
    }
    P operator - (P b){
        return P(x - b.x, y - b.y);
    }
    lli operator ^ (P b){
        return x * b.y - b.x * y;
    }
    lli operator * (P b){
        return x * b.x + y * b.y;
    }

    lli sin(P b, P c){ // "sine" of convex angle B->A->C
        return (b - (*this)) ^ (c - (*this));
    }
    lli cos(P b, P c){ // "cosine" of convex angle B->A->C
        return (b - (*this)) * (c - (*this)); 
    }
};

istream& operator>> (istream &in, P &a){
    return in >> a.x >> a.y;
}
ostream& operator<< (ostream &out, P &a){
    return out << "(" << a.x << ", " << a.y << ")";
}

struct Edge{
	int u, v, w;
	
	Edge(int u_ = 0, int v_ = 0, int w_ = 0) : u(u_), v(v_), w(w_) {};
};

int m;
Edge edges[MAXM];
P coords[MAXN];
vector <pair <int, int>> adj[MAXM];
lli d[MAXM];

void dijkstra(int v){
	for (int i = 1; i <= m; i++){
		d[i] = INF;
	}
	d[v] = 0;
	priority_queue <pair <lli, int>, vector <pair <lli, int>>, greater <pair <lli, int>>> pq;
	pq.emplace(0, v);
	
	while (!pq.empty()){
		auto [so_far, v] = pq.top();
		pq.pop();
		for (auto [child, w] : adj[v]){
			if (d[child] > so_far + w){
				d[child] = so_far + w;
				pq.emplace(d[child], child);
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
    int n, p, u, v, w;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++){
        cin >> coords[i];
    }
    for (int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        edges[i] = Edge(u, v, w);
    }
    
    for (int i = 1; i <= m; i++){
		for (int j = 1; j <= m; j++){
			if (edges[i].v == edges[j].u && coords[edges[i].v].cos(coords[edges[i].u], coords[edges[j].v]) <= 0){
				adj[i].emplace_back(j, edges[i].w + edges[j].w);
			}
		}
	}
		
	vector <lli> ans;
	lli t;
	cin >> u;
	for (int i = 0; i < p - 1; i++){
		cin >> v;
		if (v == u){
			t = INF;
			for (auto [child, w] : adj[u]){
				dijkstra(child);
				t = min(t, d[v] + w);
			}
		}
		else{
			dijkstra(u);
			t = d[v];
		}
		
		if (t == INF){
			cout << "NIE\n";
			return 0;
		}
		ans.push_back((ans.empty() ? 0 : ans.back()) + t);
		u = v;
	}
	for (lli t : ans){
		cout << t << "\n";
	}
	
	return 0;
}
