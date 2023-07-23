#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "functions.h"
#include "time.h"

using namespace std;

string funcsFile;
//string pwd = string(get_current_dir_name()) + "/";
string pwd = "../";

void tolower(string &str){
    for (int i = 0; i <str.size() ; i++) {
        str.at(i) = tolower(str.at(i));
    }
}

double timeToDouble(const string& horaString){
    string auxstring;
    double auxdouble;
    auxstring = horaString.substr(0, horaString.find(':'));
    auxdouble = stod(auxstring);
    auxstring = horaString.substr(horaString.find(':')+1,horaString.npos);
    if(stod(auxstring)/60 >= 0.5)
        auxdouble += 0.5;
    return auxdouble;
}

string removeSpaces(string fullstring){
    string result;
    for (char i : fullstring) {
        if (i != ' ') {
            result += i;
        }
    }
    return result;
}

vector<string> stringSplit(string fullstring, char delimiter){
    vector<string> result;
    size_t aux;
    fullstring.push_back(delimiter);
    while (!fullstring.empty()) {
        aux = fullstring.find(delimiter);
        result.push_back(removeSpaces(fullstring.substr(0, aux)));
        fullstring = fullstring.substr(aux, fullstring.npos);
        fullstring.erase(0,1);
    }
    return result;
}

vector<string> stringSplitWithSpaces(string fullstring, char delimiter){
    vector<string> result;
    size_t aux;
    fullstring.push_back(delimiter);
    while (!fullstring.empty()) {
        aux = fullstring.find(delimiter);
        result.push_back(fullstring.substr(0, aux));
        fullstring = fullstring.substr(aux, fullstring.npos);
        fullstring.erase(0,1);
    }
    return result;
}


map<double,bool> makeHorario(string horario){
    vector<string> aux = stringSplit(horario, ';');
    vector<string> aux2;
    vector<string> horarioS;
    vector<double> horarioD;
    map<double,bool> horarioMap;
    for (vector<string>::iterator it = aux.begin(); it < aux.end(); it++) {
        aux2 = stringSplit(*it, '-');
        horarioS.insert(horarioS.end(),aux2.begin(),aux2.end());
    }
    for (vector<string>::iterator it = horarioS.begin(); it < horarioS.end(); it++){
        horarioD.push_back(timeToDouble(*it));
    }
    for (double i = 0; i < 24; i+=0.5){
        horarioMap[i] = false;
    }
    for (size_t i = 0; i < horarioD.size()-1; i+=2){
        double count = 0;
        if(horarioD.at(i) > horarioD.at(i+1)){
            while (horarioD.at(i) + count < 24) {
                horarioMap[horarioD.at(i) + count] = true;
                count += 0.5;
            }
            count = 0;
            while(count < horarioD.at(i+1)){
                horarioMap[count] = true;
                count += 0.5;
            }
        }
        else {
            while (horarioD.at(i) + count < horarioD.at(i + 1)) {
                horarioMap[horarioD.at(i) + count] = true;
                count += 0.5;
            }
        }
    }
    return horarioMap;
}

map<double,bool> makeDisp(map<double,bool> horario, string disp){
    vector<string> aux = stringSplit(disp, ';');
    vector<string> aux2;
    vector<string> dispS;
    vector<double> dispD;
    map<double,bool> dispMap = horario;
    for (vector<string>::iterator it = aux.begin(); it < aux.end(); it++) {
        aux2 = stringSplit(*it, '-');
        dispS.insert(dispS.end(),aux2.begin(),aux2.end());
    }
    for (vector<string>::iterator it = dispS.begin(); it < dispS.end(); it++){
        dispD.push_back(timeToDouble(*it));
    }
    for (size_t i = 0; i < dispD.size()-1; i+=2){
        double count = 0;
        while(dispD.at(i)+count<dispD.at(i+1)){
            dispMap[dispD.at(i)+count] = false;
            count += 0.5;
        }
    }
    return dispMap;
}

vector<Servico>buildServ(vector<string> servscons, vector<Servico> servsdispo){
    vector<Servico> result;
    for (int i = 0; i < servscons.size() ; i++) {
        for (int j = 0; j < servsdispo.size() ; j++) {
            if (servscons.at(i) == servsdispo.at(j).getTipo())
                result.push_back(servsdispo.at(j));
        }
    }
    return result;
}

