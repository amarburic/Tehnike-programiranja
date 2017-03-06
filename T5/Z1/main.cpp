#include <iostream>

using namespace std;

int main() {
    char unos[50], *p(unos);
    cout << "Unesite recenicu: ";
    cin.getline(unos, sizeof unos);
    while(*p != ' ' && *p != '\0')p++;
    while(*p == ' ' && *p != '\0')p++;
    cout << "Unesena recenica bez prve rijeci glasi: " << p;
    return 0;
}

