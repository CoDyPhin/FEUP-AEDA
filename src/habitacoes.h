#include <iostream>
#include "servicos.h"

#ifndef PROJECT_HABITACOES_H
#define PROJECT_HABITACOES_H

using namespace std;

/**
 * Classe-mae de habitacoes
 * @brief Classe onde se tratam as habitacoes de forma geral existentes no condominio a gerir
 */
class Habitacao{
    public:
        /**
         * @brief Construtor de um objeto habitacao
         * @param ownerNif NIF do Condomino dono (0 se sem dono)
         * @param morada Morada da habitacao
         * @param areaInt Area interior da habitacao
         * @param servCons Vetor de servicos que ja foram consumidos pela habitacao
         */
        Habitacao(unsigned long int ownerNif, string morada, double areaInt, vector<Servico>servCons);
        /**
         * @brief Destrutor default
         */
        ~Habitacao();
        /**
         * @brief Metodo get para a morada de habitacao
         * @return string Morada da habitacao
         */
        virtual string getMorada(){return morada;};
        /**
         * @brief Metodo get para a area interior da habitacao
         * @return double Area interior
         */
        double getAreaInt(){return areaInt;};
        /**
         * @brief Metodo get para o NIF do Condomino dono da habitacao
         * @return unsigned long int NIF do Condomino dono
         */
        unsigned long int getOwnerNif(){return ownerNif;}
        /**
         * @brief Metodo get para o vetor de servicos consumidos pela habitacao
         * @return vector<Servico> Servicos consumidos pela habitacao
         */
        vector<Servico>getServCons(){return servCons;};
        /**
         * @brief Metodo get para a string de servicos consumidos pela habitacao
         * @return string Tipo de servicos consumidos pela habitacao
         */
        string getServsString();
        /**
         * @brief Metodo set para a morada da habitacao
         * @param morada Nova morada da habitacao
         * @return bool true se bem sucedido, false se nao
         */
        bool setMorada(string morada);
        /**
         * @brief Metodo set para a area interior
         * @param areaInt Nova area interior
         * @return bool true se bem sucedido, false se nao
         */
        bool setAreaInt(double areaInt);
        /**
         * @brief Metodo set para o NIF do Condomino dono
         * @param nif Novo NIF do Condomino dono
         * @return bool true se bem sucedido, false se nao
         */
        bool setOwnerNif(unsigned long int nif);
        /**
         * @brief Metodo set para os servicos consumidos
         * @param servCons Novo vetor de servicos consumidos
         * @return bool true se bem sucedido, false se nao
         */
        bool setServCons(vector<Servico> servCons);
        /**
         * @brief Overload do operador == para 2 habitacoes
         * @param h1 Habitacao 1
         * @param h2 Habitacao 2
         * @return true se todos os membros de h1 forem iguais aos de h2, false se nao
         */
        friend bool operator==(Habitacao h1, Habitacao h2);
    protected:
        /** Morada da habitacao
         */
        string morada;
        /** Area interior em m^2
         */
        double areaInt;
        /** NIF do Condomino dono (0 se sem dono)
         */
        unsigned long int ownerNif;
        /** Vetor com todos os servicos ja consumidos pela habitacao
         */
        vector<Servico>servCons;

};

/**
 * Classe-derivada da classe-mae Habitacao, Vivendas
 * @brief Classe onde se tratam especificamente as vivendas existentes no condominio a gerir
 */
class Vivenda : public Habitacao{
    public:
        /**
         * @brief Construtor de um objeto Vivenda
         * @param morada Morada da Vivenda
         * @param ownerNif NIF do Condomino dono (0 se sem dono)
         * @param areaInt Area interior da Vivenda
         * @param areaExt Area exterior da Vivenda
         * @param servCons Vetor de servicos que ja foram consumidos pela Vivenda
         * @param pool true se tiver piscina, false se nao
         */
        Vivenda(unsigned long int ownerNif, string morada, double areaInt, double areaExt, vector<Servico>servCons, bool pool);
        /**
         * @brief Destrutor default
         */
        ~Vivenda();
        /**
         * @brief Metodo get para a morada
         * @return string Morada da vivenda
         */
        string getMorada(){return morada;};
        /**
         * @brief Metodo get para a area exterior
         * @return double Area exterior
         */
        double getAreaExt() {return areaExt;};
        /**
         * @brief Metodo get para a existencia de piscina
         * @return bool true se tiver piscina, false se nao
         */
        bool getPool() {return pool;};
        /**
         * @brief Metodo set para a area exterior
         * @param areaExt Nova area exterior
         * @return bool true se bem sucedido, false se nao
         */
        bool setAreaExt(double areaExt);
        /**
         * @brief Metodo set para a existencia de piscina
         * @param pool Novo bool para existencia ou nao de piscina
         * @return bool true se bem sucedido, false se nao
         */
        bool setPool(bool pool);
        /**
         * @brief Overload do operador de output
         * @param os ostream
         * @param v Vivenda a fazer output
         * @return ostream& Output formatado para uma vivenda
         */
        friend ostream& operator<<(ostream& os, Vivenda v);
    private:
        /** Area exterior da vivenda (m^2)
         */
        double areaExt;
        /** Existencia de piscina (true se possui, false se nao)
         */
        bool pool;
};


/**
 * Classe-derivada da classe-mae Habitacao, Apartamentos
 * @brief Classe onde se tratam especificamente os apartamentos existentes no condominio a gerir
 */
class Apartamento : public Habitacao{
    public:
        /**
         * @brief Construtor de um objeto Apartamento
         * @param morada Morada do Apartamento
         * @param ownerNif NIF do Condomino dono (0 se sem dono)
         * @param areaInt Area interior do Apartamento
         * @param servCons Vetor de servicos que ja foram consumidos pelo Apartamento
         * @param tipo Tipo de apartamento
         * @param piso true se tiver piscina, false se nao
         */
        Apartamento(unsigned long int ownerNif, string morada, double areaInt, vector<Servico>servCons, string tipo, unsigned int piso);
        /**
         * @brief Destrutor default
         */
        ~Apartamento();
        /**
         * @brief Metodo get para a morada do Apartamento
         * @return string Morada do Apartamento
         */
        string getMorada(){return morada;};
        /**
         * @brief Metodo get para o tipo de Apartamento
         * @return string Tipo de Apartamento
         */
        string getTipo(){return tipo;};
        /**
         * @brief Metodo get para o piso
         * @return unsigned int Piso do Apartamento
         */
        unsigned int getPiso(){return piso;};
        /**
         * @brief Metodo set para o tipo
         * @param tipo Novo tipo de Apartamento
         * @return bool true se bem sucedido, false se nao
         */
        bool setTipo(string tipo);
        /**
         * @brief Metodo set para o piso
         * @param piso Novo piso do Apartamento
         * @return bool true se bem sucedido, false se nao
         */
        bool setPiso(unsigned int piso);
        /**
         * @brief Overload do operador de output
         * @param os ostream&
         * @param a Apartamento a fazer output
         * @return ostream& Output formatado do Apartamento
         */
        friend ostream& operator<<(ostream& os, Apartamento a);
    private:
        /** Tipo de Apartamento
         */
        string tipo;
        /** Piso do Apartamento
         */
        unsigned int piso;


};

#endif //PROJECT_HABITACOES_H
