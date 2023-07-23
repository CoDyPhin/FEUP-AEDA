#include "functionsmenus.h"

void cinignore(){
    while (cin.peek() != '\n')
    {
        cin.ignore(1);
    }
}

unsigned short int menuValidInput(unsigned short int min, unsigned short int max) {
    bool valid = false;
    unsigned short int input;
    string auxS = "(";
    while(!valid) {
        cout << "Option: ";
        cin >> input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            for(size_t i = min; i < max; i++)
            {
                auxS+= to_string(i) + ", ";
            }
            auxS += to_string(max) + ")";
            cout << "Invalid input! A opcao deve ser um numero " + auxS << endl;
        }
        else if((input < min || input > max)){
            cinignore();
            for(size_t i = min; i < max; i++)
            {
                auxS+= to_string(i) + ", ";
            }
            auxS += to_string(max) + ")";
            cout << "Invalid input! A opcao deve ser um numero " + auxS << endl;
        }
        else
            valid = true;
        auxS = "(";
    }
    return input;
}

unsigned numbersValidInput(unsigned min, unsigned max, const string& msg) {
    bool valid = false;
    unsigned input;
    while(!valid) {
        cout << msg << endl;
        cin >> input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid input! A opcao deve ser um numero entre " << min << " e " << max << endl;
        }
        else if((input < min || input > max)){
            cinignore();
            cout << "Invalid input! A opcao deve ser um numero entre" << min << " e " << max << endl;
        }
        else
            valid = true;
    }
    return input;
}

unsigned long int nifValidInput() {
    bool valid = false;
    unsigned long int input;
    unsigned short int aux;
    while(!valid) {
        cout << "Introduza o NIF desejado: ";
        cin >> input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid input! O NIF deve ser um numero"<< endl;
        }
        else if((input <= 0 || input > 999999999 || (to_string(input).size() != 9))){
            cinignore();
            cout << "Invalid input! O NIF e um numero com 9 digitos"<< endl;
        }
        else {
            cout << "Este NIF esta correto? " << input << endl;
            cout << "[1] Sim" << endl;
            cout << "[2] Nao" << endl;
            aux = menuValidInput(1, 2);
            if(aux == 1) valid = true;
        }
    }
    return input;
}

double areaValidInput(string msg) {
    bool valid = false;
    double input;
    unsigned short int aux;
    while(!valid) {
        cout << msg;
        cin >> input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid input! Deve ser um numero"<< endl;
        }
        else if(input < -1){
            cinignore();
            cout << "Invalid input! Nao existem distancias negativas"<< endl;
        }
        else {
            cout << "Este valor esta correto? " << input << endl;
            cout << "[1] Sim" << endl;
            cout << "[2] Nao" << endl;
            aux = menuValidInput(1, 2);
            if(aux == 1) valid = true;
        }
    }
    return input;
}

short int apartValidInput(string msg) {
    bool valid = false;
    short int input;
    unsigned short int aux;
    while(!valid) {
        cout << msg;
        cin >> input;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid input! Introduza um numero"<< endl;
        }
        else if((input < -1 || input > 100)){
            cinignore();
            cout << "Invalid input! Introduza um numero entre 0 e 100"<< endl;
        }
        else {
            cout << "Este valor esta correto? " << input << endl;
            cout << "[1] Sim" << endl;
            cout << "[2] Nao" << endl;
            aux = menuValidInput(1, 2);
            if(aux == 1) valid = true;
        }
    }
    return input;
}

