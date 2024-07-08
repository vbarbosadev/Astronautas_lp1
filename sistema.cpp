#include "sistema.h"
#include "voo.h"
#include "astronauta.h"


void Sistema::dadosIniciais() {
    if (!voos.empty() || !astronautas.empty()) {
        cout << "Os dados iniciais só podem ser adicionados quando não houver voos ou astronautas existentes." << endl;
        return;
    }

    Voo* voo1 = new Voo(101);
    Voo* voo2 = new Voo(102);
    voos.push_back(voo1);
    voos.push_back(voo2);


    // os nome são referências a brooklyn nine nine 
    Astronauta* astronauta1 = new Astronauta("12345678910", "Jake Peralta", 39);
    Astronauta* astronauta2 = new Astronauta("09876543210", "Amy Santiago", 38);
    Astronauta* astronauta3 = new Astronauta("11223344550", "Raymond Holt", 58);
    Astronauta* astronauta4 = new Astronauta("06677889900", "Terry Gerfords", 32);

    astronautas.push_back(astronauta1);
    astronautas.push_back(astronauta2);
    astronautas.push_back(astronauta3);
    astronautas.push_back(astronauta4);

    cout << "Dados iniciais adicionados com sucesso." << endl;
}

void Sistema::iniciarSistema(){
    int opcao;
    cout << "Bem-vindo ao Sistema de Gerenciamento de Voo!" << endl;
    cout << "Escolha uma opção:" << endl << endl;
    cout << "1. Iniciar o sistema." << endl;
    cout << "2. Adicionar dados iniciais." << endl;

    cin >> opcao;
    if (opcao == 1) {
        menuPrincipal();
    }
    if (opcao == 2) {
        dadosIniciais();
        menuPrincipal();
    }
    cout << "\033[2J\033[1;1H";

}

