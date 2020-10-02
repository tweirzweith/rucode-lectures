#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int LOGN = 20;

struct sparse_table {
    int n;
    vector< vector<int> > table;
    vector<int> logn; // logn[i] = log_2(i)

    sparse_table(const vector<int>& values) {
        n = values.size();
        table.resize(LOGN, vector<int>(n));
        logn.resize(n + 1);

        logn[0] = logn[1] = 0;

        for (int i = 2; i <= n; ++i) {
            logn[i] = 1 + logn[i / 2];
        }

        for (int i = 0; i < n; ++i) {
            table[0][i] = values[i]; // [i, i + 2^0) = [i, i + 1)
            // min[i, i + 1) = values[i]
        }

        for (int k = 1; k < LOGN; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) { // (1 << k) = 2^k
                // [i, i + 2^k) = [i, i + 2^{k-1}) + [i + 2^{k-1}, i + 2^k)
                // отрезок длины 2^k распался на 2 отрезка длины 2^{k-1}
                // [0, 16) = [0, 8) + [8, 16)
                // [8, 16) = [8, 12) + [12, 16)
                table[k][i] = min(
                        table[k - 1][i],
                        table[k - 1][i + (1 << (k - 1))]
                );
            }
        }
    }

    int get_min(int l, int r) { // [l, r)
        int k = logn[r - l];
        return min(
                table[k][l],
                table[k][r - (1 << k)]
        );
    }

    // [1, 5]
    // [0, 5) -- 0-индекс
    // длина отрезка = 5
    // 4 == 2^2
    // [0, 4) и [1, 5) -- каждый длины 4
    // table[k][i] -- минимум на отрезке [i, i + 2^k)

    // [0, 6)
    // [0, 4) и [2, 6)

    // 2^k <= len
    // 2^{k+1} > len
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (auto& i : a) {
        cin >> i;
    }

    sparse_table t(a);

    int q;
    cin >> q;

    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        cout << t.get_min(l - 1, r) << endl;
    }

    return 0;
}
