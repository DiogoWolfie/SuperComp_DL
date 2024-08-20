#include <iostream>
#include <cstring>
using namespace std;

int main(){

    char word[50];
    char reverse[50];
    int j = 0;

    cout << "escreva uma palavra" << endl;
    cin >> word;

    for(int i = strlen(word)-1; i>=0; i--){
        reverse[j++] = word[i];
    }

    reverse[j] = '\0';

    if(strcmp(reverse, word) == 0){
        cout << "e palindromo"<<endl;
        cout << reverse << endl;

    }else{
        cout << "não e palindromo"<<endl;
        cout << reverse << endl;
    }



    return 0;
}