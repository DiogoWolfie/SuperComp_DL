#include <iostream>
using namespace std;

int main(){

    int vec[10];
    int maior;

    cout << "escreva um numero: " << endl;
    cin >> vec[0];
    cout << "escreva um numero: " << endl;
    cin >> vec[1];
    cout << "escreva um numero: " << endl;
    cin >> vec[2];
    cout << "escreva um numero: " << endl;
    cin >> vec[3];
    cout << "escreva um numero: " << endl;
    cin >> vec[4];
    cout << "escreva um numero: " << endl;
    cin >> vec[5];
    cout << "escreva um numero: " << endl;
    cin >> vec[6];
    cout << "escreva um numero: " << endl;
    cin >> vec[7];
    cout << "escreva um numero: " << endl;
    cin >> vec[8];
    cout << "escreva um numero: " << endl;
    cin >> vec[9];

    for(int i = 0; i < 10; i++){
        if(i == 0){
            maior = vec[i];
        }
        else if(vec[i] > maior){
            maior = vec[i];
        }
    }
    cout << "esse é o maior número digitado: " << maior << endl;


    return 0;
}