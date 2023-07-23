#include "condominio.h"
#include "functions.h"
#include <algorithm>

Condominio::Condominio(string nome,string localizacao, double mensalV, double mensalA, double valorAExt, double valorPool, double valorTipo, double valorPiso, string habsFile, string condominosFile, string historicoFile) {
    this->nome = nome;
    this->localizacao = localizacao;
    this-> mensalV = mensalV;
    this->mensalA = mensalA;
    this->valorAExt = valorAExt;
    this->valorPool = valorPool;
    this->valorTipo = valorTipo;
    this->valorPiso = valorPiso;
    this->habsFile = habsFile;
    this->condominosFile = condominosFile;
    this->historicoFile = historicoFile;
}

Condominio::Condominio(string nome,string localizacao, double mensalV, double mensalA,double valorAExt, double valorPool, double valorTipo, double valorPiso, vector<Habitacao*> habs,
                       vector<Servico> servicos, string habsFile, string condominosFile, string historicoFile,string historicoCoFile,string transportesFile, vector<Condomino> condominos, vector<Funcionario> historico, HashTableOldCondominos historicoCondominos,priority_queue<Transporte> transportes) {
    this->nome = nome;
    this->localizacao = localizacao;
    this-> mensalV = mensalV;
    this->mensalA = mensalA;
    this->habs = habs;
    this->servicos = servicos;
    this->valorAExt = valorAExt;
    this->valorPool = valorPool;
    this->valorTipo = valorTipo;
    this->valorPiso = valorPiso;
    this->habsFile = habsFile;
    this->condominosFile = condominosFile;
    this->condominos = condominos;
    this->historico = historico;
    this->historicoFile = historicoFile;
    this->historicoCoFile = historicoCoFile;
    this->transportesFile = transportesFile;
    this->oldCondominos = historicoCondominos;
    this->transportes = transportes;
}

Condominio::~Condominio() = default;

string Condominio::getServsString()const {
    string result = "";
    for (int i = 0; i < servicos.size(); i++) {
        if(result.find(servicos.at(i).getTipo()) == result.npos) {
            result.append(servicos.at(i).getTipo()+", ");
        }
    }
    result = result.substr(0, result.size()-2);
    return result;
}

vector<Habitacao*> Condominio::getHabsDisp() {
    vector<Habitacao*> result;
    for (int i = 0; i < habs.size() ; i++) {
        if(habs.at(i)->getOwnerNif() < 100000000)
            result.push_back(habs.at(i));
    }
    return result;
}

bool Condominio::setNome(string nome) {
    this->nome = nome;
    return this->nome == nome;
}

bool Condominio::setMensalA(double mensalA) {
    this->mensalA = mensalA;
    return this->mensalA == mensalA;
}

bool Condominio::setMensalV(double mensalV) {
    this->mensalV = mensalV;
    return this->mensalV == mensalV;
}

bool Condominio::setValorAExt(double valorAExt) {
    this->valorAExt = valorAExt;
    return this->valorAExt == valorAExt;
}

bool Condominio::setValorPool(double valorPool) {
    this->valorPool = valorPool;
    return this->valorPool == valorPool;
}

bool Condominio::setValorTipo(double valorTipo) {
    this->valorTipo = valorTipo;
    return this->valorTipo == valorTipo;
}

bool Condominio::setValorPiso(double valorPiso) {
    this->valorPiso = valorPiso;
    return this->valorPiso == valorPiso;
}

bool Condominio::setHabs(vector<Habitacao*> habs) {
    this->habs = habs;
    return this->habs == habs;
}

bool Condominio::setServicos(vector<Servico> servicos) {
    this->servicos = servicos;
    return this->servicos == servicos;
}

bool Condominio::setCondominos(vector<Condomino> condominos) {
    this->condominos = condominos;
    return this->condominos == condominos;
}

bool Condominio::setLocalizacao(string localizacao) {
    this->localizacao = localizacao;
}

void Condominio::addOldCondomino(Condomino c) {
    this->oldCondominos.insert(c);
}

unsigned int Condominio::getNumAparts() {
    unsigned int counter = 0;
    Apartamento *a;
    for (int i = 0; i < habs.size() ; i++) {
        a = dynamic_cast<Apartamento*>(habs.at(i));
        if( a != nullptr)
            counter++;
    }
    return counter;
}

unsigned int Condominio::getNumVive() const {
    unsigned int counter = 0;
    Vivenda *v;
    for (int i = 0; i < habs.size() ; i++) {
        v = dynamic_cast<Vivenda*>(habs.at(i));
        if( v != NULL)
            counter++;
    }
    return counter;
}

