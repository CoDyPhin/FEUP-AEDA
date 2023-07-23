#include "servicos.h"

Funcionario::Funcionario(string nome, string tipo, map<double, bool> horario, map<double,bool> disp, unsigned int data) {
    this->nome = nome;
    this->tipo = tipo;
    this->horario = horario;
    this->disp = disp;
    this->data = data;
}

bool Funcionario::setNome(string nome) {
    this->nome = nome;
    return this->nome == nome;
}

bool Funcionario::setHorario(map<double, bool> horario) {
    this->horario = horario;
    return this->horario == horario;
}

bool operator==(Funcionario f1, Funcionario f2) {
    return f1.nome == f2.nome && f1.horario == f2.horario && f1.data == f2.data;
}


bool Funcionario::setDisp(map<double, bool> disp) {
    this->disp = disp;
    return this->disp == disp;
}

bool Funcionario::setData(unsigned int data) {
    this->data = data;
    return this->data == data;
}

Servico::Servico(string tipo, vector<Funcionario> funcs) {
    this->tipo = tipo;
    this->funcs = funcs;
}

bool Servico::setTipo(string tipo) {
    this->tipo = tipo;
    return this->tipo == tipo;
}

bool Servico::setFuncs(vector<Funcionario> funcs) {
    this->funcs = funcs;
    return this->funcs == funcs;
}

bool operator==(Servico s1, Servico s2) {
    return s1.tipo == s2.tipo &&  s1.funcs == s2.funcs;
}
