#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9 + 3;

struct Window{
    deque <pair <pair <int, int>, int>> q; // {{value, height of the tree}, how many other elements are "covered" by it}

    void push(pair <int, int> x){
        int covered = 0;
        while (!q.empty() && (q.back().ff.ff > x.ff || (q.back().ff.ff == x.ff && q.back().ff.ss <= x.ss))){
            covered += q.back().ss + 1;
            q.pop_back();
        }
        q.emplace_back(x, covered);
    }

    void pop(){
        assert(!q.empty());
        if (q.front().ss == 0){
            q.pop_front();
        }
        else{
            q.front().ss--;
        }
    }

    pair <int, int> query(){
        assert(!q.empty());
        return q.front().ff;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, k;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    cin >> q;
    while (q--){
        cin >> k;
        vector <int> dp(n, INF);
        Window min_q;
        dp[0] = 0;
        min_q.push({0, a[0]});
        for (int i = 1; i < n; i++){
            if (i > k){
                min_q.pop();
            }
            pair <int, int> mn = min_q.query();
            dp[i] = mn.ff + (mn.ss <= a[i]);
            min_q.push({dp[i], a[i]});
        }
        cout << dp[n - 1] << "\n";
    }

    return 0;
}   
