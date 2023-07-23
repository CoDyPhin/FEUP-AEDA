#include "habitacoes.h"
#include "BST.h"
#include "transportes.h"
#include "unordered_set"
#include "cmath"

#ifndef PROJECT_CONDOMINIO_H
#define PROJECT_CONDOMINIO_H

using namespace std;

/**
 * Classe de condominos
 * @brief Classe onde se tratam os condominos existentes no condominio a gerir
 */
class Condomino{
    public:
        /**
         * @brief Construtor de um condomino
         * @param nome Nome do condomino
         * @param nif NIF do condomino
         * @param mensalA Valor mensal-base para um apartamento no condominio em que se insere
         * @param mensalV Valor mensal-base para uma vivenda no condominio em que se insere
         * @param valorAExt Valorizacao por m^2 de area exterior (dependente do condominio)
         * @param valorPool Valorizacao por existencia de piscina (dependente do condominio)
         * @param valorTipo Valorizacao por tipo de apartamento (dependente do condominio)
         * @param valorPiso Valorizacao por piso (dependente do condominio)
         * @param ownedHabs Vetor de habitacoes pertencentes ao condomino
         * @return Condomino Objeto Condomino criado
         */
        Condomino(string nome, unsigned long int nif, double mensalA, double mensalV, double valorAExt, double valorPool, double valorTipo, double valorPiso,unsigned int startDate, vector<Habitacao*> ownedHabs);
        /**
         * @brief Destrutor default
         */
        ~Condomino();

        Condomino(string nome, unsigned long int nif, unsigned int startDate, unsigned int endDate);
        /**
         * @brief Metodo get para o nome
         * @return string Membro privado nome
         */
        string getNome()const { return nome;};
        /**
         * @brief Metodo get para o NIF
         * @return unsigned long int NIF do condomino
         */
        unsigned long int getNif() const {return nif;};
        /**
         * @brief Metodo get para as habitacoes possuidas
         * @return vector<Habitacao*> Habitacoes possuidas
         */
        vector<Habitacao*> getOwnedHabs(){return ownedHabs;};
        /**
         * @brief Metodo get para o valor da mensalidade
         * @return double Mensalidade a pagar
         */
        double getMensalBase(){return mensalBase;};

        unsigned int getStartDate() const {return this->startDate;};

        unsigned int getEndDate() const {return this->endDate;};
        /**
         * @brief Metodo set para o nome
         * @param nome Novo nome do condomino
         * @return bool true se bem sucedido, false se nao
         */
        bool setNome(string nome);
        /**
         * @brief Metodo set para o nif
         * @param nif Novo NIF do condomino
         * @return bool true se bem sucedido, false se nao
         */
        bool setNif(unsigned long int nif);
        /**
         * @brief Metodo set para as habitacoes possuidas
         * @param ownedHabs Novo vetor de habitacoes possuidas
         * @return bool true se bem sucedido, false se nao
         */
        bool setOwnedHabs(vector<Habitacao*> ownedHabs);
        /**
         * @brief Metodo set para o valor da mensalidade
         * @param mensalBase Novo valor da mensalidade
         * @return bool true se bem sucedido, false se nao
         */
        bool setMensalBase(double mensalBase);

        bool setStartDate(unsigned int startdate);

        bool setEndDate(unsigned int endDate);
        /**
         * @brief Operador < para 2 condominos (ordenacao por NIF)
         * @param c1 Condomino 1
         * @param c2 Condomino 2
         * @return bool true se c1.nif < c2.nif, false se c1.nif > c2.nif
         */
        friend bool operator<(Condomino c1, Condomino c2);
        /**
         * @brief Operador == para 2 condominos
         * @param c1 Condomino 1
         * @param c2 Condomino 2
         * @return bool true se todos os membros de c1 forem iguais aos de c2, false se nao
         */
        friend bool operator==(Condomino c1, Condomino c2);
        /**
         * @brief Operador de output para um condomino
         * @param os ostream
         * @param c Condomino a fazer output
         * @return ostream& output de condomino formatado
         */
        friend ostream& operator<<(ostream& os, Condomino c);
        friend string showHistCond(Condomino c);
    private:
        /**
         * @brief Nome do Condomino
         */
        string nome;
        /**
         * @brief NIF do Condomino
         */
        unsigned long int nif;
        /**
         * @brief Vetor de pointers para as habitacoes possuidas pelo condomino
         */
        vector<Habitacao*> ownedHabs;
        /**
         * @brief Mensalidade a pagar pelo condomino
         */
        double mensalBase;

