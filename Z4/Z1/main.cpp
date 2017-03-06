#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#define EPSILON 0.0000001

using namespace std;

struct Tacka {
 double x, y;
};

enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};

class Pravougaonik {
    Tacka t_min, t_max;
public:
    Pravougaonik(const Tacka &t1, const Tacka &t2) :
    t_min{min(t1.x, t2.x), min(t1.y, t2.y)}, t_max{max(t1.x, t2.x), max(t1.y, t2.y)} {};
    void Postavi(const Tacka &t1, const Tacka &t2) { *this = Pravougaonik(t1, t2); };
    void Postavi(Pozicija p, const Tacka &t);
    void Centriraj(const Tacka &t);
    Tacka DajTjeme(Pozicija p) const;
    Tacka DajCentar() const { return {(t_max.x + t_min.x) / 2, (t_max.y + t_min.y) / 2}; }
    double DajHorizontalnu() const { return t_max.x - t_min.x; }
    double DajVertikalnu() const { return t_max.y - t_min.y; }
    double DajObim() const { return 2 * (DajHorizontalnu() + DajVertikalnu()); }
    double DajPovrsinu() const { return DajHorizontalnu() * DajVertikalnu(); }
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2);
    void Transliraj(double delta_x, double delta_y) {
        t_min.x += delta_x; t_min.y += delta_y;
        t_max.x += delta_x; t_max.y += delta_y;
    }
    void Rotiraj(const Tacka &t, Smjer s);
    void Ispisi() const {
        cout << "{{" << t_min.x << "," << t_max.y << "},{"
        << t_max.x << "," << t_min.y << "}}";
    }
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

void Pravougaonik::Postavi(Pozicija p, const Tacka &t) {
    if(p == GoreDesno) t_max = t;
    if(p == DoljeLijevo) t_min = t;
    if(p == GoreLijevo) t_min.x = t.x, t_max.y = t.y;
    if(p == DoljeDesno) t_max.x = t.x, t_min.y = t.y;
    *this = Pravougaonik(t_min, t_max);
}

void Pravougaonik::Centriraj(const Tacka &t) {
    double hor(DajHorizontalnu()), vert(DajVertikalnu());
    t_min = {t.x - hor / 2, t.y - vert / 2};
    t_max = {t.x + hor / 2, t.y + vert / 2};
}

Tacka Pravougaonik::DajTjeme(Pozicija p) const {
    if(p == GoreLijevo) return {t_min.x, t_max.y};
    if(p == GoreDesno) return t_max;
    if(p == DoljeDesno) return {t_max.x, t_min.y};
    if(p == DoljeLijevo) return t_min;
}

Pravougaonik Pravougaonik::Presjek(const Pravougaonik &p1, const Pravougaonik &p2) {
    if(max(p1.t_min.x, p2.t_min.x) > min(p1.t_max.x, p2.t_max.x) ||
    max(p1.t_min.y, p2.t_min.y) > min(p1.t_max.y, p2.t_max.y))
        throw domain_error("Pravougaonici se ne presjecaju");
    return Pravougaonik({max(p1.t_min.x, p2.t_min.x), max(p1.t_min.y, p2.t_min.y)},
    {min(p1.t_max.x, p2.t_max.x), min(p1.t_max.y, p2.t_max.y)});
}

void Pravougaonik::Rotiraj(const Tacka &t, Smjer s) {
    Tacka temp_min(t_min), temp_max(t_max);
    double sinus(s == Nalijevo ? 1 : -1);
    t_min.x = t.x - (temp_min.y - t.y) * sinus;
    t_min.y = t.y + (temp_min.x - t.x) * sinus;
    t_max.x = t.x - (temp_max.y - t.y) * sinus;
    t_max.y = t.y + (temp_max.x - t.x) * sinus;
    *this = Pravougaonik(t_min, t_max);
}

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
    return fabs(p1.t_min.x - p2.t_min.x) <= EPSILON && fabs(p1.t_max.x - p2.t_max.x) <= EPSILON
    && fabs(p1.t_min.y - p2.t_min.y) <= EPSILON && fabs(p1.t_max.y - p2.t_max.y) <= EPSILON;
}

bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {
    return (fabs(p1.DajHorizontalnu() - p2.DajHorizontalnu()) <= EPSILON &&
    fabs(p1.DajVertikalnu() - p2.DajVertikalnu()) <= EPSILON) ||
    (fabs(p1.DajHorizontalnu() - p2.DajVertikalnu()) <= EPSILON &&
    fabs(p1.DajVertikalnu() - p2.DajHorizontalnu()) <= EPSILON);
}

bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
    return fabs(p1.DajHorizontalnu() / p2.DajHorizontalnu()
    - p1.DajVertikalnu() / p2.DajVertikalnu()) <= EPSILON ||
    fabs(p1.DajHorizontalnu() / p2.DajVertikalnu()
    - p1.DajVertikalnu() / p2.DajHorizontalnu()) <= EPSILON;
}

int main() {
    int n;
    cout << "Unesite n: ";
    cin >> n;
    Pravougaonik **niz(new Pravougaonik*[n]{});
    try {
        for(int i = 0; i < n; i++) {
            double x1, y1, x2, y2;
            cout << "Unesite 1. tjeme pravougaonika " << i + 1 << ": ";
            cin >> x1 >> y1;
            cout << "Unesite 2. tjeme pravougaonika " << i + 1 << ": ";
            cin >> x2 >> y2;
            niz[i] = new Pravougaonik({x1, y1}, {x2, y2});
        }
    } 
    catch(...) {
        for(int i = 0; i < n; i++) 
            delete niz[i];
        delete[] niz;
        throw;
    }
    cout << "Unesite podatke za transliranje (dx dy): ";
    double dx, dy;
    cin >> dx >> dy;
    transform(niz, niz + n, niz,
    [dx, dy](Pravougaonik *p) {
        p->Transliraj(dx, dy);
        p->Rotiraj(p->DajCentar(), Nadesno);
        return p;
    });
    cout << "Pravougaonici, nakon transformacija:" << endl;
    for_each(niz, niz + n, [](Pravougaonik *p) { p->Ispisi(); cout << endl; });
    cout << "Pravougaonik s najvecom povrsinom: ";
    (*max_element(niz, niz + n, [](Pravougaonik *p1, Pravougaonik *p2) {
        return p1->DajPovrsinu() < p2->DajPovrsinu();
    }))->Ispisi();
    for(int i = 0; i < n; i++) delete niz[i];
    delete[] niz
    return 0;
}
