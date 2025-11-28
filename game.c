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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== VARIAVEIS GLOBAIS ==========

// Pontuacao por virtude
int pontosCompaixao = 0;    // Floresta
int pontosAstúcia = 0;      // Pantano (escrevi sem acento pra nao dar erro)
int pontosSabedoria = 0;    // Caverna

// Controle de itens importantes (0 = nao tem, 1 = tem)
int temMithril = 0;
int temEscamaDragao = 0;
int dragaoFilhoteSalvo = 0;
int dragaoFilhoteMorto = 0;

// Controle da rota escolhida
char rotaEscolhida[20];

// ========== FUNCOES AUXILIARES ==========

// Limpa a tela (funciona em Windows e Linux)
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Pausa o jogo ate o jogador apertar ENTER
void pausar() {
    printf("\n\nPressione ENTER para continuar...");
    while(getchar() != '\n');  // Limpa o buffer
    getchar();                 // Espera o ENTER
}

// Mostra os pontos atuais (para debug, pode comentar depois)
void mostrarPontos() {
    printf("\n[DEBUG - Pontos Atuais]");
    printf("\nCompaixao: %d | Astucia: %d | Sabedoria: %d\n", 
           pontosCompaixao, pontosAstúcia, pontosSabedoria);
}

// ========== DECLARACAO DAS FUNCOES ==========
// (Declarar antes para o compilador saber que existem)

void menu();
void introducao();
void escolhaRota();

// Floresta
void rotaFloresta();
void eventoGoblinFada();
void eventoElfaGlacify();
void eventoNinfaFloresta();

// Pantano
void rotaPantano();
void eventoCelaBruxa();
void eventoLagartoFulzard();
void eventoCobraPantano();

// Caverna
void rotaCaverna();
void eventoDragaoFilhote();
void eventoAnaoEgnar();
void eventoDrakeAnciao();

// Castelo
void castelo();
void eventoGargulaCharadas();
void eventoArmadurasDancarinas();
void eventoMimicoDiario();
void confrontoFinalAnimata();

// Finais
void calcularRanking();

// ========== FUNCAO PRINCIPAL ==========

int main() {
    menu();
    return 0;
}

// ========== MENU INICIAL ==========

void menu() {
    int escolha;
    
    limparTela();
    printf("=====================================\n");
    printf("  A BUSCA DO AMULETO SAGRADO\n");
    printf("=====================================\n\n");
    
    printf("1 - Iniciar Jogo\n");
    printf("2 - Sobre o Jogo\n");
    printf("3 - Sair\n\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    
    if (escolha == 1) {
        introducao();
    } else if (escolha == 2) {
        limparTela();
        printf("\n=== SOBRE O JOGO ===\n\n");
        printf("Um RPG de escolhas onde suas decisoes importam.\n");
        printf("Tres caminhos, tres virtudes, multiplos finais.\n");
        printf("Descubra a verdade sobre os herois do passado.\n\n");
        pausar();
        menu();
    } else {
        printf("\nObrigado por jogar!\n");
        exit(0);
    }
}

// ========== INTRODUCAO ==========

void introducao() {
    limparTela();
    printf("\n=== INTRODUCAO ===\n\n");
    
    printf("Ao acordar, voce sai da sua casa e avista o anciao da vila.\n");
    printf("Ele se chama Kenshi, e parece preocupado.\n\n");
    pausar();
    
    printf("Kenshi: \"Preciso da sua ajuda, jovem aventureiro.\"\n");
    printf("\"Ha um tempo atras, havia uma maga renomada chamada Animata.\"\n");
    printf("\"Ela fazia parte de um grupo de herois lendarios.\"\n\n");
    pausar();
    
    printf("\"Eles protegiam nosso reino... ate que algo terrivel aconteceu.\"\n");
    printf("\"O lider deles, Damian, morreu em batalha.\"\n");
    printf("\"Animata enlouqueceu de dor e roubou o amuleto sagrado.\"\n");
    printf("\"Agora, enfurecida, ela se trancou no castelo junto ao amuleto, e ataca quem ousar se aproximar.\"\n\n");
    pausar();
    
    printf("\"Preciso que voce recupere o amuleto e... talvez... salve ela.\"\n\n");
    printf("Kenshi te entrega uma mochila com suprimentos e uma espada.\n");
    printf("Ele enxuga as lagrimas: \"Se cuide... Estou contando com voce.\"\n\n");
    pausar();
    
    escolhaRota();
}

// ========== ESCOLHA DA ROTA ==========

void escolhaRota() {
    int escolha;
    
    limparTela();
    printf("\n=== ESCOLHA SEU CAMINHO ===\n\n");
    
    printf("Kenshi: \"Ha tres caminhos para o castelo.\"\n\n");
    
    printf("1 - FLORESTA\n");
    printf("   'O caminho da vida e da harmonia.'\n");
    printf("   'Aqui, a COMPAIXAO eh testada.'\n\n");
    
    printf("2 - PANTANO\n");
    printf("   'O caminho dos desafios e das armadilhas.'\n");
    printf("   'Aqui, a ASTUCIA eh testada.'\n\n");
    
    printf("3 - CAVERNA\n");
    printf("   'O caminho do conhecimento e da verdade.'\n");
    printf("   'Aqui, a SABEDORIA eh testada.'\n\n");
    
    printf("Sua escolha: ");
    scanf("%d", &escolha);
    
    // Salva a rota escolhida
    if (escolha == 1) {
        strcpy(rotaEscolhida, "Floresta");
        rotaFloresta();
    } else if (escolha == 2) {
        strcpy(rotaEscolhida, "Pantano");
        rotaPantano();
    } else if (escolha == 3) {
        strcpy(rotaEscolhida, "Caverna");
        rotaCaverna();
    } else {
        printf("\nEscolha invalida! Indo pela Floresta...\n");
        pausar();
        strcpy(rotaEscolhida, "Floresta");
        rotaFloresta();
    }
}

// ========================================
//          ROTA 1: FLORESTA
// ========================================

void rotaFloresta() {
    limparTela();
    printf("\n=== FLORESTA ===\n\n");
    printf("Voce entra na floresta densa.\n");
    printf("A luz do sol reflete sobre as folhas criando um ambiente magico.\n");
    printf("Voce sente paz... mas tambem tendo constante atencao aos arredores.\n\n");
    printf("Apesar da calmaria... Voce sabe que a floresta eh traicoeira.\n\n");
    pausar();
    
    // Tres eventos da floresta
    eventoGoblinFada();
    eventoElfaGlacify();
    eventoNinfaFloresta();
    
    // Apos completar a floresta, vai para o castelo
    castelo();
}

// ---------- EVENTO 1: GOBLIN E FADA ----------

void eventoGoblinFada() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 1: ENCONTRO NA FLORESTA ===\n\n");
    
    printf("Voce avista uma iluminacao estranha por de trás do arbusto.\n");
    printf("Ao se aproximar, ouve grunidos.\n");
    printf("Voce se esconde atras de uma arvore e observa:\n\n");
    printf("Um GOBLIN esta tentando comer uma FADA!\n");
    printf("A fada suplica por ajuda!\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Atacar o goblin (violencia direta)\n");
    printf("2 - Procurar algo ao redor (preparacao)\n");
    printf("3 - Interagir com o goblin (comunicacao)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: ATACAR =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce pega sua espada e avanca!\n");
        printf("O goblin se assusta e solta a fada!\n");
        printf("Voce o persegue e...\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Deixar ele fugir (misericordia)\n");
        printf("2 - Correr atras e atacar (justica)\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce deixa o goblin fugir assustado.\n");
            printf("A fada agradece: 'Obrigada por nao matar ele!'\n");
            printf("Ela o abencoa e voce se sente revigorado.\n");
            pontosCompaixao += 2;  // +2 pontos por misericordia
        } else {
            printf("\nVoce persegue e derrota o goblin.\n");
            printf("A fada agradece, mas parece triste: 'Ele era apenas um bebe...'\n");
            pontosCompaixao += 0;  // 0 pontos - violencia desnecessaria
        }
        
    // ===== ESCOLHA 2: PROCURAR AO REDOR =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce procura ao redor cuidadosamente...\n");
        printf("Voce encontra:\n\n");
        
        printf("1 - Pedras no chao\n");
        printf("2 - Cristal brilhante\n");
        printf("3 - Frutas vermelhas\n");
        printf("O que voce pega? ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            // PEDRAS
            printf("\nVoce pega uma pedra e arremessa no goblin!\n");
            printf("Acerta! Ele solta a fada e foge.\n");
            printf("A fada agradece e te abencoa.\n");
            pontosCompaixao += 1;  // +1 ponto - resolveu sem matar
            
        } else if (escolha2 == 2) {
            // CRISTAL
            printf("\nVoce pega o cristal brilhante e o mostra!\n");
            printf("O goblin esquece a fada e corre atras do cristal!\n");
            printf("Ele pega o cristal e sai pulando feliz.\n");
            printf("A fada ri: 'Goblins adoram coisas brilhantes!'\n");
            printf("Ela gira alegremente em sua volta e te abencoa.\n");
            pontosCompaixao += 3;  // +3 pontos - solucao criativa e pacifica
            
        } else {
            // FRUTAS
            printf("\nVoce pega as frutas e joga para o goblin!\n");
            printf("Ele pega as frutas e comeca a comer feliz.\n");
            printf("Ele solta a fada e te agradece!\n");
            printf("A fada: 'Ele so estava com fome! Obrigada por entender!'\n");
            printf("Ela te abencoa com po magico.\n");
            pontosCompaixao += 3;  // +3 pontos - empatia maxima
        }
        
    // ===== ESCOLHA 3: INTERAGIR =====
    } else if (escolha1 == 3) {
        limparTela();
        printf("\nVoce se aproxima com as maos levantadas.\n");
        printf("O goblin te ve e fica na defensiva, segurando a fada.\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Gritar com ele (intimidacao)\n");
        printf("2 - Fazer mimica (comunicacao)\n");
        printf("3 - Dar comida da mochila (empatia)\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            // GRITAR
            printf("\nVoce grita alto!\n");
            printf("O goblin se assusta muito e comeca a correr!\n");
            printf("Ele deixa a fada cair no caminho.\n");
            printf("A fada agradece, um pouco abalada pelo susto.\n");
            pontosCompaixao += 1;  // +1 ponto - funcionou mas foi agressivo
            
        } else if (escolha2 == 2) {
            // MIMICA
            printf("\nVoce comeca a fazer mimica!\n");
            printf("Voce aponta para a fada, depois para o ceu.\n");
            printf("Voce faz cara de triste, depois de feliz.\n");
            printf("O goblin te olha confuso...\n");
            printf("De repente ele entende e ri muito!\n");
            printf("Ele solta a fada, ainda rindo, e vai embora feliz.\n");
            printf("A fada: 'Voce e muito engracado! E gentil!'\n");
            pontosCompaixao += 3;  // +3 pontos - criatividade e empatia
            
        } else {
            // DAR COMIDA
            printf("\nVoce pega carne seca da mochila e oferece.\n");
            printf("O goblin cheira... e seus olhos brilham!\n");
            printf("Ele solta a fada e pega a comida.\n");
            printf("Ele come feliz e te segue um pouco, agradecido.\n");
            printf("A fada: 'Ele so tinha fome! Voce tem um bom coracao!'\n");
            pontosCompaixao += 4;  // +4 pontos - maxima empatia (sacrificou comida)
        }
    }
    
    pausar();
    printf("\n[COMPAIXAO: +%d pontos neste evento]\n", pontosCompaixao);
    pausar();
}

