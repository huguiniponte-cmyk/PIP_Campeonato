#ifndef JOGOS_H
#define JOGOS_H



// Estrutura para armazenar os dados de um jogo
typedef struct {
    int id_jogo;            // ID único global do jogo
    int fase;               // 16, 8, 4, 2
    int slot;               // posição dentro da fase (1..8, 1..4, etc)

    int id_equipaA;         // ID REAL da equipa A (0 se ainda não definido)
    int id_equipaB;         // ID REAL da equipa B (0 se ainda não definido)

    int golosA;
    int golosB;
    int penaltisA;
    int penaltisB;

    int tipo_decisao;       // 0 = normal, 1 = prorrogação, 2 = penaltis
    int id_vencedor;        // ID REAL da equipa vencedora (0 = ainda não decidido)

    int proximo_jogo;       // índice do jogo da fase seguinte (-1 se for final)
    char lado_proximo;      // 'A' ou 'B'
    
} Jogo;

void menuGerirJogos(void);

void registarJogos(void);

// Casos de uso incluídos
void gerarJogosDaFase(void);
void introduzirResultado(void);
void determinarVencedor(void);
void atualizarEstatisticas(void);
void carregarJogos(void);
void gravarResultado(void);
void salvarDados(void);
void listarArvoreCompleta(void);

// Casos de uso estendidos
void sortearEquipaIsenta(void);
void sortearConfrontos(void);
void registarProrrogacao(void);
void registarPenaltis(void);

// Dados globais 
extern Jogo jogos[100];
extern int totalJogos;
extern int sorteioRealizado; // Adicione esta linha aqui

#endif

