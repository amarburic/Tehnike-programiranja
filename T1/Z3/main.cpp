#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


int main() {
    cout << "+---------+----------+----------+" << endl;
    cout << "| Brojevi | Kvadrati | Korijeni |" << endl;
    cout << "+---------+----------+----------+" << endl;
    for(int i = 1; i <= 100; i++)
        cout << "|" << left << setw(9) << i << "|" << right << setw(10) << i*i 
        << "|" << setw(10) << setprecision(3) << fixed << sqrt(i) << "|" << endl;
    cout << "+---------+----------+----------+" << endl;
    return 0;
}