void Sistema::menuPrincipal() {
    int opcao;
    do {
        cout << "\033[2J\033[1;1H";
        cout << "\n### Menu Principal ###" << endl;
        cout << "1. Criar Voo" << endl;
        cout << "2. Cadastrar Astronauta" << endl;
        cout << "3. Editar Voos" << endl;
        cout << "4. Gerenciar Voos" << endl;
        cout << "5. Listar Voos" << endl;
        cout << "6. Listar Astronautas" << endl;
        cout << "7. Status" << endl;
        cout << "8. Rest in peace" << endl;
        cout << "9. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "\033[2J\033[1;1H";
                criarVoo();
                break;
            case 2:
                cout << "\033[2J\033[1;1H";
                cadastrarAstronauta();
                break;
            case 3:
                cout << "\033[2J\033[1;1H";
                editarVoos();
                break;
            case 4:
                cout << "\033[2J\033[1;1H";
                gerenciarVoos();
                break;
            case 5:
                cout << "\033[2J\033[1;1H";
                listarVoos();
                break;
            case 6:
                cout << "\033[2J\033[1;1H";
                cout << "\n### Listar Astronautas ###" << endl;
                listarAstronautasComVoos();
                getchar();
                cout << "\nPressione enter para sair....";
                getchar();
                break;
            case 7:
                cout << "\033[2J\033[1;1H";
                status();
                break;
            case 8:
                cout << "\033[2J\033[1;1H";
                listarMortos();
                break;
            case 9:
                cout << "\033[2J\033[1;1H";
                sair();
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 9);
}

void Sistema::criarVoo() {
    int codigo;
    cout << "\n### Criar Voo ###" << endl;
    cout << "Digite o código do voo: ";
    cin >> codigo;


    if (vooExiste(codigo)) {
        cout << "Voo com este código já existe!" << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
        
        return;
    }

    Voo* novoVoo = new Voo(codigo);
    voos.push_back(novoVoo);

    cout << "Voo criado com sucesso!" << endl;
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

bool Sistema::vooExiste(int codigo) {
    for (const auto &voo : voos) {
        if (voo->codigo == codigo) {
            return true;
        }
    }
    return false;
}

bool Sistema::astronautaExiste(const string &cpf) {
    for (const auto &astronauta : astronautas) {
        if (astronauta->cpf == cpf) {
            return true;
        }
    }
    return false;
}

void Sistema::cadastrarAstronauta() {
    string cpf, nome;
    int idade;
    cout << "\n### Cadastrar Astronauta ###" << endl;
    cout << "Digite o CPF do astronauta: ";
    cin >> cpf;

    if (astronautaExiste(cpf)) {
        cout << "Astronauta com este CPF já existe!" << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
        return;
    }
    
    cout << "Digite o nome do astronauta: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite a idade do astronauta: ";
    cin >> idade;

    Astronauta* novoAstronauta = new Astronauta(cpf, nome, idade);
    astronautas.push_back(novoAstronauta);

    cout << "Astronauta cadastrado com sucesso!" << endl;
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::adicionarAstronautaEmVoo() {
    int codigo;
    string cpf;
    cout << "\033[2J\033[1;1H";
    cout << "\n### Adicionar Astronauta em Voo ###" << endl;
    cout << "\nVoos disponíveis: " << endl;
    listarVoosSimples();
    cout << endl << "\nDigite o código do voo: ";
    cin >> codigo;

    Voo* voo = encontrarVoo(codigo);
    if (voo) {
        if (voo->status != "planejado"){
            cout << endl << "Não é possivel adicionar astronautas em um voo que já foi lançado." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
            return;
        }
        cout << "\nAstronautas disponíveis: \n";
        listarAstronautas();
        
        cout << "\nDigite o CPF do astronauta a ser adicionado: ";
        cin >> cpf;

        Astronauta* astronauta = encontrarAstronauta(cpf);
        if (voo->astronautaJaNoVoo(cpf)) {
            cout << "\n\nAstronauta já está no voo." << endl;
            return;
        }
        if (astronauta) {
            if(!astronauta->vivo){
                cout << "Não é possivel adicioanr um astronauta que está morto a um voo" << endl;
                getchar();
                cout << "\nPressione enter para sair....";
                getchar();
                return;
            }
            voo->adicionarAstronauta(astronauta);
            cout << "Astronauta adicionado ao voo!" << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
        } else {
            cout << "Astronauta não encontrado." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
        }
        
    } else {
        cout << "Voo não encontrado." << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    }
}

void Sistema::removerAstronautaDeVoo() {
    int codigo;
    string cpf;
    cout << "\033[2J\033[1;1H";
    cout << "\n### Remover Astronauta de Voo ###" << endl;
    cout << "\nVoos disponíveis: " << endl;
    listarVoosSimples();
    cout << endl << "Digite o código do voo: ";
    cin >> codigo;

    Voo* voo = encontrarVoo(codigo);
    if (voo) {
        if(voo->status != "planejado"){
            cout << endl << "Não é mais possivel remover astronautas deste voo, ele já foi lançado." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
            return;
        }
        if (voo->passageiros.size() < 1){
            cout << endl << "Não é possivel remover astronautas deste voo, pois ele não possui nenhum astronauta." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
            return;
        }
        listarAstronautasDeVoo(codigo);
        cout << "Digite o CPF do astronauta a ser removido: ";
        cin >> cpf;
        voo->removerAstronauta(cpf);
        cout << "Astronauta removido do voo!" << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    } else {
        cout << "Voo não encontrado." << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    }
}

void Sistema::editarVoos() {
    int opcao;
    do {
        cout << "\033[2J\033[1;1H";
        cout << "\n### Editar Voos ###" << endl;
        cout << "3.1. Adicionar Astronauta em Voo" << endl;
        cout << "3.2. Remover Astronauta de Voo" << endl;
        cout << "Escolha uma opção (ou 0 para voltar): ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarAstronautaEmVoo();
                break;
            case 2:
                removerAstronautaDeVoo();
                break;
            case 0:
                cout << "\nVoltando ao menu principal..." << endl;
                getchar();
                cout << "\nPressione enter para sair....";
                getchar();
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 0);
}

void Sistema::gerenciarVoos() {
    int opcao;
    do {
        cout << "\033[2J\033[1;1H";
        cout << "\n### Gerenciar Voos ###" << endl;
        cout << "4.1. Lançar Voo" << endl;
        cout << "4.2. Explodir Voo" << endl;
        cout << "4.3. Finalizar Voo" << endl;
        cout << "Escolha uma opção (ou 0 para voltar): ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                
                lancarVoo();
                break;
            case 2:
                explodirVoo();
                break;
            case 3:
                finalizarVoo();
                break;
            case 0:
                cout << "\nVoltando ao menu principal..." << endl;
                getchar();
                cout << "\nPressione enter para sair....";
                getchar();
                
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 0);
}

void Sistema::listarVoos() {
    cout << "\n### Listar Voos ###" << endl;
    for (auto voo : voos) {
        cout << "Código do voo: " << voo->codigo << ", Status: " << voo->status << endl;
        if(voo->passageiros.size() > 0){
            cout << "Passageiros:" << endl;
            for (auto astronauta : voo->passageiros) {
                cout << "  Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << endl;
            }
        }
        
        cout << endl;
        
    }
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::listarVoosSimples() {
    for (const auto& voo : voos) {
        if(voo->status == "planejado"){
            cout << "Voo: " << voo->codigo << "\t";
        }
        
    }
}

void Sistema::listarVoosSimplesEmCurso() {
    for (const auto& voo : voos) {
        if(voo->status == "em curso"){
            cout << "Voo: " << voo->codigo << "\t";
        }
        
    }
}

void Sistema::listarVoosSimplesComAstronautas() {
    for (const auto& voo : voos) {
        if(voo->passageiros.size() > 0 && voo->status == "planejado"){
            cout << "Voo: " << voo->codigo << "\t";
        }
        
    }
}

void Sistema::listarAstronautasDeVoo(int codigoVoo) {
    Voo* voo = encontrarVoo(codigoVoo);
    if (!voo) {
        cout << "Voo não encontrado." << endl;
        return;
    }

    cout << endl <<"Astronautas do Voo " << codigoVoo << ":" << endl;
    for (const auto& astronauta : voo->passageiros) {
        cout << "Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf <<  endl;
    }
}

void Sistema::listarAstronautas() {
    
    for (auto astronauta : astronautas) {
        cout << "Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << ", Idade: " << astronauta->idade;
        if (!astronauta->vivo) {
            cout << " (Morto)";
        }
        cout << endl;
    }
    
}

void Sistema::listarAstronautasComVoos() {
    
    for (auto astronauta : astronautas) {
        cout << "Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << ", Idade: " << astronauta->idade;
        if (!astronauta->vivo) {
            cout << " (Morto)";
        }
        cout << endl << "Voos participados:" << endl;
            for (auto voo : voos) {
                for (auto pass : voo->passageiros) {
                    if (pass->cpf == astronauta->cpf) {
                        cout << "  Código do voo: " << voo->codigo << endl;
                    }
                }
            }
            cout << endl;
        cout << endl;
    }
    
}

void Sistema::status() {
    int opcao;
    do {
        cout << "\n### Status ###" << endl;
        cout << "7.1. Status Voos" << endl;
        cout << "7.2. Status Astronautas" << endl;
        cout << "Escolha uma opção (ou 0 para voltar): ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                statusVoos();
                break;
            case 2:
                statusAstronautas();
                break;
            case 0:
                getchar();
                cout << "Precione enter para voltar ao menu principal..." << endl;
                getchar();
                break;
            default:
                cout << "Opção inválida! Tente novamente." << endl;
        }
    } while (opcao != 0);
}

void Sistema::statusVoos() {
    cout << "\n### Status Voos ###" << endl;
    for (auto voo : voos) {
        cout << "Código do voo: " << voo->codigo << ", Status: " << voo->status << endl;
        cout << "Passageiros:" << endl;
        for (auto astronauta : voo->passageiros) {
            cout << "  Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << endl;
        }
        cout << endl;
    }
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::statusAstronautas() {
    cout << "\n### Status Astronautas ###" << endl;
    for (auto astronauta : astronautas) {
        cout << "Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << ", Idade: " << astronauta->idade;
        if (astronauta->disponivel) {
            cout << " (Disponível)";
        } else {
            cout << " (Indisponível)";
        }
        if (!astronauta->vivo) {
            cout << " (Morto)";
        }
        cout << endl;
    }
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::listarMortos() {
    cout << "\n### Listar Astronautas Mortos ###" << endl;
    for (auto astronauta : astronautas) {
        if (!astronauta->vivo) {
            cout << "Nome: " << astronauta->nome << ", CPF: " << astronauta->cpf << endl;
            cout << "Voos participados:" << endl;
            for (auto voo : voos) {
                for (auto pass : voo->passageiros) {
                    if (pass->cpf == astronauta->cpf) {
                        cout << "  Código do voo: " << voo->codigo << endl;
                    }
                }
            }
            cout << endl;
        }
    }
    getchar();
    cout << "\nPressione enter para sair....";
    getchar();
}

void Sistema::lancarVoo() {
    int codigo;
    cout << "\033[2J\033[1;1H";
    cout << "\n### Lançar Voo ###" << endl;
    cout << endl <<  "Voos: \n";
    listarVoosSimplesComAstronautas();
    cout << endl << "\nDigite o código do voo a ser lançado: ";
    cin >> codigo;

    Voo* voo = encontrarVoo(codigo);
    if (voo) {
        if (voo->status == "planejado") {
            if (voo->passageiros.size() > 0) {
                bool todosDisponiveis = true;
                for (auto astronauta : voo->passageiros) {
                    if (!astronauta->disponivel) {
                        todosDisponiveis = false; 
                        break;
                    }
                }
                if (todosDisponiveis) {
                    voo->status = "em curso";
                    for (auto astronauta : voo->passageiros) {
                        astronauta->disponivel = false;
                    }
                    cout << "Voo lançado com sucesso!" << endl;
                    getchar();
                    cout << "\nPressione enter para sair....";
                    getchar();
                } else {
                    cout << "Não é possível lançar o voo: nem todos os astronautas estão disponíveis." << endl;
                    getchar();
                    cout << "\nPressione enter para sair....";
                    getchar();
                }
            } else {
                cout << endl << "Não é possível lançar o voo: o voo não possui astronautas." << endl;
                getchar();
                cout << "\nPressione enter para sair....";
                getchar();
            }
        } else {
            cout << "Não é possível lançar o voo: o voo não está em fase de planejamento." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
        }
    } else {
        cout << "Voo não encontrado." << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    }
}

void Sistema::explodirVoo() {
    int codigo;
    cout << "\033[2J\033[1;1H";
    cout << "\n### Explodir Voo ###" << endl;
    cout << "\nVoos: \n";
    listarVoosSimplesEmCurso();
    cout << "\n\nDigite o código do voo a ser explodido: ";
    cin >> codigo;

    Voo* voo = encontrarVoo(codigo);
    if (voo) {
        
        if(voo->status == "em curso"){
            voo->status = "explodido";
            for (auto astronauta : voo->passageiros) {
                astronauta->vivo = false;
                astronauta->disponivel = false;
            }
            cout << "\nVoo explodido com sucesso!" << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
        } else{
            cout << "\nNão é possível explodir o voo: o voo não está em curso" << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
        }
    } else {
        cout << "Voo não encontrado." << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    }
}

void Sistema::finalizarVoo() {
    int codigo;
    string sucesso;
    cout << "\n### Finalizar Voo ###" << endl;
    cout << "\nVoos: \n";
    listarVoosSimplesEmCurso();
    cout << "\nDigite o código do voo a ser finalizado: ";
    cin >> codigo;

    Voo* voo = encontrarVoo(codigo);
    if (voo) {
        if (voo->status != "em curso"){
            cout << "Voo não está em curso. Não é possível finalizar." << endl;
            getchar();
            cout << "\nPressione enter para sair....";
            getchar();
            return;
        }
        voo->status = "finalizado com sucesso";
        for (auto astronauta : voo->passageiros) {
            astronauta->disponivel = true;
        }
        cout << "Voo finalizado com sucesso!" << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    } else {
        cout << "Voo não encontrado." << endl;
        getchar();
        cout << "\nPressione enter para sair....";
        getchar();
    }
}

Astronauta* Sistema::encontrarAstronauta(string cpf) {
    for (auto astronauta : astronautas) {
        if (astronauta->cpf == cpf) {
            return astronauta;
        }
    }
    return nullptr;
}

Voo* Sistema::encontrarVoo(int codigo) {
    for (auto voo : voos) {
        if (voo->codigo == codigo) {
            return voo;
        }
    }
    return nullptr;
}

void Sistema::sair(){
    cout << "\n\nObrigado por executar o programa!!!" << endl;
    getchar();
    cout << "\n\n\n\n\n\nda 10 ae professor :/" << endl;
    getchar();

}