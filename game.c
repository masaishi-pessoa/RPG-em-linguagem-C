/*
=====================================
  A BUSCA DO AMULETO SAGRADO
  RPG em Linguagem C

  Sistema de Pontuacao:
  - Cada rota tem uma virtude
  - Escolhas certas dao pontos
  - No final, ranking baseado nos pontos
=====================================
*/

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "art.h"

// Estrutura para o estado do jogo
typedef struct {
    int pontosCompaixao;
    int pontosAstucia;
    int pontosSabedoria;
    int temMithril;
    int temEscamaDragao;
    int dragaoFilhoteSalvo;
    int dragaoFilhoteMorto;
    char rotaEscolhida[20];
} GameState;

int apresentarMenu(const char *titulo, const char *opcoes[], int numOpcoes) {
    WINDOW *menu_win;
    int highlight = 1;
    int escolha = 0;
    int c;
    int startx, starty, width, height;

    height = numOpcoes + 4;
    width = 80;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    box(menu_win, 0, 0);
    mvwprintw(menu_win, 1, (width - strlen(titulo)) / 2, "%s", titulo);
    wrefresh(menu_win);

    while (1) {
        for (int i = 0; i < numOpcoes; i++) {
            if (highlight == i + 1) {
                wattron(menu_win, A_REVERSE);
                mvwprintw(menu_win, i + 2, 2, "%s", opcoes[i]);
                wattroff(menu_win, A_REVERSE);
            } else {
                mvwprintw(menu_win, i + 2, 2, "%s", opcoes[i]);
            }
        }
        wrefresh(menu_win);

        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = numOpcoes;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == numOpcoes)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10: // Enter
                escolha = highlight;
                break;
            default:
                break;
        }
        if (escolha != 0)
            break;
    }

    wclear(menu_win);
    wrefresh(menu_win);
    delwin(menu_win);
    clear();
    refresh();

    return escolha;
}

void exibirAsciiArt(const char* art) {
    clear();
    printw("%s", art);
    refresh();
}

// ========== FUNCOES AUXILIARES ==========

void limparTela() {
    clear();
}

void pausar() {
    printw("\n\nPressione qualquer tecla para continuar...");
    getch();
}

void mostrarPontos(GameState *estado) {
    printw("\n[DEBUG - Pontos Atuais]");
    printw("\nCompaixao: %d | Astucia: %d | Sabedoria: %d\n",
           estado->pontosCompaixao, estado->pontosAstucia, estado->pontosSabedoria);
}

// ========== DECLARACAO DAS FUNCOES ==========
void mostrarPontos(GameState *estado);
void menu(GameState *estado);
void introducao(GameState *estado);
void escolhaRota(GameState *estado);
void rotaFloresta(GameState *estado);
void eventoGoblinFada(GameState *estado);
void eventoElfaGlacify(GameState *estado);
void eventoNinfaFloresta(GameState *estado);
void rotaPantano(GameState *estado);
void eventoCelaBruxa(GameState *estado);
void eventoLagartoFulzard(GameState *estado);
void eventoCobraPantano(GameState *estado);
void rotaCaverna(GameState *estado);
void eventoDragaoFilhote(GameState *estado);
void eventoAnaoEgnar(GameState *estado);
void eventoDrakeAnciao(GameState *estado);
void castelo(GameState *estado);
void eventoGargulaCharadas(GameState *estado);
void eventoArmadurasDancarinas(GameState *estado);
void eventoMimicoDiario(GameState *estado);
void confrontoFinalAnimata(GameState *estado);
void calcularRanking(GameState *estado);

// ========== FUNCAO PRINCIPAL ==========

int main() {
    GameState estado = {0};

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    menu(&estado);

    endwin();
    return 0;
}

// ========== MENU INICIAL ==========

void menu(GameState *estado) {
    exibirAsciiArt(TITULO);
    const char *opcoes[] = {
        "Iniciar Jogo",
        "Sobre o Jogo",
        "Sair"
    };
    int escolha = apresentarMenu("A BUSCA DO AMULETO SAGRADO", opcoes, 3);

    if (escolha == 1) {
        introducao(estado);
    } else if (escolha == 2) {
        limparTela();
        printw("\n=== SOBRE O JOGO ===\n\n");
        printw("Um RPG de escolhas onde suas decisoes importam.\n");
        printw("Tres caminhos, tres virtudes, multiplos finais.\n");
        printw("Descubra a verdade sobre os herois do passado.\n\n");
        pausar();
        menu(estado);
    } else {
        endwin();
        exit(0);
    }
}

// ========== INTRODUCAO ==========

void introducao(GameState *estado) {
    limparTela();
    printw("\n=== INTRODUCAO ===\n\n");

    printw("Ao acordar, voce sai da sua casa e avista um senhor idoso.\n");
    printw("Ele se chama Kenshi, e parece preocupado.\n\n");
    pausar();

    printw("Kenshi: \"Preciso da sua ajuda, jovem aventureiro.\"\n");
    printw("\"Ha um tempo atras, havia uma maga renomada chamada Animata.\"\n");
    printw("\"Ela fazia parte de um grupo de herois lendarios.\"\n\n");
    pausar();

    printw("\"Eles protegiam nosso reino... ate que algo terrivel aconteceu.\"\n");
    printw("\"O lider deles, Damian, morreu em batalha.\"\n");
    printw("\"Animata enlouqueceu de dor e roubou o amuleto sagrado.\"\n");
    printw("\"Agora ela se trancou no castelo.\"\n\n");
    pausar();

    printw("\"Preciso que voce recupere o amuleto e... talvez... salve ela.\"\n\n");
    printw("Kenshi te entrega uma mochila com suprimentos e uma espada.\n");
    printw("Ele limpa uma lagrima: \"Se cuide... Confio em voce.\"\n\n");
    pausar();

    escolhaRota(estado);
}

// ========== ESCOLHA DA ROTA ==========

void escolhaRota(GameState *estado) {
    const char *opcoes[] = {
        "FLORESTA - O caminho da vida e da harmonia. Aqui, a COMPAIXAO e testada.",
        "PANTANO - O caminho dos desafios e armadilhas. Aqui, a ASTUCIA e testada.",
        "CAVERNA - O caminho do conhecimento e verdade. Aqui, a SABEDORIA e testada."
    };
    int escolha = apresentarMenu("ESCOLHA SEU CAMINHO", opcoes, 3);

    // Salva a rota escolhida
    if (escolha == 1) {
        strcpy(estado->rotaEscolhida, "Floresta");
        rotaFloresta(estado);
    } else if (escolha == 2) {
        strcpy(estado->rotaEscolhida, "Pantano");
        rotaPantano(estado);
    } else if (escolha == 3) {
        strcpy(estado->rotaEscolhida, "Caverna");
        rotaCaverna(estado);
    } else {
        printw("\nEscolha invalida! Indo pela Floresta...\n");
        pausar();
        strcpy(estado->rotaEscolhida, "Floresta");
        rotaFloresta(estado);
    }
}

// ========================================
//          ROTA 1: FLORESTA
// ========================================

void rotaFloresta(GameState *estado) {
    exibirAsciiArt(FLORESTA);
    pausar();
    limparTela();
    printw("\n=== FLORESTA ===\n\n");
    printw("Voce entra na floresta densa.\n");
    printw("A luz do sol atravessa as folhas criando um ambiente magico.\n");
    printw("Voce sente paz... mas tambem vigilancia.\n\n");
    pausar();

    // Tres eventos da floresta
    eventoGoblinFada(estado);
    eventoElfaGlacify(estado);
    eventoNinfaFloresta(estado);

    // Apos completar a floresta, vai para o castelo
    castelo(estado);
}

// ---------- EVENTO 1: GOBLIN E FADA ----------

void eventoGoblinFada(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 1: ENCONTRO NA FLORESTA ===\n\n");

    printw("Voce avista um brilho estranho no arbusto.\n");
    printw("Ao se aproximar, ouve grunidos.\n");
    printw("Voce se esconde atras de uma arvore e observa:\n\n");
    printw("Um GOBLIN esta tentando comer uma FADA!\n");
    printw("A fada grita pedindo ajuda!\n\n");
    pausar();

    const char *opcoes1[] = {
        "Atacar o goblin (violencia direta)",
        "Procurar algo ao redor (preparacao)",
        "Interagir com o goblin (comunicacao)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: ATACAR =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce pega sua espada e avanca!\n");
        printw("O goblin se assusta e solta a fada!\n");
        printw("Voce o persegue e...\n\n");

        const char *opcoes2[] = {
            "Deixar ele fugir (misericordia)",
            "Correr atras e atacar (justica)"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 2);

        if (escolha2 == 1) {
            printw("\nVoce deixa o goblin fugir assustado.\n");
            printw("A fada agradece: 'Obrigada por nao matar ele!'\n");
            printw("Ela danca ao seu redor e voce se sente revigorado.\n");
            estado->pontosCompaixao += 2;  // +2 pontos por misericordia
        } else {
            printw("\nVoce persegue e derrota o goblin.\n");
            printw("A fada agradece, mas parece triste: 'Ele era so um bebe...'\n");
            estado->pontosCompaixao += 0;  // 0 pontos - violencia desnecessaria
        }

    // ===== ESCOLHA 2: PROCURAR AO REDOR =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce procura ao redor cuidadosamente...\n");
        printw("Voce encontra:\n\n");

        const char *opcoes2[] = {
            "Pedras no chao",
            "Cristal brilhante",
            "Frutas vermelhas"
        };
        escolha2 = apresentarMenu("O que voce pega?", opcoes2, 3);

        if (escolha2 == 1) {
            // PEDRAS
            printw("\nVoce pega uma pedra e arremessa no goblin!\n");
            printw("Acerta! Ele solta a fada e foge.\n");
            printw("A fada agradece e te abencoa.\n");
            estado->pontosCompaixao += 1;  // +1 ponto - resolveu sem matar

        } else if (escolha2 == 2) {
            // CRISTAL
            printw("\nVoce pega o cristal brilhante e o mostra!\n");
            printw("O goblin esquece a fada e corre atras do cristal!\n");
            printw("Ele pega o cristal e sai pulando feliz.\n");
            printw("A fada ri: 'Goblins adoram coisas brilhantes!'\n");
            printw("Ela danca em volta de voce e te abencoa.\n");
            estado->pontosCompaixao += 3;  // +3 pontos - solucao criativa e pacifica

        } else {
            // FRUTAS
            printw("\nVoce pega as frutas e joga para o goblin!\n");
            printw("Ele pega as frutas e comeca a comer feliz.\n");
            printw("Ele solta a fada e te agradece!\n");
            printw("A fada: 'Ele so estava com fome! Obrigada por entender!'\n");
            printw("Ela te abencoa com po magico.\n");
            estado->pontosCompaixao += 3;  // +3 pontos - empatia maxima
        }

    // ===== ESCOLHA 3: INTERAGIR =====
    } else if (escolha1 == 3) {
        limparTela();
        printw("\nVoce se aproxima com as maos levantadas.\n");
        printw("O goblin te ve e fica na defensiva, segurando a fada.\n\n");

        const char *opcoes2[] = {
            "Gritar com ele (intimidacao)",
            "Fazer mimica (comunicacao)",
            "Dar comida da mochila (empatia)"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            // GRITAR
            printw("\nVoce grita alto!\n");
            printw("O goblin se assusta muito e comeca a correr!\n");
            printw("Ele deixa a fada cair no caminho.\n");
            printw("A fada agradece, um pouco abalada pelo susto.\n");
            estado->pontosCompaixao += 1;  // +1 ponto - funcionou mas foi agressivo

        } else if (escolha2 == 2) {
            // MIMICA
            printw("\nVoce comeca a fazer mimica!\n");
            printw("Voce aponta para a fada, depois para o ceu.\n");
            printw("Voce faz cara de triste, depois de feliz.\n");
            printw("O goblin te olha confuso...\n");
            printw("De repente ele entende e ri muito!\n");
            printw("Ele solta a fada, ainda rindo, e vai embora feliz.\n");
            printw("A fada: 'Voce e muito engracado! E gentil!'\n");
            estado->pontosCompaixao += 3;  // +3 pontos - criatividade e empatia

        } else {
            // DAR COMIDA
            printw("\nVoce pega carne seca da mochila e oferece.\n");
            printw("O goblin cheira... e seus olhos brilham!\n");
            printw("Ele solta a fada e pega a comida.\n");
            printw("Ele come feliz e te segue um pouco, agradecido.\n");
            printw("A fada: 'Ele so tinha fome! Voce tem um bom coracao!'\n");
            estado->pontosCompaixao += 4;  // +4 pontos - maxima empatia (sacrificou comida)
        }
    }

    pausar();
    printw("\n[COMPAIXAO: +%d pontos neste evento]\n", estado->pontosCompaixao);
    pausar();
}