// ---------- EVENTO 2: ELFA GLACIFY ----------

void eventoElfaGlacify() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 2: RIO E CACHOEIRA ===\n\n");
    
    printf("Voce continua pela floresta ate encontrar um rio cristalino.\n");
    printf("Seguindo o rio, voce chega a uma bela cachoeira.\n\n");
    printf("Do lado direito, uma ELFA NEGRA medita em posicao de lotus.\n");
    printf("Do lado esquerdo, uma ESPADA LONGA esta cravada no chao.\n");
    printf("A correnteza desagua fortemente no centro da cachoeira.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Pegar a espada (acao impulsiva)\n");
    printf("2 - Conversar com a elfa (respeito)\n");
    printf("3 - Entrar na cachoeira (purificacao)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: PEGAR ESPADA =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce se aproxima da espada.\n");
        printf("E linda, antiga, coberta de vinhas.\n");
        printf("Voce puxa... e ela sai facilmente!\n");
        printf("Um brilho azul emana dela!\n");
        printf("Voce se sente como um heroi escolhido!\n\n");
        printf("De repente... tudo ao seu redor CONGELA!\n");
        printf("Voce esta preso em gelo!\n\n");
        pausar();
        
        printf("A elfa abre os olhos e se aproxima.\n");
        printf("Ela pega a espada de suas maos congeladas.\n");
        printf("Com um gesto, o gelo derrete.\n\n");
        printf("Elfa: 'Por que pegou sem permissao?'\n\n");
        
        printf("O que voce responde?\n");
        printf("1 - Pedir desculpas humildemente\n");
        printf("2 - Se justificar\n");
        printf("3 - Ficar em silencio\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            // DESCULPAS
            printf("\nVoce: 'Me perdoe, agi por impulso. Foi errado.'\n");
            printf("Elfa sorri: 'Poucos admitem erros. Isso e compaixao por si mesmo.'\n");
            printf("'Admitir os erros eh o primeiro passo para evolucao.'\n");
            pontosCompaixao += 2;  // +2 por humildade
            
        } else if (escolha2 == 2) {
            // JUSTIFICAR
            printf("\nVoce: 'Pensei que era uma espada perdida...'\n");
            printf("Elfa balanca a cabeca: 'Justificar erros nao os apaga.'\n");
            printf("'Mas ao menos voce tenta compreender. Isso e algo.'\n");
            pontosCompaixao += 1;  // +1 por tentar
            
        } else {
            // SILENCIO
            printf("\nVoce fica em silencio, refletindo sobre seu erro.\n");
            printf("Elfa: 'O silencio tambem e resposta.'\n");
            printf("'Voce reflete. Isso e sabio.'\n");
            pontosCompaixao += 2;  // +2 por reflexao
        }
        
        printf("\nElfa: 'Meu nome e Glacify. Ja fui guerreira.'\n");
        printf("'Conheci um paladino chamado Damian...'\n");
        printf("'Ele me ensinou que errar nao e o fim.'\n");
        printf("'Espero que sua jornada termine melhor que a dele.'\n");
        
    // ===== ESCOLHA 2: CONVERSAR =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce se aproxima respeitosamente da elfa.\n");
        printf("Ela abre os olhos lentamente.\n");
        printf("O vento balanca seus cabelos prateados.\n");
        printf("Ela te cumprimenta com um aceno.\n\n");
        printf("Elfa: 'Ola, viajante. O que te traz aqui?'\n");
        printf("Voce conta sobre sua missao.\n\n");
        pausar();
        
        printf("Ela suspira: 'Animata... conheci ela.'\n");
        printf("'Eramos parte do mesmo grupo.'\n");
        printf("'Eu sou Glacify.'\n\n");
        
        printf("O que voce pergunta?\n");
        printf("1 - Treinar com ela\n");
        printf("2 - Perguntar sobre Damian\n");
        printf("3 - Perguntar sobre a espada\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            // TREINAR
            printf("\nGlacify sorri: 'Faz tempo que nao luto!'\n");
            printf("Voces treinam a tarde toda.\n");
            printf("Ela e incrivelmente rapida e precisa.\n");
            printf("Voce aprende muito com ela.\n");
            printf("Glacify: 'Obrigada. Voce me lembrou do porque eu lutava.'\n");
            printf("'Para proteger, nao para destruir.'\n");
            pontosCompaixao += 3;  // +3 por conexao e aprendizado
            
        } else if (escolha2 == 2) {
            // DAMIAN
            printf("\nGlacify: 'Damian... ele era nosso lider.'\n");
            printf("'Sempre sabia o que dizer.'\n");
            printf("'Ele me ensinou a ter confianca em mim mesma.'\n");
            printf("'Eu tinha medo de errar... de machucar alguem.'\n");
            printf("'Ele disse: Voce ja falha ao nao tentar.'\n");
            printf("'Levei isso comigo.'\n");
            pontosCompaixao += 2;  // +2 por empatia e curiosidade
            
        } else {
            // ESPADA
            printf("\nGlacify olha para a espada: 'Era de Damian.'\n");
            printf("'Deixei aqui como lembranca... e como teste.'\n");
            printf("'Quem pega sem perguntar, nao e digno.'\n");
            printf("'Voce perguntou. Isso diz muito.'\n");
            pontosCompaixao += 2;  // +2 por respeito
        }
        
        printf("\nGlacify: 'Va com cuidado. Animata sofre... mas eh perigosa.'\n");
        
    // ===== ESCOLHA 3: CACHOEIRA =====
    } else {
        limparTela();
        printf("\nVoce decide entrar na cachoeira.\n");
        printf("Tira sua armadura e espada.\n");
        printf("A agua eh gelada, mas revigorante.\n");
        printf("Voce se sente purificado... internamente.\n\n");
        pausar();
        
        printf("Ao sair, a elfa esta te observando.\n");
        printf("Ela sorri: 'Poucos escolhem a purificacao.'\n");
        printf("'A maioria escolhe o poder.' (aponta para a espada)\n");
        printf("'Meu nome e Glacify.'\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Agradecer a cachoeira (gratidao)\n");
        printf("2 - Perguntar se ela cuida do lugar\n");
        printf("3 - Meditar com ela\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce agradece em voz alta a cachoeira.\n");
            printf("Glacify: 'Gratidao e uma virtude rara.'\n");
            printf("'Que a floresta te proteja.'\n");
            pontosCompaixao += 2;
            
        } else if (escolha2 == 2) {
            printf("\nGlacify: 'Sim, cuido. Eh minha penitencia.'\n");
            printf("'Falhei em proteger alguem importante.'\n");
            printf("'Agora protejo este lugar sagrado.'\n");
            pontosCompaixao += 2;
            
        } else {
            printf("\nVoce se senta ao lado dela e medita.\n");
            printf("O silencio eh confortavel.\n");
            printf("Glacify: 'Presenca eh um presente raro.'\n");
            printf("'Obrigada.'\n");
            pontosCompaixao += 3;  // +3 por presenca plena
        }
    }
    
    pausar();
    printf("\n[COMPAIXAO TOTAL: %d pontos]\n", pontosCompaixao);
    pausar();
}

// ---------- EVENTO 3: NINFA DA FLORESTA ----------

void eventoNinfaFloresta() {
    limparTela();
    printf("\n=== EVENTO 3: A NINFA DA FLORESTA ===\n\n");
    
    printf("Ao continuar o seu caminho, uma nevoa magica surge.\n");
    printf("Uma figura eterea aparece entre as arvores.\n");
    printf("Eh uma NINFA - a guardia da floresta.\n\n");
    pausar();
    
    printf("Ninfa: 'Voce atravessou minha floresta...'\n");
    printf("'Vi como tratou os pequenos e os antigos.'\n");
    printf("'Agora... julgo seu coracao.'\n\n");
    pausar();
    
    // JULGAMENTO BASEADO NOS PONTOS
    printf("\n--- JULGAMENTO DA FLORESTA ---\n\n");
    
    if (pontosCompaixao >= 8) {
        // ALTA COMPAIXAO
        printf("Ninfa: 'Seu coracao eh puro.'\n");
        printf("'Voce protegeu sem destruir.'\n");
        printf("'Compreendeu sem julgar.'\n");
        printf("'A floresta te ABENCOA!'\n\n");
        printf("Uma luz verde te envolve.\n");
        printf("Voce se sente completamente curado e protegido.\n");
        printf("[BENCAO: Protecao da Natureza - sera util no castelo]\n");
        pontosCompaixao += 5;  // Bonus de 5 pontos
        
    } else if (pontosCompaixao >= 4) {
        // MEDIA COMPAIXAO
        printf("Ninfa: 'Voce fez o necessario.'\n");
        printf("'Nem heroi, nem vilao.'\n");
        printf("'A floresta te ACEITA.'\n\n");
        printf("Uma brisa suave te envolve.\n");
        printf("Voce se sente parcialmente curado.\n");
        pontosCompaixao += 2;  // Bonus de 2 pontos
        
    } else {
        // BAIXA COMPAIXAO
        printf("Ninfa: 'Voce deixou dor por onde passou.'\n");
        printf("'Escolheu forca sobre gentileza.'\n");
        printf("'A floresta... LEMBRA.'\n\n");
        printf("Espinhos brotam ao seu redor.\n");
        printf("Voce sente uma marca de desaprovacao.\n");
        printf("[MALDICAO: A natureza nao te ajudara]\n");
        pontosCompaixao += 0;  // Sem bonus
    }
    
    pausar();
    printf("\n--- FLORESTA COMPLETA ---");
    printf("\nPONTOS DE COMPAIXAO FINAIS: %d\n", pontosCompaixao);
    pausar();
}