        unsigned int startDate;

        unsigned int endDate;
};

struct OldCondominosHash{
    int operator()(const Condomino& c)const{
        int size = 73;
        return (c.getNif()*(int)pow(2,8))&size;
    }
    bool operator()(const Condomino &c1, const Condomino &c2)const{
        return c1.getNif() == c2.getNif();
    }
};

typedef unordered_set<Condomino,OldCondominosHash,OldCondominosHash> HashTableOldCondominos;

/**
 * Classe do condominio
 * @brief Classe onde se trata de toda a gestao do condominio
 */
class Condominio{
    public:
        Condominio(){};
        /**
         * @brief Construtor para um condominio
         * @param nome Nome do condominio
         * @param mensalV Valor mensal-base para uma vivenda
         * @param mensalA Valor mensal-base para um apartamento
         * @param valorAExt Valorizacao por m^2
         * @param valorPool Valorizacao por existencia de piscina
         * @param valorTipo Valorizacao por tipo de apartamento
         * @param valorPiso Valorizacao por piso
         * @param habs Vetor de habitacoes existentes
         * @param servicos Vetor de servicos disponibilizados
         * @param habsFile Ficheiro de habitacoes
         * @param condominosFile Ficheiro de condominos
         * @param historicoFile Ficheiro de historico de servicos
         * @param condominos Vetor de condominos
         * @param historico Vetor de servicos (historico)
         * @return Condominio Objeto Condominio criado
         */
        Condominio(string nome,string localizacao, double mensalV, double mensalA, double valorAExt, double valorPool, double valorTipo, double valorPiso, vector<Habitacao*> habs, vector<Servico> servicos, string habsFile, string condominosFile, string historicoFile, string historicoCoFile,string transportesFile, vector<Condomino> condominos, vector<Funcionario> historico, HashTableOldCondominos historicoCondominos,priority_queue<Transporte> transportes);
        /**
         * @brief Construtor para um condominio novo (sem habitacoes, servicos disponiveis ou condominos)
         * @param nome Nome do condominio
         * @param mensalV Valor mensal-base para uma vivenda
         * @param mensalA Valor mensal-base para um apartamento
         * @param valorAExt Valorizacao por m^2
         * @param valorPool Valorizacao por existencia de piscina
         * @param valorTipo Valorizacao por tipo de apartamento
         * @param valorPiso Valorizacao por piso
         * @param habsFile Ficheiro de habitacoes
         * @param condominosFile Ficheiro de condominos
         * @param historicoFile Ficheiro de historico de servicos
         * @return Condominio Objeto Condominio criado
         */
        Condominio(string nome,string localizacao, double mensalV, double mensalA, double valorAExt, double valorPool, double valorTipo, double valorPiso, string habsFile, string condominosFile, string historicoFile);
        /**
         * @brief Destrutor default
         */
        ~Condominio();
        /**
         * @brief Metodo get para o nome
         * @return string Nome do condominio
         */
        string getNome()const {return nome;};
        /**
         * @brief Metodo get para o valor mensal-base para uma vivenda
         * @return double Valor mensal-base para uma vivenda
         */
        double getMensalV()const {return mensalV;};
        /**
         * @brief Metodo get para o valor mensal-base para um apartamento
         * @return doube Valor mensal-base para um apartamento
         */
        double getMensalA()const {return mensalA;};
        /**
         * @brief Metodo get para o ficheiro de habitacoes
         * @return string Ficheiro de habitacoes
         */
        string getHabsFile()const {return habsFile;};
        /**
         * @brief Metodo get para o ficheiro de condominos
         * @return string Ficheiro de condominos
         */
        string getCondominosFile()const {return condominosFile;};
        /**
         * @brief Metodo get para o ficheiro do historico
         * @return string Ficheiro de condominos
         */
        string getHistoricoFile()const { return historicoFile;};

