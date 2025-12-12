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


typedef struct
{
    Jogo jogos[100];          // suporte para até 100 jogos (ajuste conforme fase)
    int totalJogos = 0;
    int proximoIDJogo = 1;
    int id;
    int idEquipaCasa;
    int idEquipaFora;
    int golosCasa;
    int golosFora;
    int Finalizado; //Campo finalizado permite filtrar só jogos válidos nas estatísticas
    char data[11]; //facilita uma eventual explroacao de jornadas ou cronologia
    char Equipa[50];
}Jogos;


//Array de 50 times e contador de cadastros
Equipa equipas[50];
int totalEquipas = 0;
int proximoID = 1;

//função para salvar o projeto quando selecionarmos a opção 6 na main()
void salvarDados()
{
    FILE* arquivo = fopen("equipe.txt", "w");  //abre o arquivo e escreve
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
//função para carregar dados (é ativa automaticamente quando se inicia o programa na main())
void carregarDados()
{
    FILE* arquivo = fopen("equipe.txt", "r"); //abre o arquivo e le
    if (arquivo == NULL)
    {
        printf("                       ❌ FICHEIRO NÃO ENCONTRADO!\n");
        return;
    }


    char linha[100];
    char nomeTime[50];
    int id;
    int linhasCarregadas = 0;


    while (fgets(linha, sizeof(linha), arquivo) != NULL)

        if (sscanf(linha, "%d | %49[^\n]", &id, nomeTime) == 2)
        {
            if (totalEquipas < 50)
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

// Gerencia todas as operações de equipas
void menuGerirEquipas()
{
    limparTela();
    printf("                            ╔═══════════════════════════╗\n");
    printf("                                  GESTÃO DE EQUIPAS      \n");
    printf("                            ╚═══════════════════════════╝\n\n\n");
    printf("                              ┎━─━─━━──━─━─━─━─━─━─━─━┒                          \n");
    printf("                                1 - CADASTRAR EQUIPA                             \n");
    printf("                                2 - APAGAR EQUIPA                               \n");
    printf("                                3 - LISTAR EQUIPAS                               \n");
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
                equipas[totalEquipas].id = proximoID;
                strcpy(equipas[totalEquipas].nome, equipaNome);
                totalEquipas++;
                proximoID++;

                printf("\n\n                          ✅ Equipa cadastrada com sucesso!\n");
                printf("                                      AGUARDE....\n");
                sleep(2);

                tentarNovamente = 0;
            }
            else if (opcaoConf == 2)
            {
                limparTela();
                continue;
            }
            else {
                tentarNovamente = 0;
                printf("                                     Cancelando...\n");
                sleep(2); // Alterado de Sleep(2000) para sleep(2)
            }
        }
        else
        {
            printf("Não é possível adicionar mais times!\n");
        }
    }
}

void apagarEquipa()
{

    if (totalEquipas == 0)
    {
        printf("                       ❌ Nenhuma equipa cadastrada!\n\n");
        return;
    }

    int removerId;
    int posicaoId;

    do {
        limparTela();
        {
            printf("\n\n");
            printf("                            ╔══════════════════════════╗\n");
            printf("                                   REMOVER EQUIPA       \n");
            printf("                            ╚══════════════════════════╝\n\n");
            printf("                              [0] VOLTAR           \n\n");
            printf("                              Equipas Cadastradas:      \n\n");

            for (int i = 0; i < totalEquipas; i++)
            {
                printf("                              %d ➤  %s\n", equipas[i].id, equipas[i].nome);
            }




            printf("\n\n                      Informe o ID da equipa que deseja remover: ");
            scanf("%d", &removerId);
            printf("\n\n");

            if (removerId == 0)
            {
                return;
            }
            posicaoId = -1;


            for (int i = 0; i < totalEquipas; i++)
            {
                if (equipas[i].id == removerId)
                {

                    posicaoId = i;
                    break;
                }
            }
            if (posicaoId == -1)
            {

                printf("                            ❌ Equipa não encontrada!\n\n");
                sleep(2);
                printf("                        Pressione Enter para tentar novamente....\n\n");
                while (getchar() != '\n');
                getchar();
            }

        }
    } while (posicaoId == -1);


    int confirmar;

    printf("\n                                   REMOVER EQUIPA?\n\n");

    printf("                              [1] CONFIRMAR  [0] VOLTAR\n\n");
    printf("                             ➤  ");
    scanf("%d", &confirmar);
    printf("\n\n");

    if (confirmar == 1)
    {
        for (int i = posicaoId; i < totalEquipas - 1; i++)
        {
            equipas[i] = equipas[i + 1];
        }
        totalEquipas--;

        printf("\n\n                          ✅ equipa removida com sucesso.\n\n");
    }
    else {
        printf("                             ❌ Cancelado!\n\n");
    }
    sleep(2);

}
    

// Mostra menu de gestão de equipas
void gerirEquipas()
{
    int opcaoGest;
    do {
        menuGerirEquipas();
        printf("                              Selecione uma opção ➤  ");

        while (scanf("%d", &opcaoGest) != 1 || opcaoGest < 0 || opcaoGest > 3)
        {
            menuGerirEquipas();
            printf("                              Digite uma opção válida!\n\n");
            while (getchar() != '\n');
            continue;
            printf("                              Selecione uma opção ➤  ");
            while (getchar() != '\n');
        }


        switch (opcaoGest)
        {
        case 1:
            cadastrarEquipa();
            break;
        case 2:
            apagarEquipa();
            break;
        case 3:
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