// ---------- EVENTO 2: ELFA GLACIFY ----------

void eventoElfaGlacify(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 2: RIO E CACHOEIRA ===\n\n");

    printw("Voce continua pela floresta ate encontrar um rio cristalino.\n");
    printw("Seguindo o rio, voce chega a uma bela cachoeira.\n\n");
    printw("Do lado direito, uma ELFA NEGRA medita em posicao de lotus.\n");
    printw("Do lado esquerdo, uma ESPADA LONGA esta cravada no chao.\n");
    printw("A cachoeira cai forte no centro.\n\n");
    pausar();

    const char *opcoes1[] = {
        "Pegar a espada (acao impulsiva)",
        "Conversar com a elfa (respeito)",
        "Entrar na cachoeira (purificacao)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: PEGAR ESPADA =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce se aproxima da espada.\n");
        printw("E linda, antiga, coberta de vinhas.\n");
        printw("Voce puxa... e ela sai facilmente!\n");
        printw("Um brilho azul emana dela!\n");
        printw("Voce se sente como um heroi escolhido!\n\n");
        printw("De repente... tudo ao seu redor CONGELA!\n");
        printw("Voce esta preso em gelo!\n\n");
        pausar();

        printw("A elfa abre os olhos e se aproxima.\n");
        printw("Ela pega a espada de suas maos congeladas.\n");
        printw("Com um gesto, o gelo derrete.\n\n");
        printw("Elfa: 'Por que pegou sem pedir?'\n\n");

        const char *opcoes2[] = {
            "Pedir desculpas humildemente",
            "Se justificar",
            "Ficar em silencio"
        };
        escolha2 = apresentarMenu("O que voce responde?", opcoes2, 3);

        if (escolha2 == 1) {
            // DESCULPAS
            printw("\nVoce: 'Me desculpe, agi por impulso. Foi errado.'\n");
            printw("Elfa sorri: 'Poucos admitem erros. Isso e compaixao por si mesmo.'\n");
            printw("'Aceitar falhas e o primeiro passo para crescer.'\n");
            estado->pontosCompaixao += 2;  // +2 por humildade

        } else if (escolha2 == 2) {
            // JUSTIFICAR
            printw("\nVoce: 'Pensei que era uma espada perdida...'\n");
            printw("Elfa balanca a cabeca: 'Justificar erros nao os apaga.'\n");
            printw("'Mas ao menos voce tenta entender. Isso e algo.'\n");
            estado->pontosCompaixao += 1;  // +1 por tentar

        } else {
            // SILENCIO
            printw("\nVoce fica em silencio, refletindo sobre seu erro.\n");
            printw("Elfa: 'O silencio tambem e resposta.'\n");
            printw("'Voce reflete. Isso e sabio.'\n");
            estado->pontosCompaixao += 2;  // +2 por reflexao
        }

        printw("\nElfa: 'Meu nome e Glacify. Ja fui guerreira.'\n");
        printw("'Conheci um paladino chamado Damian...'\n");
        printw("'Ele me ensinou que errar nao e o fim.'\n");
        printw("'Espero que sua jornada termine melhor que a dele.'\n");

    // ===== ESCOLHA 2: CONVERSAR =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce se aproxima respeitosamente da elfa.\n");
        printw("Ela abre os olhos lentamente.\n");
        printw("O vento balanca seus cabelos prateados.\n");
        printw("Ela te cumprimenta com um aceno.\n\n");
        printw("Elfa: 'Ola, viajante. O que te traz aqui?'\n");
        printw("Voce conta sobre sua missao.\n\n");
        pausar();

        printw("Ela suspira: 'Animata... conheci ela.'\n");
        printw("'Eramos parte do mesmo grupo.'\n");
        printw("'Eu sou Glacify.'\n\n");

        const char *opcoes2[] = {
            "Treinar com ela",
            "Perguntar sobre Damian",
            "Perguntar sobre a espada"
        };
        escolha2 = apresentarMenu("O que voce pergunta?", opcoes2, 3);

        if (escolha2 == 1) {
            // TREINAR
            printw("\nGlacify sorri: 'Faz tempo que nao luto!'\n");
            printw("Voces treinam a tarde toda.\n");
            printw("Ela e incrivelmente rapida e precisa.\n");
            printw("Voce aprende muito com ela.\n");
            printw("Glacify: 'Obrigada. Voce me lembrou porque eu lutava.'\n");
            printw("'Para proteger, nao para destruir.'\n");
            estado->pontosCompaixao += 3;  // +3 por conexao e aprendizado

        } else if (escolha2 == 2) {
            // DAMIAN
            printw("\nGlacify: 'Damian... ele era nosso lider.'\n");
            printw("'Sempre sabia o que dizer.'\n");
            printw("'Ele me ensinou a ter confianca em mim mesma.'\n");
            printw("'Eu tinha medo de errar... de machucar alguem.'\n");
            printw("'Ele disse: Voce ja falha ao nao tentar.'\n");
            printw("'Levei isso comigo.'\n");
            estado->pontosCompaixao += 2;  // +2 por empatia e curiosidade

        } else {
            // ESPADA
            printw("\nGlacify olha para a espada: 'Era de Damian.'\n");
            printw("'Deixei aqui como lembranca... e como teste.'\n");
            printw("'Quem pega sem perguntar, nao e digno.'\n");
            printw("'Voce perguntou. Isso diz muito.'\n");
            estado->pontosCompaixao += 2;  // +2 por respeito
        }

        printw("\nGlacify: 'Va com cuidado. Animata sofre... mas e perigosa.'\n");

    // ===== ESCOLHA 3: CACHOEIRA =====
    } else {
        limparTela();
        printw("\nVoce decide entrar na cachoeira.\n");
        printw("Tira sua armadura e espada.\n");
        printw("A agua e gelada, mas revigorante.\n");
        printw("Voce se sente limpo... internamente.\n\n");
        pausar();

        printw("Ao sair, a elfa esta te observando.\n");
        printw("Ela sorri: 'Poucos escolhem a purificacao.'\n");
        printw("'A maioria escolhe o poder.' (aponta para a espada)\n");
        printw("'Meu nome e Glacify.'\n\n");

        const char *opcoes2[] = {
            "Agradecer a cachoeira (gratidao)",
            "Perguntar se ela cuida do lugar",
            "Meditar com ela"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce agradece em voz alta a cachoeira.\n");
            printw("Glacify: 'Gratidao e uma virtude rara.'\n");
            printw("'Que a floresta te proteja.'\n");
            estado->pontosCompaixao += 2;

        } else if (escolha2 == 2) {
            printw("\nGlacify: 'Sim, cuido. E minha penitencia.'\n");
            printw("'Falhei em proteger alguem importante.'\n");
            printw("'Agora protejo este lugar sagrado.'\n");
            estado->pontosCompaixao += 2;

        } else {
            printw("\nVoce se senta ao lado dela e medita.\n");
            printw("O silencio e confortavel.\n");
            printw("Glacify: 'Presenca e um presente raro.'\n");
            printw("'Obrigada.'\n");
            estado->pontosCompaixao += 3;  // +3 por presenca plena
        }
    }

    pausar();
    printw("\n[COMPAIXAO TOTAL: %d pontos]\n", estado->pontosCompaixao);
    pausar();
}

// ---------- EVENTO 3: NINFA DA FLORESTA ----------

