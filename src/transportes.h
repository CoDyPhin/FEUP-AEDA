#ifndef PROJECT_TRANSPORTES_H
#define PROJECT_TRANSPORTES_H
#include "string"
#include "vector"

using namespace std;

struct Paragem{
    string name;
    double distance;
    bool operator==(const Paragem& p) const;
};

class Transporte{
    public:
        Transporte(string tipo,string destino, Paragem closestParagem, vector<Paragem> paragens);
        ~Transporte() = default;
        string getTipo()const{return this->tipo;};
        string getDestino()const {return this->destino;};
        Paragem getClosestParagem()const {return this->closestParagem;};
        vector<Paragem> getParagens()const{return this->paragens;};
        bool setClosestParagem(Paragem p);
        bool setDestino(string destino);
        void addParagem(Paragem p);
        void removeParagem(Paragem p);
        bool operator<(const Transporte& p)const;
        friend ostream& operator<<(ostream& os, Transporte c);
private:
        string tipo, destino;
        Paragem closestParagem;
        vector<Paragem> paragens;
};

#endif //PROJECT_TRANSPORTES_H
