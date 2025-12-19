#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "equipas.h"
#include "jogos.h"


//PROJETO: Sistema de Gestão de Campeonatos
//AUTOR: Airon, Hugo, Annaisa
//DATA: 2025
//DESCRIÇÃO: Sistema para cadastro de equipas, registro de jogos
//           e cálculo de classificação em campeonatos de futebol

//Estrutura para armazenar dados de uma equipa 



//Array de 50 times e contador de cadastros

//função para salvar o projeto quando selecionarmos a opção 6 na main()
//abre o arquito txt selecionado e com "w" escreve a lista dos times com a funcionalidade  "for"
void salvarDados()
{
    FILE* arquivo = fopen("data/equipas.txt", "w");  //abre o arquivo e escreve
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

    printf("\n\n                        ✅ %d equipas salvas em 'data/equipas.txt'.\n\n", totalEquipas);
    sleep(3); // Alterado de Sleep(3000) para sleep(3)
}

//
//função para carregar dados (é ativa automaticamente quando se inicia o programa na main())
//para escolher o ficheiro é necessario editar na primeira linha, com "r" ele lê o que está no arquivo
void carregarDados()
{
    FILE* arquivo = fopen("data/equipas.txt", "r"); //abre o arquivo e le
    if (arquivo == NULL)
    {
        printf("                       ❌ FICHEIRO NÃO ENCONTRADO!\n\n");
        printf("                            CRIANDO ARQUIVO...\n");
        sleep(2);
        return;
    }


    char linha[100];
    char nomeTime[50];
    int id;
    int linhasCarregadas = 0;


    while (fgets(linha, sizeof(linha), arquivo) != NULL)

        if (sscanf(linha, "%d | %49[^\n]", &id, nomeTime) == 2)
        {
            if (totalEquipas < 16)
            {
                equipas[totalEquipas].id = id;
                strcpy(equipas[totalEquipas].nome, nomeTime);
                totalEquipas++;
                linhasCarregadas++;

                if (id >= proximoID)
                {
                    proximoID = id + 1;
                }
            }
        }
    fclose(arquivo);
    if (linhasCarregadas == 1)
    {
        printf("\n\n\n                          ✅ %d equipa carregada!\n", linhasCarregadas);
    }
    else if (linhasCarregadas >= 2)
    {
        printf("\n\n\n                          ✅ %d equipas carregadas!\n", linhasCarregadas);

    }
    else
    {
        printf("                                ❗ Ficheiro vazio.\n");

    }
    sleep(2);



}





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
    printf("                            2 - REGISTRO DE JOGOS                                 \n");
    printf("                            3 - CÁLCULAR CLASSIFICAÇÃO                            \n");
    printf("                            4 - ESTATÍSTICAS                                      \n");
    printf("                            5 - SALVAR                                            \n");
    printf("                            6 - CARREGAR DADOS                                    \n");
    printf("                            0 - SAIR                                              \n");
    printf("                          ┖━─━─━─━─━─━─━─━─━─━─━─━─━─━─┚                          \n\n");
    printf("                          Selecione uma opção ➤  ");
}



// Inicia o programa e controla fluxo principal
int main()

{
    carregarDados();

    int opcaoMenu;

    do {
        menuPrincipal();
        while (scanf("%d", &opcaoMenu) != 1 || opcaoMenu < 0 || opcaoMenu > 6)
        {
            menuPrincipal();
            printf("\n\n                          Digite uma opção válida! (0 a 6)\n\n");
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
        case 6:
            carregarDados();
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

