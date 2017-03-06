#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <utility>

using namespace std;

class FourierovRed {
    double t;
    vector<double> a, b;
    static constexpr double PI = atan(1) * 4;
    static double Trapezno(function<double(double)> trig,
        double p, double q, function<double(double)> f, int m, int k);
public:
    FourierovRed(double t, initializer_list<double> _a, initializer_list<double> _b);
    FourierovRed(int n, double t, function<double(int)> f_a, function<double(int)> f_b);
    FourierovRed(int n, double p, double q, function<double(double)> f, int m);
    FourierovRed(const FourierovRed& f) = default;
    FourierovRed(FourierovRed&& f) = default;
    FourierovRed& operator = (const FourierovRed& f) = default;
    FourierovRed& operator = (FourierovRed&& f) = default;
    double operator () (double x) const;
    pair<double, double> operator [] (int k) const;
    pair<double&, double&> operator [] (int k);
    ~FourierovRed() = default;
};

FourierovRed::FourierovRed(double t, initializer_list<double> _a, initializer_list<double> _b)
: a(_a.begin(), _a.end()), b(_b.begin(), _b.end()), t(t) {
    int n(max(_a.size(), _b.size() + 1));
    a.resize(n); b.resize(n);
    b.insert(b.begin(), 0);
}

FourierovRed::FourierovRed(int n, double t, function<double(int)> f_a, function<double(int)> f_b)
: t(t) {
    if(n < 1) throw domain_error("Stepen mora biti pozitivan");
    a.resize(n + 1); b.resize(n + 1);
    a[0] = f_a(0);
    for(int i = 1; i <= n; i++) a[i] = f_a(i), b[i] = f_b(i);
}

FourierovRed::FourierovRed(int n, double p, double q, function<double(double)> f, int m) : t(q - p) {
    if(n < 1) throw domain_error("Stepen mora biti pozitivan");
    if(m < 1) throw domain_error("Broj podintervala mora biti pozitivan");
    if(p >= q) throw range_error("Neispravan interval");
    a.resize(n + 1); b.resize(n + 1);
    a[0] = Trapezno([](double x) { return cos(x); }, p, q, f, m, 0);
    for(int i = 1; i <= n; i++)
        a[i] = Trapezno([](double x) { return cos(x); }, p, q, f, m, i),
        b[i] = Trapezno([](double x) { return sin(x); }, p, q, f, m, i);
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
    for(int i = 1; i < a.size(); i++)
        vrijednost += a[i] * cos(2 * i * PI * x / t) + b[i] * sin(2 * i * PI * x / t );
    return vrijednost;
}

pair<double, double> FourierovRed::operator [] (int k) const {
    if(k < 0 || k > a.size() - 1) throw range_error("Neispravan indeks");
    return make_pair(a[k], k == 0 ? 0 : b[k]);
}

pair<double&, double&> FourierovRed::operator [] (int k) {
    if(k < 0 || k > a.size() - 1) throw range_error("Neispravan indeks");
    b[0] = 0;
    return pair<double&, double&>(a[k], b[k]);
}

int main() {

}
