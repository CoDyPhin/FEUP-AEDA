#include <string>
#include <vector>
#include <map>

#ifndef PROJECT_SERVICOS_H
#define PROJECT_SERVICOS_H

using namespace std;

/**
 * Classe de funcionarios
 * @brief Classe onde se tratam os funcionarios prestadores de um determinado servico e as suas caracteristicas
 */
class Funcionario{
    public:
        /**
         * @brief Construtor do objeto Funcionario
         * @param nome Nome do funcionario
         * @param tipo Tipo de servico que presta
         * @param horario Map representativo do horario de trabalho
         * @param disp Map representativo da disponibilidade na data de trabalho
         * @param data Data do dia de trabalho
         */
        Funcionario(string nome, string tipo, map<double,bool> horario, map<double,bool> disp, unsigned int data);
        /**
         * @brief Metodo get para o nome
         * @return string Nome do funcionario
         */
        string getNome(){return nome;};
        /**
         * @brief Metodo get para o tipo de servico que presta
         * @return string Tipo de servico que presta
         */
        string getTipo(){return tipo;};
        /**
         * @brief Metodo get para o horario de trabalho
         * @return map<double,bool> Horario de trabalho
         */
        map<double,bool> getHorario(){return horario;};
        /**
         * @brief Metodo get para a disponibilidade na data de trabalho
         * @return map<double,bool> Disponibilidade na data de trabalho
         */
        map<double,bool> getDisp(){return disp;};
        /**
         * @brief Metodo get para a data de trabalho
         * @return unsigned int Data de trabalho
         */
        unsigned int getData(){return data;};
        /**
         * @brief Metodo set para o nome do funcionario
         * @param nome Novo nome do funcionario
         * @return bool true se bem sucedido, false se nao
         */
        bool setNome(string nome);
        /**
         * @brief Metodo set para o horario de trabalho
         * @param horario Novo horario do funcionario
         * @return bool true se bem sucedido, false se nao
         */
        bool setHorario(map<double,bool> horario);
        /**
         * @brief Metodo set para a disponibilidade na data de trabalho
         * @param disp Nova disponibilidade na data de trabalho
         * @return bool true se bem sucedido, false se nao
         */
        bool setDisp(map<double,bool> disp);
        /**
         * @brief Metodo set para a data de trabalho
         * @param data Nova data de trabalho
         * @return bool true se bem sucedido, false se nao
         */
        bool setData(unsigned int data);
        /**
         * @brief Overload do operador ==
         * @param f1 Funcionario 1
         * @param f2 Funcionario 2
         * @return bool true se todos os parametros exceto a disponibilidade forem iguais, false se nao
         */
        friend bool operator==(Funcionario f1, Funcionario f2);
    private:
        /** Nome do funcionario
         */
        string nome;
        /** Tipo de servico que o funcionario presta
         */
        string tipo;
        /** Data de trabalho
         */
        unsigned int data;
        /** Map de 30 em 30 minutos, cujas horas a true representam as horas em que o funcionario trabalha
         */
        map<double,bool> horario;
        /** Map de 30 em 30 minutos, cujas horas a true representam as horas em que ainda esta disponivel para trabalhar na data
         */
        map<double,bool> disp;

};


/**
 * Classe de servicos
 * @brief Classe onde se tratam os servicos que podem ser disponibilizados para o condominio a gerir
 */
class Servico{
    public:
        /**
         * @brief Construtor de um objeto Servico
         * @param tipo Tipo de servico
         * @param funcs Vetor de funcionarios disponiveis
         */
        Servico(string tipo, vector<Funcionario> funcs);
        /**
         * @brief Metodo get para o tipo de servico
         * @return string Tipo de servico
         */
        string getTipo() const{return tipo;};
        /**
         * @brief Metodo get para os funcionarios que realizam o servico
         * @return vector<Funcionario> Funcionarios que realizam o servico
         */
        vector<Funcionario> getFuncs(){return funcs;};
        /**
         * @brief Metodo set para o tipo de servico
         * @param tipo Novo tipo de servico
         * @return bool true se bem sucedido, false se nao
         */
        bool setTipo(string tipo);
        /**
         * @brief Metodo set para os funcionarios que realizam o servico
         * @param funcs Novo vetor de funcionarios que realizam o servico
         * @return bool true se bem sucedido, false se nao
         */
        bool setFuncs(vector<Funcionario> funcs);
        /**
         * @brief Overload do operator ==
         * @param s1 Servico 1
         * @param s2 Servico 2
         * @return bool true se todos os membros forem iguais, false se nao
         */
        friend bool operator==(Servico s1, Servico s2);
    private:
        /** Tipo de servico
         */
        string tipo;
        /** Vetor de funcionarios que realizam o servico
         */
        vector<Funcionario> funcs;


};

#endif //PROJECT_SERVICOS_H