unsigned int stringDateToInt(string data){
    vector<string> elements = stringSplit(data,'-');
    unsigned int result = 0;
    result += stoi(elements.at(0))*10000;
    result += stoi(elements.at(1))*100;
    result += stoi(elements.at(2));

    return result;
}

string intDateToString(unsigned int data){
    string result = "";
    string aux = to_string(data);
    result += aux.substr(0,4) + "-" + aux.substr(4,2) + "-" + aux.substr(6,2);

    return result;
}

void sortFuncionario(vector<Funcionario> funcs){
    sort(funcs.begin(),funcs.end(),[](Funcionario f1, Funcionario f2){
        if(f1.getData() == f2.getData())
            return f1.getTipo() < f2.getTipo();
        else
            return f1.getData() == f2.getData();
    });
}

unsigned int  currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return stringDateToInt(buf);
}

HashTableOldCondominos readHistoricoCondomino(const string& filename){
    ifstream file;
    HashTableOldCondominos result;
    file.open(pwd+filename);
    if(file.is_open() && filename != ""){
        string name, line;
        unsigned long int nif;
        unsigned int beginDate, endDate;
        while(!file.eof()){
            getline(file,name);
            getline(file,line);
            nif = stoi(line);
            getline(file,line);
            beginDate = stringDateToInt(line);
            getline(file,line);
            endDate = stringDateToInt(line);
            getline(file,line);
            Condomino c(name,nif,beginDate,endDate);
            result.insert(c);
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro do historico de condominos");
    }
}

vector<Funcionario> readHistorico(const string& filename){
    ifstream file;
    vector<Funcionario> result;
    file.open(pwd+filename);
    if(file.is_open() && filename != ""){
        string line, name, tipo;
        unsigned int data;
        map<double,bool> horario, disp;
        while(!file.eof()){
            getline(file,line);
            while (line == "===================="){
                getline(file,line);
                data = stringDateToInt(line);
                getline(file,line);
                while(line == "::::::::::"){
                    getline(file,tipo);
                    getline(file,line);
                    while (line == "----------"){
                        getline(file,name);
                        getline(file,line);
                        horario = makeHorario(line);
                        getline(file,line);
                        disp = makeDisp(horario,line);
                        Funcionario f(name,tipo,horario,disp,data);
                        result.push_back(f);
                        getline(file,line);
                    }
                }
            }
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro do historico");
    }
}

bool writeHistorico(const string& filename, vector<Funcionario> funcs) {
    ifstream testfile(pwd + filename);
    if (!testfile)
        throw (ErrorWritingFile("ficheiro do historico"));
    else {
        ofstream file;
        file.open(pwd + filename);
        unsigned int data = 0;
        string tipo;
        if (file.is_open()) {
            file << "====================" << endl;
            for (size_t i = 0; i < funcs.size(); i++) {
                if (i == 0) {
                    file << intDateToString(funcs.at(i).getData()) << endl;
                    data = funcs.at(i).getData();
                    file << "::::::::::" << endl;
                    file << funcs.at(i).getTipo() << endl;
                    tipo = funcs.at(i).getTipo();
                    file << "----------" << endl;
                    file << funcs.at(i).getNome() << endl;
                    file << horarioToString(funcs.at(i).getHorario()) << endl;
                    file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp())) << endl;
                }
                else if (i == funcs.size() - 1) {
                    if (funcs.at(i).getData() == data && funcs.at(i).getTipo() == tipo) {
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp()));
                    }
                     else if (funcs.at(i).getData() == data && funcs.at(i).getTipo() != tipo) {
                        tipo = funcs.at(i).getTipo();
                        file << "::::::::::" << endl;
                        file << funcs.at(i).getTipo() << endl;
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp()));
                    } else {
                        data = funcs.at(i).getData();
                        tipo = funcs.at(i).getTipo();
                        file << "====================" << endl;
                        file << intDateToString(funcs.at(i).getData()) << endl;
                        file << "::::::::::" << endl;
                        file << funcs.at(i).getTipo() << endl;
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp()));
                    }

                } else {
                    if (funcs.at(i).getData() == data && funcs.at(i).getTipo() == tipo) {
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp())) << endl;
                    }
                    else if (funcs.at(i).getData() == data && funcs.at(i).getTipo() != tipo) {
                        tipo = funcs.at(i).getTipo();
                        file << "::::::::::" << endl;
                        file << funcs.at(i).getTipo() << endl;
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp())) << endl;
                    } else {
                        data = funcs.at(i).getData();
                        tipo = funcs.at(i).getTipo();
                        file << "====================" << endl;
                        file << intDateToString(funcs.at(i).getData()) << endl;
                        file << "::::::::::" << endl;
                        file << funcs.at(i).getTipo() << endl;
                        file << "----------" << endl;
                        file << funcs.at(i).getNome() << endl;
                        file << horarioToString(funcs.at(i).getHorario()) << endl;
                        file << horarioToString(servsMap(funcs.at(i).getHorario(), funcs.at(i).getDisp())) << endl;
                    }
                }
            }
                file.close();
                cout << "Ficheiro do historico atualizado!" << endl;
                return false;
            }
        }
        return true;
}

