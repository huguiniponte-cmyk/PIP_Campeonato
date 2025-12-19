#ifndef JOGOS_H
#define JOGOS_H



typedef struct {
    int id;
    int equipaA; // ID da equipa da A
    int equipaB; // ID da equipa B
    int golosA;
    int golosB;
} Jogo;

extern Jogo jogos[100];
extern int totalJogos;


#endif