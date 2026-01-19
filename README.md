# Sistema de Gestão de Campeonatos de Futebol – LEGA

Projeto desenvolvido em C no âmbito do PIP 2025/2026.
A aplicação permite gerir equipas, realizar sorteios, registar jogos eliminatórios e gerar estatísticas completas de um campeonato de futebol, com persistência em ficheiros.
Aplicação em modo texto, compatível com Linux / WSL.

## Funcionalidades Principais

- Gestão completa de equipas (criar, listar, remover)
- Sorteio automático do campeonato (com tratamento de isentos)
- Registo de resultados:
  - Tempo regulamentar
  - Decisão por pênaltis
- Geração automática da árvore do torneio
- Classificação final e ranking geral
- Estatísticas detalhadas:
  - Melhor ataque
  - Melhor defesa
  - Eficiência (golos por jogo)
  - Relatório completo do campeão
- Persistência de dados em ficheiros .txt
- Reset total do sistema

## Compilação e Execução

Compilar:
make

Executar:
make run

Limpar ficheiros e binários:
make clean

## Estrutura do Projeto

/src        → Código fonte (.c)
/include    → Ficheiros de cabeçalho (.h)
/data       → Dados persistentes
             ├─ equipas.txt
             └─ jogos.txt
Makefile
README.md

## Manual do Utilizador

1 - Gestão de Equipas
Criar nova equipa
Listar equipas registadas
Remover equipas (bloqueado após início do campeonato)

2 - Gestão de Jogos
Registar resultados
Registar decisão por pênaltis
Listar jogos por fase

3 - Classificação
Tabela ordenada automaticamente com base nos critérios definidos.

4 - Estatísticas
Ranking geral
Top Performers (ataque, defesa, eficiência)
Relatório detalhado do campeão

5 - Guardar Dados
Grava todas as equipas e jogos nos ficheiros

6 - Carregar Dados
Lê dados previamente guardados

7 - Limpar Dados
Reset total do sistema (memória + ficheiros)

0 - Sair
Encerra a aplicação

## Regras da Classificação

A ordenação das equipas é feita segundo os seguintes critérios (por ordem de prioridade):
- Campeão (fase_eliminada = 0)
- Número de vitórias
- Saldo de golos (golos marcados − golos sofridos)
- Golos marcados
- Golos sofridos
- Sorteio aleatório em caso de empate total

## Lógica do Torneio

Sistema eliminatório
Suporte para 2 a 16 equipas
Tratamento automático de equipas isentas
Avanço automático de vencedores entre fases:
Oitavas
Quartos
Meias
Final

## Equipa de Desenvolvimento

Airon
Hugo
Annaisa

## Observações Finais

Este projeto foi desenvolvido com foco em organização modular, validação de dados de entrada, clareza de apresentação, robustez e reutilização de código.
Cumpre todos os requisitos funcionais e não funcionais definidos para o PIP.
