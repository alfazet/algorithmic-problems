#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector <int> pref = {0};
    stack <int> moves, blocks;
    for (int i = 0; i < n; i++){
        pref.push_back(pref.back());
        if (s[i] == 'c') pref.back() -= k;
        else pref.back()++;
        blocks.push(i + 1);

        if ((int) pref.size() > k + 1 && pref.end()[-(k + 2)] == pref.back()){
            for (int j = 1; j <= k + 1; j++){
                moves.push(blocks.top());
                blocks.pop();
                pref.pop_back();
            }
        }
    }
    while (!moves.empty()){
        for (int i = 0; i < k + 1; i++){
            cout << moves.top() << " ";
            moves.pop();
        }
        cout << "\n";
    }

    return 0;
}   