void eventoNinfaFloresta(GameState *estado) {
    limparTela();
    printw("\n=== EVENTO 3: A NINFA DA FLORESTA ===\n\n");

    printw("Ao continuar seu caminho, uma nevoa magica surge.\n");
    printw("Uma figura eterea aparece entre as arvores.\n");
    printw("E uma NINFA - a guardia da floresta.\n\n");
    pausar();

    printw("Ninfa: 'Voce atravessou minha floresta...'\n");
    printw("'Vi como tratou os pequenos e os antigos.'\n");
    printw("'Agora... julgo seu coracao.'\n\n");
    pausar();

    // JULGAMENTO BASEADO NOS PONTOS
    printw("\n--- JULGAMENTO DA FLORESTA ---\n\n");

    if (estado->pontosCompaixao >= 8) {
        // ALTA COMPAIXAO
        printw("Ninfa: 'Seu coracao e puro.'\n");
        printw("'Voce protegeu sem destruir.'\n");
        printw("'Compreendeu sem julgar.'\n");
        printw("'A floresta te ABENCOA!'\n\n");
        printw("Uma luz verde te envolve.\n");
        printw("Voce se sente completamente curado e protegido.\n");
        printw("[BENCAO: Protecao da Natureza - sera util no castelo]\n");
        estado->pontosCompaixao += 5;  // Bonus de 5 pontos

    } else if (estado->pontosCompaixao >= 4) {
        // MEDIA COMPAIXAO
        printw("Ninfa: 'Voce fez o necessario.'\n");
        printw("'Nem heroi, nem vilao.'\n");
        printw("'A floresta te ACEITA.'\n\n");
        printw("Uma brisa suave te envolve.\n");
        printw("Voce se sente parcialmente curado.\n");
        estado->pontosCompaixao += 2;  // Bonus de 2 pontos

    } else {
        // BAIXA COMPAIXAO
        printw("Ninfa: 'Voce deixou dor por onde passou.'\n");
        printw("'Escolheu forca sobre gentileza.'\n");
        printw("'A floresta... LEMBRA.'\n\n");
        printw("Espinhos brotam ao seu redor.\n");
        printw("Voce sente uma marca de desaprovacao.\n");
        printw("[MALDICAO: A natureza nao te ajudara]\n");
        estado->pontosCompaixao += 0;  // Sem bonus
    }

    pausar();
    printw("\n--- FLORESTA COMPLETA ---");
    printw("\nPONTOS DE COMPAIXAO FINAIS: %d\n", estado->pontosCompaixao);
    pausar();
}

// ========================================
//          ROTA 2: PANTANO
// ========================================

void rotaPantano(GameState *estado) {
    exibirAsciiArt(PANTANO);
    pausar();
    limparTela();
    printw("\n=== PANTANO ===\n\n");
    printw("Voce entra no pantano lodoso.\n");
    printw("O cheiro e forte, o terreno e traicoeiro.\n");
    printw("Voce precisa de astucia para sobreviver aqui.\n\n");
    pausar();

    // Tres eventos do pantano
    eventoCelaBruxa(estado);
    eventoLagartoFulzard(estado);
    eventoCobraPantano(estado);

    // Apos completar o pantano, vai para o castelo
    castelo(estado);
}

// ---------- EVENTO 1: CELA E BRUXA ----------

void eventoCelaBruxa(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 1: RUINAS AMALDICOADAS ===\n\n");

    printw("Voce encontra uma construcao antiga em ruinas.\n");
    printw("Parece abandonada, mas algo parece errado...\n");
    printw("Ao entrar, voce ve runas brilhantes no chao.\n\n");
    pausar();

    const char *opcoes1[] = {
        "Investigar as runas (cuidado)",
        "Andar pelas paredes (cautela)",
        "Andar direto pelo centro (confianca)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: INVESTIGAR =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce se abaixa e examina as runas cuidadosamente.\n");
        printw("Sao runas de aprisionamento!\n");
        printw("Voce percebe que e uma ARMADILHA!\n\n");

        const char *opcoes2[] = {
            "Contornar as runas (astucia)",
            "Tentar desarmar (arriscado)",
            "Pisar sabendo o risco (confianca)"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            // CONTORNAR
            printw("\nVoce contorna as runas com cuidado!\n");
            printw("Consegue passar sem ativar a armadilha!\n");
            estado->pontosAstucia += 3;  // +3 por astucia maxima
            printw("Mais a frente, voce encontra uma bruxa ferida.\n");

        } else if (escolha2 == 2) {
            // DESARMAR
            printw("\nVoce tenta desarmar a magia...\n");
            printw("As runas piscam... e SE ATIVAM!\n");
            printw("Voce e preso em uma CELA MAGICA!\n");
            estado->pontosAstucia += 1;  // +1 por tentar
            printw("Depois de um tempo, uma bruxa aparece e te liberta.\n");

        } else {
            // PISAR
            printw("\nVoce pisa nas runas sabendo o risco.\n");
            printw("A armadilha SE ATIVA!\n");
            printw("Voce e preso em uma CELA MAGICA!\n");
            estado->pontosAstucia += 0;  // 0 pontos - imprudente
            printw("Depois de um tempo, uma bruxa aparece e te liberta.\n");
        }

    // ===== ESCOLHA 2: PAREDES =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce decide andar pelas paredes, evitando o centro.\n");
        printw("Uma pedra solta cede sob seu pe!\n");
        printw("OUTRA ARMADILHA!\n\n");

        const char *opcoes2[] = {
            "Rolar para frente (agilidade)",
            "Se proteger com o braco (defesa)",
            "Correr (panico)"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce rola rapido para frente!\n");
            printw("Evita a maioria da armadilha!\n");
            estado->pontosAstucia += 2;  // +2 por reflexo
            printw("Mas tropeça em outra armadilha... e e preso!\n");
            printw("Uma bruxa aparece e te liberta.\n");

        } else if (escolha2 == 2) {
            printw("\nVoce levanta o braco para se proteger!\n");
            printw("A armadilha te acerta, mas nao e fatal!\n");
            estado->pontosAstucia += 1;  // +1 por defesa
            printw("Voce cai em uma rede e fica preso.\n");
            printw("Uma bruxa aparece e te liberta.\n");

        } else {
            printw("\nVoce corre em panico!\n");
            printw("Pisa em TODAS as armadilhas!\n");
            estado->pontosAstucia += 0;  // 0 pontos - panico
            printw("Voce e preso em uma cela magica.\n");
            printw("Uma bruxa aparece e te liberta.\n");
        }

    // ===== ESCOLHA 3: DIRETO =====
    } else {
        limparTela();
        printw("\nVoce anda direto pelo centro, confiante.\n");
        printw("ERRO! As runas se ativam!\n");
        printw("Voce e preso em uma CELA MAGICA!\n");
        estado->pontosAstucia += 0;  // 0 pontos - sem cautela
        printw("\nDepois de um tempo, uma bruxa aparece e te liberta.\n");
    }

    pausar();

    // CONTINUACAO - BRUXA
    limparTela();
    printw("\n--- ENCONTRO COM A BRUXA ---\n\n");
    printw("Bruxa: 'Desculpe pelas armadilhas... protegem minha casa.'\n");
    printw("'Voce parece saudavel. Preciso de ajuda.'\n");
    printw("'Um SLIME roubou um ingrediente raro meu.'\n");
    printw("'Pode recupera-lo para mim?'\n\n");
    pausar();

    printw("Voces caminham juntos ate encontrar o SLIME.\n");
    printw("Ele esta saltitando, com algo brilhando dentro dele.\n\n");

    const char *opcoes3[] = {
        "Atacar o slime (forca)",
        "Modo furtivo (agilidade)",
        "Interagir com o slime (criatividade)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes3, 3);

    if (escolha1 == 1) {
        // ATACAR
        printw("\nVoce investe com a espada!\n");
        printw("Perfura o slime! Ele se desmancha!\n");
        printw("A pedra voa no ar... voce pega!\n");
        printw("Bruxa: 'Eficiente... mas um pouco brutal.'\n");
        estado->pontosAstucia += 1;  // +1 funcional mas bruto

    } else if (escolha1 == 2) {
        // FURTIVO
        printw("\nVoce se esconde no mato...\n");
        printw("Espera o momento certo...\n");
        printw("PULA em cima do slime!\n");
        printw("Ele se assusta e cospe a pedra!\n");
        printw("Voce pega no ar!\n");
        printw("Bruxa: 'Impressionante! Rapido e esperto!'\n");
        estado->pontosAstucia += 3;  // +3 astucia perfeita

    } else {
        // INTERAGIR
        printw("\nVoce se aproxima devagar do slime...\n");
        printw("Ele para e te olha curioso.\n");
        printw("Voce... comeca a fazer COCEGA nele?!\n");
        printw("O slime TREME e cospe a pedra!\n");
        printw("Ele comeca a te seguir, parecendo feliz!\n");
        printw("Bruxa: 'Incrivel! Nunca vi ninguem fazer amizade com um slime!'\n");
        estado->pontosAstucia += 4;  // +4 criatividade maxima
    }

    pausar();

    printw("\n--- DE VOLTA NA CASA DA BRUXA ---\n\n");
    printw("Bruxa joga a pedra no caldeirao.\n");
    printw("Ela prepara uma pocao e toma um pouco.\n");
    printw("Sua postura melhora, suas feridas curam!\n\n");
    printw("Ela enche dois frascos e te da um.\n");
    printw("Bruxa: 'Obrigada, aventureiro. Tome, vai precisar.'\n");
    printw("Voce bebe a pocao e se sente revigorado!\n\n");

    pausar();
    printw("\n[ASTUCIA TOTAL: %d pontos]\n", estado->pontosAstucia);
    pausar();
}

// ---------- EVENTO 2: LAGARTO FULZARD ----------