// ========================================
//          ROTA 2: PANTANO
// ========================================

void rotaPantano() {
    limparTela();
    printf("\n=== PANTANO ===\n\n");
    printf("Voce entra no pantano lodoso.\n");
    printf("O cheiro eh forte, o terreno eh traicoeiro.\n");
    printf("Voce precisa de astucia e cautela para sobreviver aqui.\n\n");
    pausar();
    
    // Tres eventos do pantano
    eventoCelaBruxa();
    eventoLagartoFulzard();
    eventoCobraPantano();
    
    // Apos completar o pantano, vai para o castelo
    castelo();
}

// ---------- EVENTO 1: CELA E BRUXA ----------

void eventoCelaBruxa() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 1: RUINAS AMALDICOADAS ===\n\n");
    
    printf("Voce encontra um templo antigo em ruinas.\n");
    printf("Parece abandonado, mas algo parece errado...\n");
    printf("Ao entrar, voce ve runas brilhantes no chao.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Investigar as runas (cuidado)\n");
    printf("2 - Andar pelas paredes (cautela)\n");
    printf("3 - Andar direto pelo centro (confianca)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: INVESTIGAR =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce se abaixa e examina as runas cuidadosamente.\n");
        printf("Sao runas de aprisionamento!\n");
        printf("Voce percebe que eh uma ARMADILHA!\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Contornar as runas (astucia e cautela)\n");
        printf("2 - Tentar desarmar (arriscado)\n");
        printf("3 - Pisar sabendo o risco (confianca)\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            // CONTORNAR
            printf("\nVoce contorna as runas com cuidado!\n");
            printf("Consegue passar sem ativar a armadilha!\n");
            pontosAstúcia += 3;  // +3 por astucia e cautela maxima
            printf("Mais a frente, voce encontra uma bruxa ferida.\n");
            
        } else if (escolha2 == 2) {
            // DESARMAR
            printf("\nVoce tenta desarmar a magia...\n");
            printf("As runas piscam... e SE ATIVAM!\n");
            printf("Voce eh preso em uma CELA MAGICA!\n");
            pontosAstúcia += 1;  // +1 por tentar
            printf("Apos um tempo, uma bruxa aparece e te liberta.\n");
            
        } else {
            // PISAR
            printf("\nVoce pisa nas runas sabendo o risco.\n");
            printf("A armadilha SE ATIVA!\n");
            printf("Voce eh preso em uma CELA MAGICA!\n");
            printf("Que tolo de sua parte passar por cima das runas sabendo dos riscos.\n")
            pontosAstúcia += 0;  // 0 pontos - imprudente e tolo
            printf("Apos um tempo, uma bruxa aparece e te liberta.\n");
        }
        
    // ===== ESCOLHA 2: PAREDES =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce decide andar pelas paredes, evitando o centro.\n");
        printf("Uma rocha solta cede sob seu pe!\n");
        printf("OUTRA ARMADILHA!\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Rolar para frente (agilidade)\n");
        printf("2 - Se proteger com o braco (defesa)\n");
        printf("3 - Correr (panico)\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce rola rapido para frente!\n");
            printf("Evita a maioria das armadilhas!\n");
            pontosAstúcia += 2;  // +2 por reflexo
            printf("Mas tropeça em outra armadilha... e eh preso!\n");
            printf("Uma bruxa aparece e te liberta.\n");
            
        } else if (escolha2 == 2) {
            printf("\nVoce levanta o braco para se proteger!\n");
            printf("A armadilha te acerta, mas nao e fatal!\n");
            pontosAstúcia += 1;  // +1 por defesa
            printf("Voce cai em uma rede e fica preso.\n");
            printf("Uma bruxa aparece e te liberta.\n");
            
        } else {
            printf("\nVoce corre em panico!\n");
            printf("Pisa em TODAS as armadilhas!\n");
            pontosAstúcia += 0;  // 0 pontos - panico
            printf("Voce eh preso em uma cela magica.\n");
            printf("Uma bruxa aparece e te liberta.\n");
        }
        
    // ===== ESCOLHA 3: DIRETO =====
    } else {
        limparTela();
        printf("\nVoce anda direto pelo centro, confiante.\n");
        printf("ERRO! As runas se ativam!\n");
        printf("Voce eh preso em uma CELA MAGICA!\n");
        printf("As vezes, a confianca nao eh um dos melhores sentidos nestes momentos.\n")
        printf("Escute mais seus pensamentos inves de suas emocoes em decisoes arriscadas.\n") 
        pontosAstúcia += 0;  // 0 pontos - sem cautela e imprudente
        printf("\nApos um tempo, uma bruxa aparece e te liberta.\n");
    }
    
    pausar();
    
    // CONTINUACAO - BRUXA
    limparTela();
    printf("\n--- ENCONTRO COM A BRUXA ---\n\n");
    printf("Bruxa: 'Me perdoe pelas armadilhas... Elas protegem minha casa.'\n");
    printf("'Voce parece saudavel. Preciso de ajuda.'\n");
    printf("'Um SLIME roubou um dos meus raros ingredientes.'\n");
    printf("'Pode recupera-lo para mim?'\n\n");
    pausar();
    
    printf("Voces caminham juntos ate encontrar o SLIME.\n");
    printf("Ele esta saltitando, com algo brilhando dentro dele.\n\n");
    
    printf("O que voce faz?\n");
    printf("1 - Atacar o slime (forca e irresponsabilidade)\n");
    printf("2 - Modo furtivo (agilidade e cautela)\n");
    printf("3 - Interagir com o slime (criatividade e astucia)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    if (escolha1 == 1) {
        // ATACAR
        printf("\nVoce investe com a espada!\n");
        printf("Perfura o slime! Ele se dissipa!\n");
        printf("O frasco voa no ar... voce o pega!\n");
        printf("Bruxa: 'Eficiente... mas um pouco brutal.'\n");
        pontosAstúcia += 1;  // +1 funcional mas bruto
        
    } else if (escolha1 == 2) {
        // FURTIVO
        printf("\nVoce se esconde no mato...\n");
        printf("Espera o momento certo...\n");
        printf("PULA em cima do slime!\n");
        printf("Ele se assusta e cospe o frasco!\n");
        printf("Voce pega no ar!\n");
        printf("Bruxa: 'Impressionante! Rapido e esperto!'\n");
        pontosAstúcia += 3;  // +3 astucia perfeita
        
    } else {
        // INTERAGIR
        printf("\nVoce se aproxima devagar do slime...\n");
        printf("Ele para e te olha curioso.\n");
        printf("Voce... comeca a fazer COCEGAS nele!?!\n");
        printf("O slime TREME e cospe ♡ frasco!\n");
        printf("Ele comeca a te seguir, parecendo feliz!\n");
        printf("Bruxa: 'Incrivel! Nunca vi ninguem fazer amizade com um slime antes!'\n");
        pontosAstúcia += 4;  // +4 criatividade maxima
    }
    
    pausar();
    
    printf("\n--- DE VOLTA NA CASA DA BRUXA ---\n\n");
    printf("Bruxa joga o frasco de cilios de morcego no caldeirao.\n");
    printf("Ela prepara uma pocao e pos a beber um gole.\n");
    printf("Sua postura melhora, suas feridas se curam!\n\n");
    printf("Ela enche dois frascos e lhe entrega um.\n");
    printf("Bruxa: 'Obrigada, aventureiro. Pegue, voce vai precisar.'\n");
    printf("Voce bebe a pocao e se sente revigorado!\n\n");
    
    pausar();
    printf("\n[ASTUCIA TOTAL: %d pontos]\n", pontosAstúcia);
    pausar();
}

// ---------- EVENTO 2: LAGARTO FULZARD ----------

