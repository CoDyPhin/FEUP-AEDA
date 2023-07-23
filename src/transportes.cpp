#include "transportes.h"
#include "algorithm"
#include "iostream"

bool Paragem::operator==(const Paragem &p) const {
    return this->name == p.name && this->distance == p.distance;
}

Transporte::Transporte(string tipo,string destino, Paragem closestParagem, vector<Paragem> paragens){
    this->tipo = tipo;
    this->destino = destino;
    this->closestParagem = closestParagem;
    this->paragens = paragens;
}

bool Transporte::setDestino(string destino) {
    this->destino = destino;
    return this->destino == destino;
}

void Transporte::addParagem(Paragem p) {
    paragens.push_back(p);
    if(p.distance < this->closestParagem.distance)
        this->closestParagem = p;
}

void Transporte::removeParagem(Paragem p) {
    vector<Paragem>::iterator it = find(paragens.begin(),paragens.end(),p);
    if(it != paragens.end())
        paragens.erase(it);
    else
        cout << "Nao existe uma paragem com esse nome" << endl;
    if(this->closestParagem == p){
        sort(paragens.begin(),paragens.end(),[](Paragem p1, Paragem p2){
            return p1.distance < p2.distance;
        });
        this->closestParagem = paragens.at(0);
    }
}

bool Transporte::setClosestParagem(Paragem p) {
    this->closestParagem = p;
    return this->closestParagem == p;
}

bool Transporte::operator<(const Transporte & p)const {
   return this->closestParagem.distance > p.getClosestParagem().distance;
}

ostream& operator<<(ostream& os, Transporte t){
    os << "Tipo: " << t.tipo << endl << "Destino: " << t.destino << endl << "Paragem mais proxima: " << t.closestParagem.name << endl << "Distancia da paragem mais proxima: " << t.closestParagem.distance << " Km" << endl;

    return os;
}