void eventoLagartoFulzard(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 2: O GUERREIRO LAGARTO ===\n\n");

    printw("Continuando pelo pantano, voce ve uma figura estranha.\n");
    printw("Um LAGARTO HUMANOIDE esta sentado em uma pedra.\n");
    printw("Ele olha para o horizonte, parecendo distraido.\n\n");
    pausar();

    const char *opcoes1[] = {
        "Cumprimentar alto (chamar atencao)",
        "Aproximar em silencio (respeito)",
        "Observar a distancia (cautela)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: CUMPRIMENTAR ALTO =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce: 'Ola! Bom dia!'\n");
        printw("O lagarto se assusta e cai da pedra!\n");
        printw("Lagarto: 'AH! Voce me assustou!'\n");
        printw("Ele se levanta rindo: 'Eu me distraio facil...'\n\n");
        pausar();

        printw("Lagarto: 'Meu nome e Fulzard. Quem e voce?'\n");
        printw("Voce conta sobre sua missao.\n");
        printw("Fulzard: 'Animata? Conheci ela...'\n");
        printw("'Quero te testar. Topas?'\n\n");

        printw("Teste: Acertar 3 alvos sem se distrair.\n");
        const char *opcoes2[] = {
            "Aceitar focado (determinacao)",
            "Aceitar mas conversar durante (casual)",
            "Recusar educadamente"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce foca completamente na tarefa.\n");
            printw("Fulzard faz barulhos para distrair, mas voce ignora.\n");
            printw("ACERTA os 3 alvos!\n");
            printw("Fulzard: 'Impressionante! Voce tem FOCO.'\n");
            printw("'Damian me ensinou isso... voce me lembra ele.'\n");
            estado->pontosAstucia += 3;  // +3 foco total

        } else if (escolha2 == 2) {
            printw("\nVoce tenta atirar enquanto conversa.\n");
            printw("Acerta 2 alvos, erra 1.\n");
            printw("Fulzard: 'Quase! Mas se distrair pode custar caro.'\n");
            estado->pontosAstucia += 2;  // +2 esforco

        } else {
            printw("\nVoce: 'Prefiro nao, obrigado.'\n");
            printw("Fulzard: 'Sem problemas! Cada um tem seu jeito.'\n");
            estado->pontosAstucia += 1;  // +1 por honestidade
        }

    // ===== ESCOLHA 2: SILENCIO =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce se aproxima em silencio, respeitoso.\n");
        printw("O lagarto vira e sorri: 'Voce e bom... eu era pessimo nisso.'\n");
        printw("Lagarto: 'Meu nome e Fulzard.'\n\n");
        pausar();

        printw("Fulzard: 'Conheci um paladino chamado Damian.'\n");
        printw("'Ele me ensinou a ter FOCO... a me importar.'\n");
        printw("'Antes, eu era distraido, nao ligava pra nada.'\n");
        printw("'Ele me mostrou que se importar dói... mas vale a pena.'\n\n");

        const char *opcoes2[] = {
            "Perguntar mais sobre Damian",
            "Perguntar por que ele esta aqui",
            "Apenas ouvir em silencio"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nFulzard: 'Ele era nosso lider... e amigo.'\n");
            printw("'Quando ele morreu, eu perdi o foco de novo.'\n");
            printw("'Agora tento honrar o que ele me ensinou.'\n");
            estado->pontosAstucia += 2;  // +2 empatia

        } else if (escolha2 == 2) {
            printw("\nFulzard: 'Estou aqui guardando memorias.'\n");
            printw("'Este pantano... lutamos aqui uma vez.'\n");
            printw("'Eu me distraí e quase morri.'\n");
            printw("'Damian me salvou. Nunca esqueci.'\n");
            estado->pontosAstucia += 2;  // +2 curiosidade

        } else {
            printw("\nVoce apenas escuta, respeitoso.\n");
            printw("Fulzard sorri: 'Obrigado por ouvir.'\n");
            printw("'Faz tempo que nao falo sobre isso.'\n");
            estado->pontosAstucia += 3;  // +3 presenca
        }

    // ===== ESCOLHA 3: OBSERVAR =====
    } else {
        limparTela();
        printw("\nVoce observa de longe.\n");
        printw("O lagarto vira: 'Sei que esta ai. Pode vir.'\n");
        printw("Ele sorri: 'Paranoia e boa. Eu tinha pouca.'\n");
        printw("Lagarto: 'Meu nome e Fulzard.'\n\n");
        pausar();

        printw("Fulzard: 'Quer cacar comigo?'\n");
        printw("'Tem uma presa por aqui.'\n\n");

        const char *opcoes2[] = {
            "Aceitar liderar (confianca)",
            "Deixar ele liderar (humildade)",
            "Cacar cada um de um lado"
        };
        escolha2 = apresentarMenu("O que voce decide?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce lidera a cacada.\n");
            printw("Fulzard te segue com atencao.\n");
            printw("Voces capturam a presa com sucesso!\n");
            printw("Fulzard: 'Voce e um bom lider!'\n");
            estado->pontosAstucia += 3;  // +3 lideranca

        } else if (escolha2 == 2) {
            printw("\nVoce deixa Fulzard liderar.\n");
            printw("Ele fica surpreso: 'Serio? Obrigado!'\n");
            printw("Ele lidera bem, focado.\n");
            printw("Fulzard: 'Fazia tempo que nao confiavam em mim.'\n");
            estado->pontosAstucia += 3;  // +3 confianca

        } else {
            printw("\nVoces se separam.\n");
            printw("Voce perde a presa por falta de coordenacao.\n");
            printw("Fulzard: 'Sozinho e mais dificil, ne?'\n");
            estado->pontosAstucia += 1;  // +1 independencia
        }
    }

    pausar();

    printw("\n--- DESPEDIDA ---\n\n");
    printw("Fulzard: 'Voce vai bem. Continue focado.'\n");
    printw("'Animata sofre... mas cuidado. Dor pode ser perigosa.'\n");
    printw("'Damian me ensinou que se importar doi...'\n");
    printw("'Mas o amor que se sente e superior a isso.'\n");
    printw("'Boa sorte, aventureiro.'\n\n");

    pausar();
    printw("\n[ASTUCIA TOTAL: %d pontos]\n", estado->pontosAstucia);
    pausar();
}

// ---------- EVENTO 3: COBRA DO PANTANO ----------

void eventoCobraPantano(GameState *estado) {
    limparTela();
    printw("\n=== EVENTO 3: A COBRA GUARDIA ===\n\n");

    printw("Ao chegar perto da saida do pantano...\n");
    printw("A agua se agita violentamente!\n");
    printw("Uma COBRA GIGANTE emerge!\n");
    printw("Seus olhos brilham com inteligencia antiga.\n\n");
    pausar();

    printw("Cobra: 'Sssss... voce atravesssou meu pantano...'\n");
    printw("'Vi ssssuas escolhasss...'\n");
    printw("'Agora... julgo ssssua assstucia.'\n\n");
    pausar();

    // JULGAMENTO BASEADO NOS PONTOS
    printw("\n--- JULGAMENTO DO PANTANO ---\n\n");

    if (estado->pontosAstucia >= 10) {
        // ALTA ASTUCIA
        printw("Cobra: 'Voce nao e pressssa... e cacador como eu.'\n");
        printw("'Pensssa antesss de agir.'\n");
        printw("'Usssa a mente, nao apenasss musculosss.'\n");
        printw("'Aceito voce como IGUAL!'\n\n");
        printw("A cobra te da uma ESCAMA VENENOSA.\n");
        printw("Cobra: 'Ussse contra a bruxa... pode ajudar.'\n");
        printw("[ITEM OBTIDO: Veneno Antigo - util contra Animata]\n");
        estado->pontosAstucia += 5;  // Bonus de 5

    } else if (estado->pontosAstucia >= 5) {
        // MEDIA ASTUCIA
        printw("Cobra: 'Voce ssobrevive... por inssstinto ou ssorte?'\n");
        printw("'Tanto faz. Passsou.'\n\n");
        printw("A cobra te da ESCAMAS PROTETORAS.\n");
        printw("[ITEM: Escamas - defesa aumentada]\n");
        estado->pontosAstucia += 2;  // Bonus de 2

    } else {
        // BAIXA ASTUCIA
        printw("Cobra: 'Voce tropeca em galhos propriosss...'\n");
        printw("'Nao pensa... apenasss age.'\n");
        printw("'Cuidado... ou ssera devorado.'\n\n");
        printw("A cobra te morde de leve - um AVISO.\n");
        printw("[MALDICAO: Reflexos lentos]\n");
        estado->pontosAstucia += 0;
    }

    pausar();
    printw("\n--- PANTANO COMPLETO ---");
    printw("\nPONTOS DE ASTUCIA FINAIS: %d\n", estado->pontosAstucia);
    pausar();
}

// ========================================
//          ROTA 3: CAVERNA
// ========================================

void rotaCaverna(GameState *estado) {
    exibirAsciiArt(CAVERNA);
    pausar();
    limparTela();
    printw("\n=== CAVERNA ===\n\n");
    printw("Voce entra na caverna escura.\n");
    printw("Tochas antigas iluminam as paredes de pedra.\n");
    printw("Aqui, a verdade sera revelada.\n\n");
    pausar();

    // Tres eventos da caverna
    eventoDragaoFilhote(estado);
    eventoAnaoEgnar(estado);
    eventoDrakeAnciao(estado);

    // Apos completar a caverna, vai para o castelo
    castelo(estado);
}

// ---------- EVENTO 1: DRAGAO FILHOTE ----------

