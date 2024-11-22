#include <iostream>
#include <string>
#include <cstdlib>  // Para srand() e rand()
#include <ctime>    // Para time()

using namespace std;

// Classe base para personagens
class Personagem {
protected:
    string nome;
    int vida;
    int forca;
    bool pocaoUsada;
public:
    Personagem(string n, int v, int f) : nome(n), vida(v), forca(f), pocaoUsada(false) {}

    virtual void mostrarStatus() const {
        cout <<  nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }

    virtual int atacar() {
        int dado = rand() % 10 + 1;
        int dano = forca * dado; // Calcula o dano
        cout <<  nome << " rolou um dado: " << dado << endl; // Mostra o dado rolado
        return dano; // Retorna o dano causado
    }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() const {
        return vida > 0;
    }

    void usarPocaoVida() {
        if (!pocaoUsada) {
            vida += 20; // Cura 20 de vida
            pocaoUsada = true; // Indica que a poção foi usada
            cout << nome << " usou uma pocao de cura e agora tem " << vida << " de vida." << endl;
        } else {
            cout << nome << " já usou uma pocao nesta batalha!" << endl;
        }
    }

    void usarPocaoForca() {
        if (!pocaoUsada) {
            forca += 5; // Aumenta 5 de força
            pocaoUsada = true; // Indica que a poção foi usada
            cout << nome << " usou uma poção de forca e agora tem " << forca << " de forca." << endl;
        } else {
            cout << nome << " já usou uma pocao nesta batalha!" << endl;
        }
    }

    string getNome() const { return nome; }
    int getVida() const { return vida; }
};

// Classes inspiradas nos personagens de Hollow Knight
class PequenoCavaleiro : public Personagem {
public:
    PequenoCavaleiro(string n) : Personagem(n, 110, 6) {}

