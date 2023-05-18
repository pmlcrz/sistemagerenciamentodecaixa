#include <stdio.h>

struct Transacao {
    char tipo;  // 'E' para entrada, 'S' para saída
    float valor;
};

void registrarTransacao(struct Transacao transacoes[], int *numTransacoes) {
    char tipo;
    float valor;

    printf("Digite o tipo de transacao ('E' para entrada, 'S' para saida): ");
    scanf(" %c", &tipo);

    printf("Digite o valor da transacao: ");
    scanf("%f", &valor);

    transacoes[*numTransacoes].tipo = tipo;
    transacoes[*numTransacoes].valor = valor;

    (*numTransacoes)++;
}

float calcularSaldo(struct Transacao transacoes[], int numTransacoes) {
    float saldo = 0.0;

    for (int i = 0; i < numTransacoes; i++) {
        if (transacoes[i].tipo == 'E') {
            saldo += transacoes[i].valor;
        } else if (transacoes[i].tipo == 'S') {
            saldo -= transacoes[i].valor;
        }
    }

    return saldo;
}

void exibirRelatorio(struct Transacao transacoes[], int numTransacoes) {
    printf("\nRelatorio de Transacoes:\n");
    printf("-------------------------\n");

    for (int i = 0; i < numTransacoes; i++) {
        printf("Tipo: %c\tValor: %.2f\n", transacoes[i].tipo, transacoes[i].valor);
    }

    printf("-------------------------\n");
    printf("Saldo atual: %.2f\n", calcularSaldo(transacoes, numTransacoes));
}

void salvarTransacoes(struct Transacao transacoes[], int numTransacoes) {
    FILE *arquivo = fopen("transacoes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < numTransacoes; i++) {
        fprintf(arquivo, "%c %.2f\n", transacoes[i].tipo, transacoes[i].valor);
    }

    fclose(arquivo);
}

void carregarTransacoes(struct Transacao transacoes[], int *numTransacoes) {
    FILE *arquivo = fopen("transacoes.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo nao encontrado. Nenhuma transacao carregada.\n");
        return;
    }

    *numTransacoes = 0;
    char tipo;
    float valor;

    while (fscanf(arquivo, " %c %f", &tipo, &valor) == 2) {
        transacoes[*numTransacoes].tipo = tipo;
        transacoes[*numTransacoes].valor = valor;
        (*numTransacoes)++;
    }

    fclose(arquivo);
}

int main() {
    struct Transacao transacoes[100];
    int numTransacoes = 0;
    char opcao;

    carregarTransacoes(transacoes, &numTransacoes);

    do {
        printf("\nGerenciamento de Caixa\n");
        printf("-------------------------\n");
        printf("1 - Registrar transacao\n");
        printf("2 - Exibir relatorio\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                registrarTransacao(transacoes, &numTransacoes);
                salvarTransacoes(transacoes, numTransacoes);
                break;
            case '2':
                exibirRelatorio(transacoes, numTransacoes);
                break;
            case '0':
                printf("Encerrando o programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != '0');

    return 0;
}