void eventoDragaoFilhote(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 1: DRAGAO FAMINTO ===\n\n");

    printw("Voce ouve GRITOS ecoando na caverna!\n");
    printw("Voce corre em direcao ao som...\n\n");
    printw("Um DRAGAO FILHOTE esta perseguindo um COMERCIANTE ANAO!\n");
    printw("Comerciante: 'SOCORRO! ME AJUDA!'\n");
    printw("O dragao rosna... mas voce nota:\n");
    printw("Ele esta MUITO magro. Costelas aparecendo.\n");
    printw("O estomago do dragao RONCA alto.\n\n");
    pausar();

    const char *opcoes1[] = {
        "Atacar o dragao (proteger humano)",
        "Pegar pedra e distrair (neutralidade)",
        "Interagir/Acalmar (sabedoria)"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: ATACAR =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce desembanha sua espada e corre em direcao ao dragao filhote!\n");
        printw("Espantado, o dragao filhote solta fogo, mas nao e muito forte.\n");
        printw("O fogo te empurra, mas nao o suficiente para voce desistir.\n");
        printw("Voce se queima um pouco, porem continua na sua investida.\n");
        printw("Voce pula, atacando e dando um golpe certeiro!\n");
        printw("O dragao cai derrotado...\n\n");
        pausar();

        estado->dragaoFilhoteMorto = 1;  // Marca que matou o dragao

        const char *opcoes2[] = {
            "Verificar o dragao (reflexao)",
            "Consolar o comerciante",
            "Pegar escama do dragao"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce se aproxima do corpo...\n");
            printw("Era apenas um FILHOTE. Com fome.\n");
            printw("Voce sente um peso na consciencia.\n");
            estado->pontosSabedoria += 1;  // +1 por reflexao

        } else if (escolha2 == 2) {
            printw("\nComercian: 'Obrigado! Voce me salvou!'\n");
            printw("Ele te da um MINERIO DE MITHRIL BRUTO.\n");
            printw("'Pegue, e valioso!'\n");
            estado->temMithril = 1;  // Ganha o mithril
            estado->pontosSabedoria += 0;  // 0 - nao refletiu

        } else {
            printw("\nVoce friamente coleta uma escama do dragao.\n");
            printw("Comerciante te olha com desaprovacao.\n");
            estado->pontosSabedoria += 0;  // 0 - frieza
        }

    // ===== ESCOLHA 2: DISTRAIR =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce pega uma pedra e arremessa longe!\n");
        printw("O dragao vai atras da pedra, distraido.\n");
        printw("O comerciante foge rapidamente.\n\n");
        printw("Voce se aproxima do dragao...\n");
        printw("Ele esta MUITO magro. Tremendo de fome.\n\n");
        pausar();

        const char *opcoes2[] = {
            "Dar comida da mochila",
            "Procurar a mae dele",
            "Sair e deixar ele"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce joga carne seca da mochila.\n");
            printw("O dragao devora e ronrona como um gatinho!\n");
            printw("Ele lambe sua mao, agradecido.\n");
            printw("Ele te segue um pouco, depois volta para a caverna.\n");
            estado->dragaoFilhoteSalvo = 1;  // Marca que salvou
            estado->pontosSabedoria += 3;  // +3 empatia
            printw("\nO comerciante aparece: 'Voce... tem um bom coracao.'\n");
            printw("Ele te da MINERIO DE MITHRIL.\n");
            estado->temMithril = 1;

        } else if (escolha2 == 2) {
            printw("\nVoce procura pegadas... e acha algo terrivel.\n");
            printw("Um esqueleto GIGANTE de dragao!\n");
            printw("Era a mae dele... morta ha tempos.\n");
            printw("O filhote chora ao ver.\n");
            printw("Voce pode:\n");
            printw("  - Deixa-lo la (duro)\n");
            printw("  - Enterrar a mae com ele (empatia)\n");
            printw("Voce escolhe enterrar.\n");
            printw("O dragao te olha grato e desaparece nas sombras.\n");
            estado->dragaoFilhoteSalvo = 1;
            estado->pontosSabedoria += 4;  // +4 maxima empatia

        } else {
            printw("\nVoce vai embora.\n");
            printw("Ouve o dragao chorando atras de voce.\n");
            estado->pontosSabedoria += 0;  // 0 - frieza
        }

    // ===== ESCOLHA 3: ACALMAR =====
    } else {
        limparTela();
        printw("\nVoce levanta as maos e fala calmamente.\n");
        printw("'Calma... calma, pequeno...'\n");
        printw("O dragao para, confuso.\n");
        printw("Voce nota: ele esta morrendo de fome!\n\n");
        printw("Voce fala para o comerciante: 'Ele nao e agressivo! Esta faminto!'\n");
        printw("Comerciante: 'E-e dai?! Ele quase me matou!'\n\n");
        pausar();

        const char *opcoes2[] = {
            "Pedir comida ao comerciante",
            "Oferecer sua propria comida",
            "Mediar a situacao"
        };
        escolha2 = apresentarMenu("O que voce faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce: 'Voce tem comida? Podemos ajuda-lo!'\n");
            printw("Comerciante hesita... mas concorda.\n");
            printw("Juntos, alimentam o dragao.\n");
            printw("Dragao ronrona feliz e vai embora.\n");
            printw("Comerciante: 'Voce me ensinou algo hoje.'\n");
            printw("Ele te da MITHRIL e um MAPA SECRETO.\n");
            estado->temMithril = 1;
            estado->dragaoFilhoteSalvo = 1;
            estado->pontosSabedoria += 4;  // +4 diplomacia perfeita

        } else if (escolha2 == 2) {
            printw("\nVoce oferece SUA comida ao dragao.\n");
            printw("Ele devora, grato, e lambe sua mao.\n");
            printw("Comerciante se sente mal: 'Eu... tenho algo pra voce.'\n");
            printw("Ele te da MITHRIL e suprimentos extras.\n");
            estado->temMithril = 1;
            estado->dragaoFilhoteSalvo = 1;
            estado->pontosSabedoria += 5;  // +5 sacrificio proprio

        } else {
            printw("\nVoce: 'Olha, ele tem fome. Voce tem recursos.'\n");
            printw("'Nao precisa haver violencia.'\n");
            printw("Comerciante pensa... 'Voce tem razao.'\n");
            printw("Voces alimentam o dragao juntos.\n");
            printw("Comerciante: 'Voce e sabio. Pegue isto.'\n");
            printw("Ele te da MITHRIL e um MAPA com atalho secreto.\n");
            estado->temMithril = 1;
            estado->dragaoFilhoteSalvo = 1;
            estado->pontosSabedoria += 5;  // +5 sabedoria maxima
        }

        printw("\nO dragao te olha com gratidao e some na floresta.\n");
        printw("Voce sente que ele nao te esquecera...\n");
    }

    pausar();
    printw("\n[SABEDORIA TOTAL: %d pontos]\n", estado->pontosSabedoria);
    pausar();
}

// ---------- EVENTO 2: ANAO EGNAR ----------

void eventoAnaoEgnar(GameState *estado) {
    int escolha1, escolha2;

    limparTela();
    printw("\n=== EVENTO 2: O FERREIRO FANTASMA ===\n\n");

    printw("Mais fundo na caverna, voce ouve sons de FORJA.\n");
    printw("Marteladas ritmicas ecoam...\n\n");
    printw("Voce encontra um ANAO FANTASMAGORICO.\n");
    printw("Ele forja em uma bigorna espectral.\n");
    printw("Fogo azul ilumina seu rosto concentrado.\n\n");
    pausar();

    const char *opcoes1[] = {
        "Perguntar o que ele forja",
        "Oferecer ajuda",
        "Observar em silencio"
    };
    escolha1 = apresentarMenu("O que voce faz?", opcoes1, 3);

    // ===== ESCOLHA 1: PERGUNTAR =====
    if (escolha1 == 1) {
        limparTela();
        printw("\nVoce: 'O que voce forja?'\n");
        printw("Anao para e te olha: 'Forjo proposito... ou forjava.'\n");
        printw("'Meu nome e Egnar.'\n\n");
        printw("'Conheci um paladino chamado Damian.'\n");
        printw("'Ele me deu razao para existir.'\n");
        printw("'Antes... eu era vazio.'\n\n");
        pausar();

        if (estado->temMithril == 1) {
            printw("Voce: 'Tenho mithril. Pode fazer algo?'\n");
            printw("Egnar sorri: 'Mithril... ha quanto tempo!'\n\n");

            const char *opcoes2[] = {
                "Melhorar espada",
                "Melhorar armadura",
                "Fazer amuleto de protecao"
            };
            escolha2 = apresentarMenu("O que voce quer?", opcoes2, 3);

            if (escolha2 == 1) {
                printw("\nEgnar forja sua espada com o mithril.\n");
                printw("Ela brilha com poder!\n");
                printw("[ESPADA MELHORADA - mais dano]\n");
                estado->pontosSabedoria += 2;

            } else if (escolha2 == 2) {
                printw("\nEgnar reforça sua armadura com mithril.\n");
                printw("Voce se sente mais protegido!\n");
                printw("[ARMADURA MELHORADA - mais defesa]\n");
                estado->pontosSabedoria += 2;

            } else {
                printw("\nEgnar forja um amuleto de protecao.\n");
                printw("'Isso te protegera de magias sombrias.'\n");
                printw("[AMULETO OBTIDO - protecao magica]\n");
                estado->pontosSabedoria += 3;  // +3 escolha estrategica
            }

        } else {
            printw("Egnar: 'Se tivesse mithril, poderia te ajudar...'\n");
            printw("'Mas obrigado por conversar.'\n");
            estado->pontosSabedoria += 1;
        }

    // ===== ESCOLHA 2: OFERECER AJUDA =====
    } else if (escolha1 == 2) {
        limparTela();
        printw("\nVoce: 'Posso ajudar em algo?'\n");
        printw("Anao para, surpreso: 'Ajuda...?'\n");
        printw("'Ha anos ninguem oferece isso...'\n");
        printw("'Meu nome e Egnar.'\n\n");
        pausar();

        printw("Egnar: 'Preciso de minerio especifico.'\n");
        printw("'Esta no lago subterraneo ou na caverna escura.'\n\n");

        const char *opcoes2[] = {
            "Caverna escura (mais perigoso)",
            "Lago subterraneo (mais seguro)",
            "Oferecer o que voce tem"
        };
        escolha2 = apresentarMenu("Onde voce vai?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce vai ate a caverna escura.\n");
            printw("Morcegos gigantes atacam!\n");
            printw("Voce luta e consegue o minerio raro!\n");
            printw("Egnar: 'Voce tem coragem! Obrigado!'\n");
            estado->pontosSabedoria += 3;  // +3 coragem

        } else if (escolha2 == 2) {
            printw("\nVoce vai ao lago subterraneo.\n");
            printw("E lindo, cristalino, com minerio no fundo.\n");
            printw("Voce mergulha e pega o minerio.\n");
            printw("Egnar: 'Obrigado por sua ajuda!'\n");
            estado->pontosSabedoria += 2;  // +2 exploracao

        } else {
            if (estado->temMithril == 1) {
                printw("\nVoce oferece o mithril que tem!\n");
                printw("Egnar fica emocionado: 'Voce... sacrifica isso por mim?'\n");
                printw("'Damian fazia isso... obrigado.'\n");
                printw("Ele forja algo especial para voce!\n");
                printw("[ITEM LENDARIO - forjado com gratidao]\n");
                estado->pontosSabedoria += 5;  // +5 sacrificio
                estado->temMithril = 0;  // Perdeu o mithril mas ganhou algo melhor
            } else {
                printw("\nVoce nao tem nada util...\n");
                printw("Egnar: 'Tudo bem, a intencao conta.'\n");
                estado->pontosSabedoria += 1;
            }
        }

    // ===== ESCOLHA 3: OBSERVAR =====
    } else {
        limparTela();
        printw("\nVoce apenas observa em silencio.\n");
        printw("O anao trabalha concentrado...\n");
        printw("Ele para e olha pra voce.\n\n");
        printw("Anao: 'Damian fazia isso... observava meu trabalho.'\n");
        printw("'Meu nome e Egnar.'\n\n");
        pausar();

        printw("Egnar: 'Posso te perguntar algo?'\n\n");

        const char *opcoes2[] = {
            "'Por que voce luta?'",
            "'O que voce protege?'",
            "'Voce tem medo?'"
        };
        escolha2 = apresentarMenu("Qual pergunta ele faz?", opcoes2, 3);

        if (escolha2 == 1) {
            printw("\nVoce reflete e responde honestamente.\n");
            printw("Egnar: 'Proposito... e tudo.'\n");
            printw("'Damian me deu o meu.'\n");
            printw("'Espero que voce encontre o seu.'\n");
            estado->pontosSabedoria += 3;  // +3 reflexao profunda

        } else if (escolha2 == 2) {
            printw("\nVoce fala sobre quem/o que protege.\n");
            printw("Egnar: 'Proteger e nobre.'\n");
            printw("'Mas nao esqueca de se proteger tambem.'\n");
            estado->pontosSabedoria += 3;  // +3 valores claros

        } else {
            printw("\nVoce: 'Sim, tenho medo.'\n");
            printw("Egnar sorri: 'Honestidade. Isso e raro.'\n");
            printw("'Damian tinha medo... mas nunca mostrava.'\n");
            printw("'Talvez por isso se foi cedo demais.'\n");
            estado->pontosSabedoria += 4;  // +4 honestidade brutal
        }
    }

    pausar();

    printw("\n--- DESPEDIDA ---\n\n");
    printw("Egnar: 'Damian me deu proposito. Mas percebi tarde...'\n");
    printw("'O proposito nao e servir. E VIVER.'\n");
    printw("'Nao cometa o erro dele... viva por voce tambem.'\n\n");

    pausar();
    printw("\n[SABEDORIA TOTAL: %d pontos]\n", estado->pontosSabedoria);
    pausar();
}

