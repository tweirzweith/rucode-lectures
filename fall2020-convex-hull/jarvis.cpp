#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct point2d {
    long long x, y;
};

struct vector2d {
    long long x, y;

    vector2d(point2d a, point2d b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

long long cross(vector2d a, vector2d b) {
    return a.x * b.y - b.x * a.y;
}

vector<point2d> get_convex_hull(vector<point2d> points) {
    for (int i = 1; i < points.size(); ++i) {
        if (points[i].x < points[0].x
            || (points[i].x == points[0].x && points[i].y < points[0].y))
        {
            swap(points[i], points[0]);
        }
    }

    int cur = 0;
    vector<point2d> ch = {points[0]};

    while (true) {
        int id = -1;

        for (int i = 0; i < points.size(); ++i) {
            if (i != cur
                && (id == -1
                    || cross(
                    vector2d(points[cur], points[i]),
                    vector2d(points[cur], points[id])
            ) > 0))
            {
                id = i;
            }
        }

        if (id == 0) {
            break;
        }

        ch.push_back(points[id]);
        cur = id;
    }

    return ch;
}

int main() {
    int n;
    cin >> n;
    vector<point2d> points(n);

    for (auto& pt : points) {
        cin >> pt.x >> pt.y;
    }

    auto ch = get_convex_hull(points);

    cout << ch.size() << endl;

    for (auto pt : ch) {
        cout << pt.x << ' ' << pt.y << endl;
    }

    return 0;
}

