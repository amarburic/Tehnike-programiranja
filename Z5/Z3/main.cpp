#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <utility>

using namespace std;

class FourierovRed {
    int n;
    double t;
    double* a = nullptr, *b = nullptr;
    static constexpr double PI = atan(1) * 4;
    static double Trapezno(function<double(double)> trig,
        double p, double q, function<double(double)> f, int m, int k);
public:
    FourierovRed(double t, initializer_list<double> _a, initializer_list<double> _b);
    FourierovRed(int n, double t, function<double(int)> f_a, function<double(int)> f_b);
    FourierovRed(int n, double p, double q, function<double(double)> f, int m);
    FourierovRed(const FourierovRed& f);
    FourierovRed(FourierovRed&& f);
    FourierovRed& operator = (const FourierovRed& f);
    FourierovRed& operator = (FourierovRed&& f);
    double operator () (double x) const;
    pair<double, double> operator [] (int k) const;
    pair<double&, double&> operator [] (int k);
    ~FourierovRed() { delete[] a; delete[] b;}
};

FourierovRed::FourierovRed(double t, initializer_list<double> _a, initializer_list<double> _b)
: n(max(int(_a.size() - 1), int(_b.size()))), t(t) {
    try {
        a = new double[n + 1]{};
        b = new double[n + 1]{};
    } catch(...) {
        delete[] a; delete[] b;
        throw;
    }
    copy(_a.begin(), _a.end(), a);
    copy(_b.begin(), _b.end(), b + 1);
}

FourierovRed::FourierovRed(int n, double t, function<double(int)> f_a, function<double(int)> f_b)
: n(n), t(t) {
    if(n < 1) throw domain_error("Stepen mora biti pozitivan");
    try {
        a = new double[n + 1]{};
        b = new double[n + 1]{};
    } catch(...) {
        delete[] a; delete[] b;
        throw;
    }
    a[0] = f_a(0);
    for(int i = 1; i <= n; i++) a[i] = f_a(i), b[i] = f_b(i);
}

FourierovRed::FourierovRed(int n, double p, double q, function<double(double)> f, int m) : n(n), t(q - p) {
    if(n < 1) throw domain_error("Stepen mora biti pozitivan");
    if(m < 1) throw domain_error("Broj podintervala mora biti pozitivan");
    if(p >= q) throw range_error("Neispravan interval");
    try {
        a = new double[n + 1]{};
        b = new double[n + 1]{};
    } catch(...) {
        delete[] a; delete[] b;
        throw;
    }
    a[0] = Trapezno([](double x) { return cos(x); }, p, q, f, m, 0);
    for(int i = 1; i <= n; i++)
        a[i] = Trapezno([](double x) { return cos(x); }, p, q, f, m, i),
        b[i] = Trapezno([](double x) { return sin(x); }, p, q, f, m, i);
}

FourierovRed::FourierovRed(const FourierovRed& f) : n(f.n), t(f.t) {
    if(this != &f) {
        try {
            a = new double[n + 1]{};
            b = new double[n + 1]{};
        } catch(...) {
            delete[] a; delete[] b;
            throw;
        }
        copy(f.a, f.a + n + 1, a);
        copy(f.b, f.b + n + 1, b);
    }
}

FourierovRed::FourierovRed(FourierovRed&& f) : n(f.n), t(f.t) {
    if(this != &f) {
        a = f.a; b = f.b;
        f.a = nullptr; f.b = nullptr;
    }
}
FourierovRed& FourierovRed::operator = (const FourierovRed& f) {
    if(f.n <= n) {
        copy(f.a, f.a + f.n + 1, a);
        copy(f.b, f.b + f.n + 1, b);
    }
    else {
        delete[] a; delete[] b;
        try {
            a = new double[n + 1]{};
            b = new double[n + 1]{};
        } catch(...) {
            delete[] a; delete[] b;
            throw;
        }
        copy(f.a, f.a + n + 1, a);
        copy(f.b, f.b + n + 1, b);
    }
    n = f.n; t = f.t;
    return *this;
}
FourierovRed& FourierovRed::operator = (FourierovRed&& f) {
    if(this != &f) {
        delete[] a; delete[] b;
        a = f.a; b = f.b;
        n = f.n; t = f.t;
        f.a = nullptr; f.b = nullptr;
    }
    return *this;
}

double FourierovRed::Trapezno(function<double(double)> trig,
        double p, double q, function<double(double)> f, int m, int k) {
    double koef(0), t(q - p);
    for(int i = 1; i < m; i++)
        koef += f(p + i * t / m) * trig(2 * k * PI * (p / t + double(i) / m));
    koef *= 2. / m;
    koef += ((f(p) + f(q)) / m) * cos(2 * k * PI * p / t);
    return koef;
}

double FourierovRed::operator () (double x) const {
    double vrijednost(a[0] / 2);
    for(int i = 1; i <= n; i++)
        vrijednost += a[i] * cos(2 * i * PI * x / t) + b[i] * sin(2 * i * PI * x / t );
    return vrijednost;
}

pair<double, double> FourierovRed::operator [] (int k) const {
    if(k < 0 || k > n) throw range_error("Neispravan indeks");
    return make_pair(a[k], k == 0 ? 0 : b[k]);
}

pair<double&, double&> FourierovRed::operator [] (int k) {
    if(k < 0 || k > n) throw range_error("Neispravan indeks");
    b[0] = 0;
    return pair<double&, double&>(a[k], b[k]);
}

int main() {

}
