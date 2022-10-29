#include <bits/stdc++.h>

using namespace std;
#include "../Matrix.cpp"

int main() {
    // Print the first 15 elements of the fibonacci sequence
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377

    mat<2, 2> fib({0, 1, 1, 1});
    for (int i = 0; i < 15; i++)
        cout << "fib(" << i << "): " << pot(fib, i)(1, 0) << "\n";

    return 0;
}