string timeValidInput(string msg){
    bool valid = false;
    string input;
    unsigned short int aux;
    while(!valid){
        cout << msg;
        //cin.ignore(1000,'\n');
        getline(cin, input);
        if(cin.fail() || (input.size() != 4 && input.size() != 5)) {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Hora invalida, verifique se esta no formato HH:MM" << endl;
        }
        else if (input.size() == 4){
            if(!(isdigit(input.at(0)) && input.at(1) == ':' && isdigit(input.at(2)) && isdigit(input.at(3)))){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Hora invalida, verifique se esta no formato HH:MM" << endl;
            }
            else {
                if((input.at(0)-'0'>=0 && input.at(0)-'0'<=9 && stoi(input.substr(2,input.npos))>=0 && stoi(input.substr(2,input.npos))<=59)){
                    cout << "Esta hora esta correta? " << input << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    aux = menuValidInput(1, 2);
                    if(aux == 1) valid = true;
                }
                else{
                    cout << "Hora invalida, verifique se as horas sao inferiores a 24 e os minutos a 60" << endl;
                }
            }
        }
        else if (input.size() == 5){
            if(!(isdigit(input.at(0)) && isdigit(input.at(1)) && input.at(2) == ':' && isdigit(input.at(3)) && isdigit(input.at(4)))){
                cin.clear();
                cinignore();
                cout << "Hora invalida, verifique se esta no formato HH:MM" << endl;
            }
            else {
                if((stoi(input.substr(0,2))<=23 && stoi(input.substr(0,2))>=0 && stoi(input.substr(3,input.npos))>=0 && stoi(input.substr(3,input.npos))<=59)) {
                    cout << "Esta hora esta correta? " << input << endl;
                    cout << "[1] Sim" << endl;
                    cout << "[2] Nao" << endl;
                    aux = menuValidInput(1, 2);
                    if (aux == 1) valid = true;
                }
                else{
                    cout << "Hora invalida, verifique se as horas sao inferiores a 24 e os minutos a 60" << endl;
                }
            }
        }

    }
    return input;
}

void mostrarHabs(vector<Habitacao*> habs){
    if(habs.empty()) cout << "Nao foram encontradas habitacoes com estes criterios!" << endl;
    else{
        Apartamento* a;
        for (int i = 0; i < habs.size(); i++) {
            a = dynamic_cast<Apartamento*>(habs.at(i));
            if(a != nullptr){
                cout <<"[" <<  i+1 << "] " << *a;
            }
            else{
                Vivenda* v = dynamic_cast<Vivenda*>(habs.at(i));
                cout <<"[" <<  i+1 << "] " << *v;
            }
        }
    }
}

bool addCondomino(Condominio& c,string name, unsigned long int nif, unsigned short int index){
    vector<Habitacao*> habs;
    habs.push_back(c.getHabsDisp().at(index));
    Condomino co(name,nif, c.getMensalA(), c.getMensalV(), c.getValorAExt(), c.getValorPool(), c.getValorTipo(), c.getValorPiso(),currentDateTime(),habs);
    vector<Condomino> condominos = c.getCondomino();
    condominos.push_back(co);
    sort(condominos.begin(), condominos.end());
    return c.setCondominos(condominos);

}

int searchCondomino(vector<Condomino> c, unsigned long int nif){
    int left = 0, right = c.size() -1;
    while (left <= right){
        int middle = (left + right) / 2;
        if (c.at(middle).getNif() < nif)
            left = middle + 1;
        else if (nif < c.at(middle).getNif())
            right= middle-1;
        else
            return middle;
    }
    return -1;
}

int searchHab(vector<Habitacao*> habs, Habitacao* habSel){
    for(size_t i = 0; i < habs.size(); i++){
        if(habSel==habs.at(i)) return i;
    }
    return -1;
}

bool eraseCondomino(Condominio& c, unsigned short int index){
    vector<Habitacao*> habs = c.getHabs();
    vector<Condomino> condominos = c.getCondomino();
    unsigned long int nif = condominos.at(index).getNif();
    for (int i = 0; i < habs.size() ; i++) {
        if(habs.at(i)->getOwnerNif() == nif)
            habs.at(i)->setOwnerNif(0);
    }
    condominos.erase(condominos.begin()+index);

    return c.setHabs(habs) && c.setCondominos(condominos);
}

