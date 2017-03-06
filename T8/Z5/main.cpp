#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct Cvor {
    T element;
    shared_ptr<Cvor<T>> veza; 
};

int main() {
    double a;
    int broj_elemenata(0);
    shared_ptr<Cvor<double>> pocetak(nullptr), prethodni;
    while(cin >> a, a != 0) {
       shared_ptr<Cvor<double>> novi(new Cvor<double>);
       novi->element = a;
       novi->veza = nullptr;
       if(!pocetak) pocetak = novi;
       else prethodni->veza = novi;
       prethodni = novi;
       broj_elemenata++;
    }
    shared_ptr<Cvor<double>> trenutni(pocetak);
    double suma(0);
    while(trenutni) {
        suma += trenutni->element;
        trenutni = trenutni->veza;
    }
    double aritmeticka_sredina(suma / broj_elemenata);
    int brojac(0);
    trenutni = pocetak;
    while(trenutni) {
        if(trenutni->element > aritmeticka_sredina) brojac++;
        trenutni = trenutni->veza;
    }
    cout << brojac;     
    return 0;
}

