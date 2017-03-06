#include <iostream>
#include <cmath>

using namespace std;

class Ugao {
    double radijani;
    static constexpr double PI = 4 * atan(1);
    static constexpr double STEP_U_RAD_KONST = 2 * PI / 360;
    static constexpr double RAD_U_STEP_KONST = 1 / STEP_U_RAD_KONST;
    static double StepenURadijan(int stepeni, int minute, int sekunde) {
        return stepeni * STEP_U_RAD_KONST + minute * STEP_U_RAD_KONST / 60 + sekunde * STEP_U_RAD_KONST / 3600;
    }
    static double DecimalniDio(double a) {
        return a - int(a);
    }
public:
    Ugao( double radijani = 0) {
        if(radijani < 0) {
            radijani -= int(radijani / (2 * PI)) * 2 * PI;
            radijani = 2 * PI + radijani;
        } 
        else if(radijani != 2 * PI) radijani -= int(radijani / (2 * PI)) * 2 * PI;
        this->radijani = radijani;
    }; 
    Ugao( int stepeni,  int minute,  int sekunde) {
        *this = Ugao(StepenURadijan(stepeni, minute, sekunde));
    };
    void Postavi( double radijani) {
        *this = Ugao(radijani);
    };  
    void Postavi( int stepeni,  int minute,  int sekunde) {
        *this = Ugao(StepenURadijan(stepeni, minute, sekunde));
    }; 
    double DajRadijane()  const { return radijani; };
    void OcitajKlasicneJedinice( int & stepeni,  int & minute,  int & sekunde) {
        stepeni = DajStepene();
        minute = DajMinute();
        sekunde = DajSekunde();
    }; 
    int DajStepene()  const { return radijani * RAD_U_STEP_KONST; }; 
    int DajMinute()  const { return DecimalniDio(radijani * RAD_U_STEP_KONST) * 60; }; 
    int DajSekunde()  const { return int(DecimalniDio(radijani * RAD_U_STEP_KONST) * 3600) % 60; }; 
    void Ispisi()  const { cout << radijani << endl; };
    void IspisiKlasicno ()  const { cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec" << endl; }; 
    Ugao  & SaberiSa( const Ugao  & u) { return *this = Ugao(radijani + u.DajRadijane()); }; 
    Ugao  & PomnoziSa( double x) { return *this = Ugao(radijani * x); }; 
    friend Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2); 
    friend Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x);
};

Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2) {
    return Ugao(u1.radijani +  u2.radijani);
}

Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x) {
    return Ugao(u.radijani * x);
}

int main() {
    Ugao u1(3.15), u2(359, 24, 36);
    u1.Ispisi();
    u2.IspisiKlasicno();
    u1.Postavi(u2.DajRadijane());
    u1.Ispisi();
    u2.Postavi(u1.DajStepene(), u1.DajMinute(), u1.DajSekunde());
    u2.IspisiKlasicno();
    u1.SaberiSa(u2).Ispisi();
    u2.PomnoziSa(2).Ispisi();
    ZbirUglova(2, 3).Ispisi();
    ProduktUglaSaBrojem(2, 3).Ispisi();
    return 0;
}