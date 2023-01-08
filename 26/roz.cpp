#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct BIT{
    int n;
    vector <lli> bit;

    void init(int n_){
        n = n_;
        bit.resize(n + 1);
    }

    lli query(int i){
        lli ans = 0;
        while (i >= 1){
            ans += bit[i];
            i -= (i & -i);
        }
        return ans;
    }

    lli query(int l, int r){
        return query(r) - (l == 1 ? 0 : query(l - 1));
    }

    void update(int i, lli val){
        while (i <= n){
            bit[i] += val;
            i += (i & -i);
        }
    }
};

int n, p = 1;
BIT bit;

void move(){
    p++;
    if (p == n + 1){
        p = 1;
    }
}

void inicjuj(int n_){
    n = n_;
    bit.init(n + 1);
}

void dodaj(int val){
    bit.update(p, 1LL * val - bit.query(p, p));
    move();
}

void koryguj(int i, int val){
    bit.update((i < p ? p - i : n - (i - p)), 1LL * val);
}

lli suma(int cnt){
    return (cnt < p ? bit.query(p - cnt, p - 1) : bit.query(1, p - 1) + bit.query(n - (cnt - p), n));
}
