#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 53, MAXM = 503;
const lli INF = 1e18 + 3;

struct P{
    lli x, y;
    
    P(lli x_ = 0, lli y_ = 0) : x(x_), y(y_) {};
    
    P operator -(const P &B) const{
        return P(x - B.x, y - B.y);    
    }
    lli operator *(const P &B) const{ // dot product
        return x * B.x + y * B.y;
    }
	lli turn(const P &B, const P &C){ // sign of cos ABC
		return (B - *this) * (C - B);
	}
    
    void read(){
        cin >> x >> y;
    }
};

struct Edge{
	int u, v, w;
	
	Edge(int u_ = 0, int v_ = 0, int w_ = 0) : u(u_), v(v_), w(w_) {};
	
	void read(){
		cin >> u >> v >> w;
	}
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
	
    int n, p;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++){
        coords[i].read();
    }
    for (int i = 1; i <= m; i++){
        edges[i].read();
    }
    
    for (int i = 1; i <= m; i++){
		for (int j = 1; j <= m; j++){
			if (edges[i].v == edges[j].u && coords[edges[i].u].turn(coords[edges[i].v], coords[edges[j].v]) >= 0){
				adj[i].push_back({j, edges[i].w + edges[j].w});
			}
		}
	}
		
	vector <lli> times;
	int u, v;
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
		times.push_back((times.empty() ? 0 : times.back()) + t);
		u = v;
	}
	for (lli t : times){
		cout << t << "\n";
	}
	
	return 0;
}
