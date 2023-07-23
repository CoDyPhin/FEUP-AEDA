#ifndef PROJECT_FUNCTIONSMENUS_H
#define PROJECT_FUNCTIONSMENUS_H
#include "functions.h"
#include <algorithm>

void cinignore();

unsigned short int menuValidInput(unsigned short int min, unsigned short int max);

unsigned numbersValidInput(unsigned min, unsigned max, const string& msg);

unsigned long int nifValidInput();

string timeValidInput(string msg);

void mostrarHabs(vector<Habitacao*> habs);

bool addCondomino(Condominio& c,string name, unsigned long int nif, unsigned short int index);

bool eraseCondomino(Condominio& c, unsigned short int id);

int searchCondomino(vector<Condomino> c, unsigned long int nif);

int searchHab(vector<Habitacao*> habs, Habitacao* habSel);

bool checkDisponibilidade(map<double,bool> disp, double inicio, double fim);

bool mudarDisp(Condominio& c, unsigned short int servIndex, Funcionario f, double inicio, double fim);

void showServs(Condominio& c);

vector<Funcionario> searchFuncsDispo(Condominio& c,double inicio, double fim, unsigned short int index);

vector<Habitacao*> searchHabitacao(vector<Habitacao*> habs, string tipo);

double areaValidInput(string msg);

short int apartValidInput(string msg);

vector<Habitacao*> searchVivendas(vector<Habitacao*> ,string morada, double minAInt, double maxAInt, unsigned short int inputDono, double minAExt, double maxAExt, unsigned short int inputPool);

vector<Habitacao*> searchAparts(vector<Habitacao*>, string morada, double minAInt, double maxAInt, unsigned short int inputDono, string tipo, short int piso);

#endif //PROJECT_FUNCTIONSMENUS_H
