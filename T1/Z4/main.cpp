#include <iostream>

using namespace std;

int main() {
    int n;
    do {
        for(;;) {
            cout << "Unesite prirodan broj: ";
            cin >> n;
            cin.clear();
            if(cin.peek() != '\n') {
                cin.ignore(10000, '\n');
                cout << "Niste unijeli prirodan broj!" << endl;
            } else
                break;
        }
        int suma(0);
        for(int i = 1; i <= n; i++)
            if(n % i == 0)
                suma += i;
        cout << "Suma svih djelilaca broja " << n << " je " << suma << endl;
    } while(n != 0);
    return 0;
}