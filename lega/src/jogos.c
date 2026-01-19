#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "equipas.h"
#include "jogos.h"

// Protótipos: Avisamos o C que estas funções existem lá em baixo
const char* traduzirFase(int alvo);
void listarArvoreCompleta(void);
void gerarJogosDaFase(void);
void sortearEquipaIsenta(void);
void sortearConfrontos(void);
extern void salvarDados(void);

// VARIÁVEIS GLOBAIS: Onde guardamos os dados
Jogo jogos[100];
int totalJogos = 0;
int jogoSendoEditado = -1;
int sorteioRealizado = 0; // 0 = Não realizado, 1 = Realizado

extern Equipa equipas[16];
extern int totalEquipas;

// protótipos das funções (declarações)
void gerarJogosDaFase(void);        // Função que agrupa a sequencia do RF 2.1
void sortearEquipaIsenta(void);     // Corresponde ao RF 2.1.1
void sortearConfrontos(void);       // Corresponde ao RF 2.1.2 (Ajustado nome)

void menuGerirJogos(void);
void registarJogos(void);           // Função que agrupa a sequência do RF 2.2
void introduzirResultado(void);     // Corresponde ao RF 2.2.1
void coletarDadosDoConfronto(void);
void determinarVencedor(void);      // Corresponde ao RF 2.2.2
void atualizarEstatisticas(void);   // Corresponde ao RF 2.2.3
void gravarResultado(void);         // Corresponde ao RF 2.2.4

void registarProrrogacao(void);     // Corresponde ao RF 2.3
void registarPenaltis(void);        // Corresponde ao RF 2.4

// UC 1.2 - Gerir Jogos (Função Principal do Módulo)
void menuGerirJogos(void) {
    int opcao;
    int resultadoScan;
    int opcaoGestao = -1;// Para validar se foi digitado um número

    do {
        limparTela();
        printf("                      ╔═════════════════════════════════╗   \n");
        printf("                                GESTÃO DE JOGOS             \n");
        printf("                      ╚═════════════════════════════════╝   \n\n\n");
        printf("                   ┎━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━┒\n");
        printf("                       1. Gerar Jogos da Fase (Sorteio)     \n"); 
        printf("                       2. Registar Resultados de Jogos      \n");            
        printf("                       3. Listar Tabela do Campeonato       \n");
        printf("                       0. Voltar ao Menu Principal         \n");
        printf("                   ┖━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━─━┚\n");
        printf("                        Escolha uma opção: ");
        
        resultadoScan = scanf("%d", &opcaoGestao); //Validação contra letras
        
        if (resultadoScan != 1) { 
            printf("\n                            ⚠️ Opção não aceita.\n");
            printf("                        Escolha uma das opções acima.\n");
            while (getchar() != '\n'); // Limpa o "lixo" do buffer
            sleep(2); // Pausa para o usuário ler o erro
            continue; // Volta para o início do loop
        }
        
        switch(opcaoGestao) {
            case 1:
                //Proteção caso já haja campeonato em andamento
                if (sorteioRealizado == 1) {
                    int confirma;
                    printf("\n                ===============================================");
                    printf("\n                            CAMPEONATO EM ANDAMENTO!           ");
                    printf("\n                ===============================================");
                    printf("\n                Deseja interrompê-lo e realizar novo sorteio?");
                    printf("\n                1 - Sim, novo sorteio");
                    printf("\n                2 - Não, voltar para o menu GESTÃO DE JOGOS");
                    printf("\n                Escolha uma opção: ");
                  

                    do {
     
                        if (scanf("%d", &confirma) != 1) {
                            while (getchar() != '\n'); // limpa lixo
                            confirma = 0;
                        }

                        if (confirma != 1 && confirma != 2) {
                            printf("\n                            ⚠️ Opção não aceita.\n");
                            printf("                        Escolha uma das opções acima.\n");
                        }

                    } while (confirma != 1 && confirma != 2);

                    if (confirma == 1) {
                        printf("\n               ✅ Reiniciando campeonato e limpando jogos anteriores...\n");
                        remove("data/jogos.txt"); // Apaga o ficheiro físico
                        sleep(2);
                        limparTela();
                        totalJogos = 0;
                        sorteioRealizado = 0;
                        gerarJogosDaFase(); 
                        printf("\n=============================================================");
                        printf("\nPressione ENTER para voltar ao menu...");
                        while (getchar() != '\n'); // limpa buffer
                        getchar(); // espera ENTER
                    } else {
                        printf("\n               Operação cancelada. O campeonato atual foi mantido.\n");
                        sleep(2);
                    }
                } else {
                    // Se não houver sorteio prévio, gera normalmente
                    limparTela();
                    gerarJogosDaFase(); 
                    printf("\n\nPressione ENTER para voltar ao menu...");
                    while (getchar() != '\n'); // limpa buffer
                    getchar(); // espera ENTER
                }
                break;

            case 2:
                registarJogos(); 
                break;
            case 3:
                limparTela();
                listarArvoreCompleta(); 
                printf("\n=============================================================================");
                printf("\nPressione ENTER para voltar ao menu...");
                while (getchar() != '\n'); // limpa buffer
                getchar(); // espera ENTER
                break; 
            case 0:
                printf("\n\n");
                printf("                        A sair da Gestão de Jogos...\n");
                sleep(2);
                return;
            default:
                printf("\n                            ⚠️ Opção não aceita.\n");
                printf("                        Escolha uma das opções acima.\n");
                sleep(2);
                break;
        }
    } while (opcaoGestao != 0);
}

