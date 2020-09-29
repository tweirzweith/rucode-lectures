#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> zfunction(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);

    int l = 0, r = 0; // [l, r)

    for (int i = 1; i < n; ++i) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }

        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    auto z = zfunction(t + "#" + s);

    for (int i = 0; i < n + m + 1; ++i) {
        if (z[i] == m) {
            cout << i - m - 1 << endl;
        }
    }

    cout << endl;
    return 0;
}

