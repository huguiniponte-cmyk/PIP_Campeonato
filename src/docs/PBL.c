
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h> 
#include <string.h>


//PROJETO: Sistema de Gestão de Campeonatos
//AUTOR: Airon, Hugo, Annaisa
//DATA: 2025
//DESCRIÇÃO: Sistema para cadastro de equipas, registro de jogos
//           e cálculo de classificação em campeonatos de futebol




 //Estrutura para armazenar dados de uma equipa
 // - id: identificador único da equipa (1-50)
 // - nome: nome da equipa (máximo 49 caracteres)
typedef struct
{
    int id;
    char nome[50];
}Time;
//Array de 50 times e contador de cadastros
Time times[50];
int totalTimes = 0;

//limpa a tela
void limparTela()
{
    system("cls");
}

//criei funções para os menus de navegação

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
    printf("                          ┎━─━─━─━─━─━─━─━─━─━─━─━─━─━─┒                         \n");
    printf("                            1 - GESTÃO DE EQUIPAS                             \n");
    printf("                            2 - REGISTRO DE JOGOS                            \n");
    printf("                            3 - CÁLCULAR CLASSIFICAÇÃO                             \n");
    printf("                            4 - ESTATÍSTICAS                                 \n");
    printf("                            5 - SALVAR                                       \n");
    printf("                            0 - SAIR                                         \n");
    printf("                          ┖━─━─━─━─━─━─━─━─━─━─━─━─━─━─┚                          \n\n");
    printf("                            Selecione uma opção ➤  ");
}
//// Gerencia todas as operações de equipas
void menuGerirEquipas()
{
    limparTela();

    printf("                            ╔═══════════════════════════╗\n");
    printf("                                  GESTÃO DE EQUIPAS      \n");
    printf("                            ╚═══════════════════════════╝\n\n\n");
    printf("                              ┎━─━─━━──━─━─━─━─━─━─━─━┒                          \n");
    printf("                                1 - CADASTRAR EQUIPA                             \n");
    printf("                                0 - VOLTAR                                         \n");
    printf("                              ┖━──━─━─━─━─━─━─━─━─━─━─┚                          \n\n");


}
// Cadastra uma nova equipa no campeonato

// Executa ações de gestão (cadastrar, etc)
void cadastrarEquipa()
{
    char timeNome[50];
    int opcaoConf;

    limparTela();

    printf("\n\n");
    printf("                            ╔══════════════════════════╗\n");
    printf("                                      CADASTRO          \n");
    printf("                            ╚══════════════════════════╝\n\n\n");
    printf("                             NOME DA EQUIPA: ");
    while (getchar() != '\n');
    fgets(timeNome, 50, stdin);
    timeNome[strcspn(timeNome, "\n")] = 0;

    printf("\n                             ➤  %s\n\n", timeNome);
    printf("                   [1] CONFIRMAR    [2] DIGITAR NOVAMENTE   [0] VOLTAR\n\n");
    printf("                             ➤  ");
    while (scanf("%d", &opcaoConf) != 1 || opcaoConf < 0 || opcaoConf > 2)
    {
        limparTela();
        printf("\n\n");
        printf("                            ╔══════════════════════════╗\n");
        printf("                                      CADASTRO          \n");
        printf("                            ╚══════════════════════════╝\n\n\n");
        printf("                             NOME DA EQUIPA: %s\n", timeNome);
        printf("\n                             ➤  %s\n\n", timeNome);
        printf("                             Selecione uma opção válida!\n\n");
        printf("                             [1] Confirmar [0] Voltar\n\n");
        printf("                             ➤  ");
        while (getchar() != '\n');
    }
    if (totalTimes < 50)
    {
        if (opcaoConf == 1)
        {
            times[totalTimes].id = totalTimes + 1;
            strcpy(times[totalTimes].nome, timeNome);
            totalTimes++;
            printf("\n\n                          ✅ Equipa cadastrada com sucesso!\n");
            printf("                                      AGUARDE....\n");
            Sleep(4000);
        }
        else if (opcaoConf == 2)
        {
            limparTela();
            cadastrarEquipa();
        }
        else {
            printf("Cancelando...\n");
            Sleep(2000);
        }
    }
    else
    {
        printf("Não é possível adicionar mais times!\n");
    }


}
// Mostra menu de gestão de equipas
void gerirEquipas()
{
    int opcaoGest;
    menuGerirEquipas();
    printf("                              Selecione uma opção ➤  ");
    while (scanf("%d", &opcaoGest) != 1 || opcaoGest < 0 || opcaoGest > 1)
    {
        menuGerirEquipas();
        printf("                              Digite uma opção válida!\n\n");
        printf("                              Selecione uma opção ➤  ");
        while (getchar() != '\n');

    }
    switch (opcaoGest)
    {
    case 1:
        cadastrarEquipa();
        break;
    case 0:
        printf("Saindo.\n");
    }


}

// Inicia o programa e controla fluxo principal
int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);



    int opcaoMenu;
    do {
        menuPrincipal();

        while (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 0 || opcaoMenu > 5)
        {

            menuPrincipal();
            printf("\n\n                          Digite uma opção válida! (0 a 5)\n\n");
            printf("                          Selecione uma opção: ");
            while (getchar() != '\n');

        }
        printf("\n\n\n");

        switch (opcaoMenu)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            gerirEquipas();
            break;
        case 2:
            printf("REGISTRO DE JOGOS!\n");
            break;
        case 3:
            printf("VER CLASSIFICAÇÃO\n");
            break;
        case 4:
            printf("ESTATÍSTICAS\n");
            break;
        case 5:
            printf("SALVAR\n");
            break;








        }
    } while (opcaoMenu != 0);

    return 0;
}