void eventoLagartoFulzard() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 2: O GUERREIRO LAGARTO ===\n\n");
    
    printf("Continuando pelo pantano, voce ve uma figura estranha.\n");
    printf("Um LAGARTO HUMANOIDE esta sentado em uma rocha.\n");
    printf("Ele olha para o horizonte, parecendo distraido.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Cumprimentar alto (chamar atencao)\n");
    printf("2 - Aproximar em silencio (respeito)\n");
    printf("3 - Observar a distancia (cautela)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: CUMPRIMENTAR ALTO =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce: 'Ola! Bom dia!'\n");
        printf("O lagarto se assusta e cai da rocha!\n");
        printf("Lagarto: 'AH! Voce me assustou!'\n");
        printf("Ele se levanta rindo: 'Eu me distraio facilmente...'\n\n");
        pausar();
        
        printf("Lagarto: 'Meu nome e Fulzard. Quem es voce?'\n");
        printf("Voce conta sobre sua missao.\n");
        printf("Fulzard: 'Animata? Sim, conheco-a...'\n");
        printf("'Quero te testar seus conhecimentos e limites. Aceitas?'\n\n");
        
        printf("Teste: Acertar 3 alvos sem se distrair.\n");
        printf("O que voce faz?\n");
        printf("1 - Aceitar focado (determinacao)\n");
        printf("2 - Aceitar mas conversar durante (casual)\n");
        printf("3 - Recusar educadamente\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce foca completamente na tarefa.\n");
            printf("Fulzard faz barulhos para distrair, mas voce ignora.\n");
            printf("ACERTA os 3 alvos!\n");
            printf("Fulzard: 'Impressionante! Voce tem FOCO.'\n");
            printf("'Damian me ensinou isso... voce me lembra ele.'\n");
            pontosAstúcia += 3;  // +3 foco total
            
        } else if (escolha2 == 2) {
            printf("\nVoce tenta atirar enquanto conversa.\n");
            printf("Acerta 2 alvos, erra 1.\n");
            printf("Fulzard: 'Quase! Mas se distrair pode custar caro.'\n");
            pontosAstúcia += 2;  // +2 esforco
            
        } else {
            printf("\nVoce: 'Oferta tentadora, mas, eu recuso, agradecido pela oferta.'\n");
            printf("Fulzard: 'Sem obstencao! Cada um decide o que prefere fazer, respeito sua decisao.'\n");
            pontosAstúcia += 1;  // +1 por honestidade
        }
        
    // ===== ESCOLHA 2: SILENCIO =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce se aproxima em silencio, respeitoso.\n");
        printf("O lagarto vira e sorri: 'Voce eh bom... eu era pessimo nisso.'\n");
        printf("Lagarto: 'Meu nome e Fulzard.'\n\n");
        pausar();
        
        printf("Fulzard: 'Conheci um paladino chamado Damian.'\n");
        printf("'Ele me ensinou a ter FOCO... a me importar.'\n");
        printf("'Antes, eu era distraido, nao me importava com nada.'\n");
        printf("'Ele me mostrou que se importar dói... mas vale a pena.'\n\n");
        
        printf("O que voce faz?\n");
        printf("1 - Perguntar mais sobre Damian\n");
        printf("2 - Perguntar por que ele esta aqui\n");
        printf("3 - Apenas ouvir em silencio\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nFulzard: 'Ele era nosso lider... e amigo.'\n");
            printf("'Quando ele morreu, eu perdi o foco novamente.'\n");
            printf("'Agora tento honrar o que ele me ensinou.'\n");
            pontosAstúcia += 2;  // +2 empatia
            
        } else if (escolha2 == 2) {
            printf("\nFulzard: 'Estou aqui guardando memorias.'\n");
            printf("'Este pantano... lutamos aqui uma vez.'\n");
            printf("'Eu me distraí e quase morri.'\n");
            printf("'Damian me salvou. Jamais esquecerei deste dia.'\n");
            pontosAstúcia += 2;  // +2 curiosidade
            
        } else {
            printf("\nVoce apenas escuta, respeitoso.\n");
            printf("Fulzard sorri: 'Obrigado por me ouvir.'\n");
            printf("'Faz tempo que nao falo sobre isso.'\n");
            pontosAstúcia += 3;  // +3 presenca
        }
        
    // ===== ESCOLHA 3: OBSERVAR =====
    } else {
        limparTela();
        printf("\nVoce observa de longe.\n");
        printf("O lagarto vira: 'Sei que esta ai. Pode vir.'\n");
        printf("Ele sorri: 'Paranoia eh boa. Eu tinha pouca.'\n");
        printf("Lagarto: 'Meu nome e Fulzard.'\n\n");
        pausar();
        
        printf("Fulzard: 'Quer cacar comigo?'\n");
        printf("'Tem uma presa por aqui.'\n\n");
        
        printf("O que voce decide?\n");
        printf("1 - Aceitar liderar (confianca)\n");
        printf("2 - Deixar ele liderar (humildade)\n");
        printf("3 - Cacar cada um de um lado\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce lidera a cacada.\n");
            printf("Fulzard te segue com atencao.\n");
            printf("Voces capturam a presa com sucesso!\n");
            printf("Fulzard: 'Voce eh um bom lider!'\n");
            pontosAstúcia += 3;  // +3 lideranca
            
        } else if (escolha2 == 2) {
            printf("\nVoce deixa Fulzard liderar.\n");
            printf("Ele fica surpreso: 'Serio? Obrigado!'\n");
            printf("Ele lidera bem, focado.\n");
            printf("Fulzard: 'Fazia tempo que nao confiavam em mim mesmo.'\n");
            pontosAstúcia += 3;  // +3 confianca
            
        } else {
            printf("\nVoces se separam.\n");
            printf("Voce perde a presa por falta de coordenacao.\n");
            printf("Fulzard: 'Sozinho eh mais dificil, ne?'\n");
            pontosAstúcia += 1;  // +1 independencia
        }
    }
    
    pausar();
    
    printf("\n--- DESPEDIDA ---\n\n");
    printf("Fulzard: 'Voce foi bem. Continue focado.'\n");
    printf("'Animata sofre... mas cuidado. Dor pode ser perigosa.'\n");
    printf("'Damian me ensinou que se importar doi...'\n");
    printf("'Mas o amor que se sente eh superior a isso.'\n");
    printf("'Boa sorte, aventureiro.'\n\n");
    
    pausar();
    printf("\n[ASTUCIA TOTAL: %d pontos]\n", pontosAstúcia);
    pausar();
}

// ---------- EVENTO 3: COBRA DO PANTANO ----------

void eventoCobraPantano() {
    limparTela();
    printf("\n=== EVENTO 3: A COBRA GUARDIA ===\n\n");
    
    printf("Ao chegar perto da saida do pantano...\n");
    printf("A agua se agita violentamente!\n");
    printf("Uma COBRA GIGANTE emerge!\n");
    printf("Seus olhos brilham com inteligencia antiga.\n\n");
    pausar();
    
    printf("Cobra: 'Sssss... voce atravesssou meu pantano...'\n");
    printf("'Vi ssssuas escolhasss...'\n");
    printf("'Agora... julgo ssssua assstucia.'\n\n");
    pausar();
    
    // JULGAMENTO BASEADO NOS PONTOS
    printf("\n--- JULGAMENTO DO PANTANO ---\n\n");
    
    if (pontosAstúcia >= 10) {
        // ALTA ASTUCIA
        printf("Cobra: 'Voce nao eh pressssa... eh cacador assim como eu.'\n");
        printf("'Pensssa antesss de agir.'\n");
        printf("'Usssa a mente, nao apenasss musculosss.'\n");
        printf("'Aceito voce como IGUAL!'\n\n");
        printf("A cobra te da uma ESCAMA VENENOSA.\n");
        printf("Cobra: 'Ussse contra a bruxa... pode ajudar.'\n");
        printf("[ITEM OBTIDO: Veneno Antigo - util contra Animata]\n");
        pontosAstúcia += 5;  // Bonus de 5
        
    } else if (pontosAstúcia >= 5) {
        // MEDIA ASTUCIA
        printf("Cobra: 'Voce ssobrevive... por inssstinto ou ssorte?'\n");
        printf("'Idependente das decisoes. Passsou.'\n\n");
        printf("A cobra te da ESCAMAS PROTETORAS.\n");
        printf("[ITEM: Escamas - defesa aumentada]\n");
        pontosAstúcia += 2;  // Bonus de 2
        
    } else {
        // BAIXA ASTUCIA
        printf("Cobra: 'Voce tropeca em galhos propriosss...'\n");
        printf("'Nao pensa... apenasss age.'\n");
        printf("'Cuidado... ou ssera devorado.'\n\n");
        printf("A cobra te morde de leve - um AVISO.\n");
        printf("[MALDICAO: Reflexos lentos]\n");
        pontosAstúcia += 0;
    }
    
    pausar();
    printf("\n--- PANTANO COMPLETO ---");
    printf("\nPONTOS DE ASTUCIA FINAIS: %d\n", pontosAstúcia);
    pausar();
}

// ========================================
//          ROTA 3: CAVERNA
// ========================================

void rotaCaverna() {
    limparTela();
    printf("\n=== CAVERNA ===\n\n");
    printf("Voce entra na caverna escura.\n");
    printf("Tochas antigas iluminam as paredes de pedra.\n");
    printf("Aqui, a verdade sera revelada.\n\n");
    pausar();
    
    // Tres eventos da caverna
    eventoDragaoFilhote();
    eventoAnaoEgnar();
    eventoDrakeAnciao();
    
    // Apos completar a caverna, vai para o castelo
    castelo();
}

// ---------- EVENTO 1: DRAGAO FILHOTE ----------