bool writeHistoricoCondomino(const string& filename, HashTableOldCondominos condominos){
    ifstream testfile(pwd + filename);
    if (!testfile)
        throw (ErrorWritingFile("ficheiro do historico dos condominos"));
    else {
        ofstream file;
        file.open(pwd + filename);
        int count = 0;
        if(file.is_open()){
            for(auto it = condominos.begin(); it != condominos.end();it++){
                file << it->getNome() << endl;
                file << it->getNif() << endl;
                file << intDateToString(it->getStartDate()) << endl;
                if(count < condominos.size()-1){
                    file << intDateToString(it->getEndDate()) << endl;
                    file << "====================" << endl;
                }
                else{
                    file << intDateToString(it->getEndDate());
                }
                count++;
            }
            file.close();
            cout << "Ficheiro do historico dos condominos atualizado!" << endl;
            return false;
        }
    }
    return true;
}

bool writeFuncionarios(vector<Funcionario> funcs){

    ifstream testfile(pwd + "funcionarios.txt");
    if(!testfile)
        throw(ErrorWritingFile("ficheiro dos funcionarios"));
    else {
        ofstream file;
        file.open(pwd + "funcionarios.txt");
        if (file.is_open()) {
            for (unsigned int i = 0; i < funcs.size(); i++) {
                file << funcs.at(i).getNome() << endl;
                file << funcs.at(i).getTipo() << endl;
                file << horarioToString(funcs.at(i).getHorario()) << endl;
                if(funcs.at(i).getDisp() == funcs.at(i).getHorario())
                    file << "0" << endl;
                else{
                    file << horarioToString(servsMap(funcs.at(i).getHorario(),funcs.at(i).getDisp())) << endl;
                }
                if(i != funcs.size()-1){
                    file << intDateToString(funcs.at(i).getData()) << endl;
                    file << "====================" << endl;
                }
                else{
                    file << intDateToString(funcs.at(i).getData());
                }
            }
            file.close();
            cout << "Ficheiro dos funcionarios atualizado!" << endl;
            return false;
        }
        return true;
    }
}

vector<Funcionario> readFuncionarios(const string& filename, vector<Funcionario>& funcsAntigos){
    ifstream file;
    vector<Funcionario> result;
    file.open(pwd+filename);
    if(file.is_open() && filename != ""){
        string line, name, tipo,  separador = "====================";
        unsigned int data;
        bool write = false;
        map<double,bool> horario, disp;
        while(!file.eof()){
            getline(file,name);
            getline(file,tipo);
            getline(file,line);
            horario = makeHorario(line);
            getline(file,line);
            if(line == "0")
                disp = horario;
            else
                disp = makeDisp(horario,line);
            getline(file,line);
            data = stringDateToInt(line);
            getline(file,line);
            Funcionario f(name,tipo, horario, disp,data);
            result.push_back(f);
        }
        file.close();
        data = currentDateTime();
        for (size_t i = 0; i < result.size() ; i++) {
            if(result.at(i).getData() != data) {
                write = true;
                if(result.at(i).getData() < data && result.at(i).getDisp() != result.at(i).getHorario()){
                    funcsAntigos.push_back(result.at(i));
                }
                result.at(i).setDisp(result.at(i).getHorario());
                result.at(i).setData(data);
            }
        }
        if(write)
            if(writeFuncionarios(result)) throw ErrorReadingFile("ficheiro dos funcionarios");

        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro dos funcionarios");
    }
}

