void listarArvoreCompleta(void) {
    if (sorteioRealizado == 0 || totalJogos == 0) {
        printf("\n****************************************************************\n");
        printf("A árvore ainda não pode ser gerada.\n");
        printf("Por favor, realize primeiro o sorteio (Opção 1).\n");
        printf("****************************************************************\n");
        return; 
    }

    if (totalEquipas < 2) {
        printf("\n[Aviso] Registe pelo menos 2 equipas antes de visualizar a árvore.\n");
        return;
    }

    printf("\n======================= ÁRVORE COMPLETA DO CAMPEONATO =======================\n");

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
    printf("==============================================\n");

}
