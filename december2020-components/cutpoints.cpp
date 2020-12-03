#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int N = 100 * 1000 + 17;

int n, m;
vector<int> g[N];
int tin[N], tup[N];
int timer = 0;
bool used[N];

void dfs(int v, int p) {
    used[v] = true;
    tin[v] = timer++;
    tup[v] = tin[v];
    int children = 0;
    bool is_cutpoint = false;

    for (auto to : g[v]) {
        if (to == p) {
            continue;
        }

        if (used[to]) {
            tup[v] = min(tup[v], tin[to]);
        } else {
            dfs(to, v);
            tup[v] = min(tup[v], tup[to]);
            ++children;

            if (tup[to] >= tin[v] && p != -1) {
                is_cutpoint = true;
            }
        }
    }

    if (p == -1 && children > 1) {
        is_cutpoint = true;
    }

    if (is_cutpoint) {
        cout << "CUTPOINT " << v + 1 << endl;
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    dfs(0, -1);

    return 0;
}
