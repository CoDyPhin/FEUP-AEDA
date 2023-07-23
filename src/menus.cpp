#include "menus.h"

using namespace std;

void menuTransportes(const string& filename, Condominio &c, vector<Servico>& servicos) {
    unsigned short int input;
    string inputS;
    bool valid = false;
    priority_queue<Transporte> aux = c.getTransportes();
    priority_queue<Transporte> aux2 = c.getTransportes();
    priority_queue<Transporte> result;
    cout << "========================================" << endl;
    cout << "      Menu de Gestao de Transportes     " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Pesquisar transporte mais proximo" << endl;
    cout << "[2] Pesquisa transporte com destino" << endl;
    cout << "[3] Alterar disponibilidade de paragens" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0,3);
    switch (input) {
        case 0:
            menuPrincipal(filename, c, servicos);
            return;
        case 1:
            cout << c.getTransportes().top() << endl;
            menuTransportes(filename, c, servicos);
            break;
        case 2:
            while(!valid){
                cout << "Insira o destino:" << endl;
                cin.ignore(1000,'\n');
                getline(cin, inputS);
                if(cin.fail()){
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input!" << endl;
                    valid = false;
                }
                else {
                    bool find = false;
                    cout << "Este destino esta correto? " << inputS << endl;
                    cout << "[0] Cancelar" << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    input = menuValidInput(0, 2);
                    switch(input) {
                        case 0:
                            menuTransportes(filename, c, servicos);
                            return;
                        case 1:
                            while(!aux.empty()){
                                if(aux.top().getDestino().find(inputS)!=aux.top().getDestino().npos){
                                    cout << aux.top() << endl;
                                    cout << "========================================" << endl;
                                    find = true;
                                }
                                aux.pop();
                            }
                            if(!find){
                                cout << "Nao ha nenhum transporte com esse destino!" << endl;
                            }
                            valid = true;
                            break;
                        case 2:
                            valid = false;
                            break;
                    }
                }
                menuTransportes(filename, c, servicos);
            }
            break;
        case 3:
            cout << "========================================" << endl;
            cout << "       Menu de Gestao de Paragens       " << endl;
            cout << "========================================" << endl;
            cout << "Selecione o transporte a alterar:" << endl;
            unsigned i = 0;
            cout << "[" << i << "] Voltar" << endl;
            while(!aux.empty()){
                i++;
                cout << "[" << i << "]" << aux.top() << endl;
                cout << "========================================" << endl;
                aux.pop();
            }
            input = menuValidInput(0, i);
            if(input == 0){
                menuTransportes(filename, c, servicos);
            }
            else {
                for (size_t k = 0; k < input-1; k++) {
                    aux2.pop();
                }
                Transporte t = aux2.top();
                vector<Paragem> paragens = t.getParagens();
                aux = c.getTransportes();
                while(!aux.empty()){
                    if(!(aux.top().getDestino() == t.getDestino() && aux.top().getClosestParagem() == t.getClosestParagem() && aux.top().getParagens() == t.getParagens() && aux.top().getTipo() == t.getTipo())){
                        result.push(aux.top());
                    }
                    aux.pop();
                }
                cout << "========================================" << endl;
                cout << "[0] Cancelar" << endl;
                cout << "[1] Remover paragem" << endl;
                cout << "[2] Adicionar paragem" << endl;
                input = menuValidInput(0,2);
                switch(input){
                    case 0:
                        menuTransportes(filename, c, servicos);
                        return;
                    case 1:
                        cout << "[0] Cancelar" << endl;
                        for(size_t k = 0; k < paragens.size(); k++){
                            cout << "[" << k+1 << "]" << paragens.at(k).name << endl;
                        }
                        input = menuValidInput(0,paragens.size());
                        if(input == 0){
                            menuTransportes(filename, c, servicos);
                            return;
                        }
                        t.removeParagem(paragens.at(input-1));
                        result.push(t);
                        c.setTransportes(result);
                        writeTransportes(c);
                        menuTransportes(filename, c, servicos);
                        break;
                    case 2:
                        struct Paragem p;
                        while(!valid){
                            cout << "Insira o nome da paragem:" << endl;
                            cin.ignore(1000,'\n');
                            getline(cin, inputS);
                            if(cin.fail()){
                                cin.clear(); cin.ignore(1000, '\n');
                                cout << "Invalid input!" << endl;
                                valid = false;
                            }
                            else {
                                cout << "Este nome esta correto? " << inputS << endl;
                                cout << "[0] Cancelar" << endl;
                                cout << "[1] Sim" << endl;
                                cout << "[2] Nao" << endl;
                                input = menuValidInput(0, 2);
                                switch(input) {
                                    case 0:
                                        menuTransportes(filename, c, servicos);
                                        return;
                                    case 1:
                                        p.name = inputS;
                                        valid = true;
                                        break;
                                    case 2:
                                        valid = false;
                                        break;
                                }
                            }
                        }
                        p.distance = areaValidInput("Introduza a distancia a que se encontra do condominio (Km): ");
                        t.addParagem(p);
                        result.push(t);
                        c.setTransportes(result);
                        writeTransportes(c);
                        menuTransportes(filename, c, servicos);
                        break;
                }
            }
            break;
    }
}

