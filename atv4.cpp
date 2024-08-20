#include <iostream>
#include <cstring>
using namespace std;

int main(){

    char palavra[50];

    cout << "escreva uma palavra" << endl;
    cin >> palavra;
    cout << "a palavra tem tamanho: " << strlen(palavra) << endl;
    

    return 0;
}