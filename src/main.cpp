#include <iostream>
#include "menus.h"

using namespace std;

int main() {
    //Condominio c("",0,0,0,0,0,0,{},{},"","","",{},{});
    try{
        string input;
        bool valid = true;
        do{
            cout << "Nome do ficheiro do condominio:" << endl;
            getline(cin, input);
            if(cin.fail()){
                cin.clear(); cin.ignore(1000, '\n');
                cout << "Invalid input!" << endl;
                valid = false;
            }
        }
        while(!valid);
        vector<Funcionario> funcsAntigos;
        vector<Servico> servs = readServicos("servicos.txt", funcsAntigos);
        if(input.size() > 4)
            if(input.substr(input.size()-4,input.npos) != ".txt") input += ".txt";
        Gestao g = readCondominio(input, servs,funcsAntigos);
        menuCondominios(input,g,servs);
    }
    catch (const ErrorReadingFile& e){
        cout << "Erro ao abrir o " << e.getFileName() << endl;
        cout << "Verifique se os ficheiros estao no mesmo diretorio que o .exe" << endl;
    }
    catch (const ErrorWritingFile& e){
        cout << "Erro ao escrever no " << e.getFileName() << endl;
    }
    catch (const ErrorSettingValue& e){
        cout << "Erro ao alterar o valor do " << e.getValErro() << endl;
    }


    return 0;

}