void menuHistCond(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input;
    string inputS;
    unsigned long int inputnif;
    bool valid = false, found = false;
    unsigned yearS, yearE, monthS = 0, monthE = 12, dayS = 0, dayE = 31;
    unsigned dateS, dateE;
    HashTableOldCondominos oldcond = c.getOldCondominos();
    cout << "========================================" << endl;
    cout << "     Menu de Historico de Condominos    " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Pesquisa por nome" << endl;
    cout << "[2] Pesquisa por NIF" << endl;
    cout << "[3] Pesquisa por periodo como condomino" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0,3);
    switch (input){
        case 0:
            menuPrincipal(filename, c, servicos);
            return;
        case 1:
            while(!valid){
                cout << "Insira o nome:" << endl;
                cin.ignore(1000,'\n');
                getline(cin, inputS);
                if(cin.fail()){
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input!" << endl;
                    valid = false;
                }
                else {
                    cout << "Este nome esta correto? " << inputS << endl;
                    cout << "[0] Cancelar" << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    input = menuValidInput(0, 2);
                    if(input==0){
                        menuHistCond(filename, c, servicos);
                        return;
                    }
                    if(input == 1){
                        for(auto it = oldcond.begin(); it != oldcond.end(); it++){
                            if(it->getNome().find(inputS) != it->getNome().npos){
                                found = true;
                                cout << showHistCond(*it) << endl;
                                cout << "========================================" << endl;
                            }
                        }
                        valid = true;
                    }
                    if(!found) cout << "No matches for the specified criteria" << endl;
                }
            }
            menuHistCond(filename, c, servicos);
            break;
        case 2:
            inputnif = nifValidInput();
            for(auto it = oldcond.begin(); it != oldcond.end(); it++){
                if(inputnif == it->getNif()){
                    found = true;
                    cout << showHistCond(*it) << endl;
                    cout << "========================================" << endl;
                    break;
                }
            }
            if(!found) cout << "No matches for the specified criteria" << endl;
            menuHistCond(filename, c, servicos);
            break;
        case 3:
            yearS = numbersValidInput(1700, 2020, "Introduza o ano de entrada:");
            yearE = numbersValidInput(yearS, 2020, "Introduza o ano de saida:");
            cout << "Deseja introduzir mes?" << endl;
            cout << "[0] Cancelar" << endl;
            cout << "[1] Sim" << endl;
            cout << "[2] Nao" << endl;
            input = menuValidInput(0,2);
            switch (input){
                case 0:
                    menuHistCond(filename, c, servicos);
                    return;
                case 1:
                    monthS = numbersValidInput(1,12,"Introduza o mes de entrada:");
                    if(yearE == yearS){
                        monthE = numbersValidInput(monthS, 12, "Introduza o mes de saida:");
                    }
                    else{
                        monthE = numbersValidInput(1,12, "Introduza o mes de saida:");
                    }
                    cout << "Deseja introduzir dia?" << endl;
                    cout << "[0] Cancelar" << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    input = menuValidInput(0,2);
                    switch (input){
                        case 0:
                            menuHistCond(filename, c, servicos);
                            return;
                        case 1:
                            dayS = numbersValidInput(1,31,"Introduza o dia de entrada:");
                            if(monthE == monthS){
                                dayE = numbersValidInput(monthS, 31, "Introduza o dia de saida:");
                            }
                            else{
                                dayE = numbersValidInput(1,31, "Introduza o dia de saida:");
                            }
                            break;
                        case 2:
                            break;
                    }
                case 2:
                    break;
            }
            dateS = yearS*10000+monthS*100+dayS;
            dateE = yearE*10000+monthE*100+dayE;
            for(auto it = oldcond.begin(); it != oldcond.end(); it++){
                if(it->getStartDate() >= dateS && it->getEndDate() <= dateE){
                    found = true;
                    cout << showHistCond(*it) << endl;
                    cout << "========================================" << endl;
                }
            }
            if(!found) cout << "No matches for the specified criteria" << endl;
            menuHistCond(filename, c, servicos);
            break;
    }
}


