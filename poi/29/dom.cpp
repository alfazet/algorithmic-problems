#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lli n;
    cin >> n;

	vector <lli> f{0, 1};
	while (f.back() <= n){
		f.push_back(f.end()[-1] + f.end()[-2]);
	}

    for (int i = f.size() - 1; i >= 2; i--){
        if (f[i] == n){
            cout << i - 1 << "\n";
            return 0;
        }
    }

    int sum_ind = 0, bars = 0, cnt_2 = 0, cnt_3 = 0, cnt = 0;

    for (int i = f.size() - 1; i >= 3; i--){
        if (f[i] > n || f[i] == 144 || f[i] == 8){
            continue;
        }
        cnt = 0;
        while (n % f[i] == 0){
            n /= f[i];
            if (f[i] != 2 && f[i] != 3){
                sum_ind += i - 1;
                bars++;
            }
            cnt++;
        }
        
        if (f[i] == 3){
            cnt_3 = cnt;
        }
        if (f[i] == 2){
            cnt_2 = cnt;
        }
    }

    if (n != 1){
        cout << "NIE\n";
        return 0;
    }

    int cnt_144 = min(cnt_2 / 4, cnt_3 / 2);
    cnt_2 -= cnt_144 * 4;
    cnt_3 -= cnt_144 * 2;

    sum_ind += cnt_144 * 11;
    bars += cnt_144;

    int cnt_8 = cnt_2 / 3;
    cnt_2 -= cnt_8 * 3;

    sum_ind += cnt_8 * 5;
    bars += cnt_8;

    sum_ind += cnt_3 * 3 + cnt_2 * 2;
    bars += cnt_3 + cnt_2;

    cout << sum_ind + bars - 1 << "\n";

    return 0;
}
