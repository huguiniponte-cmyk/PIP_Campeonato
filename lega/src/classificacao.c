#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "classificacao.h"
#include "equipas.h"
#include "jogos.h" 

void shuffle(Equipa* arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Equipa tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

void listarClassificacao() {


    Equipa ranking[16];
    memcpy(ranking, equipas, sizeof(Equipa) * totalEquipas);

    // Bubble sort adaptado para desempates
    for (int i = 0; i < totalEquipas - 1; i++) {
        for (int j = 0; j < totalEquipas - i - 1; j++) {
            int trocar = 0;

            // 1. Vitorias (mais é melhor)
            if (ranking[j].vitorias < ranking[j + 1].vitorias) trocar = 1;
            // 2. Saldo de golos
            else if (ranking[j].vitorias == ranking[j + 1].vitorias) {
                if (ranking[j].saldoGolos < ranking[j + 1].saldoGolos) trocar = 1;
                // 3. Gols marcados
                else if (ranking[j].saldoGolos == ranking[j + 1].saldoGolos) {
                    if (ranking[j].golosMarcados < ranking[j + 1].golosMarcados) trocar = 1;
                    // 4. Gols sofridos (menos é melhor)
                    else if (ranking[j].golosMarcados == ranking[j + 1].golosMarcados) {
                        if (ranking[j].golosSofridos > ranking[j + 1].golosSofridos) trocar = 1;
                        // 5. Se tudo igual, sorteio aleatório
                        else if (ranking[j].golosSofridos == ranking[j + 1].golosSofridos) {
                            if (rand() % 2 == 0) trocar = 1;
                        }
                    }
                }
            }

            if (trocar) {
                Equipa temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }

    // Impressão
    printf("\n\n");
    printf("                            ╔═══════════════════════════╗\n");
    printf("                                    CLASSIFICAÇÃO        \n");
    printf("                            ╚═══════════════════════════╝\n\n\n");
    printf("            %-5s | %-20s | %-15s | %-10s | %-5s | %-5s | %-5s\n",
        "POS", "EQUIPA", "ESTADO", "SALDO", "V", "GM", "GS");
    printf("\n");

    for (int i = 0; i < totalEquipas; i++) {
        char estado[30];

        if (ranking[i].fase_eliminada == -1)
            strcpy(estado, "--"); // ou "Fase de Grupos" se preferir
        else if (ranking[i].fase_eliminada == 0)
            strcpy(estado, "CAMPEÃO 🏆");
        else if (ranking[i].fase_eliminada == 2)
            strcpy(estado, "Finalista");
        else if (ranking[i].fase_eliminada == 4)
            strcpy(estado, "Meias-Finais");
        else if (ranking[i].fase_eliminada == 8)
            strcpy(estado, "Quartos-Finais");
        else if (ranking[i].fase_eliminada == 16)
            strcpy(estado, "Oitavas-Finais");

        printf("            %-5d | %-20s | %-15s"" | %-10d | % -5d | % -5d | % -5d\n",
            i + 1,
            ranking[i].nome,
            estado,
            ranking[i].saldoGolos,
            ranking[i].vitorias,
            ranking[i].golosMarcados,
            ranking[i].golosSofridos);
    }

    printf("\n                           Pressione ENTER para voltar...");
    getchar(); // Limpa buffer
    getchar(); // Espera tecla
}