void menuCondominio(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input, input2;
    vector<Condomino> aux;
    string inputS;
    double inputD;
    bool valid;
    cout << "========================================" << endl;
    cout << "      Menu de Gestao Do Condominio      " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Mostrar informacao do condominio" << endl;
    cout << "[2] Alterar nome do condominio" << endl;
    cout << "[3] Alterar valores de mensalidade" << endl;
    cout << "[4] Alterar servicos disponiveis" << endl;
    cout << "[5] Pesquisar no historico de condominos" << endl;
    cout << "[6] Pesquisa de transportes" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 6);
    switch (input){
        case 0:
            menuPrincipal(filename,c,servicos);
            break;
        case 1:
            cout << c;
            menuCondominio(filename,c, servicos);
            break;
        case 2:
            cout << "Atual nome do condominio:" << endl;
            cout << c.getNome() << endl;
            valid = false;
            while(!valid)
            {
                valid = true;
                cout << "Insira novo nome:" << endl;
                cin.ignore(1000,'\n');
                getline(cin, inputS);
                if(cin.fail()){
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input!" << endl;
                    valid = false;
                }
                else {
                    cout << "Este nome esta correto? " << inputS << endl;
                    cout << "[0] Cancelar" << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    input = menuValidInput(0, 2);
                    switch (input){
                        case 0:
                            break;
                        case 1:
                            if(!c.setNome(inputS)){
                                throw ErrorSettingValue("nome do condominio");
                            }
                            //if(writeCondominio(filename, c)) throw ErrorWritingFile("ficheiro do condominio");
                            break;
                        case 2:
                            valid = false;
                            break;
                    }
                }
            }
            menuCondominio(filename,c, servicos);
            break;
        case 3:
            cout << "Atuais mensalidades:" << endl;
            cout << "Mensalidade(Vivenda): " << c.getMensalV() << endl << "Mensalidade(Apartamento): " << c.getMensalA() << endl
                 << "Valorizacao Area Exterior: " << c.getValorAExt() << "%" << endl << "Valorizacao Piscina: " << c.getValorPool() << "%" << endl << "Valorizacao Tipo de Apartamento: "
                 << c.getValorTipo() <<  "%" << endl << "Valorizacao por Andar: " << c.getValorPiso() << "%" << endl;
            cout << "========================================" << endl;
            cout << "Qual mensalidade deseja alterar?" << endl;
            cout << "[0] Cancelar" << endl;
            cout << "[1] Mensalidade-base de vivenda" << endl;
            cout << "[2] Mensalidade-base de apartamento" << endl;
            cout << "[3] Valorizacao por m^2 de area exterior" << endl;
            cout << "[4] Valorizacao por existencia de piscina" << endl;
            cout << "[5] Valorizacao por tipo (No de quartos)" << endl;
            cout << "[6] Valorizacao por andar" << endl;
            input = menuValidInput(0, 6);
            if(input == 0) break;
            valid = false;
            while(!valid)
            {
                cout << "Introduza o novo valor: " << endl;
                cin >> inputD;
                if(cin.fail()){
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Invalid input!" << endl;
                    valid = false;
                }
                else {
                    cout << "Este valor esta correto? " << inputD << endl;
                    cout << "[0] Cancelar" << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    input2 = menuValidInput(0, 2);
                    switch (input2){
                        case 0:
                            break;
                        case 1:
                            switch (input){
                                case 1:
                                    if(!c.setMensalV(inputD)) throw ErrorSettingValue("mensalidade-base de vivendas");
                                    break;
                                case 2:
                                    if(!c.setMensalA(inputD)) throw ErrorSettingValue("mensalidade-base de apartamento");
                                    break;
                                case 3:
                                    if(!c.setValorAExt(inputD)) throw ErrorSettingValue("valorizacao por area exterior");
                                    break;
                                case 4:
                                    if(!c.setValorPool(inputD)) throw ErrorSettingValue("valorizacao por existencia de piscina");
                                    break;
                                case 5:
                                    if(!c.setValorTipo(inputD)) throw ErrorSettingValue("valorizacao por tipo de apartamento");
                                    break;
                                case 6:
                                    if(!c.setValorPiso(inputD)) throw ErrorSettingValue("valorizacao por andar");
                                    break;
                            }
                            for(Condomino cond: c.getCondomino()){
                                Condomino auxC(cond.getNome(), cond.getNif(), c.getMensalA(), c.getMensalV(), c.getValorAExt(), c.getValorPool(), c.getValorTipo(), c.getValorPiso(),cond.getStartDate(), cond.getOwnedHabs());
                                aux.push_back(auxC);
                            }
                            if(!c.setCondominos(aux)) throw ErrorSettingValue("vetor de condominos");
                            //if(writeCondominio(filename, c)) throw ErrorWritingFile("ficheiro do condominio");
                            valid = true;
                            break;
                        case 2:
                            valid = false;
                            break;
                    }
                }
            }
            menuCondominio(filename,c, servicos);
            break;
        case 4:
            cout << "Atuais servicos do condominio: " << endl;
            cout << c.getServsString() << endl;
            cout << "[0] Voltar" << endl;
            cout << "[1] Adicionar servicos" << endl;
            cout << "[2] Remover servicos" << endl;
            input = menuValidInput(0,2);
            switch(input){
                case 0:
                    break;
                case 1:
                    valid = false;
                    while (!valid) {
                        cout << "Selecione o servico que deseja adicionar: " << endl;
                        cout << "[0] Cancelar" << endl;
                        for (size_t i = 0; i < servicos.size(); i++){
                            cout << "[" << i+1 << "] " << servicos.at(i).getTipo() << endl;
                        }
                        cout << "========================================" << endl;
                        input = menuValidInput(0, servicos.size());
                        if(input == 0) break;
                        else{
                        if(c.getServsString().find(servicos.at(input-1).getTipo()) != c.getServsString().npos) {
                            cout << "Este servico ja esta disponivel!" << endl;
                        }
                        else{
                            vector<Servico> aux = c.getServicos();
                            aux.push_back(servicos.at(input-1));
                            if(!c.setServicos(aux)) throw ErrorSettingValue("vetor de servicos do condominio");
                            //if(writeCondominio(filename, c)) throw ErrorWritingFile("ficheiro do condominio");
                        }
                        cout << "Deseja adicionar mais algum servico?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1,2);
                        switch (input){
                            case 1:
                                valid = false;
                                break;
                            case 2:
                                valid = true;
                                break;
                        }
                    }
                    }
                    break;
                case 2:
                    cout << "Qual o servico que deseja remover?" << endl;
                    cout << "[0] Cancelar" << endl;
                    vector<Servico> aux = c.getServicos();
                    for (size_t i = 0; i < aux.size(); i++){
                        cout << "[" << i+1 << "] " << aux.at(i).getTipo() << endl;
                    }
                    cout << "========================================" << endl;
                    input = menuValidInput(0, servicos.size());
                    aux.erase(aux.begin()+input-1);
                    if(!c.setServicos(aux)) throw ErrorSettingValue("vetor de servicos do condominio");
                    //if(writeCondominio(filename, c)) throw ErrorWritingFile("ficheiro do condominio");
                    break;
            }
            menuCondominio(filename,c, servicos);
            break;
        case 5:
            menuHistCond(filename, c, servicos);
            break;
        case 6:
            menuTransportes(filename, c, servicos);
            break;
    }
}

