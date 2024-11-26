#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// estrutura do jogador
struct Jogador 
{
    string nome;
    string classe;
    int nivel;
    int xp;
    int vida;
    int ataque;
    int defesa;
    int progresso = 0;
    string especialn;
    int especial = 0;
    bool especialu = false;
    string inventario[5] = {"Pocao de cura", "Visco magico", "", "", ""}; // inventario
    string arma;
};

// funçoes do jogo
void menu();
void iniciar();
Jogador criarJogador();
void mStatus(const Jogador& jogador);
void mInventario(const Jogador& jogador);
void uItem(Jogador& jogador);
void batalha(Jogador& jogador, string inimigo, int vidai, int ataquei);
void mCenarioInicial(Jogador& jogador);
void montanha(Jogador& jogador);
void castelo(Jogador& jogador);
void upar(Jogador& jogador);
void salvarJogo(const Jogador& jogador);
bool carregarJogo(Jogador& jogador);
void progresso(Jogador& jogador);

int main() 
{
    menu();
    return 0;
}

void menu() 
{
    int opcao;
    Jogador jogador;
    do
    {
        cout << "=== A Profecia  ===" << endl;
        cout << "1. Iniciar Jogo" << endl;
        cout << "2. Carregar Jogo" << endl;
        cout << "3. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) 
        {
            case 1:
                iniciar();
                break;
            case 2:
                if (carregarJogo(jogador)) {
                    cout << "Jogo carregado com sucesso!" << endl;
                    mStatus(jogador);
                    progresso(jogador);
                } else {
                    cout << "Falha ao carregar o jogo. Comece um novo!" << endl;
                }
                break;
            case 3:
                cout << "Saindo do jogo..." << endl;
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
        }
    } while (opcao != 3);
}


// função para salvar o estado do jogo
void salvarJogo(const Jogador& jogador) 
{
    ofstream arquivo("salvar_jogo.txt");
    if (arquivo.is_open()) 
    {
        arquivo << jogador.nome << endl;
        arquivo << jogador.classe << endl;
        arquivo << jogador.nivel << endl;
        arquivo << jogador.xp << endl;
        arquivo << jogador.vida << endl;
        arquivo << jogador.ataque << endl;
        arquivo << jogador.defesa << endl;
        arquivo << jogador.especialn << endl;
        arquivo << jogador.especial << endl;
        arquivo << jogador.especialu << endl;
        arquivo << jogador.progresso << endl;

        for (const auto& item : jogador.inventario) {
            arquivo << item << endl;
        }

        arquivo << jogador.arma << endl;
        arquivo.close();
        cout << "Jogo salvo com sucesso!" << endl;
    } 
    else 
    {
        cout << "Erro ao salvar o jogo." << endl;
    }
}

// função para carregar o estado do jogo
bool carregarJogo(Jogador& jogador) 
{
    ifstream arquivo("salvar_jogo.txt");
    if (arquivo.is_open()) 
    {
        getline(arquivo, jogador.nome);      // Carrega nome
        getline(arquivo, jogador.classe);    // Carrega classe
        arquivo >> jogador.nivel;            // Carrega nível
        arquivo >> jogador.xp;               // Carrega XP
        arquivo >> jogador.vida;             // Carrega vida
        arquivo >> jogador.ataque;           // Carrega ataque
        arquivo >> jogador.defesa;           // Carrega defesa
        arquivo.ignore();                    // Ignora a nova linha após valores inteiros
        getline(arquivo, jogador.especialn); // Carrega nome do especial
        arquivo >> jogador.especial;         // Carrega dano do especial
        arquivo >> jogador.especialu;        // Carrega se o especial foi usado
        arquivo >> jogador.progresso;        // Carrega o progresso

        arquivo.ignore(); // Ignora a nova linha após valores booleanos
        for (auto& item : jogador.inventario) {
            getline(arquivo, item);  // Carrega o inventário
        }

        getline(arquivo, jogador.arma);  // Carrega a arma
        arquivo.close();

        // Corrige o retorno ao ponto correto com base no progresso
        if (jogador.progresso == 0) {
            mCenarioInicial(jogador);
        } else if (jogador.progresso == 1) {
            montanha(jogador);
        } else if (jogador.progresso == 2) {
            castelo(jogador);
        } else {
            cout << "Progresso invalido. Comecando do inicio." << endl;
            mCenarioInicial(jogador);
        }
        return true;
    } 
    else 
    {
        cout << "Arquivo de salvamento nao encontrado." << endl;
        return false;
    }
}
// para iniciar
void iniciar()
{
    Jogador jogador = criarJogador();
    mCenarioInicial(jogador);
}

