#include <iostream>
using namespace std;

int main(){

    int vec[5];

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

    cout << "a soma é: "<< vec[0]+vec[1]+vec[2]+vec[3]+vec[4] << endl;


    return 0;
}