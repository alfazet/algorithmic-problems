//XXV OI
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

void solve(){
    int n, s, x, mx = 0; //x = length
    cin >> n >> s;
    vector <int> freq(s + 1), order;
    multimap <int, int> where; //{value, where}
    for (int i = 0; i < n; i++){
        cin >> x;
        x++;
        x %= s;
        if (x == 0){
            order.push_back(i + 1);
        }
        else{
            freq[x]++;
            //where[x].push(i + 1);
            where.insert(make_pair(x, i + 1));
            mx = max(mx, x);
        }
    }
    priority_queue <pair <int, int>> pq; //{freq, length}
    for (int i = 1; i <= mx; i++){
        if (freq[i]){
            pq.push(make_pair(freq[i], i));
        }
    }

    pair <int, int> p;
    multimap <int, int> :: iterator it;
    lli ans = 0;
    int line = 0, fr, len; //numbering lines from 0 to s - 1 (line == next empty line)
    while (!pq.empty()){
        p = pq.top();
        pq.pop();
        fr = p.first;
        len = p.second;

        if (pq.empty()){ // if there's only one length possible now
            for (int i = 0; i < fr; i++){
                line = (line + len) % s;
                it = where.lower_bound(len); 
                order.push_back(it->second);
                where.erase(it);
                if (line == s - 1 && i != fr - 1){
                    ans++;
                    line = 0;
                }
            }
            break;
        }

        //trying to fit the current page length
        int maybe = (line + len) % s;
        if (maybe == s - 1){
            pair <int, int> other = pq.top();
            pq.pop();
            pq.push(make_pair(fr, len));
            fr = other.first;
            len = other.second;
            line = (line + len) % s;
            it = where.lower_bound(len); 
            order.push_back(it->second);
            where.erase(it);
            if (fr > 1){
                pq.push(make_pair(fr - 1, len));
            }
        }
        else{
            line = maybe;
            it = where.lower_bound(len); 
            order.push_back(it->second);
            where.erase(it);
            if (fr > 1){
                pq.push(make_pair(fr - 1, len));
            }
        }
    }

    cout << ans << "\n";
    for (int o : order){
        cout << o << " ";
    }
    cout << "\n";
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