// criando personagem
Jogador criarJogador() 
{
    Jogador jogador;
    cout << "Digite o nome do seu personagem: ";
    cin >> jogador.nome;
    cout << "Escolha sua classe (Cavaleiro, Mago, Druida,Arqueiro,Xama): ";
    cin >> jogador.classe;
    
    jogador.nivel = 1;
    jogador.vida = 100;
    jogador.arma;
    jogador.especial;

    if (jogador.classe == "Cavaleiro"|| jogador.classe == "cavaleiro"){
        jogador.ataque = 15;
        jogador.defesa = 20;
        jogador.arma = "Espada";
        jogador.especialn = "§§§ Corte em X §§§";
        jogador.especial = jogador.ataque*2.3;
        
    } else if (jogador.classe == "Mago"||jogador.classe == "mago") {
        jogador.ataque = 20;
        jogador.defesa = 10;
        jogador.arma = "Cajado";
        jogador.especialn = "§§§ Raio Negro §§§";
        jogador.especial = jogador.ataque + 30;
    }
      else if (jogador.classe == "Arqueiro"||jogador.classe == "arqueiro") {
        jogador.ataque = 30;
        jogador.defesa = 5;
        jogador.arma = "Arco";
        jogador.especialn = "§§§ Chuva de flechas §§§";
        jogador.especial = jogador.ataque + 30;
    } else if (jogador.classe == "Xama"||jogador.classe == "xama") {
        jogador.ataque = 10;
        jogador.defesa = 25;
        jogador.arma = "Livro de maldicoes";
        jogador.especialn = "§§§ Maldicao Vudu §§§";
        jogador.especial = jogador.ataque + 15;
    }
     else if (jogador.classe == "Druida"|| jogador.classe =="druida") {
        jogador.ataque = 18;
        jogador.defesa = 14;
        jogador.arma = "Foice";
        jogador.especialn = "§§§ Drenar §§§";
        jogador.especial == jogador.ataque + 20 ;
        
    } else {
        cout << "Classe invalida! Definido como Cavaleiro." << endl;
        jogador.classe = "Cavaleiro";
        jogador.ataque = 15;
        jogador.defesa = 20;
    }
    if(jogador.nome == "ilidam")
    {
        jogador.nivel += 100;
        jogador.vida += 100;
        jogador.ataque += 100;
        jogador.especialn = "§§§ Toque de Deus §§§";
        jogador.especial = jogador.ataque *100;
    }
    
    cout<<"sua classe eh: "<<endl;
    cout<<"§§§ "<<jogador.classe<<" §§§"<<endl;
    cout<<"dano: " <<jogador.ataque<<endl;
    cout<<"defesa: "<<jogador.defesa<<endl;

    return jogador;
}
// progresso
void progresso(Jogador& jogador) {
    jogador.progresso += 1;
    
}

// status
void mStatus(const Jogador& jogador) 
{
    cout << "=== Status do Jogador ===" << endl;
    cout << "Nome: " << jogador.nome << endl;
    cout << "Classe: " << jogador.classe << endl;
    cout << "Nivel: " << jogador.nivel << endl;
    cout << "Vida: " << jogador.vida << endl;
    cout << "Ataque: " << jogador.ataque << endl;
    cout << "Defesa: " << jogador.defesa << endl;
}