// Implementação da sequência lógica do UC 1.2.2 (RF 2.2)
void registarJogos(void) {
    if (sorteioRealizado == 0) {
        printf("\n                 ⚠️ Realize o sorteio antes de registar resultados.\n");
        sleep(2);
        return;
    }
    introduzirResultado();
    determinarVencedor();
    atualizarEstatisticas();
    gravarResultado();
    salvarDados();
    jogoSendoEditado = -1;
}

void gerarJogosDaFase(void) {
    totalJogos = 0; // Isto limpa qualquer jogo "lixo" que tenha vindo do ficheiro 
    // --- CASO ESPECIAL: Campeonato com 2 equipas → jogo direto para a final ---
    if (totalEquipas == 2) {
        jogos[0].id_jogo = 1;
        jogos[0].fase = 2; // FINAL
        jogos[0].slot = 1;
        jogos[0].id_equipaA = equipas[0].id;
        jogos[0].id_equipaB = equipas[1].id;
        jogos[0].id_vencedor = 0; // Ainda não jogado

        totalJogos = 1;
        sorteioRealizado = 1;

        printf("\n                    Sorteio concluído: Final direta entre %s X %s\n",
            equipas[0].nome, equipas[1].nome);

        gravarResultado(); // Salva o estado no ficheiro
        return; // Sai da função, não há mais sorteio necessário
    }
    // 1. Verificação de segurança (Baseado no RNF5)
    if (totalEquipas < 2) {
        printf("\n[Erro] O Campeonato precisa de pelo menos 2 equipas registadas para gerar jogos (%d).\n", totalEquipas);
        return;
    }

    // --- IMPLEMENTAÇÃO DA LÓGICA MATEMÁTICA (RF 2.1) ---
    int alvo, numJogos, numIsentos;

    // Determinar o objetivo de redução para a potência de 2 (16, 8, 4 ou 2)
    if (totalEquipas > 8) {
        alvo = 8;      // Ex: 9 a 16 equipas -> Rumo aos Quartos (8)
    } else if (totalEquipas > 4) {
        alvo = 4;      // Ex: 5 a 8 equipas -> Rumo às Meias (4)
    } else {
        alvo = 2;      // Ex: 3 a 4 equipas -> Rumo à Final (2)
    }

    // Cálculo matemático para eliminar o excesso e chegar ao alvo
    numJogos = totalEquipas - alvo;
    numIsentos = totalEquipas - (numJogos * 2);

    // Feedback visual para o Administrador
    printf("\n==================== ESTRUTURA DA FASE =====================\n");
    printf("              Equipas Registadas: %d\n", totalEquipas);
    printf("              Número de equipas para a fase seguinte: %d\n", alvo);
    printf("              Jogos a realizar nesta ronda: %d\n", numJogos);
    printf("              Equipas Isentas: %d\n", numIsentos);
    printf("=============================================================\n");

    // 2. Iniciar os Sorteios (UC 1.2.1.1 e 1.2.1.2)
    srand(time(NULL)); // Inicializa a semente para sorteios aleatórios

    if (numIsentos > 0) {
        sortearEquipaIsenta(); // Executa o RF 2.1.1
    }

    if (numJogos > 0) {
        sortearConfrontos();   // Executa o RF 2.1.2
    }

    sorteioRealizado = 1; 
    gravarResultado();
    //printf("\n***************************************************************\n");
    //printf("Sorteio concluído e guardado.");
    //printf("\n***************************************************************\n");
}

void sortearEquipaIsenta(void) {
    // Limpa o estado de isenção de todos
    for (int i = 0; i < totalEquipas; i++) {
        equipas[i].isenta = 0;
    }

    // Calcula quantos isentos são precisos (Matemática das potências de 2)
    int alvo = (totalEquipas > 8) ? 8 : (totalEquipas > 4 ? 4 : 2);
    int numJogos = totalEquipas - alvo;
    int numIsentas = totalEquipas - (numJogos * 2);

    // Escolhe as equipas aleatoriamente
    int sorteados = 0;
    while (sorteados < numIsentas) {
        int idx = rand() % totalEquipas;
        if (equipas[idx].isenta == 0) {
            equipas[idx].isenta = 1;
            sorteados++;
        }
    }
}

