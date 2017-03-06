#include <iostream>

using namespace std;

bool DaLiJeProst(int n) {
        if(n<=1)
                return false;
        for(int i = 2; i < n; i++)
                if(n%i == 0)
                        return false;
        return true;
        
}

int main() {
        int a, b;
        cin >> a >> b;
        for(int i = a; i <= b; i++)
                cout << "Broj " << i << (!DaLiJeProst(i)?" ni":" ") << "je prost." << endl;
        return 0;
}