string horarioToString(map<double,bool> horario){
    string result;
    bool check = true;
    for(auto it = horario.begin(); it != horario.end(); it++){
        if(it->second && check){
            if(abs(int(it->first) - it->first) == 0)
                result += to_string(int(it->first)) + ":00 - ";
            else
                result += to_string(int(it->first)) + ":30 - ";
            check = false;
        }
        else if(!(it->second) && !check){
            if(abs(int(it->first) - it->first) == 0)
                result += to_string(int(it->first)) + ":00; ";
            else
                result += to_string(int(it->first)) + ":30; ";
            check = true;
        }
    }
    result.pop_back();
    result.pop_back();
    if(!check){
        result.pop_back();
        result.replace(result.find("0:00"),4,result.substr(result.find_last_of(" ")+1,result.npos));
        result = result.substr(0,result.find_last_of(" "));
        result.pop_back();
    }

    return result;
}

map<double,bool> servsMap(map<double,bool> horario, map<double,bool> disp) {
    map<double,bool> result;
    for (double i = 0; i < 24; i+=0.5){
        result[i] = false;
    }
    for(auto it = result.begin(); it != result.end(); it++) {
        if(horario[it->first] && (!disp[it->first]))
            result[it->first] = true;
    }

    return result;
}


bool writeFuncionarios(vector<Servico> servs){
    vector<Funcionario> funcs;
    for (size_t i = 0; i < servs.size() ; i++) {
        for (size_t j = 0; j < servs.at(i).getFuncs().size() ; j++) {
            funcs.push_back(servs.at(i).getFuncs().at(j));
        }
    }
    ifstream testfile(pwd + "funcionarios.txt");
    if(!testfile)
        throw(ErrorWritingFile("ficheiro dos funcionarios"));
    else {
        ofstream file;
        file.open(pwd + "funcionarios.txt");
        if (file.is_open()) {
            for (unsigned int i = 0; i < funcs.size(); i++) {
                file << funcs.at(i).getNome() << endl;
                file << funcs.at(i).getTipo() << endl;
                file << horarioToString(funcs.at(i).getHorario()) << endl;
                if(funcs.at(i).getDisp() == funcs.at(i).getHorario())
                    file << "0" << endl;
                else{
                    file << horarioToString(servsMap(funcs.at(i).getHorario(),funcs.at(i).getDisp())) << endl;
                }
                if(i != funcs.size()-1){
                    file << intDateToString(funcs.at(i).getData()) << endl;
                    file << "====================" << endl;
                }
                else{
                    file << intDateToString(funcs.at(i).getData());
                }
            }
            file.close();
            cout << "Ficheiro dos funcionarios atualizado!" << endl;
            return false;
        }
        return true;
    }
}

vector<Funcionario> servsFunc(string tipo, vector<Funcionario> funcs){
    vector<Funcionario> result;
    for (int i = 0; i < funcs.size() ; i++) {
        string aux = funcs.at(i).getTipo();
        tolower(aux);
        tolower(tipo);
        if(aux == tipo)
            result.push_back(funcs.at(i));
    }
    return result;
}

