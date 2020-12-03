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

    for (auto to : g[v]) {
        if (to == p) {
            continue;
        }

        if (used[to]) {
            tup[v] = min(tup[v], tin[to]);
        } else {
            dfs(to, v);
            tup[v] = min(tup[v], tup[to]);

            if (tup[to] > tin[v]) {
                cout << "BRIDGE " << v + 1 << ' ' << to + 1 << endl;
            }
        }
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

    dfs(0, 0);

    return 0;
}
