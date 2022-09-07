#include <iostream>

using namespace std;

int main() {
    int n, x;
    cout << "Amount of numbers (up to 63 inclusive): ";
    cin >> n;
    cout << "Numbers: ";
    unsigned long long mask = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        mask |= 1ull << 63 >> x;
    }

    cout << "Sorted: ";
    for (int i = 0; i < 64; i++) {
        if (mask & (1ull << 63 >> i)) {
            cout << i << " ";
        }
    }

    return 0;
}