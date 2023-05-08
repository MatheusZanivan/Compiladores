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
			case '*':
				tokens[index].operador = '*';
				index++;
				break;
			case '/':
				tokens[index].operador = '/';
				index++;
				break;
			case '=':
				tokens[index].operador = '=';
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

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Uso: %s <arquivo>\n", argv[0]);
		return 1;
	}
	
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Erro ao abrir arquivo %s\n", argv[1]);
		return 1;
	}
	
	// determina o tamanho do arquivo
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	// aloca espaço para a string que irá armazenar o conteúdo do arquivo
	char* s = (char*) malloc(size + 1);
	if (s == NULL) {
		printf("Erro de alocação de memória\n");
		return 1;
	}
	
	// lê o conteúdo do arquivo para a string s
	fread(s, 1, size, fp);
	s[size] = '\0';
	fclose(fp);
	
	int tamanho;
	Token* tokens = tokenizar(s, &tamanho);
	printf("Tokens: ");
	for (int i = 0; i < tamanho; i++) {
		printf("%c ", tokens[i].operador);
	}
	printf("\n");
	free(tokens);
	free(s);
	return 0;
}