        string getHistoricoCoFile()const {return this->historicoCoFile;};

        string getTransportesFile()const {return this->transportesFile;};
        /**
         * @brief Metodo get para a valorizacao por m^2 de area exterior
         * @return double Valorizacao da area exterior
         */
        double getValorAExt()const {return valorAExt;};
        /**
         * @brief Metodo get para a valorizacao por existencia de piscina
         * @return double Valorizacao da piscina
         */
        double getValorPool()const {return valorPool;};
        /**
         * @brief Metodo get para a valorizacao por tipo de apartamento
         * @return double Valorizacao do tipo
         */
        double getValorTipo()const {return valorTipo;};
        /**
         * @brief Metodo get para a valorizacao por piso
         * @return double Valroizacao do piso
         */
        double getValorPiso()const {return valorPiso;};
        /**
         * @brief Metodo get para as habitacoes sem dono
         * @return vector<Habitacao*> Habitacoes sem dono (disponiveis para compra)
         */
        vector<Habitacao*> getHabsDisp();
        /**
         * @brief Metodo get para o numero de apartamentos no condominio
         * @return unsigned int Numero de apartamentos
         */
        unsigned int getNumAparts();
        /**
         * @brief Metodo get para o numero de vivendas no condominio
         * @return unsigned int Numero de vivendas
         */
        unsigned int getNumVive() const;
        /**
         * @brief Metodo get para a string de servicos disponibilizados pelo condominio
         * @return string Servicos disponibilizados pelo condominio
         */
        string getServsString()const ;
        /**
         * @brief Metodo get para o vetor de habitacoes do condominio
         * @return vector<Habitacao*> Vetor de habitacoes do condominio
         */
        vector<Habitacao*> getHabs()const {return habs;};
        /**
         * @brief Metodo get para o vetor de servicos disponibilizados pelo condominio
         * @return vector<Servico> Servicos disponibilizados pelo condominio
         */
        vector<Servico> getServicos(){return servicos;};
        /**
         * @brief Metodo get para o vetor de condominos
         * @return vector<Condomino> Condominos pertencentes ao condominio
         */
        vector<Condomino> getCondomino(){return condominos;};
        /**
         * @brief Metodo get para o historico de servicos efetuados
         * @return vector<Funcionario> Historico de funcionarios que prestaram servicos no condominio
         */
        vector<Funcionario> getHistorico(){return historico;};
        /**
         * @brief Metodo set para o nome do condominio
         * @param nome Novo nome do condominio
         * @return bool true se bem sucedido, false se nao
         */
        string getLocalizacao()const {return this->localizacao;};

        priority_queue<Transporte> getTransportes(){return this->transportes;};

        HashTableOldCondominos getOldCondominos(){return this->oldCondominos;};

