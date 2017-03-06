#include <iostream>
#include <deque>

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
        deque<int> a(n), b, c;
        cout << "Unesi elemente: ";
        for (int& x : a)
                cin >> x;
        for(int x : a){
                if(DaLiJeProst(x))
                        b.push_front(x);
                else if(x != 1)
                        c.push_front(x);
        }
        for(int i = 0; i < b.size(); i++){
                if(i!=0)
                        cout << ",";
                cout << b[i];
        }
        cout << endl;
        for(int i = 0; i < c.size(); i++){
                if(i!=0)
                        cout << ",";
                cout << c[i];
        }
        return 0;
}

