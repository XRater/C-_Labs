#include <iostream>

const int SIZE = 1;

using namespace std;

int main() {
    freopen("in", "w", stdout);
    for (int i = 0; i < SIZE; i++)
    //    cout << (char)(rand() % 200);
        cout << (char)(rand() % 256);
    return 0;
}
