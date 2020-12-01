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

int n;
vector<edge> g[N];
int dp[N][2];

void dfs(int v, int p, int pw) { // pw -- вес до предка
    int sum_if_no_edge = 0; // сумма предков без ребра наверх

    for (auto [to, w] : g[v]) {
        if (to != p) {
            dfs(to, v, w);
            sum_if_no_edge += dp[to][0];
        }
    }

    dp[v][1] = sum_if_no_edge + pw;
    dp[v][0] = sum_if_no_edge; // если не взяли никого с ребром наверх

    for (auto [to, w] : g[v]) {
        if (to != p) {
            dp[v][0] = max(dp[v][0], sum_if_no_edge - dp[to][0] + dp[to][1]);
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

    dfs(0, -1, 0);
    cout << dp[0][0] << endl;
    return 0;
}

