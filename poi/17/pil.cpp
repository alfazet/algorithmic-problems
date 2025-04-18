#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

#define ff first
#define ss second

struct Window{
	deque <pair <int, int>> q; // {value, how many other elements are "covered" by it}
	
	void push(int x){
		int cnt = 0;
		while (!q.empty() && q.back().ff <= x){
			cnt += q.back().ss + 1;
			q.pop_back();
		}
		q.emplace_back(x, cnt);
	}
	
    void pop(){
        assert(!q.empty());
        if (q.front().ss == 0){
            q.pop_front();
        }
        else{
            q.front().ss--;
        }
    }

    int query(){
        assert(!q.empty());
        return q.front().ff;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
	int n, t, ans = 0, l = 0, x;
	cin >> t >> n;
	Window mx, mn;
	for (int i = 0; i < n; i++){
		cin >> x;
		mx.push(x);
		mn.push(-x);
		while (mx.query() - (-mn.query()) > t){
			mx.pop();
			mn.pop();
			l++;
		}
		ans = max(ans, i - l + 1);
	}
	cout << ans << "\n";
	
    return 0;
}
