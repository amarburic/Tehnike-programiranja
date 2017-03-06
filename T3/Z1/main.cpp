#include <iostream>
#include <vector>

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
        int n;
        cout << "Unesi broj elemenata: ";
        cin >> n;
        vector<int> a(n), b, c;
        cout << "Unesi elemente: ";
        for (int& x : a)
                cin >> x;
        for(int x : a){
                if(DaLiJeProst(x))
                        b.push_back(x);
                else if(x != 1)
                        c.push_back(x);
        }
        for (int x : b)
                cout << x << " ";
        cout << endl;
         for (int x : c)
                cout << x << " ";
        return 0;
}

