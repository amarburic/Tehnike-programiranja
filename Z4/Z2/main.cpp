#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <memory>
#define EPSILON 0.0000001

using namespace std;

struct Tacka {
 double x, y;
};

enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};

class NepreklapajuciPravougaonik {
    Tacka t_min, t_max;
    NepreklapajuciPravougaonik* prethodni;
    static NepreklapajuciPravougaonik* posljednji;
    void TestPreklapanja(const Tacka &t_min, const Tacka &t_max);
public:
    NepreklapajuciPravougaonik(const Tacka &t1, const Tacka &t2) {
        Postavi(t1, t2); prethodni = posljednji; posljednji = this;
    }
    NepreklapajuciPravougaonik(const NepreklapajuciPravougaonik &p) = delete;
    NepreklapajuciPravougaonik& operator = (const NepreklapajuciPravougaonik &p) = delete;
    ~NepreklapajuciPravougaonik();
    void Postavi(const Tacka &t1, const Tacka &t2);
    void Postavi(Pozicija p, const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const;
    Tacka DajCentar() const { return {(t_max.x + t_min.x) / 2, (t_max.y + t_min.y) / 2}; }
    double DajHorizontalnu() const { return t_max.x - t_min.x; }
    double DajVertikalnu() const { return t_max.y - t_min.y; }
    double DajObim() const { return 2 * (DajHorizontalnu() + DajVertikalnu()); }
    double DajPovrsinu() const { return DajHorizontalnu() * DajVertikalnu(); }
    void Transliraj(double delta_x, double delta_y);
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const {
        cout << "{{" << t_min.x << "," << t_max.y << "},{"
        << t_max.x << "," << t_min.y << "}}";
    }
    friend bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
    friend bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2);
};

NepreklapajuciPravougaonik* NepreklapajuciPravougaonik::posljednji = nullptr;

void NepreklapajuciPravougaonik::TestPreklapanja(const Tacka &t_min, const Tacka &t_max) {
    auto it(posljednji);
    while(it) {
        if(max(t_min.x, it->t_min.x) < min(t_max.x, it->t_max.x) &&
        max(t_min.y, it->t_min.y) < min(t_max.y, it->t_max.y))
            throw logic_error("Nedozvoljeno preklapanje");
        it = it->prethodni;
    }
}

NepreklapajuciPravougaonik::~NepreklapajuciPravougaonik() {
    auto it(posljednji);
    if(it == this)
        posljednji = prethodni;
    else {
        while(it->prethodni != this)
            it = it->prethodni;
        it->prethodni = prethodni;
    }
}

void NepreklapajuciPravougaonik::Postavi(const Tacka &t1, const Tacka &t2) {
    Tacka temp_min({min(t1.x, t2.x), min(t1.y, t2.y)}),
    temp_max({max(t1.x, t2.x), max(t1.y, t2.y)});
    TestPreklapanja(temp_min, temp_max);
    t_min = temp_min; t_max = temp_max;
}

void NepreklapajuciPravougaonik::Postavi(Pozicija p, const Tacka &t) {
    auto temp_max(t_max), temp_min(t_min);
    if(p == GoreDesno) temp_max = t;
    if(p == DoljeLijevo) t_min = t;
    if(p == GoreLijevo) temp_min.x = t.x, temp_max.y = t.y;
    if(p == DoljeDesno) temp_max.x = t.x, temp_min.y = t.y;
    Postavi(temp_min, temp_max);
}

void NepreklapajuciPravougaonik::Centriraj(const Tacka &t) {
    double hor(DajHorizontalnu()), vert(DajVertikalnu());
    Tacka temp_min{t.x - hor / 2, t.y - vert / 2}, temp_max{t.x + hor / 2, t.y + vert / 2};
    Postavi(temp_min, temp_max);
}

Tacka NepreklapajuciPravougaonik::DajTjeme(Pozicija p) const {
    if(p == GoreLijevo) return {t_min.x, t_max.y};
    if(p == GoreDesno) return t_max;
    if(p == DoljeDesno) return {t_max.x, t_min.y};
    if(p == DoljeLijevo) return t_min;
}

