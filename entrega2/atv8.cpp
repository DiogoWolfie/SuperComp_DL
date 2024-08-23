#include <iostream>
using namespace std;

int main(){


    int matriz[3][3];
    int soma = 0;

    for(int i =0; i<3;i++){

        for(int j=0;j<3;j++){
            cout << "escreva um número para montar a matriz" << endl;
            cin >> matriz[i][j];
        }
    }


    for(int i =0; i<3;i++){
        soma += matriz[i][i];
    }

    cout << "soma da diagonal principal: " << soma << endl; 
    

    return 0;
}