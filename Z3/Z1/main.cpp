#include <iostream>
#include <functional>
#include <cmath>

using namespace std;

template <typename T>
auto ProslijediLijevo(function<T(T, T, T)> f) {
    return f;
}

template <typename T>
function<T(function<T(T, T, T)>)> ProslijediDesno(T a, T b, T c) {
    return [a, b, c](function<T(T, T, T)> f) { return f(a, b, c); };
}

template <typename T>
function<function<function<function<T(T)>(function<T(T, T)>)>(T, T)>(T)> MonstrumFunkcija(function<T(T, T, T)> f) {
        return [f] (T x) {
            return [f, x] (T y, T z) {
                return [f, x, y, z] (function<T(T, T)> g) {
                    return [f, x, y, z, g] (T r) {
                        return g(f(x, y, z), r);
                    };
                };
            };
        };
}

double ZbirSinusa(double x, double y, double z) { return sin(x) + sin(y) + sin(z); }


int main() {
    double x, y, z, r;
    cout << "Unesite x y z: ";
    cin >> x >> y >> z;
    cout << "Unesite faktor skaliranja: ";
    cin >> r;
    cout << "Prosljedjivanje ulijevo: " << ProslijediLijevo<double>(ZbirSinusa)(x, y, z) << endl;
    cout << "Prosljedjivanje udesno: " << ProslijediDesno<double>(x, y, z)
    ([](double x, double y, double z) { return cos(x) * cos(y) * cos(z); }) << endl;
    cout << "Monstrum: " << MonstrumFunkcija<double>(ZbirSinusa)(x)(y, z)
    ([](double x, double r) { return x * r; })(r) << endl;
    return 0; 
}

