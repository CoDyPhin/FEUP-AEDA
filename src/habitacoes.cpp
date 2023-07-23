#include "habitacoes.h"

//Habitacao
Habitacao::Habitacao(unsigned long int ownerNif, string morada, double areaInt, vector<Servico>servCons) {
    this->morada = morada;
    this->areaInt = areaInt;
    this->ownerNif  = ownerNif;
    this->servCons = servCons;
}

Habitacao::~Habitacao() = default;

string Habitacao::getServsString() {
    string result;
    for (int i = 0; i < servCons.size(); i++) {
        if(result.find(servCons.at(i).getTipo()) == result.npos)
            result.append(servCons.at(i).getTipo()+", ");
    }
    result = result.substr(0, result.size()-2);
    return result;
}

bool Habitacao::setMorada(string morada) {
    this->morada = morada;
    return this->morada == morada;
}

bool Habitacao::setAreaInt(double areaInt) {
    this->areaInt = areaInt;
    return this->areaInt == areaInt;
}

bool Habitacao::setOwnerNif(unsigned long int nif) {
    this->ownerNif = nif;
    return this->ownerNif == nif;
}

bool Habitacao::setServCons(vector<Servico> servCons) {
    this->servCons = servCons;
    return this->servCons == servCons;
}

bool operator==(Habitacao h1, Habitacao h2){
    return h1.morada == h2.morada && h1.areaInt == h2.areaInt && h1.ownerNif == h2.ownerNif &&
           h1.servCons == h2.servCons;
}

//Vivenda
Vivenda::Vivenda(unsigned long int ownerNif, string morada, double areaInt, double areaExt, vector<Servico>servCons, bool pool):Habitacao(ownerNif,morada,areaInt,servCons) {
    this->areaExt = areaExt;
    this->pool = pool;
}
Vivenda::~Vivenda() = default;

bool Vivenda::setAreaExt(double areaExt) {
    this->areaExt = areaExt;
    return this->areaExt == areaExt;
}

bool Vivenda::setPool(bool pool) {
    this->pool = pool;
    return this->pool == pool;
}

ostream& operator<<(ostream& os, Vivenda v){
    string pool;
    if(v.pool)
        pool = "Sim";
    else
        pool = "Nao";
    os << "Categoria: Vivenda" << endl << "NIF do Dono: " << v.ownerNif << endl << "Morada: " <<  v.morada << endl << "Area Interior: " << v.areaInt << endl
    << "Area Exterior: " << v.areaExt << endl << "Piscina: " << pool << endl << "Servicos Consumidos: " << v.getServsString() << endl << endl;

    return os;
}

//Apartamento
Apartamento::Apartamento(unsigned long int ownerNif, string morada, double areaInt, vector<Servico>servCons, string tipo, unsigned int piso):Habitacao(ownerNif,morada,areaInt,servCons) {
    this->tipo = tipo;
    this->piso = piso;
}

Apartamento::~Apartamento() = default;

bool Apartamento::setPiso(unsigned int piso) {
    this->piso = piso;
    return this->piso == piso;
}

bool Apartamento::setTipo(string tipo) {
    this->tipo = tipo;
    return this->tipo == tipo;
}

ostream& operator<<(ostream& os, Apartamento a){
    os << "Categoria: Apartamento" << endl << "NIF do Dono: " << a.ownerNif << endl << "Morada: " << a.morada << endl << "Area Interior: " << a.areaInt << endl
    << "Tipo: " << a.tipo << endl << "Andar: " << a.piso << endl << "Servicos Consumidos: " << a.getServsString() << endl << endl;

    return os;
}
