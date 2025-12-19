#ifndef EQUIPAS_H
#define EQUIPAS_H

typedef struct
{
    int id;
    char nome[50];
}Equipa;

extern Equipa equipas[16];
extern int totalEquipas;
extern int proximoID;



void menuGerirEquipas();
void gerirEquipas();
void cadastrarEquipa();
void apagarEquipa();

// Mostra menu de gestão de equipas



#endif 