bool mudarDisp(Condominio& c, unsigned short int servIndex, Funcionario f, double inicio, double fim){
    vector<Servico> servs = c.getServicos();
    vector<Funcionario> funcs = servs.at(servIndex).getFuncs();
    bool valid;
    map<double,bool> disp = f.getDisp();
    for (int i = 0; i < funcs.size() ; i++) {
        if(funcs.at(i) == f){
            funcs.erase(funcs.begin()+i);
            break;
        }
    }
    for(auto it = disp.begin(); it != disp.end(); it++){
        if(it->first >= inicio && it->first < fim)
            it->second = false;
    }
    valid = f.setDisp(disp);
    funcs.push_back(f);
    valid = servs.at(servIndex).setFuncs(funcs) && valid;
    valid = c.setServicos(servs) && valid;

    return valid;
}

void showServs(Condominio& c){
    vector<Servico> servs = c.getServicos();
    for (size_t i = 0; i < servs.size() ; i++) {
        cout << "[" << i+1 << "] " << servs.at(i).getTipo() << endl;
    }
}

vector<Funcionario> searchFuncsDispo(Condominio& c,double inicio, double fim, unsigned short int index){
    vector<Funcionario> funcs = c.getServicos().at(index).getFuncs();
    vector<Funcionario> result;
    for (size_t i = 0; i < funcs.size() ; i++) {
        map<double,bool> disp = funcs.at(i).getDisp();
        for(auto it = disp.begin(); it != disp.end(); it++){
            if(inicio > fim){
                if((it->first >= inicio && it->first < 24 && it->second )|| (it->first < fim && it->second)) {
                    result.push_back(funcs.at(i));
                    break;
                }
            }
            else {
                if (it->first >= inicio && it->first < fim && it->second) {
                    result.push_back(funcs.at(i));
                    break;
                }
            }
        }
    }
    return result;
}

bool checkDisponibilidade(map<double,bool> disp, double inicio, double fim){
    bool valid = false;
    for(auto it = disp.begin(); it != disp.end(); it++){
        if(it->first == inicio && it->second)
            valid = true;
        else if (it->first > inicio && it->first < fim && it->second && valid)
            continue;
        else if(it->first == fim)
            break;
        else
            valid = false;
    }
    return valid;
}

vector<Habitacao*> searchHabitacao(vector<Habitacao*> habs, string tipo){
    vector<Habitacao*> result;
    if(tipo == "apartamento") {
        Apartamento *a;
        for (size_t i = 0; i < habs.size(); ++i) {
            a = dynamic_cast<Apartamento *>(habs.at(i));
            if (a != nullptr)
                result.push_back(habs.at(i));
        }
    }
    else if(tipo == "vivenda"){
        Vivenda *v;
        for (size_t i = 0; i < habs.size(); ++i) {
            v = dynamic_cast<Vivenda *>(habs.at(i));
            if (v != nullptr)
                result.push_back(habs.at(i));
        }
    }
    return result;
}

