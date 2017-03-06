#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

using namespace std;

class Sat {
    int sekunde;
public:
    void Postavi(int sati, int minute, int sekunde);
    void Sljedeci() { PomjeriZa(1); };
    void Prethodni() { PomjeriZa(-1); };
    void PomjeriZa(int pomak);
    int DajSate() const { return sekunde / 3600; }
    int DajMinute() const { return (sekunde / 60) % 60; }
    int DajSekunde() const { return sekunde % 60; }
    void Ispisi() const;
    friend int BrojSekundiIzmedju(const Sat&, const Sat&);

};

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) {
    return s1.DajSekunde() + s1.DajMinute() * 60 + s1.DajSate() * 3600 
    - s2.DajSekunde() - s2.DajMinute() * 60 - s2.DajSate() * 3600;
}

void Sat::Postavi(int sati, int minute, int sekunde) {
    if(sekunde < 0 || sekunde >= 60 || minute < 0 || minute >= 60 || sati < 0 || sati >= 24)
        throw domain_error("Neispravni parametri");
    Sat::sekunde = sati * 3600 + minute * 60 + sekunde;
}

void Sat::Ispisi() const {
    cout << setw(2) << setfill('0') << (sekunde / 3600) << ":"
    << setw(2) << setfill('0') << (sekunde / 60) % 60 << ":"
    << setw(2) << setfill('0') << sekunde % 60;
}

void Sat::PomjeriZa(int pomak) {
    sekunde += pomak;
    if(sekunde < 0) sekunde = 3600 * 24 + sekunde;
    if(sekunde >= 3600 * 24) sekunde %= 3600 * 24; 
}

int main() {
    
    return 0;
}