void NepreklapajuciPravougaonik::Transliraj(double delta_x, double delta_y) {
    auto temp_max(t_max), temp_min(t_min);
    temp_min.x += delta_x; temp_min.y += delta_y;
    temp_max.x += delta_x; temp_max.y += delta_y;
    Postavi(temp_min, temp_max);
}

void NepreklapajuciPravougaonik::Rotiraj(const Tacka &t, Smjer s) {
    Tacka temp_min, temp_max;
    double sinus(s == Nalijevo ? 1 : -1);
    temp_min.x = t.x - (t_min.y - t.y) * sinus;
    temp_min.y = t.y + (t_min.x - t.x) * sinus;
    temp_max.x = t.x - (t_max.y - t.y) * sinus;
    temp_max.y = t.y + (t_max.x - t.x) * sinus;
    Postavi(temp_min, temp_max);
}

bool DaLiSePoklapaju(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2) {
    return fabs(p1.t_min.x - p2.t_min.x) <= EPSILON && fabs(p1.t_max.x - p2.t_max.x) <= EPSILON
    && fabs(p1.t_min.y - p2.t_min.y) <= EPSILON && fabs(p1.t_max.y - p2.t_max.y) <= EPSILON;
}

bool DaLiSuPodudarni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2) {
    return (fabs(p1.DajHorizontalnu() - p2.DajHorizontalnu()) <= EPSILON &&
    fabs(p1.DajVertikalnu() - p2.DajVertikalnu()) <= EPSILON) ||
    (fabs(p1.DajHorizontalnu() - p2.DajVertikalnu()) <= EPSILON &&
    fabs(p1.DajVertikalnu() - p2.DajHorizontalnu()) <= EPSILON);
}

bool DaLiSuSlicni(const NepreklapajuciPravougaonik &p1, const NepreklapajuciPravougaonik &p2) {
    return fabs(p1.DajHorizontalnu() / p2.DajHorizontalnu()
    - p1.DajVertikalnu() / p2.DajVertikalnu()) <= EPSILON ||
    fabs(p1.DajHorizontalnu() / p2.DajVertikalnu()
    - p1.DajVertikalnu() / p2.DajHorizontalnu()) <= EPSILON;
}

int main() {
    int n;
    cout << "Unesite n: ";
    cin >> n;
    vector<shared_ptr<NepreklapajuciPravougaonik>> niz;
    for(int i = 0; i < n; i++) {
        bool uspjelo(false);
        double x1, y1, x2, y2;
        while(!uspjelo) {
            cout << "Unesite 1. tjeme pravougaonika " << i + 1 << ": ";
            cin >> x1 >> y1;
            cout << "Unesite 2. tjeme pravougaonika " << i + 1 << ": ";
            cin >> x2 >> y2;
            try {
                auto s = make_shared<NepreklapajuciPravougaonik>(Tacka{x1, y1}, Tacka{x2, y2});
                niz.push_back(s);
                uspjelo = true;
            } catch(logic_error l) {
                cout << "GRESKA: " << l.what() << "! Ponovite unos: " << endl;
            }
        }
    }
    sort(niz.begin(), niz.end(), [](shared_ptr<NepreklapajuciPravougaonik> p1, shared_ptr<NepreklapajuciPravougaonik> p2) { return p1->DajPovrsinu() < p2->DajPovrsinu(); });
    cout << "Ispis pravougaonika nakon sortiranja:" << endl;
    for_each(niz.begin(), niz.end(), [](shared_ptr<NepreklapajuciPravougaonik> p) { p->Ispisi(); cout << endl; });
    cout << "Podudarni pravougaonici: " << endl;
    bool ima_podudarnih(false);
    for(int i = 0; i < niz.size() - 1; i++) 
        for(int j = i + 1; j < niz.size(); j++)
            if(DaLiSuPodudarni(*niz[i], *niz[j])) {
                niz[i]->Ispisi(); cout << " i "; niz[j]->Ispisi(); cout << endl;
                ima_podudarnih++;
            }
    if(!ima_podudarnih)
        cout << "Nema podudarnih pravougaonika.";
    return 0;
}
