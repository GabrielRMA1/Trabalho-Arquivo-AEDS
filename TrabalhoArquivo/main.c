#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#define TAMANHO_FIB 64

void gerar_fibonacci(long long int *fib) {
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < TAMANHO_FIB; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
}

bool eh_primo(long long int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    for (long long int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void criar_arquivo_entrada() {
    FILE *arquivo_entrada = fopen("valores_entrada.txt", "w");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    printf("Digite os valores de entrada. Digite -1 para acabar:\n");

    int valor;
    while (1) {
        printf("Digite um valor: ");
        scanf("%d", &valor);
        if (valor == -1)
            break;
        fprintf(arquivo_entrada, "%d\n", valor);
    }

    fclose(arquivo_entrada);
}

void testar_numeros() {
    long long int fib[TAMANHO_FIB];
    gerar_fibonacci(fib);

    FILE *arquivo_entrada = fopen("valores_entrada.txt", "r");
    FILE *arquivo_resultado = fopen("resultado.txt", "w");
    if (arquivo_entrada == NULL || arquivo_resultado == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int valor;
    while (fscanf(arquivo_entrada, "%d", &valor) != EOF && valor != -1) {
        bool encontrado = false;
        for (int i = 0; i < TAMANHO_FIB; i++) {
            if (fib[i] == valor) {
                fprintf(arquivo_resultado, "O valor %d est� no arquivo na posi��o %d\n", valor, i+1);
                printf("O valor %d est� na s�rie de Fibonacci na posi��o %d\n", valor, i+1);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            long long int inferior = -1, superior = -1;
            for (int i = 0; i < TAMANHO_FIB; i++) {
                if (fib[i] < valor) {
                    inferior = fib[i];
                } else if (fib[i] > valor) {
                    superior = fib[i];
                    break;
                }
            }
            fprintf(arquivo_resultado, "O valor %d n�o est� no arquivo, valores mais pr�ximos: %lld e %lld\n", valor, inferior, superior);
            printf("O valor %d n�o est� na s�rie de Fibonacci. Valores mais pr�ximos: %lld e %lld\n", valor, inferior, superior);
        }
    }
    fclose(arquivo_entrada);
    fclose(arquivo_resultado);
}

void mostrar_fibonacci(long long int *fib) {
    for (int i = 0; i < TAMANHO_FIB; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
}

void mostrar_pares(long long int *fib) {
    for (int i = 0; i < TAMANHO_FIB; i++) {
        if (fib[i] % 2 == 0) {
            printf("%lld ", fib[i]);
        }
    }
    printf("\n");
}

void mostrar_impares(long long int *fib) {
    for (int i = 0; i < TAMANHO_FIB; i++) {
        if (fib[i] % 2 != 0) {
            printf("%lld ", fib[i]);
        }
    }
    printf("\n");
}

void mostrar_primos(long long int *fib) {
    for (int i = 0; i < TAMANHO_FIB; i++) {
        if (eh_primo(fib[i])) {
            printf("%lld ", fib[i]);
        }
    }
    printf("\n");
}

void menu_adicional() {
    setlocale(LC_ALL, "");
    long long int fib[TAMANHO_FIB];
    gerar_fibonacci(fib);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Mostrar S�rie de Fibonacci\n");
        printf("2. Mostrar N�meros Pares\n");
        printf("3. Mostrar N�meros �mpares\n");
        printf("4. Mostrar N�meros Primos\n");
        printf("5. Testar N�meros\n");
        printf("0. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("S�rie de Fibonacci:\n");
                mostrar_fibonacci(fib);
                break;
            case 2:
                printf("N�meros Pares:\n");
                mostrar_pares(fib);
                break;
            case 3:
                printf("N�meros �mpares:\n");
                mostrar_impares(fib);
                break;
            case 4:
                printf("N�meros Primos:\n");
                mostrar_primos(fib);
                break;
            case 5:
                criar_arquivo_entrada();
                testar_numeros();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

int main() {
    long long int fib[TAMANHO_FIB];
    gerar_fibonacci(fib);

    FILE *arquivo_fibonacci = fopen("fibonacci.txt", "w");
    for (int i = 0; i < TAMANHO_FIB; i++) {
        fprintf(arquivo_fibonacci, "%lld\n", fib[i]);
    }
    fclose(arquivo_fibonacci);

    FILE *arquivo_pares = fopen("pares.txt", "w");
    FILE *arquivo_impares = fopen("impares.txt", "w");
    for (int i = 0; i < TAMANHO_FIB; i++) {
        if (fib[i] % 2 == 0) {
            fprintf(arquivo_pares, "%lld\n", fib[i]);
        } else {
            fprintf(arquivo_impares, "%lld\n", fib[i]);
        }
    }
    fclose(arquivo_pares);
    fclose(arquivo_impares);

    FILE *arquivo_primos = fopen("primos.txt", "w");
    for (int i = 0; i < TAMANHO_FIB; i++) {
        if (eh_primo(fib[i])) {
            fprintf(arquivo_primos, "%lld\n", fib[i]);
        }
    }
    fclose(arquivo_primos);

    FILE *arquivo_entrada = fopen("valores_entrada.txt", "r");
    FILE *arquivo_resultado = fopen("resultado.txt", "w");
    long long int valor;
    while (fscanf(arquivo_entrada, "%lld", &valor) != EOF && valor != -1) {
        bool encontrado = false;
        for (int i = 0; i < TAMANHO_FIB; i++) {
            if (fib[i] == valor) {
                fprintf(arquivo_resultado, "O valor %lld est� no arquivo na posi��o %d\n", valor, i+1);
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            long long int inferior = -1, superior = -1;
            for (int i = 0; i < TAMANHO_FIB; i++) {
                if (fib[i] < valor) {
                    inferior = fib[i];
                } else if (fib[i] > valor) {
                    superior = fib[i];
                    break;
                }
            }
            fprintf(arquivo_resultado, "O valor %lld n�o est� no arquivo, valores mais pr�ximos: %lld e %lld\n", valor, inferior, superior);
        }
    }
    fclose(arquivo_entrada);
    fclose(arquivo_resultado);


    menu_adicional();

    return 0;
}
