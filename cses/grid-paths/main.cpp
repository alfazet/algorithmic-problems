#include <iostream>
#include <vector>

using namespace std;

constexpr int N = 7, K = 48;
constexpr int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
constexpr char dir_char[4] = {'U', 'D', 'L', 'R'};

int ans = 0;
string pattern;

bool path_matches(const string& path) {
    bool ok = true;
    for (int i = 0; i < K; i++) {
        if (pattern[i] != '?') {
            ok &= (pattern[i] == path[i]);
        }
    }
    return ok;
}

void rec(int r, int c, int step, vector<vector<bool>>& vis, string path) {
    if (r == N - 1 && c == 0) {
        if (step == K && path_matches(path)) {
            ans++;
        } else {
            return;
        }
    }
    bool can_left, can_right, can_up, can_down;
    if (path.size() >= 1) {
        switch (path.back()) {
            case 'L':
                can_up = (r - 1 >= 0), can_down = (r + 1 < N);
                if (can_up && can_down && (c - 1 < 0 || vis[r][c - 1])) {
                    return;
                }
                break;
            case 'R':
                can_up = (r - 1 >= 0), can_down = (r + 1 < N);
                if (can_up && can_down && (c + 1 >= N || vis[r][c + 1])) {
                    return;
                }
                break;
            case 'U':
                can_left = (c - 1 >= 0), can_right = (c + 1 < N);
                if (can_left && can_right && (r - 1 < 0 || vis[r - 1][c])) {
                    return;
                }
                break;
            case 'D':
                can_left = (c - 1 >= 0), can_right = (c + 1 < N);
                if (can_left && can_right && (r + 1 >= N || vis[r + 1][c])) {
                    return;
                }
                break;
        }
    }
    for (int i = 0; i < 4; i++) {
        int new_r = r + dr[i], new_c = c + dc[i];
        if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N && !vis[new_r][new_c]) {
            vis[new_r][new_c] = true;
            rec(new_r, new_c, step + 1, vis, path + dir_char[i]);
            vis[new_r][new_c] = false;
        }
    }
}

int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);

    cin >> pattern;
    vector<vector<bool>> vis(N, vector<bool>(N));
    vis[0][0] = true;
    rec(0, 0, 1, vis, "");
    cout << ans << '\n';

    return 0;
}
