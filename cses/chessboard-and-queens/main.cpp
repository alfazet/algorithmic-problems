#include <iostream>
#include <utility>
#include <vector>

using namespace std;

constexpr int N = 8;

int ans = 0;
char grid[N][N];

void rec(int r, int c, vector<pair<int, int>> &placed) {
    if (r == N && c == 0) {
        if (placed.size() == N) {
            ans++;
        }
        return;
    }
    if (r > N - 1 || c > N - 1) {
        return;
    }
    bool free = true;
    for (auto &[i, j] : placed) {
        if (i == r || j == c || r + c == i + j || r - c == i - j) {
            free = false;
        }
    }
    int new_r = r;
    int new_c = c + 1;
    if (new_c == N) {
        new_r = r + 1;
        new_c = 0;
    }
    if (grid[r][c] == '.' && free) {
        placed.emplace_back(r, c);
        rec(new_r, new_c, placed);
        placed.pop_back();
    }
    rec(new_r, new_c, placed);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }
    rec(0, 0, vector<pair<int, int>>() = {});
    cout << ans << '\n';

    return 0;
}
