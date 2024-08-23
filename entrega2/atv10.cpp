#include <iostream>
#include <vector>
#include <string.h>
using namespace std;


void ad_item(vector <string> &vec, string a){
    vec.push_back(a);
}

void remove_item(vector <string> &vec, int a){
    vec.erase(vec.begin() + a - 1);
}

void show_e(vector <string> &vec){
    for (string i : vec){
        cout << i << " " << endl;
    }
}

int main(){

    string a;
    vector <string> vec;
    int pause = 0;
    string b;

    while(pause == 0){
        cout << "o que vc quer, adicionar itens, remover itens, ver seu estoque ou sair?" << endl;

        cin >> a;

        if(a.compare("adicionar")==0){
            cout << "qual item você quer adicionar?" << endl;
            cin >> b;
            ad_item(vec,b);

         
        }else if(a.compare("remover")==0){
            int i;
            cout << "qual a numeração do item?"<<endl;
            cin >> i;
            remove_item(vec,i);
        }else if(a.compare("ver")==0){
            show_e(vec);
        }else if(a.compare("sair")==0){
            pause = 1;
        }
        else{
            cout << "digitou errado" << endl;
        }



    }

    

    return 0;
}