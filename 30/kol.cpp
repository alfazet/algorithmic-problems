#include <bits/stdc++.h>
typedef long long int lli;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n, p, r, c, clr;
    cin >> m >> p >> n;
    vector <vector <int>> grid(m, vector <int>(m, -1)), last(m, vector <int>(m, -1));
    
    for (int i = 0; i < p; i++){
        cin >> r >> c >> clr;
		r--, c--;
        grid[r][c] = clr;
    }
    
    int hr = 0, hc = 0, dt, moves = 0; // (hr, hc) = head
    vector <int> snake;
    snake.emplace_back(0);
    last[0][0] = 0;
    char typ;
    for (int i = 0; i < n; i++){
        cin >> typ;
        if (typ == 'Z'){
            cin >> r >> c;
			      r--, c--;
            if (last[r][c] == -1){
                cout << "-1\n";
            }
            else{
                dt = moves - last[r][c];
                if ((int) snake.size() <= dt){
                    cout << "-1\n";
                }
                else{
                    cout << snake[(int) snake.size() - dt - 1] << "\n";
                }
            }
        }
        else{
            if (typ == 'D') hr++;
            else if (typ == 'G') hr--;
            else if (typ == 'P') hc++;
            else hc--;
			      moves++;
            last[hr][hc] = moves;
            
            if (grid[hr][hc] != -1){
                snake.push_back(grid[hr][hc]);
				        grid[hr][hc] = -1;
            }
        }
    }
  
    return 0;
}
