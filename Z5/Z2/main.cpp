#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <utility>
#include <sstream>

using namespace std;

class VelikiBroj {
    vector<int> cifre;
    int broj;
public:
    VelikiBroj(int broj) : broj(broj) {};
    VelikiBroj(string broj) {
        stringstream ss(broj);
        ss >> this->broj;
    }
    friend int operator + (const VelikiBroj& l, const VelikiBroj& r);
    /*

    VelikiBroj& operator += (const VelikiBroj& r);
    VelikiBroj& operator -= (const VelikiBroj& r);
    VelikiBroj& operator *= (const VelikiBroj& r);
    VelikiBroj& operator /= (const VelikiBroj& r);
    VelikiBroj& operator %= (const VelikiBroj& r);
    VelikiBroj operator + ();
    VelikiBroj operator - ();
    VelikiBroj operator ++ (int);
    VelikiBroj operator -- (int);
    VelikiBroj& operator ++ ();
    VelikiBroj& operator -- ();

    friend VelikiBroj operator + (const VelikiBroj& l, const VelikiBroj& r);
    friend VelikiBroj operator - (const VelikiBroj& l, const VelikiBroj& r);
    friend VelikiBroj operator * (const VelikiBroj& l, const VelikiBroj& r);
    friend VelikiBroj operator / (const VelikiBroj& l, const VelikiBroj& r);
    friend VelikiBroj operator % (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator == (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator != (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator < (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator > (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator <= (const VelikiBroj& l, const VelikiBroj& r);
    friend bool operator >= (const VelikiBroj& l, const VelikiBroj& r);
    friend istream& operator << (ostream& l, const VelikiBroj& r);
    friend ostream& operator >> (ostream& l, VelikiBroj&);
    */
};

int operator + (const VelikiBroj& l, const VelikiBroj& r) {
    return l.broj + r.broj;
}

void foo(const char*) {}

int main() {
    cout << VelikiBroj(1) + "1";

}