#include <iostream>

using namespace std;

enum Dani {Ponedjeljak, Utorak, Srijeda, Cetvrtak, Petak, Subota, Nedjelja};

Dani& operator ++ (Dani& d) {
    return d = Dani(((int)d + 1) % 7);
}

Dani operator ++ (Dani& d, int) {
    auto d2(d); ++d;
    return d2;
}

ostream& operator << (ostream& tok, const Dani& d) {
    const char* dani[]{"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
    tok << dani[d];
    return tok;
}

int main() {
    for(Dani d = Ponedjeljak; d <= Petak; d++) 
        cout << d << endl;
    for(Dani d = Ponedjeljak; d <= Nedjelja; d++) { 
        cout << d << endl;
        if(d == Nedjelja) break;
    }
    return 0;
}

