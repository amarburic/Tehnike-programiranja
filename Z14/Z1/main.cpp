#include <bits/stdc++.h>

using namespace std;

const string t_path("TEMPERATURE.TXT");
const string i_path("IZVJESTAJ.TXT");

class Datum {
    int d, m, g;
public:
    friend istream& operator >> (istream& in, Datum& dat);
    friend ostream& operator << (ostream& out, const Datum& dat);
    bool operator < (const Datum& dat) const;
    bool operator == (const Datum& dat) const;
};

class Mjerenje {
    Datum dat;
    string naziv_mjesta;
    vector<double> mjerenja;
public:
    double DajMinimalnu() const { return *min_element(mjerenja.begin(), mjerenja.end()); }
    double DajMaksimalnu() const { return *max_element(mjerenja.begin(), mjerenja.end()); }
    double DajProsjecnu() const { return accumulate(mjerenja.begin(), mjerenja.end(), .0) / mjerenja.size(); } 
    bool operator < (const Mjerenje& m) const { return (dat == m.dat) ? (DajProsjecnu() < m.DajProsjecnu()) : (dat < m.dat); }
    friend istream& operator >> (istream& in, Mjerenje& m); 
    friend ostream& operator << (ostream& out, const Mjerenje& m);
    
};

istream& operator >> (istream& in, Datum& dat) {
    char c;
    in >> dat.d >> c >> dat.m >> c >> dat.g;
    return in;
}

ostream& operator << (ostream& out, const Datum& dat) {
    return out << dat.d << "/" << dat.m << "/" << dat.g; 
}

bool Datum::operator < (const Datum& dat) const {
    if(this->g == dat.g) {
        if(this->m == dat.m) 
            return this->d < dat.d;
        else return this->m < dat.m;
    } else return this->g < dat.g;
}

bool Datum::operator == (const Datum& dat) const {
    return this->d == dat.d && this->m == dat.m && this->g == dat.g;
}

istream& operator >> (istream& in, Mjerenje& m) {
    char c;
    if(!(in >> m.dat)) return in;
    in.ignore(10000, '\n');
    getline(in, m.naziv_mjesta);
    double mj;
    m.mjerenja = vector<double>();
    while(true) {
        in >> mj;
        m.mjerenja.push_back(mj);
        if((c = in.peek()) == ',') in.get();
        else {
            if(c == EOF) in.clear();
            break;
        }
    }
    return in;
}

ostream& operator << (ostream& out, const Mjerenje& m) {
    out << m.naziv_mjesta << endl;
    out << string(m.naziv_mjesta.size(), '-') << endl;
    out << "Datum mjerenja: " << m.dat << endl;
    out << "Minimalna temperatura: " << m.DajMinimalnu() << endl;
    out << "Maksimalna temperatura: " << m.DajMaksimalnu() << endl;
    out << "Prosjecna temperatura: " << setprecision(2) << fixed << m.DajProsjecnu() << endl;
    out.unsetf(ios_base::floatfield);
    out << endl;
    return out;
}

int main() {
    ifstream citac(t_path, ios::in);
    if(!citac) {
        cout << "Datoteka " << t_path << " ne postoji!" << endl;
        return 1;
    }
    vector<Mjerenje> niz_mjerenja;
    Mjerenje temp;
    while(citac >> temp) 
        niz_mjerenja.push_back(temp);
    if(citac.bad()) {
        cout << "Problemi pri citanju datoteke " << t_path << endl;
        return 1;
    }
    ofstream pisac(i_path, ios::out);
    sort(niz_mjerenja.begin(), niz_mjerenja.end());
    for(Mjerenje& m : niz_mjerenja)
        pisac << m;
    return 0;
}

