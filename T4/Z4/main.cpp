#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename NumTip>
void UnosBroja(string prompt, string greska, NumTip &x) {
    while(cout << prompt, !(cin >> x) || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << greska;
    }
}

int main() {
    double x;
    int n;
    UnosBroja("Unesi realan broj x: ", "Neispravan unos\n", x);
    UnosBroja("Unesi cijeli broj n: ", "Neispravan unos\n", n);
    cout << "x^n = " << pow(x, n);
    return 0;
}

