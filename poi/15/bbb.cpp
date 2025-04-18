#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const int INF = 1e9 + 3;

struct Window{
    deque <pair <int, int>> q; // {element, covered}

    void pop(){
        if (q.front().ss == 0){
            q.pop_front();
        }
        else{
            q.front().ss--;
        }
    }

    void push(int x){
        int covered = 0;
        while (!q.empty() && q.back().ff >= x){
            covered += q.back().ss + 1;
            q.pop_back();
        }
        q.emplace_back(x, covered);
    }

    int query(){
        return q.front().ff;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cyclic rotation => just double the string
    int n, start, end, flip, move_back, ans = INF;
    cin >> n >> start >> end >> flip >> move_back;
    string s; cin >> s; s += s; n = s.size();

    vector <int> pref(n + 1);
    pref[0] = 0;
    Window min_q;
    min_q.push(0);
    for (int i = 1; i <= n / 2; i++){
        if (s[i - 1] == '+') pref[i]++;
        else pref[i]--;
        pref[i] += pref[i - 1];
        min_q.push(pref[i]);
    }

    int mn, added, l, need_flips;
    for (int i = n / 2 + 1; i < n; i++){
        if (s[i - 1] == '+') pref[i]++;
        else pref[i]--;
        pref[i] += pref[i - 1];
        min_q.pop();
        min_q.push(pref[i]);

        l = i - n / 2 + 1;
        mn = start + min_q.query() - pref[l];
        if (mn < 0){
            added = -mn + ((-mn) % 2);
        }
        else{
            added = 0;
        }
        if (start + pref[n / 2] + added < end){
            need_flips = (end - start - pref[n / 2]) / 2;
        }
        else{
            need_flips = added + (pref[n / 2] - (end - start)) / 2;
        }
        ans = min(ans, need_flips * flip + (n / 2 - l) * move_back);
    }
    cout << ans << "\n";

    return 0;
}
