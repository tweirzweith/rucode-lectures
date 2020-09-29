#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long get_substring_hash(
        const vector<long long>& prefix_hash,
        const vector<long long>& power,
        long long mod,
        int l, int r)
{
    return (mod + prefix_hash[r] - prefix_hash[l - 1] * power[r - l + 1] % mod) % mod;
}

int main() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    vector<long long> prefix_hash(n + 1, 0);
    vector<long long> power(n + 1);
    long long p = 31;
    long long mod = 1000 * 1000 * 1000 + 7;
    power[0] = 1;

    /* calculating prefix hash of s and powers:
     * power[i] = p**i % mod
     * prefix_hash[i] = (s[i] + s[i - 1] * p + s[i - 2] * p**2 + ... + s[0] * p**i) % mod
     */

    for (int i = 0; i < n; ++i) {
        int cur = int(s[i]) - 'a' + 1;
        prefix_hash[i + 1] = (prefix_hash[i] * p + cur) % mod;
        power[i + 1] = power[i] * p % mod;
    }

    /* getting hash of string t */
    long long t_hash = 0;

    for (int i = 0; i < m; ++i) {
        int cur = int(t[i]) - 'a' + 1;
        t_hash = (t_hash * p + cur) % mod;
    }

    /* checking substrings */

    for (int i = m; i <= n; ++i) {
        if (t_hash == get_substring_hash(prefix_hash, power, mod, i - m + 1, i)) {
            cout << i - m << endl;
        }
    }

    return 0;
}