void sortearConfrontos(void) {
    int faseIni, faseProx;
    // Define se começamos em 16, 8, 4 ou 2
    if (totalEquipas > 8)      { faseIni = 16; faseProx = 8; }
    else if (totalEquipas > 4) { faseIni = 8;  faseProx = 4; }
    else if (totalEquipas > 2) { faseIni = 4;  faseProx = 2; }
    else                       { faseIni = 2;  faseProx = 0; }

    int idxJogar[16], cJogar = 0, idxIsentos[16], cIsentos = 0;

    // Separa quem vai jogar agora de quem vai para a vaga da frente (isento)
    for (int i = 0; i < totalEquipas; i++) {
        if (equipas[i].isenta == 0) idxJogar[cJogar++] = i;
        else idxIsentos[cIsentos++] = i;
    }

    // Embaralha quem joga para garantir aleatoriedade no sorteio
    for (int i = cJogar - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = idxJogar[i]; idxJogar[i] = idxJogar[j]; idxJogar[j] = tmp;
    }

    // 1. Cria os jogos da fase inicial (ex: Oitavas 1, 2...)
    int numJogosR1 = cJogar / 2;
    for (int i = 0; i < numJogosR1; i++) {
        jogos[totalJogos].id_jogo = totalJogos + 1;
        jogos[totalJogos].fase = faseIni;
        jogos[totalJogos].slot = i + 1;
        jogos[totalJogos].id_equipaA = equipas[idxJogar[i*2]].id;
        jogos[totalJogos].id_equipaB = equipas[idxJogar[i*2+1]].id;
        jogos[totalJogos].id_vencedor = 0;
        printf("              [Sorteio] %s %d: %s vs %s\n", traduzirFase(faseIni), i+1, 
               equipas[idxJogar[i*2]].nome, equipas[idxJogar[i*2+1]].nome);
        totalJogos++;
    }

    // 2. LÓGICA DAS VAGAS: Coloca isentos na fase seguinte de trás para frente (Vaga 24, 23, 22...)
    if (faseProx != 0) {
        int numJogosProx = faseProx / 2;
        int isentasAlocadas = 0;

        // Percorre os jogos da próxima fase do último (ex: 4) para o primeiro (1)
        for (int i = numJogosProx; i >= 1; i--) {
            int currentIdx = totalJogos;
            jogos[currentIdx].id_jogo = totalJogos + 1;
            jogos[currentIdx].fase = faseProx;
            jogos[currentIdx].slot = i;
            jogos[currentIdx].id_equipaA = 0;
            jogos[currentIdx].id_equipaB = 0;
            jogos[currentIdx].id_vencedor = 0;

            // Preenche Vaga B (Par - ex: 24, 22, 20...)
            if (isentasAlocadas < cIsentos) {
                jogos[currentIdx].id_equipaB = equipas[idxIsentos[isentasAlocadas++]].id;
                printf("              [Sorteio] %s (Isenta) -> Vaga na %s %d\n", 
                       equipas[idxIsentos[isentasAlocadas-1]].nome, traduzirFase(faseProx), i);
            }
            // Preenche Vaga A (Ímpar - ex: 23, 21, 19...)
            if (isentasAlocadas < cIsentos) {
                jogos[currentIdx].id_equipaA = equipas[idxIsentos[isentasAlocadas++]].id;
                printf("              [Sorteio] %s (Isenta) -> Vaga na %s %d\n", 
                       equipas[idxIsentos[isentasAlocadas-1]].nome, traduzirFase(faseProx), i);
            }
            
            // Adiciona o jogo apenas se ele tiver pelo menos uma equipa (isenta)
            if (jogos[currentIdx].id_equipaA != 0 || jogos[currentIdx].id_equipaB != 0) {
                totalJogos++;
            }
        }
    }
    sorteioRealizado = 1; 
    printf("\n***************************************************************\n");
    printf("Sorteio concluído. A Tabela do campeonato já está disponível.");
    printf("\n***************************************************************\n");
}

