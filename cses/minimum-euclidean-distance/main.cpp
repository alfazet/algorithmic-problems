#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef long long int lli;

constexpr lli INF = 9e18 + 9;

struct Point {
    lli x, y;

    Point(lli _x, lli _y) : x(_x), y(_y) {};
    Point() : x(0), y(0) {};
};

istream &operator>>(istream &in, Point &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, Point &p) { return out << '(' << p.x << ", " << p.y << ')'; }

lli dist(Point p, Point q) { return (q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y); }
lli isqrt(lli x) { return (lli)sqrt(x) + 9; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }
    auto by_x = [](const Point &lhs, const Point &rhs) {
        if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        }
        return lhs.x < rhs.x;
    };
    auto by_y = [](const Point &lhs, const Point &rhs) {
        if (lhs.y == rhs.y) {
            return lhs.x < rhs.x;
        }
        return lhs.y < rhs.y;
    };
    sort(points.begin(), points.end(), by_x);
    lli ans = dist(points[0], points[1]);

    int tail_begin = -1, tail_end;
    set<Point, decltype(by_y)> sweep_line;
    sweep_line.insert(points[0]);
    for (int i = 1; i < n; i++) {
        Point cur = points[i];
        tail_end = tail_begin;
        for (int step = n; step >= 1; step /= 2) {
            if (tail_end + step < i &&
                (cur.x - points[tail_end + step].x) * (cur.x - points[tail_end + step].x) >= ans) {
                tail_end += step;
            }
        }
        for (int j = tail_begin + 1; j <= tail_end; j++) {
            sweep_line.erase(points[j]);
        }
        tail_begin = tail_end;

        Point low{cur.x, cur.y - isqrt(ans)}, high{cur.x, cur.y + isqrt(ans)};
        auto it = sweep_line.lower_bound(low);
        auto it_high = sweep_line.upper_bound(high);
        while (it != it_high) {
            ans = min(ans, dist(*it, cur));
            it++;
        }
        sweep_line.insert(cur);
    }
    cout << ans << '\n';

    return 0;
}