void eventoDragaoFilhote() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 1: DRAGAO FAMINTO ===\n\n");
    
    printf("Voce ouve GRITOS ecoando na caverna!\n");
    printf("Voce corre em direcao ao som...\n\n");
    printf("Um DRAGAO FILHOTE esta perseguindo um COMERCIANTE ANAO!\n");
    printf("Comerciante: 'SOCORRO! ME AJUDA!'\n");
    printf("O dragao rosna... mas voce nota:\n");
    printf("Ele esta MUITO magro. Costelas aparecendo.\n");
    printf("O estomago do dragao RONCA alto.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Atacar o dragao (proteger humano)\n");
    printf("2 - Pegar pedra e distrair (neutralidade)\n");
    printf("3 - Interagir/Acalmar (sabedoria)\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: ATACAR =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce desembanha sua espada e corre em direcao ao dragao filhote!\n");
        printf("Espantado, o dragao filhote solta fogo, mas nao eh muito forte.\n");
        printf("O fogo te empurra, mas nao o suficiente para voce desistir.\n");
        printf("Voce se queima um pouco, porem continua na sua investida.\n");
        printf("Voce pula, atacando e dando um golpe certeiro!\n");
        printf("O dragao cai derrotado...\n\n");
        pausar();
        
        dragaoFilhoteMorto = 1;  // Marca que matou o dragao
        
        printf("O que voce faz?\n");
        printf("1 - Verificar o dragao (reflexao)\n");
        printf("2 - Consolar o comerciante\n");
        printf("3 - Pegar escama do dragao\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce se aproxima do corpo...\n");
            printf("Era apenas um FILHOTE. Famimto.\n");
            printf("A sua consciencia pesa por agir imprudentemente.\n");
            pontosSabedoria += 1;  // +1 por reflexao
            
        } else if (escolha2 == 2) {
            printf("\nComercian: 'Obrigado! Voce me salvou!'\n");
            printf("Ele te da um MINERIO DE MITHRIL BRUTO.\n");
            printf("'Pegue, eh valioso!'\n");
            temMithril = 1;  // Ganha o mithril
            pontosSabedoria += 0;  // 0 - nao refletiu
            
        } else {
            printf("\nVoce friamente coleta uma escama do dragao.\n");
            printf("Comerciante te olha com desaprovacao.\n");
            pontosSabedoria += 0;  // 0 - frieza
        }
        
    // ===== ESCOLHA 2: DISTRAIR =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce pega uma pedra e arremessa longe!\n");
        printf("O dragao vai atras da pedra, distraido.\n");
        printf("O comerciante foge rapidamente.\n\n");
        printf("Voce se aproxima do dragao...\n");
        printf("Ele esta MUITO magro. Tremendo de fome.\n\n");
        pausar();
        
        printf("O que voce faz?\n");
        printf("1 - Dar comida da mochila\n");
        printf("2 - Procurar a mae dele\n");
        printf("3 - Sair e deixar ele\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce joga carne seca da mochila.\n");
            printf("O dragao devora e ronrona como um felino!\n");
            printf("Ele lambe sua mao, agradecido.\n");
            printf("Ele te segue um pouco, depois volta para a caverna.\n");
            dragaoFilhoteSalvo = 1;  // Marca que salvou
            pontosSabedoria += 3;  // +3 empatia
            printf("\nO comerciante aparece: 'Voce... tem um bom coracao.'\n");
            printf("Ele te da MINERIO DE MITHRIL.\n");
            temMithril = 1;
            
        } else if (escolha2 == 2) {
            printf("\nVoce procura pegadas... e acha algo terrivel.\n");
            printf("Um esqueleto GIGANTE de dragao!\n");
            printf("Era a mae dele... morta ha tempos.\n");
            printf("O filhote chora ao ver.\n");
            printf("Voce pode:\n");
            printf("  - Deixa-lo la (duro)\n");
            printf("  - Enterrar a mae com ele (empatia)\n");
            printf("Voce escolhe enterrar.\n");
            printf("O dragao te olha grato e dissipa pelas sombras.\n");
            dragaoFilhoteSalvo = 1;
            pontosSabedoria += 4;  // +4 maxima empatia
            
        } else {
            printf("\nVoce vai embora.\n");
            printf("Ouve o dragao chorando atras de voce.\n");
            pontosSabedoria += 0;  // 0 - frieza
        }
        
    // ===== ESCOLHA 3: ACALMAR =====
    } else {
        limparTela();
        printf("\nVoce levanta as maos e fala calmamente.\n");
        printf("'Calma... calma, pequeno...'\n");
        printf("O dragao para, confuso.\n");
        printf("Voce nota: ele esta faminto e pode morrer a qualquer instante por conta da fome!\n\n");
        printf("Voce fala para o comerciante: 'Ele nao e agressivo! Esta faminto!'\n");
        printf("Comerciante: 'E-e dai?! Ele quase me matou!'\n\n");
        pausar();
        
        printf("O que voce faz?\n");
        printf("1 - Pedir comida ao comerciante\n");
        printf("2 - Oferecer sua propria comida\n");
        printf("3 - Mediar a situacao\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce: 'Voce tem comida? Podemos ajuda-lo!'\n");
            printf("Comerciante hesita... mas concorda.\n");
            printf("Juntos, alimentam o dragao.\n");
            printf("Dragao ronrona feliz e vai embora.\n");
            printf("Comerciante: 'Voce me ensinou algo hoje.'\n");
            printf("Ele te da MITHRIL e um MAPA SECRETO.\n");
            temMithril = 1;
            dragaoFilhoteSalvo = 1;
            pontosSabedoria += 4;  // +4 diplomacia perfeita
            
        } else if (escolha2 == 2) {
            printf("\nVoce oferece SUA comida ao dragao.\n");
            printf("Ele devora, grato, e lambe sua mao.\n");
            printf("Comerciante se sente mal: 'Eu... tenho algo pra ti.'\n");
            printf("Ele te da MITHRIL e suprimentos extras.\n");
            temMithril = 1;
            dragaoFilhoteSalvo = 1;
            pontosSabedoria += 5;  // +5 sacrificio proprio
            
        } else {
            printf("\nVoce: 'Olha, ele tem fome. Voce tem recursos.'\n");
            printf("'Nao precisa haver violencia.'\n");
            printf("Comerciante pensa... 'Voce tem razao.'\n");
            printf("Voces alimentam o dragao juntos.\n");
            printf("Comerciante: 'Voce eh sabio. Pegue isto.'\n");
            printf("Ele te da MITHRIL e um MAPA com atalho secreto.\n");
            temMithril = 1;
            dragaoFilhoteSalvo = 1;
            pontosSabedoria += 5;  // +5 sabedoria maxima
        }
        
        printf("\nO dragao te olha com gratidao e some na floresta.\n");
        printf("Voce sente que ele nao te esquecera...\n");
    }
    
    pausar();
    printf("\n[SABEDORIA TOTAL: %d pontos]\n", pontosSabedoria);
    pausar();
}

// ---------- EVENTO 2: ANAO EGNAR ----------

void eventoAnaoEgnar() {
    int escolha1, escolha2;
    
    limparTela();
    printf("\n=== EVENTO 2: O FERREIRO FANTASMA ===\n\n");
    
    printf("Mais fundo na caverna, voce ouve sons de FORJA.\n");
    printf("Marteladas ritmicas ecoam...\n\n");
    printf("Voce encontra um ANAO FANTASMAGORICO.\n");
    printf("Ele forja em uma bigorna espectral.\n");
    printf("Fogo azul ilumina seu rosto concentrado.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Perguntar o que ele forja\n");
    printf("2 - Oferecer ajuda\n");
    printf("3 - Observar em silencio\n");
    printf("Escolha: ");
    scanf("%d", &escolha1);
    
    // ===== ESCOLHA 1: PERGUNTAR =====
    if (escolha1 == 1) {
        limparTela();
        printf("\nVoce: 'O que voce forja?'\n");
        printf("Anao para e te olha: 'Forjo proposito... ou forjava.'\n");
        printf("'Meu nome eh Egnar.'\n\n");
        printf("'Conheci um paladino chamado Damian.'\n");
        printf("'Ele deu uma razao para minha existencia.'\n");
        printf("'Antes... eu era vazio.'\n\n");
        pausar();
        
        if (temMithril == 1) {
            printf("Voce: 'Tenho mithril. Pode fazer algo?'\n");
            printf("Egnar sorri: 'Mithril... ha quanto tempo!'\n\n");
            
            printf("O que voce quer?\n");
            printf("1 - Melhorar espada\n");
            printf("2 - Melhorar armadura\n");
            printf("3 - Fazer amuleto de protecao\n");
            printf("Escolha: ");
            scanf("%d", &escolha2);
            
            if (escolha2 == 1) {
                printf("\nEgnar forja sua espada com o mithril.\n");
                printf("Ela brilha com poder!\n");
                printf("[ESPADA MELHORADA - mais dano]\n");
                pontosSabedoria += 2;
                
            } else if (escolha2 == 2) {
                printf("\nEgnar reforça sua armadura com mithril.\n");
                printf("Voce se sente mais protegido!\n");
                printf("[ARMADURA MELHORADA - mais defesa]\n");
                pontosSabedoria += 2;
                
            } else {
                printf("\nEgnar forja um amuleto de protecao.\n");
                printf("'Isso te protegera de magias sombrias.'\n");
                printf("[AMULETO OBTIDO - protecao magica]\n");
                pontosSabedoria += 3;  // +3 escolha estrategica
            }
            
        } else {
            printf("Egnar: 'Se tivesse mithril, poderia te ajudar...'\n");
            printf("'Mas obrigado por conversar.'\n");
            pontosSabedoria += 1;
        }
        
    // ===== ESCOLHA 2: OFERECER AJUDA =====
    } else if (escolha1 == 2) {
        limparTela();
        printf("\nVoce: 'Posso ajudar em algo?'\n");
        printf("Anao para, surpreso: 'Ajuda...?'\n");
        printf("'Ha anos ninguem oferece isso...'\n");
        printf("'Meu nome eh Egnar.'\n\n");
        pausar();
        
        printf("Egnar: 'Preciso de minerio especifico.'\n");
        printf("'Esta no lago subterraneo ou na caverna escura.'\n\n");
        
        printf("Onde voce vai?\n");
        printf("1 - Caverna escura (mais perigoso)\n");
        printf("2 - Lago subterraneo (mais seguro)\n");
        printf("3 - Oferecer o que voce tem\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce vai ate a caverna escura.\n");
            printf("Morcegos gigantes atacam!\n");
            printf("Voce luta e consegue o minerio raro!\n");
            printf("Egnar: 'Voce tem coragem! Obrigado!'\n");
            pontosSabedoria += 3;  // +3 coragem
            
        } else if (escolha2 == 2) {
            printf("\nVoce vai ao lago subterraneo.\n");
            printf("E lindo, cristalino, com minerio no fundo.\n");
            printf("Voce mergulha e pega o minerio.\n");
            printf("Egnar: 'Obrigado por sua ajuda!'\n");
            pontosSabedoria += 2;  // +2 exploracao
            
        } else {
            if (temMithril == 1) {
                printf("\nVoce oferece o mithril que tem!\n");
                printf("Egnar fica emocionado: 'Voce... sacrifica isso por mim?'\n");
                printf("'Damian fazia isso... obrigado.'\n");
                printf("Ele forja algo especial para voce!\n");
                printf("[ITEM LENDARIO - forjado com gratidao]\n");
                pontosSabedoria += 5;  // +5 sacrificio
                temMithril = 0;  // Perdeu o mithril mas ganhou algo melhor
            } else {
                printf("\nVoce nao tem nada util...\n");
                printf("Egnar: 'Tudo bem, a intencao eh que conta.'\n");
                pontosSabedoria += 1;
            }
        }
        
    // ===== ESCOLHA 3: OBSERVAR =====
    } else {
        limparTela();
        printf("\nVoce apenas observa em silencio.\n");
        printf("O anao trabalha concentrado...\n");
        printf("Ele para e olha pra voce.\n\n");
        printf("Anao: 'Damian fazia isso... observava meu trabalho.'\n");
        printf("'Meu nome eh Egnar.'\n\n");
        pausar();
        
        printf("Egnar: 'Posso te perguntar algo?'\n\n");
        
        printf("Qual pergunta ele faz?\n");
        printf("1 - 'Por que voce luta?'\n");
        printf("2 - 'O que voce protege?'\n");
        printf("3 - 'Voce tem medo?'\n");
        printf("Escolha: ");
        scanf("%d", &escolha2);
        
        if (escolha2 == 1) {
            printf("\nVoce reflete e responde honestamente.\n");
            printf("Egnar: 'Proposito... eh tudo.'\n");
            printf("'Damian me deu o meu.'\n");
            printf("'Espero que voce encontre o seu.'\n");
            pontosSabedoria += 3;  // +3 reflexao profunda
            
        } else if (escolha2 == 2) {
            printf("\nVoce fala sobre quem/o que protege.\n");
            printf("Egnar: 'Proteger eh nobre.'\n");
            printf("'Mas nao esqueca de se proteger tambem.'\n");
            pontosSabedoria += 3;  // +3 valores claros
            
        } else {
            printf("\nVoce: 'Sim, tenho medo.'\n");
            printf("Egnar sorri: 'Honestidade. Isso eh raro.'\n");
            printf("'Damian tinha medo... mas nunca demonstrava.'\n");
            printf("'Talvez por isso se foi cedo demais.'\n");
            pontosSabedoria += 4;  // +4 honestidade brutal
        }
    }
    
    pausar();
    
    printf("\n--- DESPEDIDA ---\n\n");
    printf("Egnar: 'Damian me deu proposito. Mas percebi tarde...'\n");
    printf("'O proposito nao eh servir. MAS SIM VIVER.'\n");
    printf("'Nao cometa o erro dele... viva por voce tambem.'\n\n");
    
    pausar();
    printf("\n[SABEDORIA TOTAL: %d pontos]\n", pontosSabedoria);
    pausar();
}