// inventário
void mInventario(const Jogador& jogador) 
{
    cout << "=== Inventario ===" << endl;
    for (int i = 0; i < 5; i++) {
        if (!jogador.inventario[i].empty()) {
            cout << i + 1 << ". " << jogador.inventario[i] << endl;
        }
    }
}

// usar item
void usarItem(Jogador& jogador) 
{
    mInventario(jogador);
    int escolha;
    cout << "Escolha um item para usar (0 para cancelar): ";
    cin >> escolha;

    if (escolha >= 1 && escolha <= 5 && !jogador.inventario[escolha - 1].empty()) {
        string item = jogador.inventario[escolha - 1];
        if (item == "Pocao de Cura") {
            jogador.vida += 30;
            jogador.inventario[escolha - 1] = "";// Remove o item usado
        }
        if (item == "Visco"&&"Visco magico") {
            jogador.vida += 20;
            cout << "Voce usou um item de cura. Vida atual: " << jogador.vida << endl;
            jogador.inventario[escolha - 1] = ""; // Remove o item usado
        } else {
            cout << "Item nao pode ser usado agora!" << endl;
        }
    } else if (escolha == 0) {
        cout << "Cancelando..." << endl;
    } else {
        cout << "Escolha invalida!" << endl;
    }
}

// upar de nivel
void upar(Jogador& jogador)
{
    
   
    if(jogador.xp >= 10)
    {
      cout<<"§§§ Voce subiu de nivel! §§§"<<endl;
      jogador.nivel += 1;
      jogador.vida +=30;
      jogador.defesa +=3;
      jogador.especialu = false;
     
    }
    
}
   



// batalha
void batalha(Jogador& jogador, string inimigo, int vidai, int ataquei)
{
    cout << "Voce esta enfrentando um " << inimigo << "!" << endl;

    while (vidai > 0 && jogador.vida > 0) {
        cout << "\n=== Turno do Jogador ===" << endl;
        cout << "\n sua vida atual eh :"<<jogador.vida<<endl;
        cout << "1. Atacar\n2. Especial\n3. Usar Item\n4. salva e sair\nEscolha: ";
        int acao;
        int dano;
        cin >> acao;

        if (acao == 1) {
            dano = jogador.ataque;
            cout << "Voce atacou o " << inimigo << "!" << endl;
            cout <<"dano: "<<vidai-dano << endl;
            vidai -= jogador.ataque;
            if (jogador.classe == "Xama" || jogador.classe == "xama") {
                    jogador.vida += jogador.ataque;
                    cout<< "Voce curou: "<<jogador.ataque<<endl;
            }        
            if (vidai <= 0) {
                cout << "Voce derrotou o " << inimigo << "!" << endl;
                progresso(jogador);
                break;
            }
        } else if (acao == 3) {
            usarItem(jogador);
            
        } else if (acao == 2){
            if (!jogador.especialu) { // verificar uso
                cout << "Voce usa: " << jogador.especialn << "!" << endl;
                dano = jogador.especial;
                cout << "Dano : " <<vidai-dano << endl;
                vidai -= jogador.especial;
                jogador.especialu = true; // especial usado
                if (jogador.classe == "Druida" || jogador.classe == "druida") {
                    jogador.vida += jogador.especial;
                    cout<< "Voce curou: "<<jogador.especial<<endl;
                 }
                if (vidai <= 0) {
                    cout << "Voce derrotou o " << inimigo << "!" << endl;
                    
                    break;
                }
            } else {    
                 cout << "Voce ja usou seu especial neste nivel!" << endl;
                }
        }else if(acao == 4){
            cout << "Salvando progresso e voltando ao menu..." << endl;
            salvarJogo(jogador);
            menu();
            return;
            
        }
        
        else {
            cout << "Escolha invalida!" << endl;
        }

        cout << "\n=== Turno do Inimigo ===" << endl;
        cout << "O " << inimigo << " atacou voce!" << endl;
        jogador.vida -= ataquei;

        if (jogador.vida <= 0) {
            cout << "Voce foi derrotado pelo " << inimigo << "." << endl;
            break;
        }
    }

    if (jogador.vida > 0) {
        cout << "Vitoria! Vida restante: " << jogador.vida << endl;
    } else {
        cout << "Game Over. Tente novamente." << endl;
        exit (0) ;
    }
}