vector<Servico> readServicos(const string& filename, vector<Funcionario>& funcsAntigos){
    ifstream file;
    vector<Servico>result;
    file.open(pwd+filename);
    if(file.is_open() && filename != ""){
        string line, tipo;
        vector<Funcionario>funcionarios;
        string separador = "===================";
        getline(file,funcsFile);
        while(!file.eof()){
            getline(file,tipo);
            getline(file,line);
            funcionarios = readFuncionarios(funcsFile, funcsAntigos);
            funcionarios = servsFunc(tipo, funcionarios);
            Servico s(tipo,funcionarios);
            result.push_back(s);
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro dos servicos");
    }
}

vector<Habitacao*> readHabitacao(const string& filename,const vector<Servico>&servsdispo){
    ifstream file;
    vector<Habitacao*> result;
    file.open(pwd+filename);
    if (file.is_open() && filename != ""){
        string line, tipo,morada;
        unsigned long int ownerNif;
        unsigned int piso;
        double areaInt, areaExt;
        vector<Servico> servs;
        bool pool = true;
        while(!file.eof()){
            getline(file,tipo);
            tolower(tipo);
            if (tipo == "vivenda"){
                pool = true;
                getline(file,line);
                ownerNif = stoi(line);
                getline(file,morada);
                getline(file,line);
                areaInt = stod(line);
                getline(file,line);
                areaExt = stod(line);
                getline(file,line);
                tolower(line);
                if (line == "false") {
                    pool = false;
                }
                getline(file,line);
                servs = buildServ(stringSplit(line,','),servsdispo);
                Vivenda* v = new Vivenda(ownerNif, morada, areaInt,areaExt,servs, pool);
                Habitacao* h = v;
                result.push_back(h);
            }
            else if(tipo == "apartamento"){
                getline(file,line);
                ownerNif = stoi(line);
                getline(file,morada);
                getline(file,line);
                areaInt = stod(line);
                getline(file,tipo);
                getline(file,line);
                piso = stoi(line);
                getline(file,line);
                servs = buildServ(stringSplit(line,','),servsdispo);
                Apartamento* a = new Apartamento(ownerNif,morada,areaInt, servs,tipo,piso);
                Habitacao* h = a;
                result.push_back(h);
            }
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro de habitacoes");
    }

}

vector<Habitacao*> habsOwned(unsigned long int nif, vector<Habitacao*> habs){
    vector<Habitacao*> result;
    for (int i = 0; i < habs.size() ; i++) {
        if (habs.at(i)->getOwnerNif() == nif)
            result.push_back(habs.at(i));
    }
    return result;
}

vector<Condomino> readCondomino(const string& filename, const vector<Habitacao*>& availableHabs, double mensalA, double mensalV, double valorAExt, double valorPool, double valorTipo, double valorPiso){
    ifstream file;
    file.open(pwd+filename);
    vector<Condomino> result;
    if(file.is_open() && ""){
        string line, name;
        unsigned long int nif;
        unsigned int date;
        vector<Habitacao*> ownedHabs;
        while(!file.eof()){
            getline(file,name);
            getline(file,line);
            nif = stoi(line);
            ownedHabs = habsOwned(nif, availableHabs);
            getline(file,line);
            date = stringDateToInt(line);
            getline(file,line);
            Condomino c(name, nif, mensalA, mensalV, valorAExt, valorPool, valorTipo, valorPiso,date, ownedHabs);
            if(c.getOwnedHabs().size() != 0) result.push_back(c);
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro dos condominos");
    }

}

priority_queue<Transporte>readTransportes(const string& filename){
    ifstream file;
    file.open(pwd+filename);
    if(file.is_open() && filename != ""){
        priority_queue<Transporte> result;
        string line,tipo,destino,paragens;
        vector<string>aux,aux1;
        vector<Paragem> paragem;
        while(!file.eof()){
            getline(file,tipo);
            getline(file,destino);
            getline(file,paragens);
            aux = stringSplitWithSpaces(paragens,';');
            for (int i = 0; i < aux.size(); i++) {
                aux1 = stringSplitWithSpaces(aux.at(i),'-');
                Paragem p;
                p.name = aux1.at(0);
                p.distance = stod(aux1.at(1));
                paragem.push_back(p);
            }
            sort(paragem.begin(),paragem.end(),[](Paragem p1, Paragem p2){
                return p1.distance < p2.distance;
            });
            result.push(Transporte(tipo,destino,paragem.at(0),paragem));
            paragem.clear();
            getline(file,line);
        }
        file.close();
        return result;
    }
    else{
        throw ErrorReadingFile("ficheiro dos transportes");
    }
}

Gestao readCondominio(const string& filename,const vector<Servico>& servsdispo, vector<Funcionario>& funcs){
    ifstream file;
    file.open(pwd+filename);
    if (file.is_open() && filename != ""){
        string line, nome, localizacao, habsFile, servicos, condominosFile, historicoFile, historicoConFile,transportesFile;
        double  mensalV, mensalA;
        vector<string> valori;
        vector<Habitacao*> habs;
        vector<Servico> servs;
        vector<Condomino> condominos;
        vector<Funcionario> historicoAtual;
        HashTableOldCondominos oldCondominos;
        priority_queue<Transporte> transportes;
        Gestao g;
        bool write = false;
        while (!file.eof()){
            getline(file,nome);
            getline(file,localizacao);
            getline(file,line);
            mensalV = stod(line);
            getline(file,line);
            mensalA = stod(line);
            getline(file,line);
            valori = stringSplit(line,'/');
            getline(file,habsFile);
            habs = readHabitacao(habsFile,servsdispo);
            getline(file,condominosFile);
            condominos = readCondomino(condominosFile, habs, mensalA, mensalV, stod(valori.at(0)), stod(valori.at(1)), stod(valori.at(2)), stod(valori.at(3)));
            sort(condominos.begin(), condominos.end());
            getline(file, servicos);
            servs = buildServ(stringSplit(servicos,','),servsdispo);
            getline(file,historicoFile);
            historicoAtual = readHistorico(historicoFile);
            if(!funcs.empty()){
                for (size_t i = 0; i < funcs.size() ; i++) {
                    auto it = find(historicoAtual.begin(),historicoAtual.end(), funcs.at(i));
                    if (it == historicoAtual.end()){
                        write = true;
                        historicoAtual.push_back(funcs.at(i));
                    }
                    else{
                        if(funcs.at(i).getDisp() != it->getDisp()){
                            write = true;
                            map<double,bool> aux;
                            for (double j = 0; j < 24; j+=0.5) {
                                aux[j] = funcs.at(i).getDisp()[j] & it->getDisp()[j];
                            }
                            if(!(it->setDisp(aux))) throw ErrorSettingValue("disponibilidade do funcionario");
                        }
                    }
                }
                if(write)
                    sortFuncionario(historicoAtual);
                if((writeHistorico(historicoFile,historicoAtual))) throw ErrorWritingFile("ficheiro do historico");
            }
            getline(file,historicoConFile);
            oldCondominos = readHistoricoCondomino(historicoConFile);
            getline(file,transportesFile);
            transportes = readTransportes(transportesFile);
            g.addCondominio(Condominio(nome,localizacao,mensalV,mensalA,stod(valori.at(0)), stod(valori.at(1)), stod(valori.at(2)), stod(valori.at(3)),habs,servs, habsFile, condominosFile, historicoFile, historicoConFile,transportesFile, condominos, historicoAtual, oldCondominos,transportes));
            getline(file,line);
        }
        file.close();
        return g;

        /*if (!habs.empty() && !servs.empty() && !condominos.empty()){
            Condominio c(nome,mensalV,mensalA,stod(valori.at(0)), stod(valori.at(1)), stod(valori.at(2)), stod(valori.at(3)),habs,servs, habsFile, condominosFile, historicoFile, condominos, historicoAtual);
            return c;
        }
        else{
            Condominio c(nome,mensalV,mensalA, stod(valori.at(0)), stod(valori.at(1)), stod(valori.at(2)), stod(valori.at(3)), habsFile, condominosFile, historicoFile);
            return c;
        }*/
    }
    else{
        throw ErrorReadingFile("ficheiro do condominio");
    }

}

bool writeTransportes(Condominio& c){
    ifstream testfile(pwd+c.getTransportesFile());
    if(!testfile)
        throw(ErrorWritingFile("ficheiro dos transportes"));
    else {
        ofstream file;
        file.open(pwd+c.getTransportesFile());
        if(file.is_open()){
            priority_queue<Transporte>aux = c.getTransportes();
            while(!aux.empty()){
                file << aux.top().getTipo() << endl;
                file << aux.top().getDestino() << endl;
                for (int i = 0; i < aux.top().getParagens().size() ; i++) {
                    if(i == aux.top().getParagens().size()-1 && aux.size() != 1){
                        file << aux.top().getParagens().at(i).name << '-' << aux.top().getParagens().at(i).distance << endl;
                    }
                    else if(i == aux.top().getParagens().size()-1 && aux.size() == 1)
                        file << aux.top().getParagens().at(i).name << '-' << aux.top().getParagens().at(i).distance;
                    else
                        file << aux.top().getParagens().at(i).name << '-' << aux.top().getParagens().at(i).distance << ';';
                }
                if(aux.size() != 1)
                    file << "====================" << endl;
                aux.pop();
            }
        }
        file.close();
        cout << "Ficheiro dos transportes atualizado!" << endl;
        return false;
    }
    return true;
}

bool writeCondomino(Condominio& c){
    ifstream testfile(pwd+c.getCondominosFile());
    if(!testfile)
        throw(ErrorWritingFile("ficheiro dos condominos"));
    else {
        ofstream file;
        file.open(pwd + c.getCondominosFile());
        if (file.is_open()) {
            for (unsigned int i = 0; i < c.getCondomino().size(); i++) {
                file << c.getCondomino().at(i).getNome() << endl;
                file << c.getCondomino().at(i).getNif() << endl;
                if (i != c.getCondomino().size() - 1) {
                    file << intDateToString(c.getCondomino().at(i).getStartDate()) << endl;
                    file << "====================" << endl;
                }
                else {
                    file << intDateToString(c.getCondomino().at(i).getStartDate());
                }
            }
            file.close();
            cout << "Ficheiro de condominos atualizado!" << endl;
            return false;
        }
        return true;
    }
}

bool writeHabitacao(Condominio& c){
    ifstream testfile(pwd+c.getHabsFile());
    if(!testfile)
        throw(ErrorWritingFile("ficheiro de habitacoes"));
    else {
        ofstream file;
        file.open(pwd + c.getHabsFile());
        Apartamento *a;
        if (file.is_open()) {
            for (int i = 0; i < c.getHabs().size(); i++) {
                a = dynamic_cast<Apartamento *>(c.getHabs().at(i));
                if (a != nullptr) {
                    file << "Apartamento" << endl;
                    file << a->getOwnerNif() << endl;
                    file << a->getMorada() << endl;
                    file << a->getAreaInt() << endl;
                    file << a->getTipo() << endl;
                    file << a->getPiso() << endl;
                    if (i != c.getHabs().size() - 1) {
                        file << a->getServsString() << endl;
                        file << "====================" << endl;
                    } else
                        file << a->getServsString();
                } else {
                    Vivenda *v = dynamic_cast<Vivenda *>(c.getHabs().at(i));
                    file << "Vivenda" << endl;
                    file << v->getOwnerNif() << endl;
                    file << v->getMorada() << endl;
                    file << v->getAreaInt() << endl;
                    file << v->getAreaExt() << endl;
                    if (v->getPool())
                        file << "true" << endl;
                    else
                        file << "false" << endl;
                    if (i != c.getHabs().size() - 1) {
                        file << v->getServsString() << endl;
                        file << "====================" << endl;
                    } else
                        file << v->getServsString();
                }
            }
            file.close();
            cout << "Ficheiro de habitacoes atualizado!" << endl;
            return false;
        } else
            return true;
    }
}

bool writeCondominio(const string& filename, BST<Condominio> condominios){
    ifstream testfile(pwd + filename);
    if(!testfile)
        throw(ErrorWritingFile(filename));
    else {
        testfile.close();
        ofstream file;
        file.open(pwd + filename);
        if (file.is_open())
        {
            BSTItrIn<Condominio> it(condominios);
            while(!it.isAtEnd()){
                file << it.retrieve().getNome() << endl;
                file << it.retrieve().getLocalizacao() << endl;
                file << it.retrieve().getMensalV() << endl;
                file << it.retrieve().getMensalA() << endl;
                file << it.retrieve().getValorAExt() << "/" << it.retrieve().getValorPool() << "/" << it.retrieve().getValorTipo() << "/" << it.retrieve().getValorPiso()<< endl;
                file << it.retrieve().getHabsFile() << endl;
                file << it.retrieve().getCondominosFile() << endl;
                file << it.retrieve().getServsString() << endl;
                file << it.retrieve().getHistoricoFile() << endl;
                file << it.retrieve().getHistoricoCoFile() << endl;
                if(it.retrieve() == condominios.findMax()){
                    file << it.retrieve().getTransportesFile();
                }
                else{
                    file << it.retrieve().getTransportesFile() << endl;
                    file << "====================" << endl;
                }
                it.advance();
            }
            file.close();
            cout << "Ficheiro do condominio atualizado!" << endl;
            return false;
        }
        else
            return true;
    }
}