void introduzirResultado(void) {
    if (totalJogos == 0) {
        printf("\n**************************************************************\n");
        printf("Nenhum jogo sorteado.");
        printf("\nRealize o sorteio primeiro para registar os resultados (Opção 1).\n");
        printf("**************************************************************\n");
        return;
    }
    limparTela();

    int indicesValidos[100];
    int contadorOpcoes = 0;

    printf("\n======= JOGOS DISPONÍVEIS PARA REGISTO =======\n\n");

    int fases[] = {16, 8, 4, 2};

    for (int f = 0; f < 4; f++) {
        int alvo = fases[f];
        int numSlots = alvo / 2;

        for (int s = 1; s <= numSlots; s++) {
            int idxExistente = -1;
            for (int j = 0; j < totalJogos; j++) {
                if (jogos[j].fase == alvo && jogos[j].slot == s) {
                    idxExistente = j;
                    break;
                }
            }

            if (idxExistente != -1 && jogos[idxExistente].id_vencedor != 0) continue;

            int idA = 0, idB = 0;
            if (idxExistente != -1) {
                idA = jogos[idxExistente].id_equipaA;
                idB = jogos[idxExistente].id_equipaB;
            }

            if (idA == 0) {
                for (int j = 0; j < totalJogos; j++) {
                    if (jogos[j].fase == alvo * 2 && jogos[j].slot == (s * 2 - 1)) {
                        idA = jogos[j].id_vencedor;
                        break;
                    }
                }
            }

            if (idB == 0) {
                for (int j = 0; j < totalJogos; j++) {
                    if (jogos[j].fase == alvo * 2 && jogos[j].slot == (s * 2)) {
                        idB = jogos[j].id_vencedor;
                        break;
                    }
                }
            }

            if (idA != 0 && idB != 0) {
                if (idxExistente == -1) {
                    jogos[totalJogos].id_jogo = totalJogos + 1;
                    jogos[totalJogos].fase = alvo;
                    jogos[totalJogos].slot = s;
                    jogos[totalJogos].id_equipaA = idA;
                    jogos[totalJogos].id_equipaB = idB;
                    jogos[totalJogos].id_vencedor = 0;
                    idxExistente = totalJogos;
                    totalJogos++;
                } else {
                    jogos[idxExistente].id_equipaA = idA;
                    jogos[idxExistente].id_equipaB = idB;
                }

                indicesValidos[contadorOpcoes] = idxExistente;
                contadorOpcoes++;

                char nA[50] = "", nB[50] = "";
                for (int e = 0; e < totalEquipas; e++) {
                    if (equipas[e].id == idA) strcpy(nA, equipas[e].nome);
                    if (equipas[e].id == idB) strcpy(nB, equipas[e].nome);
                }

                // Ajuste visual: Se for a Final (alvo == 2), não mostra o número do slot
                if (alvo == 2) {
                    printf("%d: [FINAL] - %s X %s\n", contadorOpcoes, nA, nB);
                } else {
                    printf("%d: [%s - %d] - %s X %s\n", contadorOpcoes, traduzirFase(alvo), s, nA, nB);
                }
            }
        }
    }

    if (contadorOpcoes == 0) {
        printf("\nNão há jogos prontos para registo.\n");
        return;
    }

    int opcao;
    int entradaValida = 0;

    do {
        printf("\nIntroduza a opção do jogo que deseja registar: ");
        
        // 1. Verifica se é um número e se está no intervalo correto
        if (scanf("%d", &opcao) == 1 && opcao >= 1 && opcao <= contadorOpcoes) {
            entradaValida = 1; // Sucesso!
        } else {
            // Se chegou aqui, é porque errou (letra ou número fora do intervalo)
            printf("\n\n                    ⚠️  Opção inválida.\n\n"); // As duas linhas de espaço que pediste
                        
            while(getchar() != '\n'); // Limpa o buffer para não entrar em loop infinito
            // Não fazemos return, logo o ciclo do-while repete
        }
    } while (!entradaValida);

    jogoSendoEditado = indicesValidos[opcao - 1];
    coletarDadosDoConfronto();
}

