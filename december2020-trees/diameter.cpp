#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int N = 100 * 1000 + 17;

int n;
vector<int> g[N];

// { max_depth, vertex_id }
pair<int, int> dfs(int v, int p, int h) {
    pair<int, int> result = {h, v};

    for (auto to : g[v]) {
        if (to != p) {
            result = max(result, dfs(to, v, h + 1));
        }
    }

    return result;
}

int main() {
    cin >> n;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
        g[v - 1].push_back(u - 1);
    }

    auto [_, vl] = dfs(0, -1, 0); // C++17, structure bindings
    auto [diam, vr] = dfs(vl, -1, 0);
    cout << diam << ' ' << vl + 1 << ' ' << vr + 1 << endl;
    return 0;
}
