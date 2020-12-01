#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

const int N = 100 * 1000 + 17;

int n;
vector<int> g[N];

// returns count of vertices in subtree
int dfs(int v, int p) {
    int result = 1;
    bool is_centroid = true;

    for (auto to : g[v]) {
        if (to != p) {
            auto cnt = dfs(to, v);
            result += cnt;

            if (cnt > n / 2) {
                is_centroid = false;
            }
        }
    }

    if (n - result > n / 2) {
        is_centroid = false;
    }

    if (is_centroid) {
        cout << "Candidate for centroid: " << v + 1 << endl;
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

    dfs(0, -1);
    return 0;
}