// ---------- EVENTO 3: DRAKE ANCIAO ----------

void eventoDrakeAnciao() {
    limparTela();
    printf("\n=== EVENTO 3: O DRAKE ANCIAO ===\n\n");
    
    printf("Ao chegar na saida da caverna...\n");
    printf("Um RUGIDO ATERRADOR ecoa!\n");
    printf("Um DRAGAO IMENSO bloqueia a passagem!\n");
    printf("Ele tem cicatrizes antigas e olhar penetrante.\n\n");
    pausar();
    
    printf("Drake: 'VOCE... carrega o cheiro DELE.'\n");
    printf("'Do traidor de sangue. Do filho que matou a mae.'\n\n");
    printf("Voce: 'Do que voce esta falando?!'\n\n");
    pausar();
    
    printf("Drake: 'DAMIAN... o heroi.'\n");
    printf("'Ele matou minha irma. Ela o procurou a vida toda.'\n");
    printf("'Ele foi criado por humanos. Nunca soube que era dragonato.'\n");
    printf("'Quando matou a mae... descobriu tarde demais.'\n");
    printf("'Ela veio ate o castelo... e o grupo de herois a MATOU.'\n\n");
    pausar();
    
    printf("Drake: 'O esqueleto dela esta no castelo ate hoje.'\n");
    printf("'E voce vem aqui... para que? Salvar a bruxa que o ama?'\n\n");
    
    if (dragaoFilhoteMorto == 1) {
        printf("Drake rosna: 'E VOCE MATOU MEU SOBRINHO!'\n");
        printf("'O filhote que encontrou... era filho da minha irma!'\n");
        printf("'Voce e IGUAL A ELES! DESTRUIDOR!'\n\n");
        printf("Drake te ataca!\n");
        printf("A luta e brutal... mas voce sobrevive.\n");
        printf("Drake: 'Va... mas a natureza nunca te perdoara.'\n");
        pontosSabedoria += 0;  // 0 - consequencia pesada
        
    } else if (dragaoFilhoteSalvo == 1) {
        printf("Drake para... e CHEIRA voce.\n");
        printf("Drake: 'Voce... salvou meu sobrinho.'\n");
        printf("'O filhote que encontrou era filho da minha irma.'\n");
        printf("'Voce o alimentou... o protegeu.'\n\n");
        printf("Uma lagrima cai do olho de drake.\n");
        printf("Drake: 'Voce nao eh como eles. Voce ESCUTA.'\n\n");
        
        printf("Ele te da uma ESCAMA DOURADA.\n");
        printf("Drake: 'Esta era da minha irma. Pegue.'\n");
        printf("'Use no castelo... pode trazer paz.'\n");
        temEscamaDragao = 1;  // Item especial para final alternativo
        pontosSabedoria += 10;  // +10 recompensa maxima
        
    } else {
        printf("Drake: 'Voce nao o matou... mas tambem nao o salvou.'\n");
        printf("'Indiferenca... as vezes e pior que crueldade.'\n");
        printf("'Va. Mas saiba: a bruxa nao sabe a verdade.'\n");
        printf("'Talvez deva contar a ela.'\n");
        pontosSabedoria += 2;  // +2 neutro
    }
    
    pausar();
    printf("\n--- CAVERNA COMPLETA ---");
    printf("\nPONTOS DE SABEDORIA FINAIS: %d\n", pontosSabedoria);
    pausar();
}

// ========================================
//          CASTELO - EVENTOS FINAIS
// ========================================

void castelo() {
    limparTela();
    printf("\n=====================================\n");
    printf("         CHEGADA AO CASTELO\n");
    printf("=====================================\n\n");
    
    printf("Apos sua jornada pelo %s...\n", rotaEscolhida);
    printf("Voce finalmente avista o castelo no horizonte.\n");
    printf("E sombrio, envolto em nevoa magica.\n");
    printf("As portas estao fechadas.\n\n");
    pausar();
    
    // Quatro eventos finais
    eventoGargulaCharadas();
    eventoArmadurasDancarinas();
    eventoMimicoDiario();
    confrontoFinalAnimata();
}

// ---------- EVENTO 1: GARGULA ----------

void eventoGargulaCharadas() {
    int resposta;
    int acertos = 0;
    
    limparTela();
    printf("\n=== A GARGULA DAS CHARADAS ===\n\n");
    
    printf("Ao se aproximar do portao...\n");
    printf("Uma GARGULA DE PEDRA ganha vida!\n");
    printf("Seus olhos brilham em vermelho.\n\n");
    pausar();
    
    printf("Gargula: 'TRES PERGUNTAS. TRES VERDADES.'\n");
    printf("'ERRE... E VIRE PEDRA COMO EU.'\n\n");
    pausar();
    
    // CHARADA 1 - COMPAIXAO
    printf("\n--- CHARADA 1 ---\n");
    printf("'Pequena sofre, grande a devora. Voce age. Por que?'\n\n");
    printf("1 - Para ser heroi (ego)\n");
    printf("2 - Porque era certo (moralidade)\n");
    printf("3 - Porque senti sua dor (empatia)\n");
    printf("Resposta: ");
    scanf("%d", &resposta);
    
    if (resposta == 3) {
        printf("\nGargula: 'CORRETO. Empatia move o coracao.'\n");
        acertos++;
    } else {
        printf("\nGargula: 'ERRADO. Mas continua...'\n");
    }
    pausar();
    
    // CHARADA 2 - ASTUCIA
    printf("\n--- CHARADA 2 ---\n");
    printf("'Armadilha a frente, sombra atras, agua embaixo. Qual caminho?'\n\n");
    printf("1 - Desarmar a armadilha (logica)\n");
    printf("2 - Enfrentar a sombra (coragem)\n");
    printf("3 - Mergulhar na agua (instinto)\n");
    printf("Resposta: ");
    scanf("%d", &resposta);
    
    if (resposta == 1) {
        printf("\nGargula: 'CORRETO. Pensar e melhor que agir.'\n");
        acertos++;
    } else {
        printf("\nGargula: 'ERRADO. Mas continua...'\n");
    }
    pausar();
    
    // CHARADA 3 - SABEDORIA
    printf("\n--- CHARADA 3 ---\n");
    printf("'Alguem ama tanto que rouba ate Deus. Ela e...?'\n\n");
    printf("1 - Louca (julgamento)\n");
    printf("2 - Perdida (empatia)\n");
    printf("3 - Ma (condenacao)\n");
    printf("Resposta: ");
    scanf("%d", &resposta);
    
    if (resposta == 2) {
        printf("\nGargula: 'CORRETO. Amor distorcido ainda eh amor.'\n");
        acertos++;
    } else {
        printf("\nGargula: 'ERRADO.'\n");
    }
    pausar();
    
    // RESULTADO
    limparTela();
    printf("\n--- RESULTADO ---\n");
    printf("Acertos: %d de 3\n\n", acertos);
    
    if (acertos == 3) {
        printf("Gargula: 'DIGNO. Salve-a... ou condene-a.'\n");
        printf("O portao se abre completamente.\n");
        // Bonus nos pontos da rota escolhida
        if (strcmp(rotaEscolhida, "Floresta") == 0) pontosCompaixao += 3;
        else if (strcmp(rotaEscolhida, "Pantano") == 0) pontosAstúcia += 3;
        else pontosSabedoria += 3;
        
    } else if (acertos == 2) {
        printf("Gargula: 'QUASE. Talvez baste.'\n");
        printf("O portao range e se abre lentamente.\n");
        
    } else {
        printf("Voce comeca a PETRIFICAR!\n");
        printf("Seus pes viram pedra...\n\n");
        printf("De repente, o portao se ABRE sozinho!\n");
        printf("A petrificacao para.\n");
        printf("Gargula: 'Ela ainda quer visitantes... que pena para voce.'\n");
    }
    
    pausar();
}

// ---------- EVENTO 2: ARMADURAS DANCARINAS ----------

