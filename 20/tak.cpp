#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    lli len, base;
    int n;
    cin >> len >> base >> n;
    vector <lli> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());

    lli chosen = 0, extra = 0, earliest = base; // earliest = the lowest coord we need to reach
    int taken_id; 
    auto it = upper_bound(a.begin(), a.end(), len - base, greater <lli>());

    if (it == a.begin()){
        cout << "0\n";
        return 0;
    }
    else{
        it--;
        taken_id = it - a.begin();
        chosen = *it; // a taxi that can take us from the base to the end
        if (chosen > len - base){
            extra = (chosen - (len - base)) / 2;
        }
        earliest = base - extra;
    }

    lli pos = 0, ans = 1;
    int i = 0;
    while (pos < earliest){
        if (i == taken_id){
            i++;
        }
        if (i >= n || base - pos >= a[i]){
            cout << "0\n";
            return 0;
        }
        pos += a[i] - (base - pos);
        ans++;
        i++;
    }
    if (pos >= len){ // we didn't have to use the chosen taxi
        ans--;
    }
    cout << ans << "\n";

    return 0;
}   
