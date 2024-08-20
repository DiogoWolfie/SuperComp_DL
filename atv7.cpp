#include <iostream>
#include <vector>
using namespace std;


void bubbleSort(vector <int> &vec, int n) {
    for (int i = 0; i < n-1; i++) {
        // Últimos i elementos já estão no lugar
        for (int j = 0; j < n-i-1; j++) {
            if (vec[j] > vec[j+1]) {
                // Troca arr[j] e arr[j+1]
                int temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
}



int main() {
    int n;
    
    cout << "defina o tamanho do vetor: " << endl;
    cin >> n;

    vector <int> vec(n);

    for(int i =0; i < n; i++){
        cout << "escreva um numero: " << endl;
        cin >> vec[i];
    }
    
    bubbleSort(vec, n);
    cout << "Array ordenado: \n";
    for (int i=0; i< n ; i++){
        cout << vec[i] << " ";
    }
    
    return 0;
}
