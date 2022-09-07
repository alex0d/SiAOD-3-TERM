#include <iostream>

using namespace std;

int main() {
    int n, x;
    cout << "Number of digits (up to 7 inclusive): ";
    cin >> n;
    cout << "Digits: ";
    unsigned char mask = 0;
    for (int i = 0; i < n; i++) {
        cin >> x;
        mask |= 128 >> x;
    }

    cout << "Sorted: ";
    for (int i = 0; i < 8; i++) {
        if (mask & (128 >> i)) {
            cout << i << " ";
        }
    }

    return 0;
}