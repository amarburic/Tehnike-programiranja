#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cmath>

using namespace std;

class Sat {
int sati, minute, sekunde;
public:
    void Postavi(int sati, int minute, int sekunde);
    void Sljedeci() { PomjeriZa(1); };
    void Prethodni() { PomjeriZa(-1); };
    void PomjeriZa(int pomak);
    int DajSate() const { return sati; }
    int DajMinute() const { return minute; }
    int DajSekunde() const { return sekunde; }
    void Ispisi() const;
    
    friend int BrojSekundiIzmedju(const Sat&, const Sat&);
};

int BrojSekundiIzmedju(const Sat &s1, const Sat &s2) {
    int s1_sekundi(s1.DajSate() * 3600 + s1.DajMinute() * 60 + s1.DajSekunde()), 
    s2_sekundi(s2.DajSate() * 3600 + s2.DajMinute() * 60 + s2.DajSekunde());
    return s1_sekundi - s2_sekundi;
}

void Sat::Postavi(int sati, int minute, int sekunde) {
    if(sekunde < 0 || sekunde >= 60 || minute < 0 || minute >= 60 || sati < 0 || sati >= 24)
        throw domain_error("Neispravni parametri!");
    Sat::sati = sati;
    Sat::minute = minute;
    Sat::sekunde = sekunde;
}

void Sat::Ispisi() const {
    cout << setw(2) << setfill('0') << sati << ":"
    << setw(2) << setfill('0') << minute << ":"
    << setw(2) << setfill('0') << sekunde;
}

void Sat::PomjeriZa(int pomak) {
    sekunde += pomak;
    minute += floor(sekunde / 60.);
    sekunde %= 60;
    if(sekunde < 0) sekunde = 60 + sekunde;
    sati += floor(minute / 60.); 
    minute %= 60;
    if(minute < 0) minute = 60 + minute;
    sati %= 24;
    if(sati < 0) sati = 24 + sati;
}

int main() {
    /* testni program koji upotrebljava sve 
elemente  interfejsa  napisane  klase */
    return 0;
}

