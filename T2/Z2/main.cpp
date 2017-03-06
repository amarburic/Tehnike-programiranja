#include <iostream>
#include <vector>

using namespace std;

int DuzinaPerioda(vector<double> v){
	for(int i = v.size()/2; i > 0; i--){
		bool ponavlja = true;
		for(int j = i; j < v.size(); j+=i)
			for(int k = 0; k < i; k++)
				if(j + k < v.size() && v.at(k) != v.at(j+k))
					ponavlja = false;
		if(ponavlja)
			return i;
	}
	return 0;
}

int main() {
	vector<double> unos;
	double input;
	while (cin >> input, input != 0)
		unos.push_back(input);
	int duzina(DuzinaPerioda(unos));
	if(duzina != 0)
		cout << "Duzina perioda je " << duzina << ".";
	else
		cout << "Elementi ne cine periodican slijed.";
	return 0;
}

