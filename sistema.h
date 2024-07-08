#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <list>
#include "voo.h"

using std::list;
using std::string;
using std::srand;
using std::rand;
using std::cout;
using std::cin;
using std::endl;

class Sistema {
private:
    list<Astronauta*> astronautas;
    list<Voo*> voos;

public:

    void dadosIniciais();
    void iniciarSistema();

    void menuPrincipal();
    void criarVoo();
    bool vooExiste(int codigo);
    bool astronautaExiste(const string &cpf);
    void cadastrarAstronauta();
    void adicionarAstronautaEmVoo();
    void removerAstronautaDeVoo();
    void editarVoos();
    void gerenciarVoos();
    void listarVoos();
    void listarVoosSimples();
    void listarAstronautasDeVoo(int codigoVoo);
    void listarAstronautas();
    void status();
    void statusVoos();
    void statusAstronautas();
    void listarMortos();
    void lancarVoo();
    void explodirVoo();
    void finalizarVoo();

private:
    Astronauta* encontrarAstronauta(string cpf);
    Voo* encontrarVoo(int codigo);

};

#endif // SISTEMA_H
