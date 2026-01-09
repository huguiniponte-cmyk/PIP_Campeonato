#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para a função sleep
#include "equipas.h"
#include "jogos.h"
#include "estatisticas.h"

// Importar variáveis globais dos outros módulos
extern Equipa equipas[16];
extern int totalEquipas;
extern Jogo jogos[100];
extern int totalJogos;

// --- FUNÇÕES AUXILIARES (Internas) ---

// Conta quantos jogos uma equipa realizou (para calcular média e exibir na tabela)
int contarJogosRealizados(int idEquipa) {
    int contador = 0;
    for (int i = 0; i < totalJogos; i++) {
        // Verifica se o jogo já aconteceu (tem vencedor ou golos registados)
        if (jogos[i].id_vencedor != 0 || (jogos[i].golosA > 0 || jogos[i].golosB > 0)) {
            if (jogos[i].id_equipaA == idEquipa || jogos[i].id_equipaB == idEquipa) {
                contador++;
            }
        }
    }
    return contador;
}

// Estrutura auxiliar apenas para ordenação
typedef struct {
    int id_original;
    char nome[50];
    int gMarcados;
    int gSofridos;
    int saldo;
    int jogosJogados;
    float eficiencia; // golos por jogo
} StatsAux;

// --- IMPLEMENTAÇÃO DAS FUNCIONALIDADES ---

