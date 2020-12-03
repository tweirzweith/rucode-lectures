#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int N = 100 * 1000 + 17;

int n, m;
vector<int> g[N], gr[N];
bool used[N];
vector<int> order;

void dfs1(int v) {
    used[v] = true;

    for (auto to : g[v]) {
        if (!used[to]) {
            dfs1(to);
        }
    }

    order.push_back(v);
}

void dfs2(int v, vector<int>& cur_comp) {
    used[v] = true;
    cur_comp.push_back(v);

    for (auto to : gr[v]) {
        if (!used[to]) {
            dfs2(to, cur_comp);
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        gr[v - 1].push_back(u - 1);
    }

    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs1(v);
        }
    }

    reverse(order.begin(), order.end());
    fill(used, used + n, false);

    for (auto v : order) {
        if (!used[v]) {
            vector<int> cur_comp;
            dfs2(v, cur_comp);

            for (auto u : cur_comp) {
                cout << u + 1 << ' ';
            }

            cout << endl;
        }
    }

    return 0;
}
