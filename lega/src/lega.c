#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "equipas.h"
#include "jogos.h"
#include "estatisticas.h"
#include <time.h>

extern int totalEquipas;
extern int proximoID;
extern Equipa equipas[16];
// Definição da função logo no início - Adicionado por Annaisa
void limparTela(void) {
    // No Linux/WSL, o comando de sistema para limpar o terminal é "clear"
    system("clear");
}


//PROJETO: Sistema de Gestão de Campeonatos
//AUTOR: Airon, Hugo, Annaisa
//DATA: 2025
//DESCRIÇÃO: Sistema para cadastro de equipas, registro de jogos
//           e cálculo de classificação em campeonatos de futebol

void menuPrincipal()
{


    srand(time(NULL));
    limparTela();
printf("\n");
    printf("                                 ┓ ┏┓┏┓┏┓\n");
    printf("                                 ┃ ┣ ┃┓┣┫\n");
    printf("                                 ┗┛┗┛┗┛┛┗\n\n"); 


    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║     ██▄  ▄██ ██████ ███  ██ ██  ██   ██ ███  ██ ██ ▄█████ ██ ▄████▄ ██         ║\n");
    printf("║     ██ ▀▀ ██ ██▄▄   ██ ▀▄██ ██  ██   ██ ██ ▀▄██ ██ ██     ██ ██▄▄██ ██         ║\n");
    printf("║     ██    ██ ██▄▄▄▄ ██   ██ ▀████▀   ██ ██   ██ ██ ▀█████ ██ ██  ██ ██████     ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n\n");
    printf("                          ┎━─━─━─━─━─━─━─━─━─━─━─━─━─━─┒                          \n");
    printf("                            1 - GESTÃO DE EQUIPAS                                 \n");
    printf("                            2 - GESTÃO DE JOGOS                                   \n"); //Alterado por Annaisa de REGISTO para GESTÃO
    printf("                            3 - CLASSIFICAÇÃO                                     \n");
    printf("                            4 - ESTATÍSTICAS                                      \n");
    printf("                            5 - SALVAR DADOS                                      \n");
    printf("                            6 - CARREGAR DADOS                                    \n");
    printf("                            7 - LIMPAR DADOS                                      \n");
    printf("                            0 - SAIR                                              \n");
    printf("                          ┖━─━─━─━─━─━─━─━─━─━─━─━─━─━─┚                          \n\n");
    printf("                          Selecione uma opção ➤  ");
}


void resetTotal(void) {

    int confirma;
    printf("\n\n                           ⚠️  AVISO DE RESET TOTAL ⚠️\n\n");
    printf("                           Isto apagará TODOS OS DADOS!\n\n");
    do {
        printf("                         Tens a certeza? [1] SIM / [0] NÃO: ");
        scanf("%d", &confirma);
        while (getchar() != '\n');
     if (confirma != 1 && confirma != 0)
    {
        printf("\n                         ⚠️  Digite apenas 1 (SIM) ou 0 (NÃO).\n\n");
    }
} while (confirma != 0 && confirma != 1);

    if (confirma == 1) {
        // 1. Apagar ficheiros físicos
        remove("data/equipas.txt");
        remove("data/jogos.txt");

        // 2. Limpar memória RAM (Variáveis globais das equipas)

        totalEquipas = 0;
        proximoID = 1;

        // 3. Limpar memória RAM (Variáveis globais dos jogos)
        extern int totalJogos;
        extern int sorteioRealizado;
        totalJogos = 0;
        sorteioRealizado = 0;

    //adicionado por Hugo para estatisticas.
        for (int i = 0; i < 16; i++) {
            equipas[i].golosMarcados = 0;   
            equipas[i].golosSofridos = 0;
            equipas[i].saldoGolos = 0;
            equipas[i].fase_eliminada = -1;
            equipas[i].isenta = 0;
            strcpy(equipas[i].nome, ""); // Limpa também o nome
        }

        printf("\n\n");
        printf("                             ✅ Sistema reiniciado!\n");
        sleep(2);
    }
    else {
        printf("\n                               Operação cancelada!\n");
        sleep(1);
    }
}
// Inicia o programa e controla fluxo principal
int main()

{
    carregarDados();
    carregarJogos();

    int opcaoMenu;

    do {
        menuPrincipal();
        while (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 0 || opcaoMenu > 7)
        {
            menuPrincipal();
            printf("\n\n                          Digite uma opção válida! (0 a 7)\n\n");
            printf("                          Selecione uma opção: ");
            while (getchar() != '\n');
        }
        printf("\n\n");

        switch (opcaoMenu)
        {
        case 0:

            printf("                          Finalizando o programa...\n");
            sleep(2);
            limparTela();
            printf("\n\n                          Pressione Enter para continuar...\n\n");

            while (getchar() != '\n');
            getchar();
            break;

        case 1:
            gerirEquipas();
            break;
        case 2: //Adicionado por Annaisa
            menuGerirJogos(); // Chama a função que criámos no jogos.c
            break;

        case 3:
            listarClassificacao();
            break;
        case 4:
            menuEstatisticas();
            break;
        case 5:
            gravarResultado();
            salvarDados();
            break;
        case 6:
            carregarDados();
            carregarJogos(); // Recarrega os jogos também para sincronizar
            break;
        case 7:
            resetTotal();
            break;
        }
    } while (opcaoMenu != 0);

    return 0;
}
