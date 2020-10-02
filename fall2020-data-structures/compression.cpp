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

    /* сжатие массива: [15, 1, 7, 4, 4, 90] -> [3, 0, 2, 1, 1, 4]
     * переводим элементы массива в меньшие, сохраняя отношение больше/меньше/равно */

    vector<int> tmp = a;
    sort(tmp.begin(), tmp.end());
    tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());

    for (auto& i : a) {
        i = lower_bound(tmp.begin(), tmp.end(), i) - tmp.begin();
    }

    for (auto i : a) {
        cout << i << ' ';
    }

    cout << endl;

    return 0;
}

