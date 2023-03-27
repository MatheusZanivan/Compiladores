#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char operador;
} Token;

Token* tokenizar(char* s, int* tamanho) {
    Token* tokens = (Token*) malloc(strlen(s) * sizeof(Token));
    int index = 0;
    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        switch (c) {
            case '+':
                tokens[index].operador = '+';
                index++;
                break;
            case '-':
                tokens[index].operador = '-';
                index++;
                break;
            default:
                // caso seja outro caractere, não faz nada
                break;
        }
    }
    *tamanho = index;
    return tokens;
}

int main() {
    int tamanho;
    Token* tokens = tokenizar("+++-", &tamanho);
    printf("Tokens: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%c ", tokens[i].operador);
    }
    printf("\n");
    free(tokens);
    return 0;
}

