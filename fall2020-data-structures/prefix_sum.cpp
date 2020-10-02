#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);

    for (auto& i : a) {
        cin >> i;
    }

    /* BUILD */
    vector<int> pref_sum(n + 1);
    pref_sum[0] = 0;

    for (int i = 0; i < n; ++i) {
        pref_sum[i + 1] = a[i] + pref_sum[i];
    }

    /* QUERY */

    int q;
    cin >> q;

    for (int j = 0; j < q; ++j) {
        int l, r;
        cin >> l >> r;
        cout << pref_sum[r] - pref_sum[l - 1] << endl;
    }

    return 0;
}