void menuCondominoEsp(int index, const string& filename, Condominio &c, vector<Servico>& servicos){
    vector<Condomino> aux = c.getCondomino();
    vector<Habitacao*> auxHabs = c.getHabs();
    unsigned short int input;
    unsigned long int input2;
    string inputS;
    bool valid;
    cout << "========================================" << endl;
    cout << "Bem-vindo, " << aux.at(index).getNome().substr(0,aux.at(index).getNome().find_first_of(' '))  << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Alterar informacoes pessoais" << endl;
    cout << "[2] Compra de propriedades" << endl;
    cout << "[3] Venda de propriedades" << endl;
    cout << "[4] Verificar mensalidade a pagar" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 4);
    switch (input){
        case 0:
            break;
        case 1:
            cout << "[0] Voltar" << endl;
            cout << "[1] Nome" << endl;
            cout << "[2] NIF" << endl;
            input = menuValidInput(0,2);
            if(input != 0){
                switch (input){
                    case 1:
                        cout << "Atual nome do condomino:" << endl;
                        cout << aux.at(index).getNome() << endl;
                        valid = false;
                        while(!valid)
                        {
                            valid = true;
                            cout << "Insira o novo nome:" << endl;
                            cin.ignore(1000,'\n');
                            getline(cin, inputS);
                            if(cin.fail()){
                                cin.clear(); cin.ignore(1000, '\n');
                                cout << "Invalid input!" << endl;
                                valid = false;
                            }
                            else {
                                cout << "Este nome esta correto? " << inputS << endl;
                                cout << "[0] Cancelar" << endl;
                                cout << "[1] Sim" << endl;
                                cout << "[2] Nao" << endl;
                                input = menuValidInput(0, 2);
                                switch (input){
                                    case 0:
                                        break;
                                    case 1:
                                        if(!aux.at(index).setNome(inputS)){
                                            throw ErrorSettingValue("nome do condomino");
                                        }
                                        if(!c.setCondominos(aux)) throw ErrorSettingValue("vetor de condominos");
                                        if(writeCondomino(c)) throw ErrorWritingFile("ficheiro dos condominos");
                                        break;
                                    case 2:
                                        valid = false;
                                        break;
                                }
                            }
                        }
                        break;
                    case 2:
                        cout << "NIF atual: " << aux.at(index).getNif() << endl;
                        input2 = nifValidInput();
                        while((searchCondomino(aux, input2) != -1)){
                            cout << "NIF ja existente!" << endl;
                            input2 = nifValidInput();
                        }
                        if(!aux.at(index).setNif(input2)) throw ErrorSettingValue("nif do condomino");
                        for(Habitacao* hab: auxHabs){
                            if(hab->getOwnerNif() == aux.at(index).getNif())
                                if(!hab->setOwnerNif(input2)) throw ErrorSettingValue("nif do dono");
                        }
                        for(Habitacao* hab: aux.at(index).getOwnedHabs()){
                            if(!hab->setOwnerNif(input2)) throw ErrorSettingValue("nif do dono");
                        }
                        sort(aux.begin(), aux.end());
                        index = searchCondomino(aux, input2);
                        if(!c.setHabs(auxHabs)) throw ErrorSettingValue("vetor de habitacoes");
                        if(!c.setCondominos(aux)) throw ErrorSettingValue("vetor de condominos");
                        if(writeCondomino(c)) throw ErrorWritingFile("ficheiro dos condominos");
                        if(writeHabitacao(c)) throw ErrorWritingFile("ficheiro de habitacoes");
                        break;
                }
            }
            menuCondominoEsp(index, filename, c, servicos);
            break;
        case 2:
            if (c.getHabsDisp().empty()) {
                cout << "Nao ha propriedades disponiveis!" << endl;
            }
            else {
                cout << "Selecione a habitacao a comprar:" << endl;
                cout << "[0] Cancelar" << endl;
                mostrarHabs(c.getHabsDisp());
                input = menuValidInput(0, c.getHabsDisp().size());
                if (input == 0) {
                    menuCondomino(filename, c, servicos);
                    return;
                }
                else {
                    unsigned short int indexH = input - 1;
                    vector<Habitacao *> auxHabs = c.getHabs();
                    indexH = searchHab(auxHabs, c.getHabsDisp().at(indexH));
                    if(!auxHabs.at(indexH)->setOwnerNif(c.getCondomino().at(index).getNif())) throw ErrorSettingValue("owner nif");
                    if(!c.setHabs(auxHabs)) throw ErrorSettingValue("habitacoes do condominio");
                    vector <Habitacao*> auxOwnedHabs = aux.at(index).getOwnedHabs();
                    auxOwnedHabs.push_back(auxHabs.at(indexH));
                    Condomino cond(aux.at(index).getNome(), aux.at(index).getNif(), c.getMensalA(), c.getMensalV(), c.getValorAExt()
                    , c.getValorPool(), c.getValorTipo(), c.getValorPiso(),aux.at(index).getStartDate(), auxOwnedHabs);
                    aux.erase(aux.begin()+index);
                    aux.push_back(cond);
                    sort(aux.begin(), aux.end());
                    if(!c.setCondominos(aux)) throw ErrorSettingValue("condominos do condominio");
                    if(writeHabitacao(c)) throw ErrorWritingFile("ficheiro das habitacoes");
                }
            }
            menuCondominoEsp(index, filename, c, servicos);
            break;
        case 3:
            cout << "Selecione a habitacao a vender:" << endl;
            cout << "[0] Cancelar" << endl;
            mostrarHabs(aux.at(index).getOwnedHabs());
            cout << "[" << aux.at(index).getOwnedHabs().size()+1 << "] Todas as propriedades" << endl;
            input = menuValidInput(0, aux.at(index).getOwnedHabs().size()+1);
            if(input == 0){
                menuCondominoEsp(index, filename, c, servicos);
                break;
            }
            else{
                if(input == aux.at(index).getOwnedHabs().size()+1){
                    cout << "O condomino sera apagado (nao possui propriedades). Deseja continuar?" << endl;
                    cout << "[1] Sim" << endl << "[2] Nao" << endl;
                    input = menuValidInput(1,2);
                    if(input == 2){
                        menuCondominoEsp(index,filename,c,servicos);
                        return;
                    }
                    aux.at(index).setEndDate(currentDateTime());
                    c.addOldCondomino(aux.at(index));
                    if(!eraseCondomino(c,index)) throw ErrorSettingValue("habitacoes do condominio e lista de condominos");
                    if (writeCondomino(c)) throw ErrorWritingFile("ficheiro dos condominos");
                    if (writeHabitacao(c)) throw ErrorWritingFile("ficheiro das habitacoes");
                    if(writeHistoricoCondomino(c.getHistoricoCoFile(),c.getOldCondominos())) throw ErrorWritingFile("ficheiro do historico de condominos");
                    menuCondomino(filename, c , servicos);
                    return;
                }
                else {
                    unsigned short int indexH = input - 1;
                    vector<Habitacao *> auxHabs = c.getHabs();
                    indexH = searchHab(auxHabs, aux.at(index).getOwnedHabs().at(indexH));
                    if (!auxHabs.at(indexH)->setOwnerNif(0)) throw ErrorSettingValue("owner nif");
                    if (!c.setHabs(auxHabs)) throw ErrorSettingValue("habitacoes do condominio");
                    vector<Habitacao *> auxOwnedHabs = habsOwned(aux.at(index).getNif(), c.getHabs());
                    if(auxOwnedHabs.empty()){
                        cout << "O condomino sera apagado (nao possui propriedades). Deseja continuar?" << endl;
                        cout << "[1] Sim" << endl << "[2] Nao" << endl;
                        input = menuValidInput(1,2);
                        if(input == 2){
                            menuCondominoEsp(index,filename,c,servicos);
                            return;
                        }
                        aux.at(index).setEndDate(currentDateTime());
                        c.addOldCondomino(aux.at(index));
                        if(!eraseCondomino(c,index)) throw ErrorSettingValue("habitacoes do condominio e lista de condominos");
                        if (writeCondomino(c)) throw ErrorWritingFile("ficheiro dos condominos");
                        if(writeHistoricoCondomino(c.getHistoricoCoFile(),c.getOldCondominos())) throw ErrorWritingFile("ficheiro do historico dos condominos");
                    }
                    else{
                        Condomino cond(aux.at(index).getNome(), aux.at(index).getNif(), c.getMensalA(), c.getMensalV(),
                                c.getValorAExt(), c.getValorPool(), c.getValorTipo(), c.getValorPiso(),aux.at(index).getStartDate(),
                                auxOwnedHabs);
                        aux.erase(aux.begin() + index);
                        aux.push_back(cond);
                        sort(aux.begin(), aux.end());
                        if (!c.setCondominos(aux)) throw ErrorSettingValue("condominos do condominio");
                        }
                    if (writeHabitacao(c)) throw ErrorWritingFile("ficheiro das habitacoes");
                    menuCondomino(filename, c, servicos);
                    break;
                }
            }
        case 4:
            cout << "A mensalidade a pagar e: " << c.getCondomino().at(index).getMensalBase() << " euros" << endl;
            menuCondominoEsp(index, filename, c, servicos);
            break;
    }
}

