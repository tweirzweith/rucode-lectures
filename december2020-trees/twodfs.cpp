#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int N = 100 * 1000 + 17;

struct edge {
    int to, weight;
};

struct info { // необходимая информация для подсчёта суммы квадратов
    int sum_sqr, sum, cnt;
};

info operator + (const info& lhs, const info& rhs) { // сложить информацию для двух поддеревьев
    info result = {lhs.sum_sqr + rhs.sum_sqr, lhs.sum + rhs.sum, lhs.cnt + rhs.cnt};
    return result;
}

info operator - (const info& lhs, const info& rhs) { // вычесть информацию одного поддерева из другого
    info result = {lhs.sum_sqr - rhs.sum_sqr, lhs.sum - rhs.sum, lhs.cnt - rhs.cnt};
    return result;
}

info& operator += (info& lhs, const info& rhs) {
    lhs = lhs + rhs;
    return lhs;
}

info add_edge(const info& lhs, int w) { // добавить ребро веса w к корню поддерева
    return {lhs.sum_sqr + 2 * w * lhs.sum + w * w * lhs.cnt, lhs.sum + w * lhs.cnt, lhs.cnt};
}

int n;
vector<edge> g[N];
info dp_down[N];
int ans[N];

void dfs_down(int v, int parent) { // считаем только для путей вниз
    dp_down[v] = {0, 0, 1};

    for (auto [to, w] : g[v]) {
        if (to != parent) {
            dfs_down(to, v);
            dp_down[v] += add_edge(dp_down[to], w);
        }
    }
}

void dfs_up(int v, int parent, info upper) { // считаем для путей наверх
    ans[v] = (upper + dp_down[v]).sum_sqr;
    ++upper.cnt;

    for (auto [to, w] : g[v]) {
        if (to != parent) {
            upper += add_edge(dp_down[to], w);
        }
    }

    for (auto [to, w] : g[v]) {
        if (to != parent) {
            // переходим в потомка, исключая из upper текущее поддерево и добавляя ребро
            dfs_up(to, v, add_edge(upper - add_edge(dp_down[to], w), w));
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u - 1].push_back({v - 1, w});
        g[v - 1].push_back({u - 1, w});
    }

    dfs_down(0, -1);
    dfs_up(0, -1, {});

    for (int v = 0; v < n; ++v) {
        cout << ans[v] << endl;
    }

    return 0;
}