void coletarDadosDoConfronto(void) {
    int i = jogoSendoEditado;
    int alvo = jogos[i].fase;
    int s = jogos[i].slot;
    char nA[50] = "", nB[50] = "";
    char confirmar;

    // 1. Sincronização de IDs
    if (jogos[i].id_equipaA == 0) {
        for(int j=0; j < totalJogos; j++) {
            if(jogos[j].fase == alvo * 2 && jogos[j].slot == (s * 2 - 1)) {
                jogos[i].id_equipaA = jogos[j].id_vencedor;
                break;
            }
        }
    }
    if (jogos[i].id_equipaB == 0) {
        for(int j=0; j < totalJogos; j++) {
            if(jogos[j].fase == alvo * 2 && jogos[j].slot == (s * 2)) {
                jogos[i].id_equipaB = jogos[j].id_vencedor;
                break;
            }
        }
    }

    // Busca os nomes reais das equipas
    for(int e=0; e < totalEquipas; e++) {
        if(equipas[e].id == jogos[i].id_equipaA) strcpy(nA, equipas[e].nome);
        if(equipas[e].id == jogos[i].id_equipaB) strcpy(nB, equipas[e].nome);
    }

    // Ciclo principal de recolha com confirmação final
    do {
        //Coleta de golos do tempo normal (com trava para negativos)
        do {
            printf("\n---> Digite os golos de %s: ", nA);
            if (scanf("%d", &jogos[i].golosA) != 1) {
                printf("[Erro] Por favor, digite um número válido!\n");
                while(getchar() != '\n'); // Limpa o erro do teclado
                jogos[i].golosA = -1;    // Força a repetição do loop
            } else if(jogos[i].golosA < 0) {
                printf("[Erro] O número de golos não pode ser negativo!\n");
            }
        } while(jogos[i].golosA < 0);

        do {
            printf("---> Digite os golos de %s: ", nB);
            if (scanf("%d", &jogos[i].golosB) != 1) {
                printf("[Erro] Por favor, digite um número válido!\n");
                while(getchar() != '\n'); 
                jogos[i].golosB = -1;
            } else if(jogos[i].golosB < 0) {
                printf("[Erro] O número de golos não pode ser negativo!\n");
            }
        } while(jogos[i].golosB < 0);

        //Lógica de Empate e Pênaltis
        if (jogos[i].golosA == jogos[i].golosB) {
            printf("\nEmpate no tempo regulamentar ou na prorrogação. Registar Pênaltis:\n");
            
            do {
                // Trava para penaltis negativos e letras- Equipa A
                do {
                    printf("---> Pênaltis %s: ", nA);
                    if (scanf("%d", &jogos[i].penaltisA) != 1) {
                        printf("[Erro] Digite um número válido!\n");
                        while(getchar() != '\n');
                        jogos[i].penaltisA = -1;
                    } else if(jogos[i].penaltisA < 0) {
                        printf("[Erro] Valor negativo não permitido!\n");
                    }
                } while(jogos[i].penaltisA < 0);

                // Trava para penaltis negativos e letras - Equipa B
                do {
                    printf("---> Pênaltis %s: ", nB);
                    if (scanf("%d", &jogos[i].penaltisB) != 1) {
                        printf("[Erro] Digite um número válido!\n");
                        while(getchar() != '\n');
                        jogos[i].penaltisB = -1;
                    } else if(jogos[i].penaltisB < 0) {
                        printf("[Erro] Valor negativo não permitido!\n");
                    }
                } while(jogos[i].penaltisB < 0);

                if (jogos[i].penaltisA == jogos[i].penaltisB) {
                    printf("[Erro] Os pênaltis não podem terminar empatados. Repita o registo.\n");
                }
            } while (jogos[i].penaltisA == jogos[i].penaltisB);

            if (jogos[i].penaltisA > jogos[i].penaltisB) 
                jogos[i].id_vencedor = jogos[i].id_equipaA;
            else 
                jogos[i].id_vencedor = jogos[i].id_equipaB;
            
            jogos[i].tipo_decisao = 2; // Pênaltis
        } else {
            // Vencedor no tempo normal
            if (jogos[i].golosA > jogos[i].golosB) 
                jogos[i].id_vencedor = jogos[i].id_equipaA;
            else 
                jogos[i].id_vencedor = jogos[i].id_equipaB;
            
            jogos[i].tipo_decisao = 0; // Normal
            jogos[i].penaltisA = 0;
            jogos[i].penaltisB = 0;
        }

        // --- EXIBIÇÃO DA CONFIRMAÇÃO ---
        int respostaValida = 0;
        do {
            if (jogos[i].tipo_decisao == 2) {
                printf("\nConfirmar: %s %d (%d) X (%d) %d %s? [S/N]: ", 
                       nA, jogos[i].golosA, jogos[i].penaltisA, 
                       jogos[i].penaltisB, jogos[i].golosB, nB);
            } else {
                printf("\nConfirmar: %s %d X %d %s? [S/N]: ", 
                       nA, jogos[i].golosA, jogos[i].golosB, nB);
            }

            while(getchar() != '\n'); // Limpa o buffer
            scanf("%c", &confirmar);

            if (confirmar == 's' || confirmar == 'S' || confirmar == 'n' || confirmar == 'N') {
                respostaValida = 1;
            } else {
                printf("\n⚠️ Resposta inválida! Por favor, digite apenas 'S' para Sim ou 'N' para Não.\n");
            }
        } while (!respostaValida);

        if (confirmar == 'n' || confirmar == 'N') {
            printf("\n[Aviso] Reiniciando introdução de golos para este jogo...\n");
        }

    } while (confirmar == 'n' || confirmar == 'N');

    //Processamento Final
    determinarVencedor(); 
    atualizarEstatisticas();
    gravarResultado(); 

    jogoSendoEditado = -1;
}

