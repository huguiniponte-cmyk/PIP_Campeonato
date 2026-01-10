#ifndef EQUIPAS_H
#define EQUIPAS_H

typedef struct
{
    int id;
    char nome[50];
    int isenta; // 0 = joga nesta fase, 1 = isenta (avança direto) - Adicionado por Annaisa
    int golosMarcados;    // Necessário para armazenar 
    int golosSofridos;    // os dados acumulados no 
    int saldoGolos;       // campeonato 
    int fase_eliminada; // necessário para definir a situação da equipa (fase de grupo, campeão...) para a classificação
    int vitorias;// Útil para (classificação final) - Adicionado por Annaisa
}Equipa;

extern Equipa equipas[16];
extern int totalEquipas;
extern int proximoID;



void menuGerirEquipas();
void gerirEquipas();
void cadastrarEquipa();
void apagarEquipa();
void salvarDados(); //Declação da função para que o lega.c também a conheça

void carregarDados(void);

void limparTela(void); //Adicionado por Annaisa

#endif 