// ---------- EVENTO 3: DRAKE ANCIAO ----------

void eventoDrakeAnciao(GameState *estado) {
    limparTela();
    printw("\n=== EVENTO 3: O DRAKE ANCIAO ===\n\n");

    printw("Ao chegar na saida da caverna...\n");
    printw("Um RUGIDO ATERRADOR ecoa!\n");
    printw("Um DRAGAO IMENSO bloqueia a passagem!\n");
    printw("Ele tem cicatrizes antigas e olhar penetrante.\n\n");
    pausar();

    printw("Drake: 'VOCE... carrega o cheiro DELE.'\n");
    printw("'Do traidor de sangue. Do filho que matou a mae.'\n\n");
    printw("Voce: 'Do que voce esta falando?!'\n\n");
    pausar();

    printw("Drake: 'DAMIAN... o heroi.'\n");
    printw("'Ele matou minha irma. Ela o procurou a vida toda.'\n");
    printw("'Ele foi criado por humanos. Nunca soube que era dragonato.'\n");
    printw("'Quando matou a mae... descobriu tarde demais.'\n");
    printw("'Ela veio ate o castelo... e o grupo de herois a MATOU.'\n\n");
    pausar();

    printw("Drake: 'O esqueleto dela esta no castelo ate hoje.'\n");
    printw("'E voce vem aqui... para que? Salvar a bruxa que o ama?'\n\n");

    if (estado->dragaoFilhoteMorto == 1) {
        printw("Drake rosna: 'E VOCE MATOU MEU SOBRINHO!'\n");
        printw("'O filhote que encontrou... era filho da minha irma!'\n");
        printw("'Voce e IGUAL A ELES! DESTRUIDOR!'\n\n");
        printw("Drake te ataca!\n");
        printw("A luta e brutal... mas voce sobrevive.\n");
        printw("Drake: 'Va... mas a natureza nunca te perdoara.'\n");
        estado->pontosSabedoria += 0;  // 0 - consequencia pesada

    } else if (estado->dragaoFilhoteSalvo == 1) {
        printw("Drake para... e CHEIRA voce.\n");
        printw("Drake: 'Voce... salvou meu sobrinho.'\n");
        printw("'O filhote que encontrou era filho da minha irma.'\n");
        printw("'Voce o alimentou... o protegeu.'\n\n");
        printw("Uma lagrima cai do olho do drake.\n");
        printw("Drake: 'Voce nao e como eles. Voce ESCUTA.'\n\n");

        printw("Ele te da uma ESCAMA DOURADA.\n");
        printw("Drake: 'Esta era da minha irma. Pegue.'\n");
        printw("'Use no castelo... pode trazer paz.'\n");
        estado->temEscamaDragao = 1;  // Item especial para final alternativo
        estado->pontosSabedoria += 10;  // +10 recompensa maxima

    } else {
        printw("Drake: 'Voce nao o matou... mas tambem nao o salvou.'\n");
        printw("'Indiferenca... as vezes e pior que crueldade.'\n");
        printw("'Va. Mas saiba: a bruxa nao sabe a verdade.'\n");
        printw("'Talvez deva contar a ela.'\n");
        estado->pontosSabedoria += 2;  // +2 neutro
    }

    pausar();
    printw("\n--- CAVERNA COMPLETA ---");
    printw("\nPONTOS DE SABEDORIA FINAIS: %d\n", estado->pontosSabedoria);
    pausar();
}

// ========================================
//          CASTELO - EVENTOS FINAIS
// ========================================

void castelo(GameState *estado) {
    exibirAsciiArt(CASTELO);
    pausar();
    limparTela();
    printw("\n=====================================\n");
    printw("         CHEGADA AO CASTELO\n");
    printw("=====================================\n\n");

    printw("Apos sua jornada pelo %s...\n", estado->rotaEscolhida);
    printw("Voce finalmente avista o castelo no horizonte.\n");
    printw("E sombrio, envolto em nevoa magica.\n");
    printw("As portas estao fechadas.\n\n");
    pausar();

    // Quatro eventos finais
    eventoGargulaCharadas(estado);
    eventoArmadurasDancarinas(estado);
    eventoMimicoDiario(estado);
    confrontoFinalAnimata(estado);
}

// ---------- EVENTO 1: GARGULA ----------

void eventoGargulaCharadas(GameState *estado) {
    int resposta;
    int acertos = 0;

    limparTela();
    printw("\n=== A GARGULA DAS CHARADAS ===\n\n");

    printw("Ao se aproximar do portao...\n");
    printw("Uma GARGULA DE PEDRA ganha vida!\n");
    printw("Seus olhos brilham em vermelho.\n\n");
    pausar();

    printw("Gargula: 'TRES PERGUNTAS. TRES VERDADES.'\n");
    printw("'ERRE... E VIRE PEDRA COMO EU.'\n\n");
    pausar();

    // CHARADA 1 - COMPAIXAO
    const char *opcoes1[] = {
        "Para ser heroi (ego)",
        "Porque era certo (moralidade)",
        "Porque senti sua dor (empatia)"
    };
    resposta = apresentarMenu("'Pequena sofre, grande a devora. Voce age. Por que?'", opcoes1, 3);

    if (resposta == 3) {
        printw("\nGargula: 'CORRETO. Empatia move o coracao.'\n");
        acertos++;
    } else {
        printw("\nGargula: 'ERRADO. Mas continua...'\n");
    }
    pausar();

    // CHARADA 2 - ASTUCIA
    const char *opcoes2[] = {
        "Desarmar a armadilha (logica)",
        "Enfrentar a sombra (coragem)",
        "Mergulhar na agua (instinto)"
    };
    resposta = apresentarMenu("'Armadilha a frente, sombra atras, agua embaixo. Qual caminho?'", opcoes2, 3);

    if (resposta == 1) {
        printw("\nGargula: 'CORRETO. Pensar e melhor que agir.'\n");
        acertos++;
    } else {
        printw("\nGargula: 'ERRADO. Mas continua...'\n");
    }
    pausar();

    // CHARADA 3 - SABEDoria
    const char *opcoes3[] = {
        "Louca (julgamento)",
        "Perdida (empatia)",
        "Ma (condenacao)"
    };
    resposta = apresentarMenu("'Alguem ama tanto que rouba ate Deus. Ela e...?'", opcoes3, 3);

    if (resposta == 2) {
        printw("\nGargula: 'CORRETO. Amor distorcido ainda e amor.'\n");
        acertos++;
    } else {
        printw("\nGargula: 'ERRADO.'\n");
    }
    pausar();

    // RESULTADO
    limparTela();
    printw("\n--- RESULTADO ---\n");
    printw("Acertos: %d de 3\n\n", acertos);

    if (acertos == 3) {
        printw("Gargula: 'DIGNO. Salve-a... ou condene-a.'\n");
        printw("O portao se abre completamente.\n");
        // Bonus nos pontos da rota escolhida
        if (strcmp(estado->rotaEscolhida, "Floresta") == 0) estado->pontosCompaixao += 3;
        else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) estado->pontosAstucia += 3;
        else estado->pontosSabedoria += 3;

    } else if (acertos == 2) {
        printw("Gargula: 'QUASE. Talvez baste.'\n");
        printw("O portao range e se abre lentamente.\n");

    } else {
        printw("Voce comeca a PETRIFICAR!\n");
        printw("Seus pes viram pedra...\n\n");
        printw("De repente, o portao se ABRE sozinho!\n");
        printw("A petrificacao para.\n");
        printw("Gargula: 'Ela ainda quer visitantes... que pena para voce.'\n");
    }

    pausar();
}

// ---------- EVENTO 2: ARMADURAS DANCARINAS ----------

void eventoArmadurasDancarinas(GameState *estado) {
    int escolha;

    limparTela();
    printw("\n=== SALAO DAS ARMADURAS ===\n\n");

    printw("Voce entra em um salao de festas abandonado.\n");
    printw("Lustres cobertos de teias, mesa com comida podre.\n");
    printw("De repente... 7 ARMADURAS comecam a se mover!\n");
    printw("Elas dançam em sincronia, como nobres fantasmas.\n\n");
    pausar();

    const char *opcoes[] = {
        "Lutar contra todas (forca)",
        "Dancar com elas (criatividade)",
        "Procurar a fonte da magia (inteligencia)"
    };
    escolha = apresentarMenu("O que voce faz?", opcoes, 3);

    if (escolha == 1) {
        // LUTAR
        limparTela();
        printw("\nVoce ataca as armaduras!\n");
        printw("Elas revidam, mas sao velhas e lentas.\n");
        printw("Voce as derrota uma por uma.\n");
        printw("Ao destruir a ultima, ela cai... e uma voz sussurra:\n");
        printw("'Forcasempre escolhe forca...'\n\n");
        printw("Voce ve uma armadura caida no fundo, segurando uma CHAVE.\n");

    } else if (escolha == 2) {
        // DANCAR
        limparTela();
        printw("\nVoce guarda a espada... e comeca a DANCAR!\n");
        printw("As armaduras param, surpresas.\n");
        printw("Voce imita seus movimentos.\n");
        printw("Elas... APLAUDEM!\n");
        printw("(Sao fantasmas de nobres que morreram aqui)\n\n");
        printw("Elas apontam para uma armadura caida no fundo.\n");
        printw("Uma voz feminina sussurra: 'Obrigada... ha muito nao dancavamos.'\n\n");
        printw("Voce pega a CHAVE da armadura caida.\n");
        // Bonus de criatividade
        if (strcmp(estado->rotaEscolhida, "Floresta") == 0) estado->pontosCompaixao += 2;
        else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) estado->pontosAstucia += 2;
        else estado->pontosSabedoria += 2;

    } else {
        // PROCURAR MAGIA
        limparTela();
        printw("\nVoce ignora as armaduras e procura a fonte da magia.\n");
        printw("Voce encontra um CRISTAL no lustre!\n");

        const char *opcoes2[] = {
            "Quebrar o cristal",
            "Deixar intacto"
        };
        escolha = apresentarMenu("Voce pode quebra-lo ou deixa-lo.", opcoes2, 2);

        if (escolha == 1) {
            printw("\nVoce quebra o cristal!\n");
            printw("As armaduras CAEM, sem vida.\n");
            printw("Silencio total...\n");
            printw("Voce pega a CHAVE da armadura caida.\n");
        } else {
            printw("\nVoce deixa o cristal intacto.\n");
            printw("As armaduras te guiam ate a armadura caida.\n");
            printw("Uma voz sussurra: 'Obrigada por nos deixar existir...'\n");
            printw("Voce pega a CHAVE.\n");
            // Bonus de empatia
            if (strcmp(estado->rotaEscolhida, "Floresta") == 0) estado->pontosCompaixao += 2;
            else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) estado->pontosAstucia += 2;
            else estado->pontosSabedoria += 2;
        }
    }

    pausar();
    printw("\n[CHAVE OBTIDA - Acesso a Sala do Tesouro]\n");
    pausar();
}