void menuCondomino(const string& filename, Condominio &c, vector<Servico>& servicos) {
    unsigned short int input;
    unsigned long int input2;
    string inputS;
    int inputI;
    bool valid;
    vector<Condomino> aux = c.getCondomino();
    cout << "========================================" << endl;
    cout << "      Menu de Gestao Do Condomino      " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Ver informacao de todos os condominos" << endl;
    cout << "[2] Adicionar condomino" << endl;
    cout << "[3] Menu de condomino especifico" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 3);
    switch (input) {
        case 0:
            menuPrincipal(filename, c, servicos);
            break;
        case 1:
            for (size_t i = 0; i < c.getCondomino().size(); i++) {
                cout << c.getCondomino().at(i);
                cout << "========================================" << endl;
            }
            menuCondomino(filename, c, servicos);
            break;
        case 2:
            if (c.getHabsDisp().empty()) {
                cout << "Nao ha propriedades disponiveis!" << endl;
            }
            else {
                cout << "Selecione a habitacao do novo condomino:" << endl;
                cout << "[0] Cancelar" << endl;
                mostrarHabs(c.getHabsDisp());
                input = menuValidInput(0, c.getHabsDisp().size());
                if (input == 0) {
                    menuCondomino(filename, c, servicos);
                } else {
                    unsigned short int index = input - 1;
                    vector<Habitacao*> auxHabs = c.getHabs();
                    valid = false;
                    while (!valid) {
                        valid = true;
                        cout << "Insira o nome do novo condomino:" << endl;
                        cin.ignore(1000,'\n');
                        getline(cin, inputS);
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input!" << endl;
                            valid = false;
                        } else {
                            cout << "Este nome esta correto? " << inputS << endl;
                            cout << "[0] Cancelar" << endl;
                            cout << "[1] Sim" << endl;
                            cout << "[2] Nao" << endl;
                            input = menuValidInput(0, 2);
                            switch (input) {
                                case 0:
                                    break;
                                case 1:
                                    input2 = nifValidInput();
                                    while((searchCondomino(aux, input2) != -1)){
                                        cout << "NIF ja existente!" << endl;
                                        input2 = nifValidInput();
                                    }
                                    if (!addCondomino(c, inputS, input2, index))
                                        throw ErrorSettingValue("novo condomino");
                                    index = searchHab(auxHabs, c.getHabsDisp().at(index));
                                    if(!auxHabs.at(index)->setOwnerNif(input2)) throw ErrorSettingValue("owner nif");
                                    if(!c.setHabs(auxHabs)) throw ErrorSettingValue("habitacoes do condominio");
                                    if(writeHabitacao(c)) throw ErrorWritingFile("ficheiro das habitacoes");
                                    if(writeCondomino(c)) throw ErrorWritingFile("ficheiro dos condominos");
                                    break;
                                case 2:
                                    valid = false;
                                    break;
                            }
                        }
                    }
                }
            }
            menuCondomino(filename, c, servicos);
            break;
        case 3:
            input2 = nifValidInput();
            inputI = searchCondomino(c.getCondomino(), input2);
            if(inputI == -1) cout << "Nao existe nenhum condomino com esse NIF!" << endl;
            else{
                menuCondominoEsp(inputI, filename, c, servicos);
            }
            menuCondomino(filename, c, servicos);
            break;
    }
}

