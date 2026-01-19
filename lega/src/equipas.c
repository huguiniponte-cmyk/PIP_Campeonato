#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "equipas.h"
#include "jogos.h"
//PROJETO: Sistema de

Equipa equipas[16];
int totalEquipas = 0;
int proximoID = 1;

extern int sorteioRealizado;


void menuGerirEquipas()
{
    limparTela();
    printf("\n\n");
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
        printf("                  [1] CONFIRMAR    [2] DIGITAR NOVAMENTE   [0] CANCELAR\n\n");
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
            printf("                  [1] CONFIRMAR    [2] DIGITAR NOVAMENTE   [0] CANCELAR\n\n");
            printf("                             ➤  ");
            while (getchar() != '\n');
        }




        if (totalEquipas < 16)
        {
            if (opcaoConf == 1)
            {
                equipas[totalEquipas].id = proximoID;
                strcpy(equipas[totalEquipas].nome, equipaNome);
                equipas[totalEquipas].vitorias = 0;
                equipas[totalEquipas].golosMarcados = 0;
                equipas[totalEquipas].golosSofridos = 0;
                equipas[totalEquipas].saldoGolos = 0;
                equipas[totalEquipas].fase_eliminada = -1; // ainda não jogou
                equipas[totalEquipas].isenta = 0;

                totalEquipas++;
                proximoID++;

                printf("\n\n                           ✅ Equipa cadastrada com sucesso!\n");
                sleep(1);

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
                sleep(2);
            }
            
        }
        else
        {

            tentarNovamente = 0;
            printf("\n\n");
            printf("                        Não é possível adicionar mais equipas!\n");
            sleep(2);
        }

    }


}



//apaga a equipa selecionada
void apagarEquipa()
{

    if (totalEquipas == 0)
    {
        printf("\n\n");
        printf("                              ❌ Nenhuma equipa cadastrada!\n\n");
        sleep(2);
        return;
    }

    if (sorteioRealizado == 1)
    {
        printf("\n\n");
        printf("               ⚠️ Não é possível apagar equipas com o campeonato em andamento! \n");
        sleep(2);
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
            while (getchar() != '\n');
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
                getchar();
            }

        }
    } while (posicaoId == -1);


    int confirmar;

    int valido = 0;
    do {
        printf("\n                                   REMOVER EQUIPA?\n\n");
        printf("                              [1] CONFIRMAR  [0] VOLTAR\n\n");
        printf("                             ➤  ");

        if (scanf("%d", &confirmar) != 1 || (confirmar != 0 && confirmar != 1)) {
            while (getchar() != '\n'); // limpa buffer
            printf("\n\n                           ⚠️ Opção inválida! Tente novamente.\n");
            sleep(1);                   // espera 1 segundo
                          // limpa a tela
            // aqui você pode reimprimir o menu de remover equipas se quiser manter visível
        }
        else if (confirmar == 1)
        {
            valido = 1;                 // entrada correta
            while (getchar() != '\n');

            for (int i = posicaoId; i < totalEquipas - 1; i++)
            {
                equipas[i] = equipas[i + 1];
            }
            totalEquipas--;



            printf("\n\n                           ✅ Equipa removida com sucesso.\n\n");
            sleep(2);
        
 
        }
    } while (!valido);

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
            printf("                              Selecione uma opção ➤  ");
            while (getchar() != '\n');
            continue;


        }


        switch (opcaoGest)
        {
        case 1:
            if (totalEquipas >= 16 && opcaoGest == 1)
            {
                printf("\n\n");
                printf("               ⚠️ Não é possível adicionar mais equipas (Capacidade Máxima: 16) \n");
                printf("                      Apague uma equipa ou inicie um novo campeonato!\n\n");
                sleep(4);
                return;
            }
            else {
                cadastrarEquipa();
            }
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

void salvarDados(void) {
    FILE *f = fopen("data/teste.txt", "w"); // "w" para sobrescrever o ficheiro antigo
    if (f == NULL) {
        printf("\n[Erro] Não foi possível abrir data/equipas.txt para gravar!\n");
        return;
    }

    for (int i = 0; i < totalEquipas; i++) {
        // Usando EXATAMENTE os nomes da sua struct:
        // id;nome;isenta;golosMarcados;golosSofridos;saldoGolos;fase_eliminada
        fprintf(f, "%d;%s;%d;%d;%d;%d;%d;%d\n",
                equipas[i].id, 
                equipas[i].nome, 
            equipas[i].vitorias,
                equipas[i].isenta, 
                equipas[i].golosMarcados, 
                equipas[i].golosSofridos, 
                equipas[i].saldoGolos,
                equipas[i].fase_eliminada);
    }
    printf("\n\n");
    printf("                         ✅ Dados salvos com sucesso!\n\n");
    sleep(2);

    fclose(f);
}

void carregarDados(void) {
    FILE *f = fopen("data/teste.txt", "r");
    if (f == NULL) {
        printf("\n[Aviso] Ficheiro data/equipas.txt não encontrado. Iniciando vazio.\n");
        sleep(1);
        return;
    }


    totalEquipas = 0;
    // Lê os 7 campos exatamente como gravados no salvarDados
    // O formato %49[^;] lê o nome até encontrar o próximo ponto e vírgula
    while (fscanf(f, "%d;%49[^;];%d;%d;%d;%d;%d;%d\n",
           &equipas[totalEquipas].id, 
           equipas[totalEquipas].nome,
        &equipas[totalEquipas].vitorias,
           &equipas[totalEquipas].isenta, 
           &equipas[totalEquipas].golosMarcados, 
           &equipas[totalEquipas].golosSofridos, 
           &equipas[totalEquipas].saldoGolos,
           &equipas[totalEquipas].fase_eliminada) != EOF) {
        
        totalEquipas++;
    }

    fclose(f);

    // Ajusta o proximoID para não duplicar IDs já existentes
    if (totalEquipas > 0) {
        proximoID = equipas[totalEquipas - 1].id + 1;
    }
        printf("\n                       ✅ Dados carregados com sucesso!\n");
        sleep(2);
    

}