// ---------- EVENTO 3: MIMICO E DIARIO ----------

void eventoMimicoDiario(GameState *estado) {
    int escolha;

    limparTela();
    printw("\n=== SALA DO TESOURO ===\n\n");

    printw("Voce abre a porta com a chave.\n");
    printw("Uma sala cheia de BAUS dourados!\n");
    printw("De repente, um deles... ABRE A BOCA!\n");
    printw("E um MIMICO!\n\n");
    pausar();

    printw("Mimico: 'Espera! Nao vou te atacar!'\n");
    printw("'Estou cansado disso... so quero conversar.'\n");
    printw("'Tenho algo que voce quer... um DIARIO.'\n\n");

    const char *opcoes[] = {
        "Desconfiar (cautela)",
        "Aceitar conversar (abertura)",
        "Oferecer algo primeiro (bondade)"
    };
    escolha = apresentarMenu("O que voce faz?", opcoes, 3);

    if (escolha == 1) {
        // DESCONFIAR
        printw("\nVoce: 'Mimicos nao falam... o que voce quer?'\n");
        printw("Mimico: 'Esperto. Mas olha, nao quero lutar.'\n");
        printw("'A bruxa me pediu para guardar um diario.'\n");
        printw("'Posso te dar... em troca de algo.'\n\n");
        printw("Voce oferece comida da mochila.\n");
        printw("Mimico: 'Obrigado... ha anos nao como.'\n");
        printw("Ele te entrega o DIARIO.\n");

    } else if (escolha == 2) {
        // CONVERSAR
        printw("\nVoce: 'Tudo bem, vamos conversar.'\n");
        printw("Mimico: 'Serio?! Ninguem nunca...'\n");
        printw("Ele chora (mimicos tem sentimentos!).\n");
        printw("Mimico: 'A bruxa me pediu pra guardar um diario.'\n");
        printw("'Ela disse que era importante... sobre os herois.'\n");
        printw("'Voce parece bom. Pegue.'\n");
        printw("Ele te entrega o DIARIO gratuitamente.\n");
        // Bonus de empatia
        if (strcmp(estado->rotaEscolhida, "Floresta") == 0) estado->pontosCompaixao += 2;
        else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) estado->pontosAstucia += 2;
        else estado->pontosSabedoria += 2;

    } else {
        // OFERECER
        printw("\nVoce: 'Tenho algo para voce.'\n");
        printw("Voce oferece comida da mochila.\n");
        printw("Mimico: 'Voce... nao vai me atacar?'\n");
        printw("Ele CHORA copiosamente.\n");
        printw("Mimico: 'Obrigado... obrigado...'\n");
        printw("Ele te entrega o DIARIO e um TESOURO extra.\n");
        printw("[BONUS: Item raro obtido!]\n");
        // Bonus maximo
        if (strcmp(estado->rotaEscolhida, "Floresta") == 0) estado->pontosCompaixao += 3;
        else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) estado->pontosAstucia += 3;
        else estado->pontosSabedoria += 3;
    }

    pausar();
    limparTela();

    // LEITURA DO DIARIO
    printw("\n========================================\n");
    printw("           DIARIO DOS HEROIS\n");
    printw("       Compilado por Animata\n");
    printw("========================================\n\n");
    pausar();

    printw("--- Entrada de Egnar (Anao Ferreiro) ---\n\n");
    printw("'Damian me deu proposito. Antes, eu apenas existia.'\n");
    printw("'Forjar para ele... tinha significado.'\n");
    printw("'Mas quando ele se foi, eu continuei forjando...'\n");
    printw("'Por que? Porque aprendi que o proposito e viver.'\n");
    printw("'Nao importa para quem, mas viver tem valor.'\n\n");
    pausar();

    printw("--- Entrada de Glacify (Elfa Negra) ---\n\n");
    printw("'Eu tinha medo de tudo. De errar, de machucar, de falhar.'\n");
    printw("'Damian me disse: Voce ja falhou ao nao tentar.'\n");
    printw("'Na ultima batalha, eu tentei. Falhei. Ele morreu.'\n");
    printw("'Mas nao me arrependo de ter tentado.'\n");
    printw("'Ele sorriu para mim no final.'\n\n");
    pausar();

    printw("--- Entrada de Fulzard (Lagarto Guerreiro) ---\n\n");
    printw("'Nunca liguei pra nada. Para que? Doi.'\n");
    printw("'Damian me obrigou a ligar. Odiei ele por isso.'\n");
    printw("'Depois amei. Depois sofri quando ele partiu.'\n");
    printw("'Mas eu nao trocaria. A dor prova que eu vivi.'\n");
    printw("'A dor prova que eu amei.'\n\n");
    pausar();

    printw("--- Entrada sobre Damian (por Animata) ---\n\n");
    printw("'Ele sempre ajudou. Nunca pediu ajuda.'\n");
    printw("'Eu perguntei: Por que voce se sacrificou?'\n");
    printw("'Ele nao respondeu. Apenas sorriu.'\n");
    printw("'Eu acho que... ele estava cansado.'\n");
    printw("'Cansado de ser o forte. O sabio. O heroi.'\n");
    printw("'Ele queria descansar. Mas EU nao deixei.'\n\n");
    pausar();

    printw("--- Entrada OCULTA (pagina rasgada) ---\n\n");
    printw("'Eu matei minha mae.'\n");
    printw("'Eu nao sabia. Mas isso importa?'\n");
    printw("'Ela veio me procurar. Anos procurando.'\n");
    printw("'E eu... eu a matei.'\n");
    printw("'Suas ultimas palavras: Meu filho... finalmente.'\n");
    printw("'Como eu vivo com isso?'\n\n");
    pausar();

    printw("--- Ultima entrada de Animata ---\n\n");
    printw("'Roubei o amuleto. Tentei revive-lo.'\n");
    printw("'Nao funcionou. Ele nao voltou.'\n");
    printw("'Talvez... ele nao QUEIRA voltar.'\n");
    printw("'Talvez eu seja egoista.'\n");
    printw("'Talvez eu o ame tanto que o prendi aqui.'\n");
    printw("'Se alguem ler isso... pare-me.'\n");
    printw("'Ou me deixe com ele para sempre.'\n\n");
    pausar();

    printw("========================================\n");
    printw("         FIM DO DIARIO\n");
    printw("========================================\n\n");

    printw("Voce fecha o diario, entendendo tudo agora...\n");
    pausar();
}

// ---------- CONFRONTO FINAL ----------