// cenario
void mCenarioInicial(Jogador& jogador)
{
    cout << "Bem-vindo a Provincia de Ilidam" <<endl;
    cout << "ola " << jogador.nome <<",como sabe eu sou Pendragon um dos reis da provincia!"<<endl;
    cout << "Convoco-o aqui, pois o reino está em perigo e preciso de sua ajuda, nobre herói."<<endl;
    cout << "Você deve ir até a Floresta da Perdição para encontrar o Castelo de Meleagant e Matar seu Dragao" << endl;
    cout << "apos aceitar a missao do rei, nosso heroi vai Floresta adentro,"<<endl;
    cout << "mas quando  menos esperava encontra..."<<endl;
    batalha(jogador, "Lobo indomavel", 30, 5);
    jogador.xp += 5;
    cout << "apos a primeira batalha nosso heroi descobre que a jornada nao sera facil!"<<endl;
    cout << jogador.nome <<" volta a seguir o caminho da floresta correndo, em um ato consciente de nao ficar a noite na floresta"<<endl;
    cout <<"apesar de seus esforços a escuridao toma os ceus da Floresta da Perdicao,foi quando "<<jogador.nome<<" nao conseguindo mais enxegar"<<endl;
    cout <<"ve um esperanca,uma luz no meio da floresta,algo como uma fogueira,sendo assim o heroi se aproxima"<<endl;
    cout <<"para descobrir que nao estaria sozinho..."<<endl;
    batalha(jogador, "turtran o Terrivel", 60, 12);
    montanha(jogador);
}

void montanha(Jogador& jogador) 
{
    cout << "Voce chegou na Montanha sinistra. Um Orc raivoso aparece para te atacar!" << endl;
    batalha(jogador, "Orc raivoso", 60, 17);
    cout << "voce encontrou uma "<< jogador.arma <<" dourada "<<endl;
    jogador.ataque += 15;
    jogador.xp += 5;
    upar(jogador);
    castelo(jogador);
}

void castelo(Jogador& jogador) 
{
    cout << "Voce chegou ao Castelo de Meleagant o Temido. O vilao final, o Dragao Sombrio de Meleagant aparece" << endl;
    batalha(jogador, "Dragao de Meleagant", 100, 25);
    cout << "Parabens! Voce derrotou o Dragao de Meleagant e salvou o reino!" << endl;
   
   
   
    if(jogador.nome == "ilidam"){
     cout << "mas quando Ilidam achava que tudo tinha acabado,ele encontra uma pista do Meleagant,e descobre que na verdade ele era o rei\ne so queria que ilidam matasse o dragao pois o mesmo estava guardando o poder verdadeiro de Meleagant\nentao ilidam alca voo,em direcao ao 'rei'"<<endl;
     cout << "ao chegar no castelo ilidam descobre que o rei obteve os poderes do dragao..." << endl;
     cout << "(Melegant):\nvoce eh tolo Ilidam,chegou tarde de mais,agora vou conquistar toda a Provincia "<<endl;
     cout << "(Meleagant):usa §§§ Fogo Infernal §§§"<<endl;
     jogador.vida -= 100;
     batalha(jogador,"Rei Meleagant o Dragao",200,50);
     cout << "ao derrotar o rei tirano,ilidam tras paz de volta a sua provincia"<<endl;
     cout << "§§§ Fim §§§\nObrigado por jogar :)"<<endl;
     cout << "Creditos:\n Arthur Lopes\n Leonardo mota\n;Daniel"<<endl;
    }
}