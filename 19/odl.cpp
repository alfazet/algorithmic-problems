#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int INF = 1e9 + 3;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x, mx = 0;
    cin >> n;
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    vector <int> pos(mx + 1, INF), ans(n + 1, INF), ans_id(n + 1, INF), dist(mx + 1, INF), dist_other(mx + 1), closest(mx + 1);
    queue <pair <int, bool>> q; // {v, did we start multiplying already}
    for (int i = 1; i <= n; i++){
        x = a[i];
        if (pos[x] != INF){
            if (ans[pos[x]] != 0){
                ans[pos[x]] = 0;
                ans_id[pos[x]] = i;
            }
            ans[i] = 0;
            ans_id[i] = pos[x];
        }
        else{
            pos[x] = i;
            dist[x] = 0;
            closest[x] = x;
            q.emplace(x, false);
            q.emplace(x, true);
        }
    }

    vector <int> lpf(mx + 1), primes;
    vector <vector <int>> prime_divs(mx + 1); // max size = 7 since 2*3*5*7*11*13*19*23 > 10^6
    iota(lpf.begin(), lpf.end(), 0);
    for (int i = 2; i * i <= mx; i++){
        if (lpf[i] == i){
            for (int j = i * i; j <= mx; j += i){
                if (lpf[j] == j){
                    lpf[j] = i;
                }
            }
        }
    }
    for (int i = 2; i <= mx; i++){
        if (lpf[i] == i){
            primes.push_back(i);
        }
        int j = i;
        while (j != 1){
            if (prime_divs[i].empty() || prime_divs[i].back() != lpf[j]){
                prime_divs[i].push_back(lpf[j]);    
            }
            j /= lpf[j];
        }
    }

    vector <pair <int, int>> edges;
    while (!q.empty()){
        auto[v, flag] = q.front();
        q.pop();
        if (flag){ // here we can only multiply
            for (int p : primes){
                if (v * p > mx){
                    break;
                }
                if (dist[v * p] == INF){
                    dist[v * p] = dist[v] + 1;
                    closest[v * p] = closest[v];
                    q.emplace(v * p, true);
                }
                edges.emplace_back(v, v * p);
            }
        }
        else{
            for (int p : prime_divs[v]){
                if (dist[v / p] == INF){
                    dist[v / p] = dist[v] + 1;
                    closest[v / p] = closest[v];
                    q.emplace(v / p, false);
                    q.emplace(v / p, true);
                }
            }
        }
    }

    for (int rep = 0; rep < 2; rep++){
        for (auto[u, v] : edges){
            if (rep == 1){
                swap(u, v);
            }
            int cu = closest[u], cv = closest[v], du = dist[u], dv = dist[v], icu = pos[cu], icv = pos[cv], maybe = du + dv + 1;
            if (cu != cv){
                if (maybe < ans[icu] || (maybe == ans[icu] && icv < ans_id[icu])){
                    ans[icu] = maybe;
                    ans_id[icu] = icv;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++){
        assert(ans_id[i] != INF);
        cout << ans_id[i] << "\n";
    }

    return 0;
}
