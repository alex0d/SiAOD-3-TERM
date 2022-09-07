#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <bitset>
#include <algorithm>
#include <chrono>

using namespace std;

void create_file() {
    default_random_engine generator(time(nullptr));
    uniform_int_distribution<> size_distribution(1, 10'000'000);

    int* set = new int[9'000'000];

    for (int i = 0; i < 9'000'000; i++) {
        set[i] = i + 1'000'000;
    }

    shuffle(set, set + 9'000'000, generator);

    int size = size_distribution(generator);

    ofstream fout;
    fout.open("unsorted.txt");

    for (int i = 0; i < size; i++) {
        fout << set[i] << endl;
    }

    fout.close();
    delete[] set;
}

int main() {
//    create_file(); // Uncomment to generate a new input file
    auto start = chrono::steady_clock::now();

    ifstream fin;
    fin.open("unsorted.txt");

    int x;
    bitset<9'000'000> mask = 0;

    while (fin >> x) {
        mask.set(x - 1'000'000);
    }
    fin.close();

    ofstream fout;
    fout.open("sorted.txt");

    for (int i = 0; i < 9'000'000; i++) {
        if (mask[i]) {
            fout << i + 1'000'000 << endl;
        }
    }
    fout.close();

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    cout << sizeof(mask) << " bytes" << endl;

    return 0;
}