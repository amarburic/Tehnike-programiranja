#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

vector<vector<int>> TablicaMnozenja(int m, int n){
        vector<vector<int>> matrica(m, vector<int>(n));
        for(int i = 0; i < n; i++)
                matrica[0][i] = i + 1;
        for(int i = 1; i < m; i++)
                for(int j = 0; j < n; j++)
                        matrica[i][j] = matrica[0][j]*(i+1);
        return matrica;
}

int main() {
        int m, n;
        cin >> m >> n;
        
        for(vector<int> v: TablicaMnozenja(m, n)){
                for(int a: v)
                       cout << setw(5) << a; 
                cout << endl;
        }
        return 0;
}

