#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

struct P{
    lli x, y;
    void read(){
        cin >> x >> y;
    }
    void print(){
        cout << "(" << x << ", " << y << ")\n";
    }
    bool operator <(const P &a){ //
        return x < a.x || (x == a.x && y < a.y);
    }
    bool operator ==(const P &a){
        return x == a.x && y == a.y;
    }
    P operator -(const P& b) const{
        return P{x - b.x, y - b.y};
    }
    lli operator *(const P& b) const{
        return x * b.y - y * b.x;
    }

    //returns x, |x| = 2 * area of triangle, x > 0 <==> when going A->B->C we turn ccwise (+ve angle)
    lli orient(const P& b, const P& c) const { 
        return (b - *this) * (c - *this);
    }

    lli dist_sq(const P& b) const {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }
};

const int MAXN = 503;
const lli INF = 1e18 + 3;

P coords[MAXN];
vector <int> into[MAXN], outof[MAXN];
pair <int, int> edges[MAXN];
vector <pair <int, lli>> adj[MAXN];
lli edge_weight[MAXN];

struct Dijkstra{
    int n, src;
    vector <lli> dist;

    void init(int n_){
        n = n_;
        dist.assign(n + 1, INF);
    }

    void run(int src_){
        src = src_;
        priority_queue <pair <lli, int>> pq;
        pq.push({0, src});
        dist[src] = 0;
        int v;
        lli d;
        while (!pq.empty()){
            pair <lli, int> cur = pq.top();
            pq.pop();
            v = cur.ss;
            d = -cur.ff;

            if (d != dist[v]){
                continue;
            }

            for (pair <int, lli> child : adj[v]){
                if (dist[v] + child.ss < dist[child.ff]){
                    dist[child.ff] = dist[v] + child.ss;
                    pq.push({-dist[child.ff], child.ff});
                }
            }
        }
    }

    lli get_path_len(int v){
        return dist[v];
    }
};

bool valid(P A, P B, P C){ //is A->B->C a possible path 
    return (B.x - A.x) * (C.x - B.x) + (B.y - A.y) * (C.y - B.y) >= 0;
}

void solve(){
    int n, m, p, a, b, src, v, so_far = 0;
    lli w, len;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++){
        coords[i].read();
    }
    for (int i = 1; i <= m; i++){
        cin >> a >> b >> w;
        into[b].push_back(i);
        outof[a].push_back(i);
        edges[i] = {a, b};
        edge_weight[i] = w;
    }
    for (int i = 1; i <= n; i++){
        for (int in_edge : into[i]){
            for (int out_edge : outof[i]){
                if (valid(coords[edges[in_edge].ff], coords[i], coords[edges[out_edge].ss])){
                    adj[in_edge].emplace_back(out_edge, edge_weight[in_edge] + edge_weight[out_edge]);
                }
            }
        }
    }
    Dijkstra dij;
    dij.init(m);
    cin >> src;
    for (int i = 1; i < p; i++){
        dij.init(m);
        dij.run(src);
        cin >> v;
        len = dij.get_path_len(v);
        if (len == INF){
            cout << "NIE\n";
            return;
        }
        so_far += len;
        cout << so_far << "\n";
        src = v;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int t;
    //cin >> t;
    t = 1;
    while (t--){
        solve();
    }
    return 0;
}
