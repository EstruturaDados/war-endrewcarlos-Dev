#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
typedef struct
{
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército do território
    int tropas;      // Quantidade de tropas no território
} Territorio;       // Cria um novo tipo chamado Territorio

// Declaração de um vetor para armazenar 5 territórios
Territorio territorios[5];

int main() {

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("--------------------------\n");
        printf("Vamos Cadastrar os 5 territorios iniciais\n");
        printf("Cadastrando o Territorio %d\n", i + 1);

        // Lendo o nome do Territorio (sem espaços)
        printf("Nome do Territorio: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Lendo a cor do exército (sem espaços)
        printf("Cor do Exercito (EX:AZUL, VERDE...): ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Lendo número de tropas do território
        printf("Numero de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
    }

    // Exibição dos territórios cadastrados
    for (int i = 0; i < 5; i++) {
        printf("--------------------------\n");
        printf("Territorio %d\n", i + 1);

        // Mostra o nome do território
        printf("Nome do Territorio: %s\n", territorios[i].nome);

        // Mostra a cor do exército
        printf("Cor do Exercito (EX:AZUL, VERDE...): %s\n", territorios[i].cor);

        // Mostra a quantidade de tropas
        printf("Numero de tropas: %d\n", territorios[i].tropas);
    }

    // Fim
    return 0;
}