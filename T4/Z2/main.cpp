#include <iostream>

using namespace std;

void Cifre(int n, int &c_min, int &c_max){
    c_min = n%10, c_max = n%10;
    while((n/=10) != 0){
        if(n%10 < c_min)
            c_min = n%10;
        if(n%10 > c_max)
            c_max = n%10;
    }
}

int main() {
    int n, c_min, c_max;
    cout << "Unesite broj n: ";
    cin >> n;
    Cifre(n, c_min, c_max);
    cout << "Najmanja cifra broja " << n << " je: " << c_min 
    << ".\nNajveca cifra broja " << n << " je: " << c_max <<".";
    return 0;
}

