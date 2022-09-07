#include <iostream>

using namespace std;

int main() {
    unsigned char x = 0;
    unsigned char mask = 1;
    x = x | (mask << 6);
    cout << int(x);

    return 0;
}