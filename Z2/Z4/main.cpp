#include <iostream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename Tip>
int** AlocirajFragmentirano(const vector<Tip> &v, int koliko_puta) {
    if(v.empty()) throw "Prazan vektor!";
    for(auto i: v)
        if(i <= 0) throw domain_error("Neispravan vektor!");
    if(koliko_puta <= 0) throw domain_error("Neispravan broj ponavljanja!");
    int** matrica(new int*[v.size() * koliko_puta]);
    for(unsigned int i = 0; i < v.size() * koliko_puta; i++) matrica[i] = nullptr;
    try {
        for(unsigned int i = 0; i < v.size() * koliko_puta; i++)
            matrica[i] = new int[v[i % v.size()]];
    } catch(...) {
        for(unsigned int i = 0; i < v.size() * koliko_puta; i++) delete[] matrica[i];
        delete[] matrica;
        throw;
    }
    int maksimalni(*max_element(v.begin(), v.end()));
    for(int k = 0; k < koliko_puta; k++)
        for(unsigned int i = 0; i < v.size(); i++)
            for(unsigned int j = 0; j < v[i]; j++)
                matrica[i + k * v.size()][j] = maksimalni - v[i] + j + 1;
    return matrica;
}

template <typename Tip>
int** AlocirajKontinualno(const vector<Tip> &v, int koliko_puta) {
    if(v.empty()) throw "Prazan vektor!";
    for(auto i: v)
        if(i <= 0) throw domain_error("Neispravan vektor!");
    if(koliko_puta <= 0) throw domain_error("Neispravan broj ponavljanja!");
    int** matrica(new int*[v.size() * koliko_puta]);
    unsigned int velicina(accumulate(v.begin(), v.end(), Tip()) * koliko_puta);
    matrica[0] = nullptr;
    try {
        matrica[0] = new int[velicina];
    } catch(...) {
        delete[] matrica;
        throw;
    }
    for(unsigned int i = 1; i < v.size() * koliko_puta; i++)
        matrica[i] = matrica[i - 1] + v[(i - 1) % v.size()];
    for(int k = 0; k < koliko_puta; k++)
        for(unsigned int i = 0; i < v.size(); i++)
            for(unsigned int j = 0; j < v[i]; j++)
                matrica[i + k * v.size()][j] = v[i] - j;
    return matrica;
}

template <typename Tip>
int** KreirajPoUvrnutomPravilu(vector<Tip> &v, int koliko_puta, bool fragmentirano = true) {
    if(v.empty()) throw "Prazan vektor!";
    int period(0);
    for(unsigned int i = 1; i < v.size(); i++) {
        bool je_period(true);
        for(unsigned int j = 0; j < v.size(); j++)
            if(j + i < v.size() && v[j] != v[j + i]) {
                je_period = false;
                break;
            }
        if(je_period) {
            period = i;
            break;
        }
    }
    if(period != 0)
        v.erase(v.begin() + period, v.end());
    else {
        Tip maksimalni = *max_element(v.begin(), v.end()) + 1;
        for(auto &i: v)
            i = maksimalni - i;
    }
    if(fragmentirano) return AlocirajFragmentirano(v, koliko_puta);
    else return AlocirajKontinualno(v, koliko_puta);
}

int main(){
    int n;
    cout << "Unesite broj elemenata vektora: ";
    cin >> n;
    vector<int> v(n);
    cout << "Unesite elemente vektora: ";
    for(int &i: v)
        cin >> i;
    cout << "Unesite broj ponavljanja: ";
    int koliko_puta;
    cin >> koliko_puta;
    cout << "Odaberite alokaciju: 1 - fragmentirana, 0 - kontinualna: ";
    bool fragmentirano;
    cin >> fragmentirano;
    try {
        int** matrica(KreirajPoUvrnutomPravilu(v, koliko_puta, fragmentirano));
        cout << "Dinamicki alocirana matrica: " << endl;
        for(int k = 0; k < koliko_puta; k++)
            for(int i = 0; i < v.size(); i++){
                for(int j = 0; j < v[i]; j++)
                    cout << left << setw(3) << matrica[i + k * v.size()][j];
                cout << endl;
            }
        if(fragmentirano)
            for(int i = 0; i < v.size() * koliko_puta; i++) delete[] matrica[i];
        else delete[] matrica[0];
        delete[] matrica;
    } catch(domain_error e) {
        cout << "Izuzetak: " << e.what() << endl;
    } catch(const char* poruka) {
        cout << "Izuzetak: " << poruka << endl;
    }
    return 0;
}