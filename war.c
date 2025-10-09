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
    int dadoAtacante = rand() % 6 + 1;   // rola dado do atacante (1 a 6)
    int dadoDefensor = rand() % 6 + 1;   // rola dado do defensor (1 a 6)

    // Mostra resultado do ataque
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

// Vetor de missões possíveis
char* missoes[]= {
    "Eliminar todas as tropas da cor vermelha",
    "Eliminar todas as tropas da cor verde",
    "Eliminar todas as tropas da cor amarela",
    "Eliminar todas as tropas da cor marrom",
    "Ter pelo menos 10 tropas em um território",
};

// Função para atribuir uma missão aleatória ao jogador
void atribuirMissao(char* destino, char* missao[5], int totaldeMissao){
    int indice = rand() % totaldeMissao;
    strcpy(destino, missao[indice]);
}

// Função que verifica se a missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0; // missão não cumprida
            }
        }
        return 1; // missão cumprida
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor verde") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor amarela") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "amarela") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (strcmp(missao, "Eliminar todas as tropas da cor marrom") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "marrom") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    else if (strcmp(missao, "Ter pelo menos 10 tropas em um território") == 0){
        for (int i = 0; i < tamanho; i++){
            if (mapa[i].tropas >=10 ) return 1; // missão cumprida
        }
    }
    return 0; // missão não cumprida
}

int main() {
    int quantidade;

    srand(time(NULL)); // inicializa números aleatórios

    // Pergunta ao usuário quantos territórios serão cadastrados
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

    // Atribui missão aleatória ao jogador
    char* missaojogador = calloc (100, sizeof(char));
    atribuirMissao(missaojogador, missoes, 5);
    printf("\nSua missão secreta: %s\n", missaojogador);

    int opcao;
    do {
        // Menu principal
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

            // Seleção de territórios para ataque
            printf("Escolha o territorio atacante (1 a %d): ", quantidade);
            scanf("%d", &atacante);
            printf("Escolha o territorio defensor (1 a %d): ", quantidade);
            scanf("%d", &defensor);
            getchar();

            if (atacante == defensor) {
                printf("Não é possível atacar o mesmo território!\n");
            }
            else if (strcmp(mapa[atacante-1].cor, mapa[defensor-1].cor) == 0) {
                printf("Não é possível atacar um território do mesmo exército!\n");
            }
            else {
                atacar(&mapa[atacante - 1], &mapa[defensor - 1]); // realiza ataque
            }

            // Verifica se missão foi cumprida após o ataque
            if (verificarMissao(missaojogador, mapa, quantidade)){
                printf("\nParabéns! Você cumpriu sua missão e venceu o jogo!!!\n");
                break;
            }
        }
    } while(opcao != 3);
    
    // Libera memória alocada
    liberarMemoria(mapa);
    free(missaojogador);

    printf("\nPrograma encerrado. Obrigado por jogar!\n");

    return 0;
}