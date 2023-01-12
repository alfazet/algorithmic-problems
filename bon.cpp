#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

const int MAXN = 1e6 + 3;

bool good[MAXN], taken[MAXN];
int next_to_take[MAXN]; // next_to_take[i] = next available multiple of i

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int m, x;
    cin >> m;
    for (int i = 0; i < m; i++){
        cin >> x;
        good[x] = true;
    }
    iota(next_to_take, next_to_take + MAXN, 0);

    int n;
    lli client = 0;
    vector <lli> ans;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> x;
        for (int j = 0; j < x; j++){
            client++;
            while (next_to_take[x] < MAXN && taken[next_to_take[x]]){
                next_to_take[x] += x;
            }
            if (next_to_take[x] >= MAXN){
                client += x - j - 1;
                break;
            }

            int we_take = next_to_take[x];
            taken[we_take] = true;
            if (good[we_take]){
                ans.push_back(client);
            }
        }
    }

    cout << ans.size() << "\n";
    for (lli c : ans){
        cout << c << "\n";
    }

    return 0;
}   