void eventoArmadurasDancarinas() {
    int escolha;
    
    limparTela();
    printf("\n=== SALAO DAS ARMADURAS ===\n\n");
    
    printf("Voce entra em um salao de festas abandonado.\n");
    printf("Lustres cobertos de teias, mesa com comida podre.\n");
    printf("De repente... 7 ARMADURAS comecam a se mover!\n");
    printf("Elas dançam em sincronia, como nobres fantasmas.\n\n");
    pausar();
    
    printf("O que voce faz?\n");
    printf("1 - Lutar contra todas (forca)\n");
    printf("2 - Dancar com elas (criatividade)\n");
    printf("3 - Procurar a fonte da magia (inteligencia)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    
    if (escolha == 1) {
        // LUTAR
        limparTela();
        printf("\nVoce ataca as armaduras!\n");
        printf("Elas revidam, mas sao velhas e lentas.\n");
        printf("Voce as derrota uma por uma.\n");
        printf("Ao destruir a ultima, ela cai... e uma voz sussurra:\n");
        printf("'Forca sempre escolhe forca...'\n\n");
        printf("Voce ve uma armadura caida no fundo, segurando uma CHAVE.\n");
        
    } else if (escolha == 2) {
        // DANCAR
        limparTela();
        printf("\nVoce guarda a espada... e comeca a DANCAR!\n");
        printf("As armaduras param, surpresas.\n");
        printf("Voce imita seus movimentos.\n");
        printf("Elas... APLAUDEM!\n");
        printf("(Sao fantasmas de nobres que morreram aqui)\n\n");
        printf("Elas apontam para uma armadura caida no fundo.\n");
        printf("Uma voz feminina sussurra: 'Obrigada... ha muito nao dancavamos.'\n\n");
        printf("Voce pega a CHAVE da armadura caida.\n");
        // Bonus de criatividade
        if (strcmp(rotaEscolhida, "Floresta") == 0) pontosCompaixao += 2;
        else if (strcmp(rotaEscolhida, "Pantano") == 0) pontosAstúcia += 2;
        else pontosSabedoria += 2;
        
    } else {
        // PROCURAR MAGIA
        limparTela();
        printf("\nVoce ignora as armaduras e procura a fonte da magia.\n");
        printf("Voce encontra um CRISTAL no lustre!\n");
        printf("Voce pode quebra-lo ou deixa-lo.\n\n");
        printf("1 - Quebrar o cristal\n");
        printf("2 - Deixar intacto\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        
        if (escolha == 1) {
            printf("\nVoce quebra o cristal!\n");
            printf("As armaduras CAEM, sem vida.\n");
            printf("Silencio total...\n");
            printf("Voce pega a CHAVE da armadura caida.\n");
        } else {
            printf("\nVoce deixa o cristal intacto.\n");
            printf("As armaduras te guiam ate a armadura caida.\n");
            printf("Uma voz sussurra: 'Obrigada por nos deixar existir...'\n");
            printf("Voce pega a CHAVE.\n");
            // Bonus de empatia
            if (strcmp(rotaEscolhida, "Floresta") == 0) pontosCompaixao += 2;
            else if (strcmp(rotaEscolhida, "Pantano") == 0) pontosAstúcia += 2;
            else pontosSabedoria += 2;
        }
    }
    
    pausar();
    printf("\n[CHAVE OBTIDA - Acesso a Sala do Tesouro]\n");
    pausar();
}

// ---------- EVENTO 3: MIMICO E DIARIO ----------

void eventoMimicoDiario() {
    int escolha;
    
    limparTela();
    printf("\n=== SALA DO TESOURO ===\n\n");
    
    printf("Voce abre a porta com a chave.\n");
    printf("Uma sala cheia de BAUS dourados!\n");
    printf("De repente, um deles... ABRE A BOCA!\n");
    printf("Eh um MIMICO!\n\n");
    pausar();
    
    printf("Mimico: 'Espera! Nao vou te atacar!'\n");
    printf("'Estou cansado disso... so quero conversar.'\n");
    printf("'Tenho algo que voce quer... um DIARIO.'\n\n");
    
    printf("O que voce faz?\n");
    printf("1 - Desconfiar (cautela)\n");
    printf("2 - Aceitar conversar (abertura)\n");
    printf("3 - Oferecer algo primeiro (bondade)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    
    if (escolha == 1) {
        // DESCONFIAR
        printf("\nVoce: 'Mimicos nao falam... o que voce quer?'\n");
        printf("Mimico: 'Esperto. Mas olha, nao quero lutar.'\n");
        printf("'A bruxa me pediu para guardar um diario.'\n");
        printf("'Posso te dar... em troca de algo.'\n\n");
        printf("Voce oferece comida da mochila.\n");
        printf("Mimico: 'Obrigado... ha anos nao como.'\n");
        printf("Ele te entrega o DIARIO.\n");
        
    } else if (escolha == 2) {
        // CONVERSAR
        printf("\nVoce: 'Tudo bem, vamos conversar.'\n");
        printf("Mimico: 'Serio?! Ninguem nunca quis conversar comigo...'\n");
        printf("Ele chora (mimicos tem sentimentos!).\n");
        printf("Mimico: 'A bruxa me pediu pra guardar um diario.'\n");
        printf("'Ela disse que era importante... sobre os herois.'\n");
        printf("'Voce parece bom. Pegue.'\n");
        printf("Ele te entrega o DIARIO gratuitamente.\n");
        // Bonus de empatia
        if (strcmp(rotaEscolhida, "Floresta") == 0) pontosCompaixao += 2;
        else if (strcmp(rotaEscolhida, "Pantano") == 0) pontosAstúcia += 2;
        else pontosSabedoria += 2;
        
    } else {
        // OFERECER
        printf("\nVoce: 'Tenho algo para voce.'\n");
        printf("Voce oferece comida da mochila.\n");
        printf("Mimico: 'Voce... nao vai me atacar?'\n");
        printf("Ele CHORA copiosamente.\n");
        printf("Mimico: 'Obrigado... obrigado...'\n");
        printf("Ele te entrega o DIARIO e um TESOURO extra.\n");
        printf("[BONUS: Item raro obtido!]\n");
        // Bonus maximo
        if (strcmp(rotaEscolhida, "Floresta") == 0) pontosCompaixao += 3;
        else if (strcmp(rotaEscolhida, "Pantano") == 0) pontosAstúcia += 3;
        else pontosSabedoria += 3;
    }
    
    pausar();
    limparTela();
    
    // LEITURA DO DIARIO
    printf("\n========================================\n");
    printf("           DIARIO DOS HEROIS\n");
    printf("       Compilado por Animata\n");
    printf("========================================\n\n");
    pausar();
    
    printf("--- Entrada de Egnar (Anao Ferreiro) ---\n\n");
    printf("'Damian me deu proposito. Antes, eu apenas existia.'\n");
    printf("'Forjar para ele... tinha significado.'\n");
    printf("'Mas quando ele se foi, eu continuei forjando...'\n");
    printf("'Por que? Porque aprendi que o proposito eh viver.'\n");
    printf("'Nao importa para quem, mas viver tem valor.'\n\n");
    pausar();
    
    printf("--- Entrada de Glacify (Elfa Negra) ---\n\n");
    printf("'Eu tinha medo de tudo. De errar, de machucar, de falhar.'\n");
    printf("'Damian me disse: Voce ja falhou ao nao tentar.'\n");
    printf("'Na ultima batalha, eu tentei. Falhei. Ele morreu.'\n");
    printf("'Mas nao me arrependo de ter tentado.'\n");
    printf("'Ele sorriu para mim no final.'\n\n");
    pausar();
    
    printf("--- Entrada de Fulzard (Lagarto Guerreiro) ---\n\n");
    printf("'Nunca liguei pra nada. Para que? Doi.'\n");
    printf("'Damian me obrigou a ligar. Odiei ele por isso.'\n");
    printf("'Depois amei. Depois sofri quando ele partiu.'\n");
    printf("'Mas eu nao trocaria. A dor prova de que eu vivi.'\n");
    printf("'A dor prova que eu amei.'\n\n");
    pausar();
    
    printf("--- Entrada sobre Damian (por Animata) ---\n\n");
    printf("'Ele sempre ajudou. Nunca pediu ajuda.'\n");
    printf("'Eu perguntei: Por que voce se sacrificou?'\n");
    printf("'Ele nao respondeu. Apenas sorriu.'\n");
    printf("'Eu acho que... ele estava cansado.'\n");
    printf("'Cansado de ser o forte. O sabio. O heroi.'\n");
    printf("'Ele queria descansar. Mas EU nao deixei.'\n\n");
    pausar();
    
    printf("--- Entrada OCULTA (pagina rasgada) ---\n\n");
    printf("'Eu matei minha mae.'\n");
    printf("'Eu nao sabia. Mas isso importa?'\n");
    printf("'Ela veio me procurar. Anos procurando.'\n");
    printf("'E eu... eu a matei.'\n");
    printf("'Suas ultimas palavras: Meu filho... finalmente.'\n");
    printf("'Como eu vivo com isso?'\n\n");
    pausar();
    
    printf("--- Ultima entrada de Animata ---\n\n");
    printf("'Roubei o amuleto. Tentei revive-lo.'\n");
    printf("'Nao funcionou. Ele nao voltou.'\n");
    printf("'Talvez... ele nao QUEIRA voltar.'\n");
    printf("'Talvez eu seja egoista.'\n");
    printf("'Talvez eu o ame tanto que o prendi aqui.'\n");
    printf("'Se alguem ler isso... pare-me.'\n");
    printf("'Ou me deixe com ele para sempre.'\n\n");
    pausar();
    
    printf("========================================\n");
    printf("         FIM DO DIARIO\n");
    printf("========================================\n\n");
    
    printf("Voce fecha o diario, entendendo tudo agora...\n");
    pausar();
}

// ---------- CONFRONTO FINAL ----------

void confrontoFinalAnimata() {
    int escolhaFinal;
    
    limparTela();
    printf("\n========================================\n");
    printf("         SALAO DO TRONO\n");
    printf("========================================\n\n");
    
    printf("Voce abre a ultima porta...\n");
    printf("O salao eh imenso, sombrio.\n\n");
    printf("No centro: um ESQUELETO GIGANTE de dragao.\n");
    printf("Ao lado: ANIMATA, abraçada ao amuleto.\n");
    printf("Ao redor: os fantasmas de Egnar, Glacify e Fulzard, presos.\n\n");
    pausar();
    
    printf("Animata levanta a cabeca: 'Voce veio... como todos pedem.'\n");
    printf("'Salve-nos, heroi. Sempre a mesma historia.'\n");
    printf("Ela ri amargamente.\n\n");
    pausar();
    
    printf("Os fantasmas falam:\n");
    printf("Egnar: 'Deixe-nos ir, Animata... por favor.'\n");
    printf("Glacify: 'Voce nao esta errando por tentar... esta errando por nao parar.'\n");
    printf("Fulzard: 'Doi, eu sei. Mas prender a gente doi mais.'\n\n");
    pausar();
    
    printf("Animata: 'CALEM-SE! Voces nao entendem!'\n");
    printf("'Sem ele, sem VOCES... eu nao sou nada!'\n\n");
    pausar();
    
    // ESCOLHA FINAL
    printf("\n========================================\n");
    printf("           ESCOLHA FINAL\n");
    printf("========================================\n\n");
    
    printf("O que voce faz?\n");
    printf("1 - Combater Animata (forca)\n");
    printf("2 - Conversar com ela (empatia)\n");
    printf("3 - Usar a Escama do Dragao (se tiver)\n");
    printf("Escolha: ");
    scanf("%d", &escolhaFinal);
    
    if (escolhaFinal == 1) {
        // FINAL A: COMBATE
        limparTela();
        printf("\n=== FINAL: LIBERTACAO FORCADA ===\n\n");
        printf("Voce desembanha sua espada.\n");
        printf("Animata: 'Entao eh isso? Violencia? Igual a todos?'\n\n");
        printf("Voce a derrota em combate magico intenso.\n");
        printf("O amuleto se QUEBRA.\n");
        printf("Os fantasmas sao libertos... mas Animata cai, chorando.\n\n");
        pausar();
        
        printf("Animata: 'Voce salvou todos... exceto eu...'\n");
        printf("Ela desaparece nas sombras, sozinha e amarga.\n\n");
        printf("Kenshi: 'O amuleto foi destruido... mas a que custo?'\n");
        printf("'As vezes, a forca nao eh a resposta.'\n\n");
        
    } else if (escolhaFinal == 2) {
        // FINAL B: CONVERSA
        limparTela();
        printf("\n=== FINAL: REDENCAO ===\n\n");
        printf("Voce guarda sua espada.\n");
        printf("Voce: 'Posso entender voce?'\n");
        printf("Animata para, surpresa: 'Voce... nao vai me atacar?'\n\n");
        pausar();
        
        printf("Voce: 'Li o diario. Voce o amava.'\n");
        printf("Animata chora: 'Eu... eu ajudei a matar a mae dele...'\n");
        printf("Voce: 'Voce nao sabia. Ele tambem nao.'\n\n");
        pausar();
        
        // Calcula se teve boas escolhas
        int pontosTotal = pontosCompaixao + pontosAstúcia + pontosSabedoria;
        
        if (pontosTotal >= 20) {
            // FINAL B1 - REDENCAO COMPLETA
            printf("Voce: 'Voce pode deixa-los ir. Ainda ha tempo.'\n");
            printf("Animata chora copiosamente.\n");
            printf("Ela abraca o amuleto uma ultima vez...\n");
            printf("E o LIBERTA.\n\n");
            pausar();
            
            printf("Os fantasmas a abraçam antes de partir.\n");
            printf("Damian aparece por ultimo: 'Obrigado... por tudo.'\n");
            printf("Animata: 'Me perdoa?'\n");
            printf("Damian: 'Sempre perdoei. Agora perdoe-se.'\n\n");
            printf("Todos partem em paz.\n");
            printf("Animata vive, se torna guardia do castelo.\n");
            printf("'Vou honrar a memoria deles... do jeito certo.'\n\n");
            
        } else {
            // FINAL B2 - ACEITACAO PARCIAL
            printf("Voce: 'Deixe-os ir... por favor.'\n");
            printf("Animata: 'Eu... ainda nao estou pronta...'\n");
            printf("Ela liberta Egnar, Glacify e Fulzard.\n");
            printf("Mas mantem Damian um pouco mais.\n\n");
            printf("Damian: 'Tudo bem... estarei aqui ate voce estiver pronta.'\n");
            printf("Nao eh perfeito... mas eh um começo.\n\n");
        }
        
    } else if (escolhaFinal == 3 && temEscamaDragao == 1) {
        // FINAL C - ESCAMA DO DRAGAO (FINAL SECRETO)
        limparTela();
        printf("\n=== FINAL SECRETO: PAZ COMPLETA ===\n\n");
        printf("Voce: 'Tenho algo para voce.'\n");
        printf("Voce mostra a ESCAMA DOURADA.\n");
        printf("Animata: 'Isso eh... da dragoa?'\n\n");
        pausar();
        
        printf("Voce: 'Drake me deu. Era da mae de Damian.'\n");
        printf("Animata pega a escama, tremendo.\n\n");
        printf("Voce coloca a escama no esqueleto do dragao.\n");
        printf("MAGIA ACONTECE!\n\n");
        pausar();
        
        printf("O esqueleto BRILHA!\n");
        printf("Uma forma espectral aparece: a DRAGOA ANCIA!\n\n");
        printf("Dragoa: 'Voce ama meu filho.'\n");
        printf("Animata chora: 'Eu... eu ajudei a matar voce!'\n");
        printf("Dragoa: 'Eu sei. Mas voce tambem o amou quando ninguem mais conseguia.'\n\n");
        pausar();
        
        printf("A dragoa toca o amuleto.\n");
        printf("Ele se TRANSFORMA!\n");
        printf("Nao eh mais prisao... eh MEMORIA.\n\n");
        printf("Os fantasmas sao libertos, mas suas lembrancas permanecem.\n");
        printf("Damian aparece e abraça a mae e Animata.\n");
        printf("Todos partem juntos, em paz.\n\n");
        pausar();
        
        printf("Animata fica com o amuleto transformado.\n");
        printf("Ela se torna Guardia da Memoria.\n");
        printf("'Vou proteger o legado deles... nao suas almas.'\n\n");
        
        if (dragaoFilhoteSalvo == 1) {
            printf("De repente... o DRAGAO FILHOTE aparece, agora ADULTO!\n");
            printf("Ele cresceu rapido e lembrou de voce!\n");
            printf("Dragao: 'Voce me salvou... agora protegerei esta guardia.'\n");
            printf("Ele fica com Animata.\n");
            printf("'Ele e tudo que restou da mae de Damian. Vou protege-lo.'\n\n");
        }
        
        printf("O esqueleto eh enterrado com honras.\n");
        printf("A paz finalmente reina.\n\n");
        
    } else {
        // Caso escolha 3 mas nao tenha a escama
        printf("\nVoce nao tem a Escama do Dragao...\n");
        printf("Voltando as opcoes anteriores.\n");
        pausar();
        confrontoFinalAnimata();  // Chama de novo
        return;
    }
    
    pausar();
    calcularRanking();  // Vai para o ranking final
}

// ========== RANKING FINAL ==========

void calcularRanking() {
    int pontosTotal = pontosCompaixao + pontosAstúcia + pontosSabedoria;
    
    limparTela();
    printf("\n========================================\n");
    printf("           RANKING FINAL\n");
    printf("========================================\n\n");
    
    printf("--- PONTUACAO ---\n");
    printf("Compaixao: %d pontos\n", pontosCompaixao);
    printf("Astucia: %d pontos\n", pontosAstúcia);
    printf("Sabedoria: %d pontos\n", pontosSabedoria);
    printf("\nTOTAL: %d pontos\n\n", pontosTotal);
    pausar();
    
    // RANKING BASEADO NOS PONTOS
    printf("\n--- SEU RANK ---\n\n");
    
    if (pontosTotal >= 40) {
        printf("****************************************\n");
        printf("     RANK S - HEROI LENDARIO\n");
        printf("****************************************\n\n");
        printf("Voce nao apenas completou a missao.\n");
        printf("Voce trouxe PAZ, JUSTICA e REDENCAO.\n");
        printf("Sua jornada sera contada por geracoes.\n");
        printf("Pessoas nao falam apenas de suas vitorias...\n");
        printf("Mas de seu CORACAO.\n\n");
        
    } else if (pontosTotal >= 30) {
        printf("****************************************\n");
        printf("     RANK A - HEROI VERDADEIRO\n");
        printf("****************************************\n\n");
        printf("Voce fez escolhas dificeis com sabedoria.\n");
        printf("Nem sempre perfeito, mas sempre tentando.\n");
        printf("Voce salvou vidas e almas.\n");
        printf("O reino te agradece.\n\n");
        
    } else if (pontosTotal >= 20) {
        printf("****************************************\n");
        printf("     RANK B - AVENTUREIRO CAPAZ\n");
        printf("****************************************\n\n");
        printf("Voce completou a missao.\n");
        printf("Nem heroi, nem vilao. Apenas humano.\n");
        printf("Suas escolhas foram praticas.\n");
        printf("Fez o necessario.\n\n");
        
    } else if (pontosTotal >= 10) {
        printf("****************************************\n");
        printf("     RANK C - SOBREVIVENTE\n");
        printf("****************************************\n\n");
        printf("Voce sobreviveu... mas a que custo?\n");
        printf("Muitas escolhas dificeis.\n");
        printf("Talvez pudesse ter feito melhor.\n");
        printf("Mas voce chegou ate o fim.\n\n");
        
    } else {
        printf("****************************************\n");
        printf("     RANK D - CAMINHO SOMBRIO\n");
        printf("****************************************\n\n");
        printf("Voce completou a missao... tecnicamente.\n");
        printf("Mas deixou muita dor pelo caminho.\n");
        printf("A violencia foi sua primeira escolha.\n");
        printf("Talvez precise refletir sobre suas acoes.\n\n");
    }
    
    pausar();
    
    // MENSAGEM ESPECIAL POR ROTA
    printf("\n--- MENSAGEM DA SUA ROTA ---\n\n");
    
    if (strcmp(rotaEscolhida, "Floresta") == 0) {
        if (pontosCompaixao >= 15) {
            printf("A Ninfa da Floresta sorri:\n");
            printf("'Voce provou que a compaixao nao eh fraqueza.'\n");
            printf("'E a maior forca que existe.'\n");
        } else {
            printf("A Ninfa da Floresta suspira:\n");
            printf("'Voce passou pela floresta, mas nao aprendeu com ela.'\n");
            printf("'A natureza perdoa... mas nao esquece.'\n");
        }
        
    } else if (strcmp(rotaEscolhida, "Pantano") == 0) {
        if (pontosAstúcia >= 15) {
            printf("A Cobra do Pantano assobia:\n");
            printf("'Voce eh cacador, nao pressssa.'\n");
            printf("'Pensssa antes de agir. Isso eh ssssabedoria.'\n");
        } else {
            printf("A Cobra do Pantano balanca a cabeca:\n");
            printf("'Voce tropecou em muitas armadilhas.'\n");
            printf("'No pantano, quem nao pensa... afunda.'\n");
        }
        
    } else {
        if (pontosSabedoria >= 15) {
            printf("O Drake Anciao te olha com respeito:\n");
            printf("'Voce nao eh como os outros.'\n");
            printf("'Voce ESCUTA. Voce APRENDE.'\n");
            printf("'Isso eh verdadeira sabedoria.'\n");
        } else {
            printf("O Drake Anciao franze o rosto:\n");
            printf("'Voce tem forca... mas falta sabedoria.'\n");
            printf("'Forca sem sabedoria e destruicao.'\n");
        }
    }
    
    pausar();
    
    // EPILOGO 
    printf("\n========================================\n");
    printf("              EPILOGO\n");
    printf("========================================\n\n");
    
    printf("Voce retorna a vila.\n");
    printf("Kenshi te abraca, chorando de alivio.\n");
    printf("'Voce conseguiu... obrigado.'\n\n");
     
    if (pontosTotal >= 30) {
        printf("A vila celebra seu retorno com uma festa.\n");
        printf("Criancas correm ate voce pedindo para ouvir suas historias.\n");
        printf("Voce se tornou uma LENDA!ll.\n\n");
    } else if (pontosTotal >= 15) {
        printf("A vila comemora discretamente.\n");
        printf("Voce fez o que era necessario.\n");
        printf("Nao eh um heroi... mas fez a diferenca.\n\n");
    } else {
        printf("A vila recebe voce em silencio.\n");
        printf("A missao foi cumprida... mas algo parece vazio.\n");
        printf("Voce olha para tras... e sente que perdeu algo.\n\n");
    }
    
    printf("========================================\n");
    printf("            FIM DO JOGO\n");
    printf("========================================\n\n");
    printf("Obrigado por jogar!\n");
    printf("Sua jornada termina aqui... ou comeca?\n\n");
    
    pausar();

}

