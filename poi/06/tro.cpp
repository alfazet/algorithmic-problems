#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Node{
	int min_g, max_g, min_bg, max_bg;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
	cin >> s;
	reverse(s.begin(), s.end());
	stack <Node> st;
	Node u, w;
	for (char c : s){
		if (c == '0'){
			st.push({1, 1, 0, 0});
		}
		else if (c == '1'){
			u = st.top();
			st.pop();
			st.push({u.min_bg + 1, u.max_bg + 1, min(u.min_g, u.min_bg), max(u.max_g, u.max_bg)});
		}
		else{
			u = st.top();
			st.pop();
			w = st.top();
			st.pop();
			st.push({u.min_bg + w.min_bg + 1, u.max_bg + w.max_bg + 1, min(u.min_g + w.min_bg, u.min_bg + w.min_g), max(u.max_g + w.max_bg, u.max_bg + w.max_g)});
		}
	}
	Node root = st.top();
	cout << max(root.max_g, root.max_bg) << " " << min(root.min_g, root.min_bg) << "\n";

    return 0;
}
