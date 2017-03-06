#include <iostream>
#include <cmath>

using namespace std;

int main(){
    double a, b, c;
    cout << "Unesite tri broja: ";
    cin >> a >> b >> c;
    if(a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a){
        cout << "Ne postoji trougao cije su duzine stranica " <<  a << ", " << b << " i " << c << endl;
        return 0;
    }
    double s((a+b+c)/2), p(sqrt(s*(s-a)*(s-b)*(s-c)));
    if(a < b){
        int temp(a);
        a = b;
        b = temp;
    }
    if(b < c){
        int temp(b);
        b = c;
        c = temp;
    }
    if(a < b){
        int temp(a);
        a = b;
        b = temp;
    }
    double max_ugao(acos((c*c + b*b - a*a)/(2*b*c)));
    max_ugao*=180/(4*atan(1));
    int st(max_ugao), mi((max_ugao - st)*60), sek((max_ugao - st - mi/60.)*3600); 
    cout << "Povrsina trougla sa duzinama stranica " <<  a << ", " << b << " i " << c 
    << " iznosi " << p << "." << endl;
    cout << "Njegov najveći ugao ima " << st << " stepeni, " << mi << " minuta i " 
    << sek << " sekundi." <<endl;
    return 0;
}