#include <iostream>
#include <algorithm>

using namespace std;

bool StepenDvojke(int a) {
    return !(a&(a-1));      //Trik sa MLTI-a. Ako je stepen dvojke samo je jedan bit 1, svi ostali 0. 
}

bool NajmanjaSumaCifara(int x, int y) {
    int suma_x(0), suma_y(0);
    do {
        suma_x += x%10;
    } while((x/=10) != 0);
    do {
        suma_y += y%10;
    } while((y/=10) != 0);
    return suma_x < suma_y;
}

bool jeDvocifren(int a) {
    return a >= 10 && a < 100;
}

int main() {
    int niz[100], vel;
    cout << "Unesite velicinu niza[max 100]: ";
    cin >> vel;
    for(int i = 0; i < vel; i++) {
        cout << "Unesite " << i + 1 << ". element niza: ";
        cin >> niz[i];
    }
    cout << "Najveci element niza: " << *max_element(niz, niz + vel);
    cout << "\nNajmanji element se pojavljuje " << count(niz, niz + vel, *min_element(niz, niz + vel)) << " puta.";
    cout << "\nBroj stepena dvojke u nizu je: " << count_if(niz, niz + vel, StepenDvojke);
    cout << "\nNajmanju sumu cifara ima " << *min_element(niz, niz + vel, NajmanjaSumaCifara)<< ".";
    int niz2[100], *p(niz2), *k(remove_copy_if(niz, niz + vel, niz2, jeDvocifren));
    cout << "\nNiz bez dvocifrenih brojeva glasi: ";
    for(; p != k; p++) 
        cout << *p << " ";
    return 0;
}