void determinarVencedor(void) {
    // Como esta função é chamada logo após introduzirResultado,
    // processa o jogo que foi editado. 
    // O sistema analisa todos os jogos e define o vencedor.
    
    if (jogoSendoEditado == -1) return;
    int i = jogoSendoEditado;

    if (jogos[i].tipo_decisao != 2) {
        if (jogos[i].golosA > jogos[i].golosB)
            jogos[i].id_vencedor = jogos[i].id_equipaA;
        else if (jogos[i].golosB > jogos[i].golosA)
            jogos[i].id_vencedor = jogos[i].id_equipaB;
    
    }

    if (jogos[i].id_vencedor == 0) return;

    for (int e = 0; e < totalEquipas; e++) {
        if (equipas[e].id == jogos[i].id_equipaA && equipas[e].id != jogos[i].id_vencedor) {
            equipas[e].fase_eliminada = jogos[i].fase; // perdeu nesta fase
        }
        if (equipas[e].id == jogos[i].id_equipaB && equipas[e].id != jogos[i].id_vencedor) {
            equipas[e].fase_eliminada = jogos[i].fase; // perdeu nesta fase
        }
    }
    int faseSeguinte = 0;
    if (jogos[i].fase == 16)      faseSeguinte = 8;
    else if (jogos[i].fase == 8)  faseSeguinte = 4;
    else if (jogos[i].fase == 4)  faseSeguinte = 2;
    
    if (faseSeguinte != 0) {
        int slotDestino = (jogos[i].slot + 1) / 2;
        int ladoA = (jogos[i].slot % 2 != 0); 

        for (int j = 0; j < totalJogos; j++) {
            if (jogos[j].fase == faseSeguinte && jogos[j].slot == slotDestino) {
                if (ladoA) {
                    jogos[j].id_equipaA = jogos[i].id_vencedor;
                } else {
                    jogos[j].id_equipaB = jogos[i].id_vencedor;
                }
                
                // Ajuste na mensagem de feedback
                if (faseSeguinte == 2) {
                    printf("[Avanço] Vencedor garantiu lugar na FINAL!\n");
                } else {
                    printf("\n ✅ Vencedor avançou para a Vaga %c do %s %d\n", 
                           ladoA ? 'A' : 'B', traduzirFase(faseSeguinte), slotDestino);
                }
                break;
            }
        }
    } else {
        // Se a faseSeguinte for 0, significa que acabou a Final
        char nomeCampeao[60] = "Desconhecido";
        for(int e=0; e < totalEquipas; e++) {
            if(equipas[e].id == jogos[i].id_vencedor) strcpy(nomeCampeao, equipas[e].nome);
        }
        printf("\n****************************************************************\n");
        printf("                       CAMPEÃO DO TORNEIO: %s   \n", nomeCampeao);
        printf("****************************************************************\n");
    }
}

void atualizarEstatisticas(void) {
    if (jogoSendoEditado == -1) return;

    int i = jogoSendoEditado;
    int idxA = -1, idxB = -1;

    // 1. Localizar os índices das equipas no array global de equipas
    for (int j = 0; j < totalEquipas; j++) {
        if (equipas[j].id == jogos[i].id_equipaA) idxA = j;
        if (equipas[j].id == jogos[i].id_equipaB) idxB = j;
    }

    // 2. Só atualiza se encontrar ambas as equipas (Segurança)
    if (idxA != -1 && idxB != -1) {
        
        /* REGRA IMPORTANTE: 
           Somamos apenas golosA e golosB (Tempo Normal/Prorrogação).
           Os campos penaltisA e penaltisB são ignorados para as estatísticas de saldo,
           servindo apenas para determinar quem avança na árvore.
        */

        // Atualização da Equipa A
        equipas[idxA].golosMarcados += jogos[i].golosA;
        equipas[idxA].golosSofridos += jogos[i].golosB;
        equipas[idxA].saldoGolos = equipas[idxA].golosMarcados - equipas[idxA].golosSofridos;

        // Atualização da Equipa B
        equipas[idxB].golosMarcados += jogos[i].golosB;
        equipas[idxB].golosSofridos += jogos[i].golosA;
        equipas[idxB].saldoGolos = equipas[idxB].golosMarcados - equipas[idxB].golosSofridos;

        // 3. Registo da fase de eliminação (opcional para relatórios)
        // Se a equipa perdeu, marcamos em que fase ela saiu
        if (jogos[i].id_vencedor == jogos[i].id_equipaA) {
            equipas[idxA].vitorias++; // Incrementa vitória para Equipa A
            equipas[idxB].fase_eliminada = jogos[i].fase; // Equipa B eliminada nesta fase

            // Se a fase do jogo era 2 (FINAL), a Equipa A é a campeã!
            if (jogos[i].fase == 2) {
                equipas[idxA].fase_eliminada = 0; // 0 significa CAMPEÃO
            }
        }
        else if (jogos[i].id_vencedor == jogos[i].id_equipaB) {
            equipas[idxB].vitorias++; // Incrementa vitória para Equipa B
            equipas[idxA].fase_eliminada = jogos[i].fase; // Equipa A eliminada nesta fase

            // Se a fase do jogo era 2 (FINAL), a Equipa B é a campeã!
            if (jogos[i].fase == 2) {
                equipas[idxB].fase_eliminada = 0; // 0 significa CAMPEÃO
            }
        }

        printf("\nEstatísticas de saldo de golos atualizadas (Penaltis desconsiderados).\n");
    }
}

