#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    cout << "Unesite broj elemenata: ";
    cin.get();
    transform(std::istream_iterator<double>(cin), std::istream_iterator<double>(), 
    ostream_iterator<double>(cout, " "), bind(divides<double>(), 1, placeholders::_1)); 
    return 0;
}

//Da nema unosa broja elemenata main bi bio tacno jedna naredba :)
//Radi za beskonacno mnogo elemenata dokle god se unose u jednom redu