#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct
{
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército do território
    int tropas;      // Quantidade de tropas no território
} Territorio;

// Função que simula o ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor){

    int dadoAtacante = rand() % 6 + 1;   // rola dado atacante (1 a 6)
    int dadoDefensor = rand() % 6 + 1;   // rola dado defensor (1 a 6)

    printf("\n%s atacou %s!\n", atacante->nome, defensor->nome);
    printf("O Território atacante %s rolou o dado: %d\n", atacante->nome, dadoAtacante);
    printf("O Território defensor %s rolou o dado: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("%s venceu %s!!\n", atacante->nome, defensor->nome);

        defensor->tropas = atacante->tropas / 2;     // metade das tropas do atacante vão para o defensor
        strcpy(defensor->cor, atacante->cor);        // defensor muda para a cor do atacante
    } 
    else {
        // Defensor resiste
        printf("%s defendeu com sucesso!!\n\n", defensor->nome);
        atacante->tropas--; // atacante perde 1 tropa
    }
}

// Função que libera memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {

    int quantidade;

    srand(time(NULL)); // garante que os números aleatórios mudem a cada execução

    printf("Quantos Territorios deseja Cadastrar? ");
    scanf("%d", &quantidade);
    getchar();
    
    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));
    
    // Cadastro dos territórios
    for (int i = 0; i < quantidade; i++) {
        printf("--------------------------\n");
        printf("Cadastrando o Territorio %d\n", i + 1);

        // Nome do território
        printf("Nome do Territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        // Cor do exército
        printf("Cor do Exercito (EX: AZUL, VERDE...): ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        // Número de tropas
        printf("Numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }

    int opcao;
    do {
        printf("\n----- MENU -----\n");
        printf("1 - Listar territorios\n");
        printf("2 - Atacar\n");
        printf("3 - Sair\n");
        scanf("%d", &opcao);
        getchar();
    
        if (opcao == 1) {   
            // Exibe todos os territórios cadastrados
            for (int i = 0; i < quantidade; i++) {
                printf("--------------------------\n");
                printf("Territorio %d\n", i + 1);
                printf("Nome: %s\n", mapa[i].nome);
                printf("Cor: %s\n", mapa[i].cor);
                printf("Tropas: %d\n", mapa[i].tropas);
            }
        }
        else if (opcao == 2) {
            int atacante, defensor;

            printf("Escolha o territorio atacante (1 a %d): ", quantidade);
            scanf("%d", &atacante);
            printf("Escolha o territorio defensor (1 a %d): ", quantidade);
            scanf("%d", &defensor);
            getchar();

            if (atacante == defensor) {
                printf("Não é possível atacar o mesmo território!\n");
            }
            else if (strcmp(mapa[atacante-1].cor, mapa[defensor-1].cor) == 0) {
                // impede ataque entre territórios da mesma cor
                printf("Não é possível atacar um território do mesmo exército!\n");
            }
            else {
                atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
            }
        }
    } while(opcao != 3);
    
    // Libera memória alocada
    liberarMemoria(mapa);

    printf("\nPrograma encerrado. Obrigado por jogar!\n");

    return 0;
}