#include <iostream>
#include <cmath>

using namespace std;


class Ugao {
    double stepeni, minute, sekunde;
    static constexpr double PI = 4 * atan(1);
    static constexpr int KRUG = 360;
    static constexpr double STEP_U_RAD_KONST = 2 * PI / KRUG;
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
        *this = Ugao(radijani * RAD_U_STEP_KONST, radijani * RAD_U_STEP_KONST / 60, int(radijani * RAD_U_STEP_KONST / 3600) % 60);
    }; 
    Ugao( int stepeni,  int minute,  int sekunde) {
        stepeni %= KRUG;
        if(stepeni < 0 ) stepeni = KRUG + stepeni;
        this->stepeni = stepeni;
        this->minute = minute;
        this->sekunde = sekunde;
    };
    void Postavi( double radijani) {
        *this = Ugao(radijani);
    };  
    void Postavi( int stepeni,  int minute,  int sekunde) {
        *this = Ugao(stepeni, minute, sekunde);
    }; 
    double DajRadijane()  const { return StepenURadijan(stepeni, minute, sekunde); };
    void OcitajKlasicneJedinice( int & stepeni,  int & minute,  int & sekunde) {
        stepeni = DajStepene();
        minute = DajMinute();
        sekunde = DajSekunde();
    }; 
    int DajStepene()  const { return stepeni; }; 
    int DajMinute()  const { return minute; }; 
    int DajSekunde()  const { return sekunde; }; 
    void Ispisi()  const { cout << StepenURadijan(stepeni, minute, sekunde) << endl; };
    void IspisiKlasicno ()  const { cout << DajStepene() << "deg " << DajMinute() << "min " << DajSekunde() << "sec" << endl; }; 
    Ugao  & SaberiSa( const Ugao  & u) { return *this = Ugao(StepenURadijan(stepeni, minute, sekunde) + u.DajRadijane()); }; 
    Ugao  & PomnoziSa( double x) { return *this = Ugao(StepenURadijan(stepeni, minute, sekunde) * x); }; 
    friend Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2); 
    friend Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x);
};

Ugao ZbirUglova( const Ugao  & u1,  const Ugao  & u2) {
    return Ugao(u1.DajRadijane() +  u2.DajRadijane());
}

Ugao ProduktUglaSaBrojem( const Ugao  & u,  double x) {
    return Ugao(u.DajRadijane() * x);
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
