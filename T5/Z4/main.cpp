#include <iostream>
#include <algorithm>

using namespace std;

int SumaCifara(int a) {
    int suma(0);
    do {
        suma += a%10;
    }while((a/=10) != 0);
    return suma;
}

int main() {
    vector<int> niz; 
    int vel;
    cout << "Unesite velicinu niza: ";
    cin >> vel;
    niz.resize(vel);
    for(int i = 0; i < vel; i++) {
        cout << "Unesite " << i + 1 << ". element niza: ";
        cin >> niz[i];
    }
    cout << "Najveci element niza: " << *max_element(niz.begin(), niz.end());
    cout << "\nNajmanji element se pojavljuje " << count(niz.begin(), niz.end(), *min_element(niz.begin(), niz.end())) << " puta.";
    cout << "\nBroj stepena dvojke u nizu je: " << count_if(niz.begin(), niz.end(), 
    [](int a) -> bool {return !(a&(a-1));});
    cout << "\nNajmanju sumu cifara ima " << *min_element(niz.begin(), niz.end(),
    [](int x, int y) -> bool { return SumaCifara(x) < SumaCifara(y);})<< ".";
    vector<int> niz2(vel); 
    vector<int>::iterator k(remove_copy_if(niz.begin(), niz.end(), niz2.begin(), 
    [](int a) -> bool {return a >= 10 && a < 100;}));
    cout << "\nNiz bez dvocifrenih brojeva glasi: ";
    for(vector<int>::iterator p = niz2.begin(); p != k; p++) 
        cout << *p << " ";
    
    return 0;
}

