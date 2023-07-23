#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include "condominio.h"
#include "exceptions.h"

using namespace std;

void tolower(string &str);
double timeToDouble(const string& horaString);
string removeSpaces(string fullstring);
vector<string> stringSplit(string fullstring, char delimiter);
vector<string> stringSplitWithSpaces(string fullstring, char delimiter);
map<double,bool> makeHorario(string horario);
vector<Servico>buildServ(vector<string> servscons, vector<Servico> servsdispo);
unsigned int stringDateToInt(string data);
string intDateToString(unsigned int data);
unsigned int  currentDateTime();
vector<Funcionario> readHistorico(const string& filename);
void sortFuncionario(vector<Funcionario> funcs);
bool writeHistorico(const string& filename, vector<Funcionario> funcs);
vector<Funcionario> readFuncionarios(const string& filename, vector<Funcionario>& funcsAntigos);
vector<Servico> readServicos(const string& filename, vector<Funcionario>& funcsAntigos);
vector<Habitacao*> readHabitacao(const string& filename,const vector<Servico>&servsdispo);
vector<Habitacao*> habsOwned(unsigned long int nif, vector<Habitacao*> habs);
vector<Condomino> readCondomino(const string& filename, const vector<Habitacao*>& ownedHabs, double mensalA, double mensalV, double valorAExt, double valorPool, double valorTipo, double valorPiso);
Gestao readCondominio(const string& filename,const vector<Servico>& servsdispo, vector<Funcionario>& funcs);
HashTableOldCondominos readHistoricoCondomino(const string& filename);
priority_queue<Transporte>readTransportes(const string& filename);
bool writeCondominio(const string& filename, BST<Condominio> condominios);
bool writeHabitacao(Condominio &c);
bool writeCondomino(Condominio &c);
map<double,bool> makeDisp(map<double,bool> horario, string disp);
string horarioToString(map<double,bool> horario);
map<double,bool> servsMap(map<double,bool> horario, map<double,bool> disp);
bool writeFuncionarios(vector<Funcionario> funcs);
bool writeFuncionarios(vector<Servico> servs);
bool writeHistoricoCondomino(const string& filename, HashTableOldCondominos condominos);
bool writeTransportes(Condominio& c);
vector<Funcionario> servsFunc(string tipo, vector<Funcionario> funcs);


#endif //PROJECT_FUNCTIONS_H
