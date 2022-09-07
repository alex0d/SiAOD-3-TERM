#include <iostream>
#include <bitset>

using namespace std;

int main() {
    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned mask = (1 << n - 1);
    cout << "Начальный вид маски: " << bitset<n>(mask) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & mask) >> (n - i));
        mask = mask >> 1;
    }
    cout << endl;

    return 0;
}