void gravarResultado(void) {
    // Usando "w" para sobrescrever o arquivo com o estado atual de TODOS os jogos
    FILE *ficheiro = fopen("data/jogos.txt", "w");
    if (ficheiro == NULL) {
        printf("[Erro] Não foi possível abrir ficheiro para gravação.\n");//ficheiro é o mesmo que data/jogos.txt
        return;
    }

    for (int i = 0; i < totalJogos; i++) {
        fprintf(ficheiro, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", 
                jogos[i].id_jogo,
                jogos[i].fase,
                jogos[i].slot,
                jogos[i].id_equipaA,
                jogos[i].golosA,
                jogos[i].penaltisA,
                jogos[i].golosB,
                jogos[i].penaltisB,
                jogos[i].id_equipaB,
                jogos[i].id_vencedor);
    }

    fclose(ficheiro);
    //printf("\n[Sistema] Estado do campeonato guardado em data/jogos.txt.\n");
}

void carregarJogos(void) {
    // Limpa tudo o que estiver na memória RAM
    totalJogos = 0;
    sorteioRealizado = 0; 

    // Limpa os IDs antigos para não sobrar "lixo" - É OPCIONAL
    for(int i = 0; i < 100; i++) {
        jogos[i].id_equipaA = 0;
        jogos[i].id_equipaB = 0;
        jogos[i].id_vencedor = 0;
    }

    // Tenta abrir o ficheiro
    FILE *f = fopen("data/jogos.txt", "r");
    
    if (f == NULL) {
        // Se não houver ficheiro, as variáveis já estão em 0,
        // então o programa saberá que não houve sorteio.
        return; 
    }

    
    // Se o ficheiro abrir, lemos os dados e atualizamos a flag
    while (fscanf(f, "%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n", 
           &jogos[totalJogos].id_jogo,
           &jogos[totalJogos].fase,
           &jogos[totalJogos].slot,
           &jogos[totalJogos].id_equipaA,
           &jogos[totalJogos].golosA,
           &jogos[totalJogos].penaltisA,
           &jogos[totalJogos].golosB,
           &jogos[totalJogos].penaltisB,
           &jogos[totalJogos].id_equipaB,
           &jogos[totalJogos].id_vencedor) != EOF) {
        
        totalJogos++;
    }

    // Se carregou dados, ativa a flag que permite ver a árvore e registrar resultados
    if (totalJogos > 0) {
        sorteioRealizado = 1; 
        //printf("\n[Sistema] %d jogos recuperados da pasta data.\n", totalJogos);
    }
    fclose(f);
}

/* Funções auxiliares - UC extendidos */

void registarProrrogacao(void) {
    if (jogoSendoEditado == -1) return;

    int i = jogoSendoEditado;
    int extraA, extraB;

    jogos[i].tipo_decisao = 1; // 1 = prorrogação conforme a tua struct

    printf("Golos extra na prorrogação para a primeira equipa: ");
    scanf("%d", &extraA);
    printf("Golos extra na prorrogação para a segunda equipa: ");
    scanf("%d", &extraB);

    jogos[i].golosA += extraA;
    jogos[i].golosB += extraB;

    printf("Golos da prorrogação adicionados ao total.\n");
}

void registarPenaltis(void) {
    if (jogoSendoEditado == -1) return;

    int i = jogoSendoEditado;
    jogos[i].tipo_decisao = 2; // 2 = penaltis conforme a tua struct

    printf("Pênaltis convertidos pela primeira equipa: ");
    scanf("%d", &jogos[i].penaltisA);
    printf("Pênaltis convertidos pela segunda equipa: ");
    scanf("%d", &jogos[i].penaltisB);

    if (jogos[i].penaltisA > jogos[i].penaltisB) {
        jogos[i].id_vencedor = jogos[i].id_equipaA; 
    } else {
        jogos[i].id_vencedor = jogos[i].id_equipaB;
    }
    printf("Vencedor por pênaltis registado.\n");
}

// Função auxiliar para traduzir o número do "alvo" para nome da fase
const char* traduzirFase(int alvo) {
    if (alvo == 16) return "OITAVAS";
    if (alvo == 8)  return "QUARTOS";
    if (alvo == 4)  return "MEIAS";
    if (alvo == 2)  return "FINAL";
    return "FASE DESCONHECIDA";
}

