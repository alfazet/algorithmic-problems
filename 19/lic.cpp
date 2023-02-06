#include <bits/stdc++.h>
#include "cliclib.h"
typedef long long int lli;
using namespace std;

int n;

map <pair <int, int>, int> dp; // dp[{wager, stack}] = 0 if position is losing, else the winning move

void DFS(pair <int, int> v){
    int w = v.first, s = v.second;
    if (dp.count(v)){
        return;
    }
    if (w + s >= n){
        dp[v] = 0;
        return;
    }

    pair <int, int> op1 = {1, s + w}, op2 = {2 * w, s}, op3 = {3 * w, s};
    DFS(op1); DFS(op2); DFS(op3);

    if (!dp[op1]){
        dp[v] = 1;
    }
    else if (!dp[op2]){
        dp[v] = 2;
    }
    else if (!dp[op3]){
        dp[v] = 3;
    }
    else{ // this position leads only to winning, so it's losing
        dp[v] = 0;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    n = inicjuj();
    pair <int, int> v = {1, 0};
    DFS(v);

    auto change_state = [&](int mv){
        if (mv == 1){
            v = {1, v.first + v.second};
        }
        else if (mv == 2){
            v = {2 * v.first, v.second};
        }
        else{
            v = {3 * v.first, v.second};
        }
    };

    int mv;
    while (true){
        mv = dp[v];
        alojzy(mv);
        change_state(mv);
        mv = bajtazar();
        change_state(mv);
    }

    return 0;
}
