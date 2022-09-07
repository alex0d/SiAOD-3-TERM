#include <iostream>

using namespace std;

int main() {
    int n, x;
    cout << "Amount of numbers (up to 63 inclusive): ";
    cin >> n;
    cout << "Numbers: ";
    unsigned char mask[8] = {0};
    for (int i = 0; i < n; i++) {
        cin >> x;
        mask[x/8] |= 128 >> (x % 8);
    }

    cout << "Sorted: ";
    for (int i = 0; i < 64; i++) {
        if (mask[i/8] & (128 >> (i % 8))) {
            cout << i << " ";
        }
    }

    return 0;
}