vector<Habitacao*> searchAparts(vector<Habitacao*> habs, string morada, double minAInt, double maxAInt, unsigned short int inputDono, string tipo, short int piso) {
    vector<Habitacao*> result;
    vector<Habitacao*> aux1;
    if(morada == "-1") morada = "";
    if(maxAInt == -1) maxAInt = 9999999999999;
    int auxT = (tipo != "-1");
    int auxP = (piso != -1);
    if(habs.empty()) cout << "Nao existem vivendas no condominio!" << endl;
    else {
        switch (inputDono) {
            case 0:
                aux1 = habs;
                break;
            case 1:
                for (Habitacao *hab: habs) {
                    Apartamento *v = dynamic_cast<Apartamento *>(hab);
                    if (v->getOwnerNif() == 0) {
                        aux1.push_back(hab);
                    }
                }
                break;
            case 2:
                for (Habitacao *hab: habs) {
                    Apartamento *v = dynamic_cast<Apartamento *>(hab);
                    if (v->getOwnerNif() != 0) {
                        aux1.push_back(hab);
                    }
                }
                break;
        }
        switch (auxT){
            case 0:
                switch (auxP){
                    case 0:
                        for(Habitacao* hab: aux1){
                            Apartamento* v = dynamic_cast<Apartamento*>(hab);
                            if((v->getMorada().find(morada) != v->getMorada().npos) && (v->getAreaInt()>=minAInt && v->getAreaInt()<=maxAInt) && (v->getPiso() == piso) && (v->getTipo().find(tipo) != v->getTipo().npos)){
                                result.push_back(hab);
                            }
                        }
                        break;
                    case 1:
                        for(Habitacao* hab: aux1){
                            Apartamento* v = dynamic_cast<Apartamento*>(hab);
                            if((v->getMorada().find(morada) != v->getMorada().npos) && (v->getAreaInt()>=minAInt && v->getAreaInt()<=maxAInt) && (v->getPiso() == piso)){
                                result.push_back(hab);
                            }
                        }
                        break;
                }
                break;
            case 1:
                switch (auxP){
                    case 0:
                        for(Habitacao* hab: aux1){
                            Apartamento* v = dynamic_cast<Apartamento*>(hab);
                            if((v->getMorada().find(morada) != v->getMorada().npos) && (v->getAreaInt()>=minAInt && v->getAreaInt()<=maxAInt) && (v->getTipo().find(tipo) != v->getTipo().npos)){
                                result.push_back(hab);
                            }
                        }
                        break;
                    case 1:
                        for(Habitacao* hab: aux1){
                            Apartamento* v = dynamic_cast<Apartamento*>(hab);
                            if((v->getMorada().find(morada) != v->getMorada().npos) && (v->getAreaInt()>=minAInt && v->getAreaInt()<=maxAInt)){
                                result.push_back(hab);
                            }
                        }
                        break;
                }
                break;
        }
    }
    return result;
}

vector<Habitacao*> searchVivendas(vector<Habitacao*> habs, string morada, double minAInt, double maxAInt, unsigned short int inputDono, double minAExt, double maxAExt, unsigned short int inputPool){
    vector<Habitacao*> result;
    vector<Habitacao*> aux1;
    vector<Habitacao*> aux2;
    if(morada == "-1") morada = "";
    if(maxAInt == -1) maxAInt = 9999999999999;
    if(maxAExt == -1) maxAExt = 9999999999999;
    if(habs.empty()) cout << "Nao existem vivendas no condominio!" << endl;
    else{
        switch (inputDono){
            case 0:
                aux1 = habs;
                break;
            case 1:
                for(Habitacao* hab: habs){
                    Vivenda* v = dynamic_cast<Vivenda*>(hab);
                    if(v->getOwnerNif()==0){
                        aux1.push_back(hab);
                    }
                }
                break;
            case 2:
                for(Habitacao* hab: habs){
                    Vivenda* v = dynamic_cast<Vivenda*>(hab);
                    if(v->getOwnerNif() != 0){
                        aux1.push_back(hab);
                    }
                }
                break;
        }
        switch (inputPool){
            case 0:
                aux2 = aux1;
                break;
            case 1:
                for(Habitacao* hab: aux1){
                    Vivenda* v = dynamic_cast<Vivenda*>(hab);
                    if(!v->getPool()){
                        aux2.push_back(hab);
                    }
                }
                break;
            case 2:
                for(Habitacao* hab: aux1){
                    Vivenda* v = dynamic_cast<Vivenda*>(hab);
                    if(v->getPool()){
                        aux2.push_back(hab);
                    }
                }
                break;
        }
        for(Habitacao* hab: aux2){
            Vivenda* v = dynamic_cast<Vivenda*>(hab);
            if((v->getMorada().find(morada) != v->getMorada().npos) && (v->getAreaInt()>=minAInt && v->getAreaInt()<=maxAInt) && (v->getAreaExt()>=minAExt && v->getAreaExt()<=maxAExt)){
                result.push_back(hab);
            }
        }
    }
    return result;
}