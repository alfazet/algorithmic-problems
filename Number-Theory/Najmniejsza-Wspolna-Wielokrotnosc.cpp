//XXVII OI
#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

const lli MAX_VALS[4] = {2000000, 70000, 10000, 3000};

vector <pair <lli, pair <int, int>>> LCM_tab; 

lli special_case(lli n){
    lli delta = 4*n + 1;
    lli root = sqrt(delta);
    for (lli i = root - 8; i <= root + 8; i++){
        if (i * i == delta && i % 2 == 1){
            return (i - 1) / 2;
        }
    }
    return -1;
}

lli __lcm(lli a, lli b){
    return (a / __gcd(a, b)) * b;
}

lli LCM(int a, int b){
    lli res = 1;
    for (int i = a; i <= b; i++){
        res = __lcm(res, i);
    }
    return res;
}

int b_search(lli n){
    int l = 0, r = LCM_tab.size(), mid, ans = -1;
    while (l <= r){
        mid = (l + r) / 2;
        if (LCM_tab[mid].ff < n){
            l = mid + 1;
        }
        else if (LCM_tab[mid].ff == n){
            ans = mid;
            r = mid - 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ans;
}

void preprocess(){
    for (int k = 3; k <= 100; k++){
        for (int start = 1; start <= MAX_VALS[min(3, k - 3)]; start++){
            LCM_tab.emplace_back(LCM(start, start + k - 1), make_pair(start, start + k - 1));
        }
    }
    sort(LCM_tab.begin(), LCM_tab.end());
}

void solve(){
    int where;
    lli n, a;
    
    cin >> n;
    a = special_case(n);
    where = b_search(n);
    
    if (where == -1){
        if (a != -1){
            cout << a << " " << a + 1 << "\n";
        }
        else{
            cout << "NIE\n";
        }
    }
    else{
        if (a <= LCM_tab[where].ss.ff && a != -1){
            cout << a << " " << a + 1 << "\n";
        }
        else{
            cout << LCM_tab[where].ss.ff << " " << LCM_tab[where].ss.ss << "\n";
        }
    }
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    preprocess();
    int t;
    cin >> t;
    //t = 1;
    while (t--){
        solve();
    }
    return 0;
}