void exibirRankingGeral() {
    if (totalEquipas == 0) { 
        printf("\nSem equipas cadastradas.\n"); 
        sleep(1);
        return; 
    }
    
    // 1. Criar array temporário com os dados
    StatsAux lista[16];
    for(int i=0; i<totalEquipas; i++) {
        lista[i].id_original = equipas[i].id;
        strcpy(lista[i].nome, equipas[i].nome);
        lista[i].gMarcados = equipas[i].golosMarcados;
        lista[i].gSofridos = equipas[i].golosSofridos;
        lista[i].saldo = equipas[i].saldoGolos;
        lista[i].jogosJogados = contarJogosRealizados(equipas[i].id);
        
        if(lista[i].jogosJogados > 0)
            lista[i].eficiencia = (float)lista[i].gMarcados / lista[i].jogosJogados;
        else 
            lista[i].eficiencia = 0.0;
    }

    // 2. Ordenar por Saldo (Bubble Sort)
    for(int i=0; i<totalEquipas-1; i++) {
        for(int j=0; j<totalEquipas-i-1; j++) {
            int troca = 0;
            if (lista[j].saldo < lista[j+1].saldo) troca = 1;
            else if (lista[j].saldo == lista[j+1].saldo && lista[j].gMarcados < lista[j+1].gMarcados) troca = 1;

            if(troca) {
                StatsAux temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    // 3. Exibir Tabela Formatada e Melhorada
    limparTela();
    printf("\n===============================================================================\n");
    printf("                                RANKING GERAL                                  \n");
    printf("===============================================================================\n");
    
    // Cabeçalho com larguras fixas:
    // # (3) | Equipa (25) | Jogos (5) | GM (3) | GS (3) | DIF (3) | Média (5)
    printf("%-3s | %-25s | %-5s | %-3s | %-3s | %-3s | %-5s\n", 
           "#", "EQUIPA", "JOGOS", "GM", "GS", "DIF", "MEDIA");
    
    printf("-------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < totalEquipas; i++) {
        char nomeFormatado[26];
        strncpy(nomeFormatado, lista[i].nome, 22); // Copia os primeiros 22 caracteres
        
        // Se o nome for muito longo, adiciona "..."
        if (strlen(lista[i].nome) > 22) {
            nomeFormatado[22] = '\0';
            strcat(nomeFormatado, "...");
        } else {
            nomeFormatado[22] = '\0'; // Garante terminação se for menor
            strcpy(nomeFormatado, lista[i].nome);
        }

        // CORREÇÃO DE ALINHAMENTO AQUI:
        // Ajustei os espaços nos %d para baterem certo com o tamanho do cabeçalho
        printf("%02d  | %-25s |  %2d   | %2d  | %2d  | %3d |  %4.2f\n", 
            i + 1,
            nomeFormatado,         
            lista[i].jogosJogados, 
            lista[i].gMarcados,    
            lista[i].gSofridos,    
            lista[i].saldo,        
            lista[i].eficiencia    
        );
    }
    printf("===============================================================================\n");
    printf("Pressione Enter para voltar...");
    while(getchar() != '\n'); 
    getchar();
} 

void exibirTopPerformers() {
    if (totalEquipas < 2) { 
        printf("\nDados insuficientes para estatísticas.\n"); 
        sleep(1); 
        return; 
    }

    // Usamos ponteiros para ordenar sem mover os dados originais
    Equipa* ptrs[16];
    for(int i=0; i<totalEquipas; i++) ptrs[i] = &equipas[i];

    limparTela();
    printf("\n🏆 TOP PERFORMERS 🏆\n\n");

    // --- TOP 3 ATAQUES (Mais Golos Marcados) ---
    for(int i=0; i<totalEquipas-1; i++) 
        for(int j=0; j<totalEquipas-i-1; j++) 
            if(ptrs[j]->golosMarcados < ptrs[j+1]->golosMarcados) {
                Equipa* temp = ptrs[j]; ptrs[j] = ptrs[j+1]; ptrs[j+1] = temp;
            }

    printf("🔥 MELHORES ATAQUES (Golos Marcados):\n");
    for(int i=0; i<3 && i<totalEquipas; i++) {
        printf("   %d. %-15s (%d golos)\n", i+1, ptrs[i]->nome, ptrs[i]->golosMarcados);
    }
    printf("\n");

    // --- TOP 3 DEFESAS (Menos Golos Sofridos) ---
    // Reinicia ponteiros
    for(int i=0; i<totalEquipas; i++) ptrs[i] = &equipas[i];
    // Ordena (crescente de golos sofridos - quem sofreu menos é melhor)
    for(int i=0; i<totalEquipas-1; i++) 
        for(int j=0; j<totalEquipas-i-1; j++) 
            if(ptrs[j]->golosSofridos > ptrs[j+1]->golosSofridos) {
                Equipa* temp = ptrs[j]; ptrs[j] = ptrs[j+1]; ptrs[j+1] = temp;
            }

    printf("🛡️  MELHORES DEFESAS (Menos Golos Sofridos):\n");
    for(int i=0; i<3 && i<totalEquipas; i++) {
        printf("   %d. %-15s (%d sofridos)\n", i+1, ptrs[i]->nome, ptrs[i]->golosSofridos);
    }
    printf("\n");

    // --- EQUIPA MAIS EFICIENTE (Média) ---
    float maiorMedia = -1.0;
    int idMelhor = -1;
    char nomeMelhor[50];

    for(int i=0; i<totalEquipas; i++) {
        int jogos = contarJogosRealizados(equipas[i].id);
        if(jogos > 0) {
            float media = (float)equipas[i].golosMarcados / jogos;
            if(media > maiorMedia) {
                maiorMedia = media;
                idMelhor = equipas[i].id;
                strcpy(nomeMelhor, equipas[i].nome);
            }
        }
    }

    printf("⚡ EQUIPA MAIS EFICIENTE (Golos/Jogo):\n");
    if(idMelhor != -1)
        printf("   ➤  %-15s com média de %.2f golos/jogo\n", nomeMelhor, maiorMedia);
    else
        printf("   (Sem jogos suficientes)\n");

    printf("\n\nPressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();
}

void exibirResumoCampeao() {
    int idCampeao = 0;
    
    // 1. Verificar se existe vencedor da FINAL (Fase 2)
    for(int i=0; i<totalJogos; i++) {
        if(jogos[i].fase == 2 && jogos[i].id_vencedor != 0) {
            idCampeao = jogos[i].id_vencedor;
            break;
        }
    }

    limparTela();
    if(idCampeao == 0) {
        printf("\n⚠️  O CAMPEONATO AINDA NÃO TEM VENCEDOR!\n");
        printf("Realize todos os jogos até à Final para ver este relatório.\n");
        sleep(3);
        return;
    }

    // Buscar dados do campeão
    char nome[50];
    int gM=0, gS=0, penaltisVencidos=0;
    
    for(int i=0; i<totalEquipas; i++) {
        if(equipas[i].id == idCampeao) {
            strcpy(nome, equipas[i].nome);
            gM = equipas[i].golosMarcados;
            gS = equipas[i].golosSofridos;
            break;
        }
    }

    printf("\n⭐ RESUMO DO CAMPEÃO: %s ⭐\n", nome);
    printf("==================================================\n");
    printf("📊 Estatísticas Totais:\n");
    printf("   • Golos Marcados: %d\n", gM);
    printf("   • Golos Sofridos: %d\n", gS);
    printf("   • Saldo Final:    %d\n", gM - gS);
    printf("==================================================\n");
    printf("📍 Caminho até à Glória:\n\n");

    // Varre as fases da maior para a menor (16 -> 8 -> 4 -> 2)
    int fases[] = {16, 8, 4, 2};
    for(int f=0; f<4; f++) {
        for(int i=0; i<totalJogos; i++) {
            if(jogos[i].fase == fases[f] && 
              (jogos[i].id_equipaA == idCampeao || jogos[i].id_equipaB == idCampeao)) {
                
                char adversario[50] = "Isento/Desconhecido";
                int idAdv = (jogos[i].id_equipaA == idCampeao) ? jogos[i].id_equipaB : jogos[i].id_equipaA;
                
                // Pega nome do adversário
                if(idAdv != 0) {
                    for(int k=0; k<totalEquipas; k++) 
                        if(equipas[k].id == idAdv) strcpy(adversario, equipas[k].nome);
                } else {
                    strcpy(adversario, "(Isento)");
                }

                int golosFavor, golosContra;
                if(jogos[i].id_equipaA == idCampeao) {
                    golosFavor = jogos[i].golosA;
                    golosContra = jogos[i].golosB;
                } else {
                    golosFavor = jogos[i].golosB;
                    golosContra = jogos[i].golosA;
                }

                printf("   [%s] vs %s\n", 
                       (fases[f]==16?"Oitavas": (fases[f]==8?"Quartos": (fases[f]==4?"Meias  ":"FINAL  "))), 
                       adversario);
                
                if(jogos[i].tipo_decisao == 2) {
                    printf("      ↳ Empate %d-%d (Venceu nos Pênaltis)\n", golosFavor, golosContra);
                    penaltisVencidos++;
                } else {
                    printf("      ↳ Vitória por %d-%d\n", golosFavor, golosContra);
                }
            }
        }
    }
    printf("\n🏆 Jogos decididos nos pênaltis: %d\n", penaltisVencidos);
    printf("\nPressione Enter para voltar...");
    while(getchar() != '\n');
    getchar();
}

void menuEstatisticas() {
    int opcao;
    do {
        limparTela();
        printf("╔══════════════════════════════════╗\n");
        printf("║       CENTRAL DE ESTATÍSTICAS    ║\n");
        printf("╚══════════════════════════════════╝\n\n");
        printf("  1. Ranking Geral (Saldo/Pontos)\n");
        printf("  2. Top Performers (Ataque/Defesa)\n");
        printf("  3. Relatório do Campeão\n");
        printf("  0. Voltar\n\n");
        printf("  Selecione ➤ ");
        
        while (scanf("%d", &opcao) != 1) {
            while(getchar() != '\n'); // Limpa buffer
            printf("  Opção inválida! Tente novamente ➤ ");
        }

        switch(opcao) {
            case 1: exibirRankingGeral(); break;
            case 2: exibirTopPerformers(); break;
            case 3: exibirResumoCampeao(); break;
            case 0: break;
            default: 
                printf("Opção inválida!\n"); 
                sleep(1);
        }
    } while(opcao != 0);

}

void limparEstatisticas(void) {
    // Acede à variável global equipas e limpa os campos numéricos
    for (int i = 0; i < 16; i++) {
        equipas[i].golosMarcados = 0;
        equipas[i].golosSofridos = 0;
        equipas[i].saldoGolos = 0;
        equipas[i].fase_eliminada = 0;
        
    }
    printf(" >> Estatísticas internas reiniciadas.\n");
}