void confrontoFinalAnimata(GameState *estado) {
    int escolhaFinal;

    limparTela();
    printw("\n========================================\n");
    printw("         SALAO DO TRONO\n");
    printw("========================================\n\n");

    printw("Voce abre a ultima porta...\n");
    printw("O salao e imenso, sombrio.\n\n");
    printw("No centro: um ESQUELETO GIGANTE de dragao.\n");
    printw("Ao lado: ANIMATA, abraçada ao amuleto.\n");
    printw("Ao redor: os fantasmas de Egnar, Glacify e Fulzard, presos.\n\n");
    pausar();

    printw("Animata levanta a cabeca: 'Voce veio... como todos pedem.'\n");
    printw("'Salve-nos, heroi. Sempre a mesma historia.'\n");
    printw("Ela ri amargamente.\n\n");
    pausar();

    printw("Os fantasmas falam:\n");
    printw("Egnar: 'Deixe-nos ir, Animata... por favor.'\n");
    printw("Glacify: 'Voce nao esta errando por tentar... esta errando por nao parar.'\n");
    printw("Fulzard: 'Doi, eu sei. Mas prender a gente doi mais.'\n\n");
    pausar();

    printw("Animata: 'CALEM-SE! Voces nao entendem!'\n");
    printw("'Sem ele, sem VOCES... eu nao sou nada!'\n\n");
    pausar();

    // ESCOLHA FINAL
    const char *opcoes[] = {
        "Combater Animata (forca)",
        "Conversar com ela (empatia)",
        "Usar a Escama do Dragao (se tiver)"
    };
    escolhaFinal = apresentarMenu("O que voce faz?", opcoes, 3);

    if (escolhaFinal == 1) {
        // FINAL A: COMBATE
        limparTela();
        printw("\n=== FINAL: LIBERTACAO FORCADA ===\n\n");
        printw("Voce desembanha sua espada.\n");
        printw("Animata: 'Entao e isso? Violencia? Igual a todos?'\n\n");
        printw("Voce a derrota em combate magico intenso.\n");
        printw("O amuleto se QUEBRA.\n");
        printw("Os fantasmas sao libertos... mas Animata cai, chorando.\n\n");
        pausar();

        printw("Animata: 'Voce salvou todos... exceto eu...'\n");
        printw("Ela desaparece nas sombras, sozinha e amarga.\n\n");
        printw("Kenshi: 'O amuleto foi destruido... mas a que custo?'\n");
        printw("'As vezes, a forca nao e a resposta.'\n\n");

    } else if (escolhaFinal == 2) {
        // FINAL B: CONVERSA
        limparTela();
        printw("\n=== FINAL: REDENCAO ===\n\n");
        printw("Voce guarda sua espada.\n");
        printw("Voce: 'Posso entender voce?'\n");
        printw("Animata para, surpresa: 'Voce... nao vai me atacar?'\n\n");
        pausar();

        printw("Voce: 'Li o diario. Voce o amava.'\n");
        printw("Animata chora: 'Eu... eu ajudei a matar a mae dele...'\n");
        printw("Voce: 'Voce nao sabia. Ele tambem nao.'\n\n");
        pausar();

        // Calcula se teve boas escolhas
        int pontosTotal = estado->pontosCompaixao + estado->pontosAstucia + estado->pontosSabedoria;

        if (pontosTotal >= 20) {
            // FINAL B1 - REDENCAO COMPLETA
            printw("Voce: 'Voce pode deixa-los ir. Ainda ha tempo.'\n");
            printw("Animata chora copiosamente.\n");
            printw("Ela abraca o amuleto uma ultima vez...\n");
            printw("E o LIBERTA.\n\n");
            pausar();

            printw("Os fantasmas a abraçam antes de partir.\n");
            printw("Damian aparece por ultimo: 'Obrigado... por tudo.'\n");
            printw("Animata: 'Me perdoa?'\n");
            printw("Damian: 'Sempre perdoei. Agora perdoe-se.'\n\n");
            printw("Todos partem em paz.\n");
            printw("Animata vive, se torna guardia do castelo.\n");
            printw("'Vou honrar a memoria deles... do jeito certo.'\n\n");

        } else {
            // FINAL B2 - ACEITACAO PARCIAL
            printw("Voce: 'Deixe-os ir... por favor.'\n");
            printw("Animata: 'Eu... ainda nao estou pronta...'\n");
            printw("Ela liberta Egnar, Glacify e Fulzard.\n");
            printw("Mas mantem Damian um pouco mais.\n\n");
            printw("Damian: 'Tudo bem... estarei aqui ate voce estiver pronta.'\n");
            printw("Nao e perfeito... mas e um começo.\n\n");
        }

    } else if (escolhaFinal == 3 && estado->temEscamaDragao == 1) {
        // FINAL C - ESCAMA DO DRAGAO (FINAL SECRETO)
        limparTela();
        printw("\n=== FINAL SECRETO: PAZ COMPLETA ===\n\n");
        printw("Voce: 'Tenho algo para voce.'\n");
        printw("Voce mostra a ESCAMA DOURADA.\n");
        printw("Animata: 'Isso e... da dragoa?'\n\n");
        pausar();

        printw("Voce: 'Drake me deu. Era da mae de Damian.'\n");
        printw("Animata pega a escama, tremendo.\n\n");
        printw("Voce coloca a escama no esqueleto do dragao.\n");
        printw("MAGIA ACONTECE!\n\n");
        pausar();

        printw("O esqueleto BRILHA!\n");
        printw("Uma forma espectral aparece: a DRAGOA ANCIA!\n\n");
        printw("Dragoa: 'Voce ama meu filho.'\n");
        printw("Animata chora: 'Eu... eu ajudei a matar voce!'\n");
        printw("Dragoa: 'Eu sei. Mas voce tambem o amou quando ninguem mais conseguia.'\n\n");
        pausar();

        printw("A dragoa toca o amuleto.\n");
        printw("Ele se TRANSFORMA!\n");
        printw("Nao e mais prisao... e MEMORIA.\n\n");
        printw("Os fantasmas sao libertos, mas suas lembrancas permanecem.\n");
        printw("Damian aparece e abraça a mae e Animata.\n");
        printw("Todos partem juntos, em paz.\n\n");
        pausar();

        printw("Animata fica com o amuleto transformado.\n");
        printw("Ela se torna Guardia da Memoria.\n");
        printw("'Vou proteger o legado deles... nao suas almas.'\n\n");

        if (estado->dragaoFilhoteSalvo == 1) {
            printw("De repente... o DRAGAO FILHOTE aparece, agora ADULTO!\n");
            printw("Ele cresceu rapido e lembrou de voce!\n");
            printw("Dragao: 'Voce me salvou... agora protegerei esta guardia.'\n");
            printw("Ele fica com Animata.\n");
            printw("'Ele e tudo que restou da mae de Damian. Vou protege-lo.'\n\n");
        }

        printw("O esqueleto e enterrado com honras.\n");
        printw("A paz finalmente reina.\n\n");

    } else {
        // Caso escolha 3 mas nao tenha a escama
        printw("\nVoce nao tem a Escama do Dragao...\n");
        printw("Voltando as opcoes anteriores.\n");
        pausar();
        confrontoFinalAnimata(estado);  // Chama de novo
        return;
    }

    pausar();
    calcularRanking(estado);  // Vai para o ranking final
}

// ========== RANKING FINAL ==========

void calcularRanking(GameState *estado) {
    int pontosTotal = estado->pontosCompaixao + estado->pontosAstucia + estado->pontosSabedoria;

    limparTela();
    printw("\n========================================\n");
    printw("           RANKING FINAL\n");
    printw("========================================\n\n");

    printw("--- PONTUACAO ---\n");
    printw("Compaixao: %d pontos\n", estado->pontosCompaixao);
    printw("Astucia: %d pontos\n", estado->pontosAstucia);
    printw("Sabedoria: %d pontos\n", estado->pontosSabedoria);
    printw("\nTOTAL: %d pontos\n\n", pontosTotal);
    pausar();

    // RANKING BASEADO NOS PONTOS
    printw("\n--- SEU RANK ---\n\n");

    if (pontosTotal >= 40) {
        printw("****************************************\n");
        printw("     RANK S - HEROI LENDARIO\n");
        printw("****************************************\n\n");
        printw("Voce nao apenas completou a missao.\n");
        printw("Voce trouxe PAZ, JUSTICA e REDENCAO.\n");
        printw("Sua jornada sera contada por geracoes.\n");
        printw("Pessoas nao falam apenas de suas vitorias...\n");
        printw("Mas de seu CORACAO.\n\n");

    } else if (pontosTotal >= 30) {
        printw("****************************************\n");
        printw("     RANK A - HEROI VERDADEIRO\n");
        printw("****************************************\n\n");
        printw("Voce fez escolhas dificeis com sabedoria.\n");
        printw("Nem sempre perfeito, mas sempre tentando.\n");
        printw("Voce salvou vidas e almas.\n");
        printw("O reino te agradece.\n\n");

    } else if (pontosTotal >= 20) {
        printw("****************************************\n");
        printw("     RANK B - AVENTUREIRO CAPAZ\n");
        printw("****************************************\n\n");
        printw("Voce completou a missao.\n");
        printw("Nem heroi, nem vilao. Apenas humano.\n");
        printw("Suas escolhas foram praticas.\n");
        printw("Fez o necessario.\n\n");

    } else if (pontosTotal >= 10) {
        printw("****************************************\n");
        printw("     RANK C - SOBREVIVENTE\n");
        printw("****************************************\n\n");
        printw("Voce sobreviveu... mas a que custo?\n");
        printw("Muitas escolhas dificeis.\n");
        printw("Talvez pudesse ter feito melhor.\n");
        printw("Mas voce chegou ate o fim.\n\n");

    } else {
        printw("****************************************\n");
        printw("     RANK D - CAMINHO SOMBRIO\n");
        printw("****************************************\n\n");
        printw("Voce completou a missao... tecnicamente.\n");
        printw("Mas deixou muita dor pelo caminho.\n");
        printw("A violencia foi sua primeira escolha.\n");
        printw("Talvez precise refletir sobre suas acoes.\n\n");
    }

    pausar();

    // MENSAGEM ESPECIAL POR ROTA
    printw("\n--- MENSAGEM DA SUA ROTA ---\n\n");

    if (strcmp(estado->rotaEscolhida, "Floresta") == 0) {
        if (estado->pontosCompaixao >= 15) {
            printw("A Ninfa da Floresta sorri:\n");
            printw("'Voce provou que a compaixao nao e fraqueza.'\n");
            printw("'E a maior forca que existe.'\n");
        } else {
            printw("A Ninfa da Floresta suspira:\n");
            printw("'Voce passou pela floresta, mas nao aprendeu com ela.'\n");
            printw("'A natureza perdoa... mas nao esquece.'\n");
        }

    } else if (strcmp(estado->rotaEscolhida, "Pantano") == 0) {
        if (estado->pontosAstucia >= 15) {
            printw("A Cobra do Pantano assobia:\n");
            printw("'Voce e cacador, nao pressssa.'\n");
            printw("'Pensssa antes de agir. Isso e ssssabedoria.'\n");
        } else {
            printw("A Cobra do Pantano balanca a cabeca:\n");
            printw("'Voce tropecou em muitas armadilhas.'\n");
            printw("'No pantano, quem nao pensa... afunda.'\n");
        }

    } else {
        if (estado->pontosSabedoria >= 15) {
            printw("O Drake Anciao te olha com respeito:\n");
            printw("'Voce nao e como os outros.'\n");
            printw("'Voce ESCUTA. Voce APRENDE.'\n");
            printw("'Isso e verdadeira sabedoria.'\n");
        } else {
            printw("O Drake Anciao franze o rosto:\n");
            printw("'Voce tem forca... mas falta sabedoria.'\n");
            printw("'Forcasem sabedoria e destruicao.'\n");
        }
    }

    pausar();

    // EPILOGO
    printw("\n========================================\n");
    printw("              EPILOGO\n");
    printw("========================================\n\n");

    printw("Voce retorna a vila.\n");
    printw("Kenshi te abraca, chorando de alivio.\n");
    printw("'Voce conseguiu... obrigado.'\n\n");

    if (pontosTotal >= 30) {
        printw("A vila celebra seu retorno com uma festa.\n");
        printw("Criancas correm ate voce pedindo para ouvir suas historias.\n");
        printw("Voce se tornou LENDA.\n\n");
    } else if (pontosTotal >= 15) {
        printw("A vila comemora discretamente.\n");
        printw("Voce fez o que era necessario.\n");
        printw("Nao e heroi... mas fez a diferenca.\n\n");
    } else {
        printw("A vila recebe voce em silencio.\n");
        printw("A missao foi cumprida... mas algo parece vazio.\n");
        printw("Voce olha para tras... e sente que perdeu algo.\n\n");
    }

    printw("========================================\n");
    printw("            FIM DO JOGO\n");
    printw("========================================\n\n");
    printw("Obrigado por jogar!\n");
    printw("Sua jornada termina aqui... ou comeca?\n\n");

    pausar();
}