void listarArvoreCompleta(void) {
    if (sorteioRealizado == 0 || totalJogos == 0) {
        printf("\n****************************************************************\n");
        printf("A Tabela ainda não pode ser gerada.\n");
        printf("Por favor, realize primeiro o sorteio (Opção 1).\n");
        printf("****************************************************************\n");
        return; 
    }

    if (totalEquipas < 2) {
        printf("\n[Aviso] Registe pelo menos 2 equipas antes de visualizar a árvore.\n");
        return;
    }

    printf("\n======================= TABELA COMPLETA DO CAMPEONATO =======================\n\n");

    int fases[] = {16, 8, 4, 2}; 
    int faseInicial;
    if (totalEquipas > 8)      faseInicial = 0; // OITAVAS
    else if (totalEquipas > 4) faseInicial = 1; // QUARTOS
    else if (totalEquipas > 2) faseInicial = 2; // MEIAS
    else                       faseInicial = 3; // FINAL

    for (int f = faseInicial; f < 4; f++) {
        int alvo = fases[f];
        int numSlots = alvo / 2;

        for (int s = 1; s <= numSlots; s++) {
            int idx = -1;
            for (int j = 0; j < totalJogos; j++) {
                if (jogos[j].fase == alvo && jogos[j].slot == s) {
                    idx = j;
                    break;
                }
            }

            // --- TRATAMENTO DE ISENTOS ---
            if (idx == -1 && f < 3) {
                int faseProx = fases[f+1];
                int slotProx = (s + 1) / 2;
                int eLadoA = (s % 2 != 0);
                int isentaNaVaga = 0;
                for (int j = 0; j < totalJogos; j++) {
                    if (jogos[j].fase == faseProx && jogos[j].slot == slotProx) {
                        if ((eLadoA && jogos[j].id_equipaA != 0) || (!eLadoA && jogos[j].id_equipaB != 0))
                            isentaNaVaga = 1;
                    }
                }
                if (isentaNaVaga) {
                    printf("[%s - %d] - EQUIPA AVANÇA PARA A FASE SEGUINTE\n", traduzirFase(alvo), s);
                    continue;
                }
            }

            if (alvo == 2) printf("[FINAL] - ");
            else printf("[%s - %d] - ", traduzirFase(alvo), s);

            char nA[60] = "", nB[60] = "";
            char placarA[15] = "", placarB[15] = "";

            // --- LÓGICA CORRIGIDA PARA NOMES (EQUIPA A) ---
            int idA = (idx != -1) ? jogos[idx].id_equipaA : 0;
            if (idA != 0) {
                for(int e=0; e<totalEquipas; e++) if(equipas[e].id == idA) strcpy(nA, equipas[e].nome);
            } else if (f > faseInicial) {
                // Se ID é 0, procura vencedor do jogo anterior
                int ja = -1;
                for(int j=0; j<totalJogos; j++) if(jogos[j].fase == alvo*2 && jogos[j].slot == (s*2-1)) { ja = j; break; }
                if (ja != -1 && jogos[ja].id_vencedor != 0) {
                    for(int e=0; e<totalEquipas; e++) if(equipas[e].id == jogos[ja].id_vencedor) strcpy(nA, equipas[e].nome);
                } else sprintf(nA, "VENCEDOR %s %d", traduzirFase(alvo*2), s*2-1);
            } else strcpy(nA, "VAGA");
            
            // --- LÓGICA CORRIGIDA PARA NOMES (EQUIPA B) ---
            int idB = (idx != -1) ? jogos[idx].id_equipaB : 0;
            if (idB != 0) {
                for(int e=0; e<totalEquipas; e++) if(equipas[e].id == idB) strcpy(nB, equipas[e].nome);
            } else if (f > faseInicial) {
                int jb = -1;
                for(int j=0; j<totalJogos; j++) if(jogos[j].fase == alvo*2 && jogos[j].slot == (s*2)) { jb = j; break; }
                if (jb != -1 && jogos[jb].id_vencedor != 0) {
                    for(int e=0; e<totalEquipas; e++) if(equipas[e].id == jogos[jb].id_vencedor) strcpy(nB, equipas[e].nome);
                } else sprintf(nB, "VENCEDOR %s %d", traduzirFase(alvo*2), s*2);
            } else strcpy(nB, "VAGA");

            // --- FORMATAÇÃO DOS PLACARES ---
            if (idx != -1 && jogos[idx].id_vencedor != 0) {
                sprintf(placarA, "(%d)", jogos[idx].golosA);
                sprintf(placarB, "(%d)", jogos[idx].golosB);
            } else {
                // Só mostra parênteses se já tivermos nomes de equipas reais (não começam por "VENCEDOR")
                if (strncmp(nA, "VENCEDOR", 8) != 0 && strncmp(nB, "VENCEDOR", 8) != 0 && 
                    strcmp(nA, "VAGA") != 0 && strcmp(nB, "VAGA") != 0) {
                    strcpy(placarA, "(  )");
                    strcpy(placarB, "(  )");
                }
            }

            printf("%s %s X %s %s\n", nA, placarA, nB, placarB);
        }
    }


}


