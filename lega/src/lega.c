#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "equipas.h"
#include "jogos.h"

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

//Estrutura para armazenar dados de uma equipa 



//Array de 50 times e contador de cadastros

//função para salvar o projeto quando selecionarmos a opção 6 na main()
//abre o arquito txt selecionado e com "w" escreve a lista dos times com a funcionalidade  "for"


//
//função para carregar dados (é ativa automaticamente quando se inicia o programa na main())
//para escolher o ficheiro é necessario editar na primeira linha, com "r" ele lê o que está no arquivo





//criei funções para os menus de navegação onde irá chamar a partir da seleção do usuário
// Exibe o menu principal do sistema
void menuPrincipal()
{
    limparTela();

    printf("   ██████   ███████ ███████ ████████  ██████  ██████      ██████  ███████          ██  ██████   ██████   ██████  ███████\n");
    printf("  ██        ██      ██         ██    ██    ██ ██   ██     ██   ██ ██               ██ ██    ██ ██       ██    ██ ██     \n");
    printf("  ██   ███  █████   ███████    ██    ██    ██ ██████      ██   ██ █████            ██ ██    ██ ██   ███ ██    ██ ███████\n");
    printf("  ██    ██  ██           ██    ██    ██    ██ ██   ██     ██   ██ ██          ██   ██ ██    ██ ██    ██ ██    ██      ██\n");
    printf("   ██████   ███████ ███████    ██     ██████  ██   ██     ██████  ███████      █████   ██████   ██████   ██████  ███████\n\n\n\n");

    printf("╔════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║     ██▄  ▄██ ██████ ███  ██ ██  ██   ██ ███  ██ ██ ▄█████ ██ ▄████▄ ██         ║\n");
    printf("║     ██ ▀▀ ██ ██▄▄   ██ ▀▄██ ██  ██   ██ ██ ▀▄██ ██ ██     ██ ██▄▄██ ██         ║\n");
    printf("║     ██    ██ ██▄▄▄▄ ██   ██ ▀████▀   ██ ██   ██ ██ ▀█████ ██ ██  ██ ██████     ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════════════╝\n\n\n");
    printf("                          ┎━─━─━─━─━─━─━─━─━─━─━─━─━─━─┒                          \n");
    printf("                            1 - GESTÃO DE EQUIPAS                                 \n");
    printf("                            2 - GESTÃO DE JOGOS                                   \n"); //Alterado por Annaisa de REGISTO para GESTÃO
    printf("                            3 - CÁLCULAR CLASSIFICAÇÃO                            \n");
    printf("                            4 - ESTATÍSTICAS                                      \n");
    printf("                            5 - SALVAR                                            \n");
    printf("                            6 - CARREGAR DADOS                                    \n");
    printf("                            7 - RESET TOTAL (LIMPAR TUDO)                         \n");
    printf("                            0 - SAIR                                              \n");
    printf("                          ┖━─━─━─━─━─━─━─━─━─━─━─━─━─━─┚                          \n\n");
    printf("                          Selecione uma opção ➤  ");
}


void resetTotal(void) {
    int confirma;
    printf("\n\n                        ⚠️  AVISO DE RESET TOTAL ⚠️\n");
    printf("                         Isto apagará TODAS as equipas e jogos!\n");
    printf("                           Tem a certeza? [1] SIM / [0] NÃO: ");
    scanf("%d", &confirma);

    if (confirma == 1) {
        // 1. Apagar ficheiros físicos
        remove("data/equipas.txt");
        remove("data/jogos.txt");

        // 2. Limpar memória RAM (Variáveis globais das equipas)
        extern int totalEquipas;
        extern int proximoID;
        totalEquipas = 0;
        proximoID = 1;

        // 3. Limpar memória RAM (Variáveis globais dos jogos)
        extern int totalJogos;
        extern int sorteioRealizado;
        totalJogos = 0;
        sorteioRealizado = 0;

        printf("\n\n               ✅ Sistema reiniciado do zero absoluto!\n");
        sleep(2);
    } else {
        printf("\n                           Operação cancelada.\n");
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
            printf("                               Selecione uma opção: ");
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

        //case 2: 
            //limparTela();
            //printf("REGISTRO DE JOGOS - Em desenvolvimento\n");
            //sleep(2);
            //break;
        case 2: //Adicionado por Annaisa
            menuGerirJogos(); // Chama a função que criámos no jogos.c
            break;

        case 3:
            printf("VER CLASSIFICAÇÃO\n");
            break;
        case 4:
            printf("ESTATÍSTICAS\n");
            break;
        case 5:
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





// precisamos ver se o campeonato é em forma de fae de grupos
//jogos fora de casa jogos dentro de casa
//combinar as equipas com os jogos
//jogos tem que ter id junto com jogos
//equipas com id, todos int
//diagrama de objetos
//escrever o resultado no id do jogo, numeros de gols do time dentro de casa e de fora
//salvar os times num documento e resultados jogos em outro jogos.txt equipas.txt
//criar uma sctruct para jogos?
//selecionar de forma random nos arrays
//pode ser de eliminação direto pra já (mais facil)
//igual a copa do mundo por exemplo
//muito mais facil
