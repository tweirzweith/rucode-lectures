#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> p(n, 0);

    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];

        while (j > 0 && s[i] != s[j]) {
            j = p[j - 1];
        }

        if (s[i] == s[j]) {
            p[i] = j + 1;
        } else {
            p[i] = 0;
        }
    }

    return p;
}

int main() {
    int n;
    string s;
    cin >> n >> s;

    auto p = prefix_function(s);

    for (int i = 0; i < n; ++i) {
        cout << p[i] << ' ';
    }

    cout << endl;
    return 0;
}
