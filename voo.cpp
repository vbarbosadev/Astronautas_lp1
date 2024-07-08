#include "voo.h"

Voo::Voo(int codigo) : codigo(codigo), status("planejado") {}

void Voo::adicionarAstronauta(Astronauta* astronauta) {
    if (status == "planejado" && astronauta->vivo) {
        passageiros.push_back(astronauta);
        
    }
}

void Voo::removerAstronauta(string cpf) {
    if (status == "planejado") {
        for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
            if ((*it)->cpf == cpf) {
                
                passageiros.erase(it);
                break;
            }
        }
    }
}

bool Voo::astronautaJaNoVoo(const string &cpf) {
    for (const auto &astronauta : passageiros) {
        if (astronauta->cpf == cpf) {
            return true;
        }
    }
    return false;
}

void Voo::lancarVoo() {
    if (status == "planejado" && !passageiros.empty() && todosAstronautasDisponiveis()) {
        status = "Em curso";
        cout << "Voo lançado com sucesso!" << endl;
    } else {
        cout << "Não é possível lançar o voo. Verifique se há astronautas no voo ou se todos estão disponíveis." << endl;
    }
}

void Voo::explodirVoo() {
    status = "Explodido";
    for (auto astronauta : passageiros) {
        astronauta->disponivel = false;
        astronauta->vivo = false;
    }
    cout << "Voo explodido com sucesso!" << endl;
}

void Voo::finalizarVoo(bool sucesso) {
    if (sucesso) {
        status = "Finalizado com sucesso";
        for (auto astronauta : passageiros) {
            astronauta->disponivel = true;
        }
        cout << "Voo finalizado com sucesso!" << endl;
    } else {
        status = "Finalizado sem sucesso";
        cout << "Voo finalizado sem sucesso!" << endl;
    }
}

bool Voo::todosAstronautasDisponiveis() {
    for (auto astronauta : passageiros) {
        if (!astronauta->disponivel) {
            return false;
        }
    }
    return true;
}
