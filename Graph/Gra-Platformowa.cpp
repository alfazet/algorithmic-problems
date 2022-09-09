//XXVIII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int MAXN = 1e5 + 3, MAXK = 2.2e6 + 3, INF = 1e9 + 3;

vector <pair <int, int>> adj[MAXK];
int n, begin_id[MAXN], end_id[MAXN], dist[MAXK];
int cnt = 1;

void merge(int i, vector <pair <int, int>> &holes_bot, vector <pair <int, int>> &holes_top){
    int last = begin_id[i], p = 0, q = 0;
    pair <int, int> nxt;
    bool flag;
    
    for (int j = 0; j < (int) holes_bot.size() + (int) holes_top.size(); j++){
        if ((q == (int) holes_top.size()) || (p < (int) holes_bot.size() && holes_bot[p].ss < holes_top[q].ss)){
            nxt = holes_bot[p];
            flag = true;
            p++;
        }
        else{
            nxt = holes_top[q];
            flag = false;
            q++;
        }
        
        if (flag){
            adj[nxt.ff].emplace_back(last, 1);
            last = nxt.ff;
        }
        else{
            adj[nxt.ff].emplace_back(last, 1);
            adj[last].emplace_back(nxt.ff - 1, 0);
        }
    }
    end_id[i] = last;
}

//front - 0, back - 1
void BFS(){
    deque <int> dq;
    for (int i = 1; i <= n; i++){
        dq.push_front(end_id[i]);
        dist[end_id[i]] = 0;
    }
    int v, u, cost;
    while (!dq.empty()){
        v = dq.front();
        dq.pop_front();
        for (auto child : adj[v]){
            u = child.ff;
            cost = child.ss;
            if (dist[u] > dist[v] + cost){
                dist[u] = dist[v] + cost;
                if (cost == 0){
                    dq.push_front(u);
                }
                else{
                    dq.push_back(u);
                }
            }
        }
    }
}

void solve(){
	int Q, k, x, X;
    int flag = 1;
    cin >> n >> X >> Q;
    for (int i = 1; i < MAXK; i++){
        dist[i] = INF;
    }
    
    vector <pair <int, int>> holes1, holes2;
    for (int i = 1; i <= n; i++){
        cin >> k;
        begin_id[i] = cnt++;
        for (int j = 0; j < k; j++){
            cin >> x;
            if (flag){
                holes1.emplace_back(cnt++, x);
            }
            else{
                holes2.emplace_back(cnt++, x);
            }
        }
        if (flag){
            merge(i, holes1, holes2);
            holes2.clear();
        }
        else{
            merge(i, holes2, holes1);
            holes1.clear();
        }
        end_id[i] = cnt - 1;
        flag ^= 1;
    }
    
    BFS();
    while (Q--){
        cin >> k;
        cout << dist[begin_id[k]] << "\n";
    }
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int t;
	t = 1;
	//cin >> t;
	while (t--){
		solve();
	}
	return 0;
}