    void mostrarStatus() const override {
        cout << "    Pequeno Cavaleiro " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class PrincesaDeHallownest : public Personagem {
public:
    PrincesaDeHallownest(string n) : Personagem(n, 105, 15) {}

    void mostrarStatus() const override {
        cout << "    Princesa de Hallownest " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class ReceptaculoPuro : public Personagem {
public:
    ReceptaculoPuro(string n) : Personagem(n, 100, 20) {}

    void mostrarStatus() const override {
        cout << "    Receptaculo Puro " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

class CavaleiroDasSombras : public Personagem {
public:
    CavaleiroDasSombras(string n) : Personagem(n, 120, 5) {}

    void mostrarStatus() const override {
        cout << "    Cavaleiro das Sombras " << nome << " - Vida: " << vida << ", Forca: " << forca << endl;
    }
};

// Classe para Chefes/Inimigos
class Chefe {
private:
    string nome;
    int vida;
    int forca;
public:
    Chefe(string n, int v, int f) : nome(n), vida(v), forca(f) {}

    int atacar() {
        int dado = rand() % 10 + 1;
         cout <<     nome << " rolou um dado: " << dado << endl; // Mostra o dado rolado
        return forca * dado;
    }

    void receberDano(int dano) {
        vida -= dano;
        if (vida < 0) vida = 0;
    }

    bool estaVivo() const {
        return vida > 0;
    }

    string getNome() const { return nome; }
    int getVida() const { return vida; }
};

// Função para batalha entre um personagem e um chefe
void batalha(Personagem &heroi, Chefe &inimigo) {
    cout << "   A batalha entre " << heroi.getNome() << " e o chefe " << inimigo.getNome() << " comeca!" << endl;

    while (heroi.estaVivo() && inimigo.estaVivo()) {
        char acao;
        cout << "     Escolha sua acao: (G)irar o dado para atacar, (P) usar pocao ou (F)ugir: ";
        cin >> acao;

        if (acao == 'F' || acao == 'f') {
            cout << heroi.getNome() << " fugiu da batalha!" << endl;
            return;  // Sai da função batalha se o jogador fugir
        } else if (acao == 'P' || acao == 'p') {
            char tipoPocao;
            cout << "    Escolha o tipo da pocao: (V)ida ou (F)orca: ";
            cin >> tipoPocao;

            if (tipoPocao == 'V' || tipoPocao == 'v') {
                heroi.usarPocaoVida();
            } else if (tipoPocao == 'F' || tipoPocao == 'f') {
                heroi.usarPocaoForca();
            } else {
                cout << "    Tipo de pocao invalido!" << endl;
            }
        } else if (acao == 'G' || acao == 'g') {
            // Ataque do personagem
            int danoHeroi = heroi.atacar();
            inimigo.receberDano(danoHeroi);
            cout << heroi.getNome() << " causa " << danoHeroi << " de dano ao chefe!" << endl;

            // Verifica se o chefe foi derrotado
            if (!inimigo.estaVivo()) {
                cout << inimigo.getNome() << " foi derrotado!" << endl;
                break;
            }

            // Ataque do chefe
            int danoInimigo = inimigo.atacar();
            heroi.receberDano(danoInimigo);
            cout << inimigo.getNome() << " causa " << danoInimigo << " de dano ao " << heroi.getNome() << "!" << endl;

            // Verifica se o heroi foi derrotado
            if (!heroi.estaVivo()) {
                cout << heroi.getNome() << " foi derrotado!" << endl;
                break;
            }

            cout << heroi.getNome() << " vida: " << heroi.getVida() << " | " << inimigo.getNome() << " vida: " << inimigo.getVida() << endl;
        } else {
            cout << "    Acao invalida! Escolha (G)irar o dado, (P) usar pocao ou (F)ugir." << endl;
        }
    }
}

// Função para o jogador escolher uma classe de personagem
Personagem* escolherPersonagem() {
    int escolha;
    cout << " Escolha sua classe de personagem:\n";
    cout << "1. Pequeno Cavaleiro\n";
    cout << "2. Princesa de Hallownest\n";
    cout << "3. Receptaculo Puro\n";
    cout << "4. Cavaleiro das Sombras\n";
    cout << " Digite o numero correspondente a classe escolhida: ";
    cin >> escolha;

    string nome;
    cout << " Digite o nome do seu personagem: ";
    cin >> nome;

    switch (escolha) {
        case 1: return new PequenoCavaleiro(nome);
        case 2: return new PrincesaDeHallownest(nome);
        case 3: return new ReceptaculoPuro(nome);
        case 4: return new CavaleiroDasSombras(nome);
        default:
            cout << " Escolha invalida! Pequeno Cavaleiro foi selecionado por padrao.\n";
            return new PequenoCavaleiro(nome);
    }
}

void mostrarCreditos() {
    cout << "\n=========== CREDITOS ===========" << endl;
    cout << "       Desenvolvido por:" << endl;
    cout << "    1. Arthur Villas" << endl;
    cout << "    2. Bianca Medina" << endl;
    cout << "    3. Carlos Eduardo M M" << endl;
    cout << "    4. Henrico" << endl;
    cout << "================================\n" << endl;
}

int main() {
    srand(time(0)); // Semente para números aleatórios

    // Mensagem de boas-vindas e opções
    cout << "                 Bem vindo ao mundo de Hollow Knight\n\n";
    cout << "                         @@@             @@@                          \n";
    cout << "                      @@@@@                @@@@@                      \n";
    cout << "                    @@@@@                   @@@@@                    \n";
    cout << "                   @@@@                       @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                  @@@@                        @@@@                    \n";
    cout << "                   @@@@                      @@@@                     \n";
    cout << "                    @@@@                   @@@@@                      \n";
    cout << "                      @@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "                      @@%%%%%%%%%%%%%%%%%%%%@@                        \n";
    cout << "                       @#%%%%%%%%%%%%%%%%%%%@                        \n";
    cout << "                       @#%%%%%%%%%%%%%%%%%%%@                        \n";
    cout << "                       @@@@@@@@@%%%%@@@@@@@@@                        \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                       @@      @@%%@@      @@                         \n";
    cout << "                        @@@@@@@@@@@@@@@@@@@@                          \n";
    cout << "                         @@@@@@@@@@@@@@@@@@                           \n\n";

    char opcao;
    while (true) {
        cout << "            Digite (I) para Iniciar,(C) para creditos ou (S) para Sair:\n";
        cin >> opcao;

        if (opcao == 'I' || opcao == 'i') {
            // Inicia o jogo
            cout << "\n   Em um reino subterraneo esquecido chamado Hallownest, uma antiga civilizacao se desmorona sob o peso de uma praga misteriosa. Voce, um cavaleiro destemido, desperta em meio as sombras, sem memoria de seu passado. Determinado a descobrir a verdade, voce embarca em uma jornada perigosa. Conforme avanca, voce enfrentara criaturas corrompidas, encontrara aliados inesperados e revelara os segredos do reino. O destino de Hallownest e a origem de sua propria existencia estao entrelacados em uma luta contra uma forca obscura conhecida como 'A Radiancia.' Prepare-se para desbravar os misterios de Hallownest e desafiar o que se esconde nas profundezas!\n" << endl;

            // Escolha de personagem pelo jogador
            Personagem* heroi = escolherPersonagem();
            heroi->mostrarStatus();
std::cout << "" << std::endl; // Pula para a próxima linha
            // Criação do chefe
            Chefe miniChefe("Cavaleiro Falso", 120, 4);
            //historia da encruzilhada
			cout << "  Apos voce entrar em Hallownest, a primeira cidade que ele se depara "
     			 << "e a Encruzilhada Esquecida. Um lugar sombrio e desolado, cheio de vida e energia, "
     			 << "mas agora apenas ecos de uma gloria esquecida permanecem.\n"
     			 << "As construcoes antigas e o silencio opressivo sao quebrados apenas pelo som distante "
     			 << "de criaturas vagando nas sombras.\n"
     			 << "  Enquanto explora as ruinas, voce sente que algo nao esta certo. "
     			 << "Uma sensacao de vazio se mistura a tensao no ar, como se o proprio reino estivesse "
      			 << "tentando esconder seus segredos. A poeira e o brilho espectral de pequenos insetos "
     			 << "iluminam o caminho, guiando o personagem por corredores abandonados e pontes precarias.\n"
     			 << "  Logo, voce comeca a encontrar sinais de resistencia: pequenas marcas de batalha nas paredes "
     			 << "e armadilhas deixadas por antigos guerreiros. Cada passo o leva mais fundo nas encruzilhadas, "
     			 << "ate que ele escuta um som perturbador e uma respiracao pesada de uma criatura colossal.\n"
     			 << "Avancando com cautela, ele chega a um salao amplo, onde um antigo guerreiro caido, conhecido como "
     			 << "Cavaleiro Falso, permanece em guarda, como se estivesse esperando por intrusos.\n"
     			 << "  O Cavaleiro Falso, uma figura grotesca e intimidadora, bloqueia o caminho. Sua armadura pesada "
     			 << "reflete a luz fraca, e seus olhos brilham com uma ferocidade sombria. Para seguir adiante e desvendar "
     			 << "os segredos de Hallownest, voce sabe que deve enfrentar essa ameaca imponente." << endl;
     			 std::cout << "" << std::endl; // Pula para a próxima linha
            // Opção de combate com o mini chefe
            char escolha;
            cout << "              		    @     @                        \n";
    	cout << "              		   @@     @@                        \n";
    cout << "                        @@@      @@@                            \n";
    cout << "                      @@@@        @@                            \n";
    cout << "              @@      @@@         @@@          @@@@@@          \n";
    cout << "    @@@@@@@@@@@@@@   @@@@@      @@@@@        @@@@@@@@@@@       \n";
    cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@@@@@@@@      \n";
    cout << "          @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@  @@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@@  @@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@      \n";
    cout << "         @@@@@@@@@@@@@@  @@@@@  @@@@@@@@@@@@@@@@@@@@@@@@       \n";
    cout << "           @@@@@@@@@@@@@ @@@@ @@@@@@@@@@@@@@@@@@@@@@@@@        \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@@  @@@                   \n";
    cout << "                @@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "               @@@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "               @@@@@@@@@@@@@@@@@@@@@@@@@                        \n";
    cout << "              @@@@                @@@@@@@                       \n";
    cout << "               @@@                   @@@@@                      \n";
    cout << "                                       @@                     \n";
            cout << "\n            Voce encontrou um chefe, o Cavaleiro Falso! Deseja batalhar? (B para batalha, F para fugir): ";
            cin >> escolha;

            if (escolha == 'B' || escolha == 'b') {
                batalha(*heroi, miniChefe);
            } else {
                cout << heroi->getNome() << " decidiu nao batalhar com Cavaleiro Falso e seguiu em frente." << endl;
            }
		     // Criação do segundo mini chefe
        Chefe miniChefe2("Mestre Das Almas", 90, 5);
        
    cout << "                            @@          @@                      \n";
    cout << "                         @@%#%@ @@@@@@@@@%%@                    \n";
    cout << "                        @%####%+.-+..:*:-%##@@                  \n";
    cout << "                      @@##@@@@+++=+*#*#-@@@@%%%@                \n";
    cout << "                     @%#@-----@+*======@-===@*#%@@               \n";
    cout << "                @@ @@##@-----=@=========@---@-#%@@              \n";
    cout << "               @%%@@###=@@@@@+=+*********@@@@=%%@%##@          \n";
    cout << "               @####%%=====+#*==============##*+%%%%@          \n";
    cout << "               @%##***#%*#*===================+#%#*@@          \n";
    cout << "               @###******####*+======#*+**===+##***@@          \n";
    cout << "             @@####*************#%@%%:.::=%%#*******%@         \n";
    cout << "              @##%##****************%-.::=%*********##@        \n";
    cout << "              @@@@@@%%%%*************%*-+%******######%@       \n";
    cout << "              @@%%#%%#@@@@%@@@@*###%@#*%#*#@@@@@@%%%%@@        \n";
    cout << "            @@%%%@%%#%%##%%#####%#*%#**%#*%#@###%@#%@%%%@@     \n";
    cout << "         @@@%%%@%%%%%@##%%####%%****#%*@#%**#%###%%%%%@%%%@    \n";
    cout << "    @@@%%%%%%@%%%%%%%%%@%##%@%@******#@@%***#%@%%%%@%%%@@%%@   \n";
    cout << "    @@@%%%%@%%%%%%@%%%@%%%%%#%#*******%#*##%%%@@%%%%@%%%%@%%@  \n";
    cout << " @@@%@@%%%@%%%%%@%%%%@%%%%%####%%#####%##%%#@%#%@%%%%%@%%%%@@  \n";
    cout << "@@@     @@@@@%@@%%%%%%%%%@%######%%%%@%%##%%@%%%@@%%%%%@%%%%@@ \n";
    cout << "         @ @@@@@@%%@%%%%%%%#@@%####%%#%@@%##@%%%%@%%%%@@@%%%%@@\n";
    cout << "             @@%@@@%%%%%@%%#@@#%%%%%%@##%%#%%##%%@%%%%@@ @@@@%@\n";
    cout << "            @@@@ @@%%%%%@%%@%@%%@@%%@@#%@%#%@@%@ @@%%%@@ @@  @@\n";
    cout << "           @@@    @  @%@@%@@@#@%@@%@@#@@@@@@@@@  @%%%@@@     @@\n";
    cout << "            @        @%@@@  @%%%%@@@#@@@#@@      @%%%@         \n";
    cout << "                      @@@   @@#@#@@%@ @%@@       @%@@@@        \n";
    cout << "                       @@    @@@%@@%@ @@         @@@           \n";
    cout << "                             @@ @@@@@ @@          @@@          \n";
    cout << "                                @                   @          \n";
    std::cout << "" << std::endl; // Pula para a próxima linha
        cout << "\nVoce encontrou o Mestre Das Almas! Deseja batalhar? (B para batalha, F para fugir): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe2);
        } else {
            cout << heroi->getNome() << " decidiu nao batalhar com o Mestre Das Almas e seguiu em frente." << endl;
        }
        
    Chefe miniChefe3("Defensor Do Esterco", 90, 5);
    cout << "                       @@   @@            \n";    
    cout << "                     @@%@   @@@            \n";
    cout << "                   @%%@      @%@           \n";
    cout << "                  @%%@@     @@%%@          \n";
    cout << "                 @%#@@       @%#@          \n";
    cout << "                  @%@@%%%@@@@%#%@          \n";
    cout << "        @@@       @*=%###=#%%@@@           \n";
    cout << "     @%%###%@   @@%######%%%#%             \n";
    cout << "  @@@%#%%@@%%@@@@%%%%######%*#@            \n";
    cout << " @#%###@%%@%@#++%%####*++#@%+%@@@@@@       \n";
    cout << "@@%#@%**%@%*#%@@%%%%%%@%%#%%@@%*++++*#@    \n";
    cout << "@%%@%##%%++##%%######%%%@@@%##%@%%%%#*+*@  \n";
    cout << "@#%%%%%%+*##%@########%%##%@%%%#%@@%###*%@@\n";
    cout << " @%+#%%+*##%@################%@%%###%@%#+*@\n";
    cout << "   @%%%%%%@@%%@@@@@@@%%%#########%%%@%#%#+%\n";
    cout << "     @+####%%%########%%%@%%######@##@@%%*@\n";
    cout << "    @#+####%%##############%@%%###@@@@@#+@ \n";
    cout << "     @*####%%#################%@+%##*+*%@  \n";
    cout << "     @+####%%##################*%@@@@@     \n";
    cout << "      @*###%%#################**@          \n";
    cout << "       @%%@@@%%@@@@@@@@%%%###+#@           \n";
    cout << "      @##@%##@%############@%@             \n";
    cout << "      @+#%@@@@@@%#######%@@#+%@            \n";
    cout << "      @*##%@########%@@%####*+%@           \n";
    cout << "      @#%%@@@@@@@@%%@%@@@%%%#**@           \n";
    cout << "     @@*%@                  @@@*@@         \n";
    cout << "     @+#@                    @@%*#@        \n";
    cout << "     @+@@                      @@*@        \n";
    cout << "    @%@@                         %%@       \n";
    cout << "   @@                            @@@       \n";
    std::cout << "" << std::endl; // Pula para a próxima linha
        cout << "\nVoce encontrou o Defensor Do Esterco! Deseja batalhar? (B para batalha, F para fugir): ";
        cin >> escolha;

        if (escolha == 'B' || escolha == 'b') {
            batalha(*heroi, miniChefe3);
        } else {
            cout << heroi->getNome() << " decidiu nao batalhar com o Defensor Do Esterco e seguiu em frente." << endl;
        }
        
            // Libera a memória alocada para o heroi
            delete heroi;
            break; // Sai do loop principal após iniciar o jogo
        } else if (opcao == 'C' || opcao == 'c') {
            mostrarCreditos();
        } else if (opcao == 'S' || opcao == 's') {
            cout << "\nObrigado por jogar Hollow Knight! Ate a proxima!" << endl;
            break; // Sai do loop principal e encerra o programa
        } else {
            cout << "\nOpcao invalida! Tente novamente.\n" << endl;
        }
    }

    return 0;
}