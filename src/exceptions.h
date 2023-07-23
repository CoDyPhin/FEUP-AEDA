#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H
#include <string>

using namespace std;

/**
 * Exception Class
 * @brief Classe onde se tratam erros causados por metodos SET
 */
class ErrorSettingValue{
    public:
        /**
         * @brief Construtor da exception de erro ao alterar um valor de um membro
         * @param valErro Membro onde ocorreu o erro
         */
        ErrorSettingValue(string valErro){this->valErro = valErro;};
        /**
         * @brief Metodo get do membro onde ocorreu o erro
         * @return string membro onde ocorreu o erro
         */
        string getValErro() const {return valErro;};
    private:
        /** Membro onde ocorreu o erro
         */
        string valErro;
};

/**
 * Exception Class
 * @brief Classe onde se tratam erros causados por escrita em ficheiros
 */
class ErrorWritingFile{
    public:
        /**
         * @brief Construtor da exception de erro ao escrever num ficheiro
         * @param filename Ficheiro onde ocorreu o erro
         */
        ErrorWritingFile(string filename){this->filename = filename;};
        /**
         * @brief Metodo get para o ficheiro onde ocorreu o erro
         * @return string Ficheiro onde ocorreu o erro
         */
        string getFileName() const {return filename;};
    private:
        /** Ficheiro onde ocorreu o erro
         */
        string filename;
};

/**
 * Exception Class
 * @brief Classe onde se tratam erros causados por leitura de ficheiros
 */
class ErrorReadingFile{
    public:
        /**
         * @brief Construtor da exception de erro ao ler um ficheiro
         * @param filename Ficheiro onde ocorreu o erro
         */
        ErrorReadingFile(string filename){this->filename = filename;};
        /**
         * @brief Metodo get para o ficheiro onde ocorreu o erro
         * @return string Ficheiro onde ocorreu o erro
         */
        string getFileName() const { return filename;};
    private:
        /** Ficheiro onde ocorreu o erro
         */
        string filename;
};


#endif //PROJECT_EXCEPTIONS_H
