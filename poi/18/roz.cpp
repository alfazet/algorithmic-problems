#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    char c;
    vector <vector <int>> pos(26); 
    for (int i = 0; i < n; i++){
        cin >> c;
        pos[c - 'a'].push_back(i);
    }

    auto solve = [&](int x, int y){
        vector <int> a;
        int p = 0, q = 0;
        while (p < (int) pos[x].size() && q < (int) pos[y].size()){
            if (pos[x][p] < pos[y][q]){
                a.push_back(-1);
                p++;
            }
            else{
                a.push_back(1);
                q++;
            }
        }
        while (p < (int) pos[x].size()){
            a.push_back(-1);
            p++;
        }
        while (q < (int) pos[y].size()){
            a.push_back(1);
            q++;
        }

        int l = a.size();
        vector <int> pref = {0}, min_pref = {0};
        for (int i = 0; i < l; i++){
            pref.push_back(pref.back() + a[i]);
            min_pref.push_back(min(min_pref.back(), pref.back()));
        }

        int ans = 0, last_minus = l;
        for (int i = 0; i < l; i++){
            if (a[i] == -1){
                last_minus = i;
            }
            if (last_minus != l){
                ans = max(ans, pref[i + 1] - min_pref[last_minus]);
            }
        }
        return ans;
    };

    int ans = 0;
    for (char x = 'a'; x <= 'z'; x++){
        for (char y = 'a'; y <= 'z'; y++){
            if (x != y) ans = max(ans, solve(x - 'a', y - 'a'));
        }
    }
    cout << ans << "\n";

    return 0;
}