bool Condominio::setHistorico(vector<Funcionario> historico) {
    this->historico = historico;
    return this->historico == historico;
}

bool Condomino::setStartDate(unsigned int startDate) {
    this->startDate = startDate;
    return this->startDate == startDate;
}

bool Condomino::setEndDate(unsigned int endDate) {
    this->endDate = endDate;
    return this->endDate == endDate;
}

bool Condominio::operator<(const Condominio &c)const {
    if(this->habs.size() == c.habs.size())
        return this->getNumVive() < c.getNumVive();
    else
        return this->habs.size() < c.habs.size();

}

ostream &operator<<(ostream &os,Condominio c) {
    os << "Nome: " <<  c.getNome() << endl << "Localizacao: " << c.getLocalizacao() << endl << "Mensalidade(Vivenda): " << c.getMensalV() << endl << "Mensalidade(Apartamento): " << c.getMensalA() << endl
       << "Valorizacao Area Exterior: " << c.getValorAExt() << "%" << endl << "Valorizacao Piscina: " << c.getValorPool() << "%" << endl << "Valorizacao Tipo de Apartamento: "
       << c.getValorTipo() <<  "%" << endl << "Valorizacao por Andar: " << c.getValorPiso() << "%" << endl << "Numero de Vivendas: " << c.getNumVive() << endl
       << "Numero de Apartamentos: " << c.getNumAparts() << endl << "Numero de comdominos: " << c.getCondomino().size() << endl << "Servicos: " << c.getServsString() << endl;

    return os;
}

bool Condominio::operator==(const Condominio &c) const {
    return this->nome == c.getNome() && this->localizacao == c.getLocalizacao() && this->habs == c.getHabs();
}

void Condominio::setTransportes(priority_queue<Transporte> transportes) {
    this->transportes = transportes;
}


Condomino::Condomino(string nome, unsigned long int nif, double mensalA, double mensalV, double valorAExt, double valorPool, double valorTipo, double valorPiso,unsigned int startDate, vector<Habitacao*> ownedHabs = {}){
    this->nome = nome;
    this->nif = nif;
    this->ownedHabs = ownedHabs;
    Apartamento* a;
    double aux = 0;
    if (ownedHabs.empty()) this->mensalBase = 0;
    for(size_t i = 0; i< ownedHabs.size(); i++){
        a = dynamic_cast<Apartamento*>(ownedHabs.at(i));
        if(a != nullptr){
            aux += ((100 + valorPiso*(a->getPiso()+1) + valorTipo*(1+a->getTipo().at(1)))/100)*mensalA;
        }
        else{
            Vivenda* v;
            v = dynamic_cast<Vivenda*>(ownedHabs.at(i));
            aux += ((100 + valorAExt*(v->getAreaExt()) + valorPool*(v->getPool()))/100)*mensalV;
        }
    }
    aux = int(aux*100+0.5);
    aux = double(aux)/100;
    this->mensalBase = aux;
    this->startDate = startDate;
    this->endDate = 0;
}

Condomino::Condomino(string nome, unsigned long int nif, unsigned int startDate, unsigned int endDate) {
    this->nome = nome;
    this->nif = nif;
    this->startDate = startDate;
    this->endDate = endDate;
}

Condomino::~Condomino() = default;

bool Condomino::setNome(string nome) {
    this->nome = nome;
    return this->nome == nome;
}

bool Condomino::setNif(unsigned long int nif) {
    this->nif = nif;
    return this->nif == nif;
}

bool Condomino::setOwnedHabs(vector<Habitacao*> ownedHabs) {
    this->ownedHabs = ownedHabs;
    return this->ownedHabs == ownedHabs;
}

bool Condomino::setMensalBase(double mensalBase) {
    this->mensalBase = mensalBase;
    return this->mensalBase == mensalBase;
}

bool operator<(Condomino c1, Condomino c2){
    return c1.nif < c2.nif;
}

bool operator==(Condomino c1, Condomino c2){
    return c1.nome == c2.nome && c1.nif == c2.nif && c1.ownedHabs == c2.ownedHabs && c1.mensalBase == c2.mensalBase;
}

ostream& operator<<(ostream& os, Condomino c){
    os << "Nome: " << c.nome << endl << "NIF: " << c.nif << endl << "Numero de Propriedades: " << c.ownedHabs.size() << endl
    << "Mensalidade: " << c.mensalBase << endl;

    return os;
}

string showHistCond(Condomino c) {
    string os;
    os = "Nome: " + c.nome + '\n' + "NIF: " + to_string(c.nif) + '\n' + "Data de entrada: " + intDateToString(c.getStartDate()) + '\n' + "Data de saida: " + intDateToString(c.getEndDate()) + '\n';
    return os;
}