void menuServicos(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input, habindex, indexServ;
    unsigned long int input2;
    int indexC;
    double inicio, fim;
    cout << "========================================" << endl;
    cout << "       Menu de Gestao de Servicos       " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Requisitar servicos" << endl;
    cout << "[2] Visualizar servicos efetuados" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0,2);
    switch (input){
        case 0:
            menuPrincipal(filename, c, servicos);
            break;
        case 1:{
            if(c.getServicos().empty()) cout << "Nao ha servicos disponiveis para requisitar!" << endl;
            else{
                input2 = nifValidInput();
                indexC = searchCondomino(c.getCondomino(), input2);
                if(indexC == -1) cout << "Nao existe nenhum condomino com esse NIF!" << endl;
                else {
                    cout << "========================================" << endl;
                    cout << "Bem-vindo, " << c.getCondomino().at(indexC).getNome().substr(0, c.getCondomino().at(
                            indexC).getNome().find_first_of(' ')) << endl;
                    cout << "Selecione o servico que deseja requisitar:" << endl;
                    cout << "========================================" << endl;
                    cout << "[0] Voltar" << endl;
                    showServs(c);
                    indexServ = menuValidInput(0, c.getServicos().size());
                    if(indexServ == 0) menuServicos(filename, c, servicos);
                    else{
                        indexServ = indexServ - 1;
                        cout << "Selecione a habitacao para a qual deseja requisitar o servico de " << c.getServicos().at(indexServ).getTipo() << endl;
                        cout << "[0] Voltar" << endl;
                        mostrarHabs(c.getCondomino().at(indexC).getOwnedHabs());
                        habindex = menuValidInput(0, c.getCondomino().at(indexC).getOwnedHabs().size());
                        if(habindex == 0) menuPrincipal(filename, c, servicos);
                        else {
                            habindex = habindex - 1;
                            cout << "Insira o intervalo de disponibilidade para requisicao do servico:" << endl;
                            cin.ignore(1000,'\n');
                            inicio = timeToDouble(timeValidInput("Hora de inicio (HH:MM): "));
                            cin.ignore(1000,'\n');
                            fim = timeToDouble(timeValidInput("Hora de fim (HH:MM): "));
                            vector<Funcionario> foundFuncs = searchFuncsDispo(c, inicio, fim, indexServ);
                            if (foundFuncs.empty()) {
                                cout << "Nao foram encontrados funcionarios disponiveis neste intervalo!" << endl;
                                menuServicos(filename, c, servicos);
                            }
                            else{
                                cout << "Selecione o funcionario: " << endl;
                                cout << "[0] Voltar" << endl;
                                for(size_t i = 0; i<foundFuncs.size(); i++){
                                    cout << "[" << i+1 << "] O funcionario " << foundFuncs.at(i).getNome() << " esta disponivel nos seguintes intervalos: " << endl;
                                    cout << horarioToString(foundFuncs.at(i).getDisp()) << endl;
                                }
                                input = menuValidInput(0, foundFuncs.size());
                                if (input == 0) menuServicos(filename, c, servicos);
                                else{
                                    cin.ignore(1000,'\n');
                                    inicio = timeToDouble(timeValidInput("Introduza a hora de inicio do servico (HH:MM):"));
                                    cin.ignore(1000,'\n');
                                    fim = timeToDouble(timeValidInput("Introduza a hora de fim do servico (HH:MM):"));
                                    while(!checkDisponibilidade(foundFuncs.at(input-1).getDisp(), inicio, fim)){
                                        cout << "Erro! O funcionario nao esta disponivel a essa hora!" << endl;
                                        cin.ignore(1000,'\n');
                                        inicio = timeToDouble(timeValidInput("Introduza a hora de inicio do servico (HH:MM):"));
                                        cin.ignore(1000,'\n');
                                        fim = timeToDouble(timeValidInput("Introduza a hora de fim do servico (HH:MM):"));
                                    }
                                    if(!mudarDisp(c, indexServ, foundFuncs.at(input-1), inicio, fim)) throw ErrorSettingValue("disponibilidade do funcionario");
                                    vector<Habitacao*> aux = c.getHabs();
                                    auto it = find(aux.begin(), aux.end(), c.getCondomino().at(indexC).getOwnedHabs().at(habindex));
                                    vector<Servico> aux2 = (*it)->getServCons();
                                    if(find(aux2.begin(), aux2.end(), c.getServicos().at(indexServ))==aux2.end()){
                                        aux2.push_back(c.getServicos().at(indexServ));
                                        (*it)->setServCons(aux2);
                                    }
                                    if(writeFuncionarios(c.getServicos())) throw ErrorWritingFile("ficheiro dos funcionarios");
                                    if(writeHabitacao(c)) throw ErrorWritingFile("ficheiro das habitacoes");
                                    menuServicos(filename, c, servicos);
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case 2:
            vector <Funcionario> aux = c.getHistorico();
            cout << "No dia (YYYY-MM-DD) " << intDateToString(aux.at(0).getData()) << " foram efetuados os seguintes servicos:" << endl;
            cout << "Servicos de " << aux.at(0).getTipo() << endl << "Efetuados por: " << aux.at(0).getNome() << endl << "Nos intervalos: "
            << horarioToString(servsMap(aux.at(0).getHorario(), aux.at(0).getDisp()))<< endl << "--------------------" << endl;
            for(size_t i=1; i<aux.size(); i++){
                if(aux.at(i).getData() != aux.at(i-1).getData()) {
                    cout << "=====================================================================" << endl;
                    cout << "No dia (YYYY-MM-DD) " << intDateToString(aux.at(i).getData()) << " foram efetuados os seguintes servicos:" << endl;
                }
                cout << "Servicos de " << aux.at(i).getTipo() << endl << "Efetuados por: " << aux.at(i).getNome()
                     << endl << "Nos intervalos: "
                     << horarioToString(servsMap(aux.at(i).getHorario(), aux.at(i).getDisp())) << endl << "--------------------" << endl;
            }
            menuServicos(filename,c,servicos);
            break;
    }
}

void menuPesquisaApartamentos(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input;
    string morada = "-1";
    double minAInt = -1;
    double maxAInt = -1;
    unsigned short int inputDono = 0;
    short int quartos = -1;
    string tipo = "-1";
    short int piso = -1;
    bool valid = false;
    bool valid2 = false;
    cout << "========================================" << endl;
    cout << "    Menu de Pesquisa De Apartamentos    " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Ver todos os apartamentos" << endl;
    cout << "[2] Selecionar filtros de pesquisa" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 2);
    switch (input){
        case 0:
            break;
        case 1:
            mostrarHabs(searchHabitacao(c.getHabs(), "apartamento"));
            menuPesquisaApartamentos(filename, c, servicos);
            break;
        case 2:
            while(!valid) {
                cout << "Selecione os filtros que deseja: " << endl;
                cout << "[0] Cancelar" << endl;
                cout << "[1] Morada" << endl;
                cout << "[2] Area interior" << endl;
                cout << "[3] Com/Sem dono" << endl;
                cout << "[4] Numero de quartos" << endl;
                cout << "[5] Andar" << endl;
                input = menuValidInput(0, 5);
                switch(input){
                    case 0:
                        return;
                    case 1:
                        while(!valid2) {
                            cout << "Insira a morada a pesquisar (Introduza -1 para retirar o filtro):" << endl;
                            cin.ignore(1000,'\n');
                            getline(cin, morada);
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input!" << endl;
                                valid2 = false;
                            }
                            else {
                                cout << "Esta morada esta correta? " << morada << endl;
                                cout << "[0] Cancelar" << endl;
                                cout << "[1] Sim" << endl;
                                cout << "[2] Nao" << endl;
                                input = menuValidInput(0, 2);
                                switch (input) {
                                    case 0:
                                        break;
                                    case 1:
                                        valid2 = true;
                                        cout << "Deseja adicionar mais filtros?" << endl;
                                        cout << "[1] Sim" << endl;
                                        cout << "[2] Nao" << endl;
                                        input = menuValidInput(1,2);
                                        if(input == 2) valid = true;
                                        break;
                                    case 2:
                                        valid2 = false;
                                        break;
                                }
                            }
                        }
                        break;
                    case 2:
                        minAInt = areaValidInput("Introduza a area interior minima (-1 para sem limite inferior): ");
                        maxAInt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior): ");
                        if(maxAInt < minAInt) maxAInt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior):");
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 3:
                        cout << "[0] Ambas" << endl;
                        cout << "[1] Apartamentos sem dono" << endl;
                        cout << "[2] Apartamentos com dono" << endl;
                        inputDono = menuValidInput(0,2);
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 4:
                        quartos = apartValidInput("Introduza o numero de quartos (-1 para retirar o filtro): ");
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 5:
                        piso = apartValidInput("Introduza o andar (-1 para retirar o filtro): ");
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                }
            }
            if(quartos != -1) tipo = "T" + to_string(quartos);
            mostrarHabs(searchAparts(searchHabitacao(c.getHabs(), "apartamento"), morada, minAInt, maxAInt, inputDono, tipo, piso));
            menuPesquisaApartamentos(filename, c, servicos);
            break;
    }
}

void menuPesquisaVivendas(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input;
    string morada = "-1";
    double minAInt = -1;
    double maxAInt = -1;
    unsigned short int inputDono = 0;
    double minAExt = -1;
    double maxAExt = -1;
    unsigned short int inputPool = 0;
    bool valid = false;
    bool valid2 = false;
    cout << "========================================" << endl;
    cout << "      Menu de Pesquisa De Vivendas      " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Ver todas as vivendas" << endl;
    cout << "[2] Selecionar filtros de pesquisa" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 2);
    switch (input){
        case 0:
            break;
        case 1:
            mostrarHabs(searchHabitacao(c.getHabs(), "vivenda"));
            menuPesquisaVivendas(filename, c, servicos);
            break;
        case 2:
            while(!valid) {
                cout << "Selecione os filtros que deseja: " << endl;
                cout << "[0] Cancelar" << endl;
                cout << "[1] Morada" << endl;
                cout << "[2] Area interior" << endl;
                cout << "[3] Com/Sem dono" << endl;
                cout << "[4] Area exterior" << endl;
                cout << "[5] Com/Sem piscina" << endl;
                input = menuValidInput(0, 5);
                switch(input){
                    case 0:
                        return;
                    case 1:
                        while(!valid2) {
                            cout << "Insira a morada a pesquisar (Introduza -1 para retirar o filtro):" << endl;
                            cin.ignore(1000,'\n');
                            getline(cin, morada);
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input!" << endl;
                                valid2 = false;
                            }
                            else {
                                cout << "Esta morada esta correta? " << morada << endl;
                                cout << "[0] Cancelar" << endl;
                                cout << "[1] Sim" << endl;
                                cout << "[2] Nao" << endl;
                                input = menuValidInput(0, 2);
                                switch (input) {
                                    case 0:
                                        break;
                                    case 1:
                                        valid2 = true;
                                        cout << "Deseja adicionar mais filtros?" << endl;
                                        cout << "[1] Sim" << endl;
                                        cout << "[2] Nao" << endl;
                                        input = menuValidInput(1,2);
                                        if(input == 2) valid = true;
                                        break;
                                    case 2:
                                        valid2 = false;
                                        break;
                                }
                            }
                        }
                        break;
                    case 2:
                        minAInt = areaValidInput("Introduza a area interior minima (-1 para sem limite inferior): ");
                        maxAInt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior): ");
                        if(maxAInt < minAInt) maxAInt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior):");
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 3:
                        cout << "[0] Ambas" << endl;
                        cout << "[1] Vivendas sem dono" << endl;
                        cout << "[2] Vivendas com dono" << endl;
                        inputDono = menuValidInput(0,2);
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 4:
                        minAExt = areaValidInput("Introduza a area interior minima (-1 para sem limite inferior): ");
                        maxAExt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior): ");
                        if(maxAExt < minAExt) maxAExt = areaValidInput("Introduza a area interior maxima (-1 para sem limite superior):");
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                    case 5:
                        cout << "[0] Ambas" << endl;
                        cout << "[1] Vivendas sem piscina" << endl;
                        cout << "[2] Vivendas com piscina" << endl;
                        inputPool = menuValidInput(0,2);
                        cout << "Deseja adicionar mais filtros?" << endl;
                        cout << "[1] Sim" << endl;
                        cout << "[2] Nao" << endl;
                        input = menuValidInput(1, 2);
                        if (input == 2) valid = true;
                        break;
                }
            }
            mostrarHabs(searchVivendas(searchHabitacao(c.getHabs(), "vivenda"), morada, minAInt, maxAInt, inputDono, minAExt, maxAExt, inputPool));
            menuPesquisaVivendas(filename, c, servicos);
            break;
    }
}

