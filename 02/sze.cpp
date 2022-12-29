#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

struct Task{
    double a, b;
    int id;

    bool operator <(const Task &t){
        return t.a * b < a * t.b;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	
    int n;
    cin >> n;
    vector <Task> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i].a >> a[i].b;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++){
        cout << a[i].id << "\n";
    }

    return 0;
}   
