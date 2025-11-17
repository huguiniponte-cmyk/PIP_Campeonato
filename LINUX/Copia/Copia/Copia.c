#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//PROJETO: Sistema de Gestão de Campeonatos
//AUTOR: Airon, Hugo, Annaisa
//DATA: 2025
//DESCRIÇÃO: Sistema para cadastro de equipas, registro de jogos
//           e cálculo de classificação em campeonatos de futebol

//Estrutura para armazenar dados de uma equipa
typedef struct
{
    int id;
    char nome[50];
}Equipa;

//Array de 50 times e contador de cadastros
Equipa equipas[50];
int totalEquipas = 0;

void salvarDados()
{
    FILE* arquivo = fopen("equipe.txt", "w");
    if (arquivo == NULL)
    {
        printf("                       ❌ ERRO AO CRIAR ARQUIVO!\n");
        return;
    }
    for (int i = 0; i < totalEquipas; i++)
    {
        fprintf(arquivo, "%d | %s\n", equipas[i].id, equipas[i].nome);
    }
    fclose(arquivo);

    printf("\n\n                        ✅ %d equipas salvas em 'equipe.txt'.\n\n", totalEquipas);
    sleep(3); // Alterado de Sleep(3000) para sleep(3)
}

//limpa a tela
void limparTela()
{
    system("clear"); // Alterado de "cls" para "clear"
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
    printf("                          Selecione uma opção ➤  ");
}

// Gerencia todas as operações de equipas
void menuGerirEquipas()
{
    limparTela();
    printf("                            ╔═══════════════════════════╗\n");
    printf("                                  GESTÃO DE EQUIPAS      \n");
    printf("                            ╚═══════════════════════════╝\n\n\n");
    printf("                              ┎━─━─━━──━─━─━─━─━─━─━─━┒                          \n");
    printf("                                1 - CADASTRAR EQUIPA                             \n");
    printf("                                2 - LISTAR EQUIPAS                               \n");
    printf("                                0 - VOLTAR                                       \n");
    printf("                              ┖━──━─━─━─━─━─━─━─━─━─━─┚                          \n\n");
}

// Cadastra uma nova equipa no campeonato
void cadastrarEquipa()
{
    char equipaNome[50];
    int opcaoConf;
    int tentarNovamente = 1;
    limparTela();

    while (tentarNovamente)
    {
        printf("\n\n");
        printf("                            ╔══════════════════════════╗\n");
        printf("                                      CADASTRO          \n");
        printf("                            ╚══════════════════════════╝\n\n\n");
        printf("                             NOME DA EQUIPA: ");

        while (getchar() != '\n'); // Limpa buffer
        fgets(equipaNome, 50, stdin);
        equipaNome[strcspn(equipaNome, "\n")] = 0;

        printf("\n                             ➤  %s\n\n", equipaNome);
        printf("                  [1] CONFIRMAR    [2] DIGITAR NOVAMENTE   [0] VOLTAR\n\n");
        printf("                             ➤  ");

        while (scanf("%d", &opcaoConf) != 1 || opcaoConf < 0 || opcaoConf > 2)
        {
            limparTela();
            printf("\n\n");
            printf("                            ╔══════════════════════════╗\n");
            printf("                                      CADASTRO          \n");
            printf("                            ╚══════════════════════════╝\n\n\n");
            printf("                             NOME DA EQUIPA: %s\n", equipaNome);
            printf("\n                             ➤  %s\n\n", equipaNome);
            printf("                             Selecione uma opção válida!\n\n");
            printf("                             [1] Confirmar [0] Voltar\n\n");
            printf("                             ➤  ");
            while (getchar() != '\n');
        }

        if (totalEquipas < 50)
        {
            if (opcaoConf == 1)
            {
                equipas[totalEquipas].id = totalEquipas + 1;
                strcpy(equipas[totalEquipas].nome, equipaNome);
                totalEquipas++;
                printf("\n\n                          ✅ Equipa cadastrada com sucesso!\n");
                printf("                                      AGUARDE....\n");
                sleep(2); // Alterado de Sleep(2000) para sleep(2)
                tentarNovamente = 0;
            }
            else if (opcaoConf == 2)
            {
                limparTela();
                continue;
            }
            else {
                tentarNovamente = 0;
                printf("Cancelando...\n");
                sleep(2); // Alterado de Sleep(2000) para sleep(2)
            }
        }
        else
        {
            printf("Não é possível adicionar mais times!\n");
        }
    }
}

// Mostra menu de gestão de equipas
void gerirEquipas()
{
    int opcaoGest;
    do {
        menuGerirEquipas();
        printf("                              Selecione uma opção ➤  ");

        while (scanf("%d", &opcaoGest) != 1 || opcaoGest < 0 || opcaoGest > 2)
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
        case 2:
            limparTela();
            printf("\n\n");
            printf("                            ╔═══════════════════════════╗\n");
            printf("                                 EQUIPAS CADASTRADAS     \n");
            printf("                            ╚═══════════════════════════╝\n\n\n");

            if (totalEquipas == 0) {
                printf("                             Nenhuma equipa cadastrada.\n");
            }
            else {
                for (int i = 0; i < totalEquipas; i++) {
                    printf("                              %d ➤  %s\n", equipas[i].id, equipas[i].nome);
                }
            }

            printf("\n\n                             Pressione Enter para voltar...");
            while (getchar() != '\n');
            getchar();
            break;

        case 0:
            printf("Saindo.\n");
        }
    } while (opcaoGest != 0);
}

// Inicia o programa e controla fluxo principal
int main() {
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
        printf("\n\n");

        switch (opcaoMenu)
        {
        case 0:
            printf("                             Finalizando o programa...\n");
            sleep(2);
            limparTela();
            printf("\n\n                          Pressione Enter para continuar...\n\n");
          
            while (getchar() != '\n');
            getchar(); 
            break;

        case 1:
            gerirEquipas();
            break;
        case 2:
            limparTela();
            printf("REGISTRO DE JOGOS - Em desenvolvimento\n");
            sleep(2);
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
        }
    } while (opcaoMenu != 0);

    return 0;
}