void menuHabitacoes(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input;
    cout << "========================================" << endl;
    cout << "      Menu de Gestao De Habitacoes      " << endl;
    cout << "========================================" << endl;
    cout << "[0] Voltar" << endl;
    cout << "[1] Ver informacao de todas as habitacoes" << endl;
    cout << "[2] Pesquisa de vivendas" << endl;
    cout << "[3] Pesquisa de apartamentos" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0,3);
    switch (input){
        case 0:
            menuPrincipal(filename, c, servicos);
            break;
        case 1:
            mostrarHabs(c.getHabs());
            menuHabitacoes(filename, c, servicos);
            break;
        case 2:
            menuPesquisaVivendas(filename, c, servicos);
            menuHabitacoes(filename, c, servicos);
            break;
        case 3:
            menuPesquisaApartamentos(filename, c, servicos);
            menuHabitacoes(filename, c, servicos);
            break;
    }

}

void menuPrincipal(const string& filename, Condominio &c, vector<Servico>& servicos){
    unsigned short int input;
    cout << "========================================" << endl;
    cout << "Bem-vindo a gestao de " << c.getNome() << endl;
    cout << "========================================" << endl;
    cout << "[0] Sair" << endl;
    cout << "[1] Menu do Condominio" << endl;
    cout << "[2] Menu do Condomino" << endl;
    cout << "[3] Menu de Habitacoes" << endl;
    cout << "[4] Menu de Servicos" << endl;
    cout << "========================================" << endl;
    input = menuValidInput(0, 4);
    switch (input){
        case 0:
            return;
        case 1:
            menuCondominio(filename,c, servicos);
            break;
        case 2:
            menuCondomino(filename, c, servicos);
            break;
        case 3:
            menuHabitacoes(filename, c, servicos);
            break;
        case 4:
            menuServicos(filename, c, servicos);
            break;
    }
}


