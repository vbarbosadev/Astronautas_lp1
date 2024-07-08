#ifndef ASTRONAUTA_H
#define ASTRONAUTA_H

#include <string>
#include <iostream>
#include <list>

using std::string;


class Astronauta {
public:
    string cpf;
    string nome;
    int idade;
    bool disponivel;
    bool vivo;

    Astronauta(string cpf, string nome, int idade);

};

#endif // ASTRONAUTA_H
