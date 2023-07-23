#ifndef PROJECT_MENUS_H
#define PROJECT_MENUS_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "functions.h"
#include "functionsmenus.h"

void menuCondominio(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuPrincipal(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuCondomino(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuCondominoEsp(int index, const string&filename, Condominio &c, vector<Servico>& servicos);
void menuServicos(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuPesquisaApartamentos(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuPesquisaVivendas(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuHabitacoes(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuCondominios(const string& filename, Gestao &g, vector<Servico>& servicos);
void menuTransportes(const string& filename, Condominio &c, vector<Servico>& servicos);
void menuHistCond(const string& filename, Condominio &c, vector<Servico>& servicos);





#endif //PROJECT_MENUS_H