void menuCondominios(const string& filename, Gestao &g, vector<Servico>& servicos){
    unsigned short int input;
    unsigned int input2;
    BST<Condominio> bst = g.getCondominios();
    BSTItrPre<Condominio> pre(bst);
    BSTItrPre<Condominio> pre2(bst);
    BSTItrIn<Condominio> em(bst);
    BSTItrIn<Condominio> em2(bst);
    BSTItrPost<Condominio> pos(bst);
    BSTItrPost<Condominio> pos2(bst);
    BSTItrLevel<Condominio> niv(bst);
    BSTItrLevel<Condominio> niv2(bst);
    unsigned int i = 0;
    cout << "========================================" << endl;
    cout << "Bem-vindo ao programa de gestao CondomiX" << endl;
    cout << "========================================" << endl;
    cout << "Selecione a listagem dos condominios:   " << endl;
    cout << "========================================" << endl;
    cout << "[0] Sair" << endl;
    cout << "[1] Pre-Ordem" << endl;
    cout << "[2] Em-Ordem" << endl;
    cout << "[3] Pos-Ordem" << endl;
    cout << "[4] Por nivel" << endl;
    input = menuValidInput(0,4);
    switch (input){
        case 0:
            return;
        case 1:
            cout << "Selecione o condominio a gerir:" << endl;
            cout << "[0] Voltar" << endl;
            while(!pre.isAtEnd()){
                cout << "[" << i+1 << "]" << pre.retrieve() << endl;
                cout << "========================================" << endl;
                pre.advance();
                i++;
            }
            input2 = menuValidInput(0,i);
            if(input2 == 0) menuCondominios(filename, g, servicos);
            else {
                for (size_t k = 1; k < input2; k++) {
                    pre2.advance();
                }
                Condominio aux = pre2.retrieve();
                bst.remove(pre2.retrieve());
                menuPrincipal(filename, aux, servicos);
                bst.insert(aux);
                g.setCondominos(bst);
                writeCondominio(filename,bst);
            }
            break;
        case 2:
            cout << "Selecione o condominio a gerir:" << endl;
            cout << "[0] Voltar" << endl;
            while(!em.isAtEnd()){
                cout << "[" << i+1 << "]" << em.retrieve() << endl;
                cout << "========================================" << endl;
                em.advance();
                i++;
            }
            input2 = menuValidInput(0,i);
            if(input2 == 0) menuCondominios(filename, g, servicos);
            else{
                for(size_t k = 1; k<input2; k++){
                    em2.advance();
                }
                Condominio aux = em2.retrieve();
                bst.remove(em2.retrieve());
                menuPrincipal(filename, aux, servicos);
                bst.insert(aux);
                g.setCondominos(bst);
                writeCondominio(filename,bst);
            }
            break;
        case 3:
            cout << "Selecione o condominio a gerir:" << endl;
            cout << "[0] Voltar" << endl;
            while(!pos.isAtEnd()){
                cout << "[" << i+1 << "]" << pos.retrieve() << endl;
                cout << "========================================" << endl;
                pos.advance();
                i++;
            }
            input2 = menuValidInput(0,i);
            if(input2 == 0) menuCondominios(filename, g, servicos);
            else{
                for(size_t k = 1; k<input2; k++){
                    pos2.advance();
                }
                Condominio aux = pos2.retrieve();
                bst.remove(pos2.retrieve());
                menuPrincipal(filename, aux, servicos);
                bst.insert(aux);
                g.setCondominos(bst);
                writeCondominio(filename,bst);
            }
            break;
        case 4:
            cout << "Selecione o condominio a gerir:" << endl;
            cout << "[0] Voltar" << endl;
            while(!niv.isAtEnd()){
                cout << "[" << i+1 << "]" << niv.retrieve() << endl;
                cout << "========================================" << endl;
                niv.advance();
                i++;
            }
            input2 = menuValidInput(0,i);
            if(input2 == 0) menuCondominios(filename, g, servicos);
            else{
                for(size_t k = 1; k<input2; k++){
                    niv2.advance();
                }
                Condominio aux = niv2.retrieve();
                bst.remove(niv2.retrieve());
                menuPrincipal(filename, aux, servicos);
                bst.insert(aux);
                g.setCondominos(bst);
                writeCondominio(filename,bst);
            }
            break;
    }
}
