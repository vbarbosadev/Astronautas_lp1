#ifndef VOO_H
#define VOO_H


#include <string>
#include "astronauta.h"

using std::list;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Voo {
public:
    int codigo;
    list<Astronauta*> passageiros;
    string status;

    Voo(int codigo);

    void adicionarAstronauta(Astronauta* astronauta);
    void removerAstronauta(string cpf);
    bool astronautaJaNoVoo(const string &cpf);

    void lancarVoo();
    void explodirVoo();
    void finalizarVoo(bool sucesso);

private:
    bool todosAstronautasDisponiveis();
};

#endif // VOO_H