        bool setNome(string nome);
        /**
         * @brief Metodo set para a valor mensal-base para uma vivenda
         * @param mensalV Nova valor mensal-base para vivendas
         * @return bool true se bem sucedido, false se nao

         */
        bool setMensalV(double mensalV);
        /**
         * @brief Metodo set para o valor mensal-base para um apartamento
         * @param mensalA Nova valor mensal-base para apartamentos
         * @return bool true se bem sucedido, false se nao
         */
        bool setMensalA(double mensalA);
        /**
         * @brief Metodo set para a valorizacao da area exterior
         * @param valorAExt Nova percentagem de valorizacao por area exterior
         * @return bool true se bem sucedido, false se nao
         */
        bool setValorAExt(double valorAExt);
        /**
         * @brief Metodo set para a valorizacao por piscina
         * @param valorPool Nova percentagem de valorizacao por piscina
         * @return bool true se bem sucedido, false se nao
         */
        bool setValorPool(double valorPool);
        /**
         * @brief Metodo set para a valorizacao por tipo
         * @param valorTipo Nova percentagem de valorizacao por tipo
         * @return bool true se bem sucedido, false se nao
         */
        bool setValorTipo(double valorTipo);
        /**
         * @brief Metodo set para a valorizacao por piso
         * @param valorPiso Nova percentagem de valorizacao por piso
         * @return bool true se bem sucedido, false se nao
         */
        bool setValorPiso(double valorPiso);
        /**
         * @brief Metodo set para o vetor de habitacoes
         * @param habs Novo vetor de habitacoes
         * @return bool true se bem sucedido, false se nao
         */
        bool setHabs(vector<Habitacao*> habs);
        /**
         * @brief Metodo set para o vetor de servicos disponibilizados
         * @param servicos Novo vetor de servicos disponibilizados
         * @return bool true se bem sucedido, false se nao
         */
        bool setServicos(vector<Servico> servicos);
        /**
         * @brief Metodo set para o vetor de condominos
         * @param condominos Novo vetor de condominos
         * @return bool true se bem sucedido, false se nao
         */
        bool setCondominos(vector<Condomino> condominos);
        /**
         * @brief Metodo set para o vetor de funcionarios que ja efetuaram servicos para o condominio
         * @param historico Novo vetor de historico
         * @return bool true se bem sucedido, false se nao
         */
        bool setHistorico(vector<Funcionario> historico);

        bool setLocalizacao(string localizacao);

        void setTransportes(priority_queue<Transporte> transportes);

        void addOldCondomino(Condomino c);
        /**
         * @brief Overload do operator de output para um condominio
         * @param os ostream
         * @param c Condominio a fazer output
         * @return ostream& Output formatado do condominio
         */
         bool operator<(const Condominio &c)const;

         bool operator==(const Condominio &c)const;
        friend ostream& operator<<(ostream& os, Condominio c);
    private:
        string /** Nome do condominio */ nome, /** Ficheiro de habitacoes */ habsFile, /** Ficheiro de condominos */ condominosFile, /** Ficheiro do historico de servicos efetuados */ historicoFile, localizacao, historicoCoFile, transportesFile;
        /** Valor mensal-base para uma vivenda
         */
        double mensalV;
        /** Valor mensal-base para um apartamento
         */
        double mensalA;
        /** Vetor de pointers para as habitacoes do condomino
         */
        vector<Habitacao*> habs;
        /** Vetor de servicos disponibilizados pelo condominio
         */
        vector<Servico>servicos;
        /** Vetor de condominos do condominio
         */
        vector<Condomino> condominos;
        /** Vetor de funcionarios que efetuaram servicos pelo condominio (historico)
         */
        vector<Funcionario> historico;
        /** Percentagem de valorizacao por m^2 de area exterior
         */
        double valorAExt;
        /** Percentagem de valorizacao por existencia de piscina
         */
        double valorPool;
        /** Percentagem de valorizacao por tipo de apartamento
         */
        double valorTipo;
        /** Percentagem de valorizacao por piso
         */
        double valorPiso;

        priority_queue<Transporte> transportes;

        HashTableOldCondominos oldCondominos;



};

class Gestao{
public:
    Gestao():condominios(Condominio()){};
    ~Gestao() = default;
    BST<Condominio>getCondominios()const{return this->condominios;};
    void setCondominos(BST<Condominio> condominos){this->condominios = condominos;};
    bool addCondominio(Condominio c){
        return this->condominios.insert(c);
    };
private:
    BST<Condominio>condominios;
};


#endif //PROJECT_CONDOMINIO_H
