#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector <int> dp(n); // dp[i] - max score difference that can be achieved by the person who is about to make a move on the prefix [0..i]
    dp[0] = a[0];
    for (int i = 1; i < n; i++){
        dp[i] = max(a[i] - dp[i - 1], dp[i - 1]); // either we take the new card and the opponent takes the rest or we take the rest 
    }
    cout << dp[n - 1] << "\n";

    return 0;
}   
