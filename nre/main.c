#include <stdio.h>
#include <string.h>

#define MAX_VAL 256

int main(int argc, char** argv) {
	unsigned char buffer[MAX_VAL];
	int acumulador = 0;  // Registrador de acumulação (ACC)
	int pc = 0;   // Contador de programa (PC)
	int n_flag = 0;  // Indicador de sinal negativo (N_FLAG)
	int z_flag = 0;  // Indicador de zero (Z_FLAG)
	int run = 1;
	
	if (argc < 2) {
		printf("\nUSO: ./nre <input_file.nar>\n");  // Imprime instruções de uso
		return 1;
	}
	
	FILE *input_file;
	input_file = fopen(argv[1], "rb");
	
	if (!input_file) {
		printf("\nErro ao carregar arquivo de entrada!\n");  // Imprime mensagem de erro se não for possível abrir o arquivo
		return 1;
	}
	
	// inicializa o array com 0s
	memset(buffer, 0, sizeof(buffer));
	
	// Carrega do arquivo
	fread(buffer, sizeof(unsigned char), MAX_VAL, input_file);
	fclose(input_file);
	
	
	// Verificação do byte mágico 42
	if (buffer[0] != 0x2A) {
		printf("\nNúmero mágico 0x2A não encontrado!\nAbortando..\n\n");  // Imprime mensagem de erro se o byte mágico não for encontrado
		return 1;
	}
	
	// Carrega ACC e PC a partir do arquivo
	acumulador = buffer[1];
	pc = buffer[2];
	
	// Define os indicadores de ACC
	z_flag = (acumulador == 0) ? 1 : 0;  // Define Z_FLAG como 1 se ACC for zero, caso contrário, define como 0
	n_flag = (acumulador < 0) ? 1 : 0;   // Define N_FLAG como 1 se ACC for negativo, caso contrário, define como 0
	
	while (pc < MAX_VAL && run) {
		switch (buffer[pc]) {
			//HLZ
			case 0xF0:
				run = 0;  // Finaliza a execução do programa
				break;
			//STA
			case 0x10:
				pc++;
				buffer[buffer[pc]] = acumulador;  // Armazena o valor de ACC na posição de memória apontada pelo valor em buffer[pc]
				break;
			//LDA
			case 0x20:
				pc++;
				acumulador = buffer[buffer[pc]];  // Carrega o valor da memória na posição apontada por buffer[pc] para ACC
				break;
			//ADD
			case 0x30:
				pc++;
				acumulador += buffer[buffer[pc]];  // Soma o valor da memória na posição apontada por buffer[pc] a ACC
				break;
			//OR
			case 0x40:
				pc++;
				acumulador |= buffer[buffer[pc]];  // Realiza uma operação de OR entre o valor da memória em buffer[pc] e ACC, armazenando o resultado em ACC
				break;
			//AND
			case 0x50:
				pc++;
				acumulador &= buffer[buffer[pc]];  // Realiza uma operação de AND entre o valor da memória em buffer[pc] e ACC, armazenando o resultado em ACC
				break;
			//NOT
			case 0x60:
				pc++;
				acumulador = ~buffer[buffer[pc]];  // Realiza uma operação de NOT no valor da memória em buffer[pc] e armazena o resultado em ACC
				break;
			//JMP
			case 0x80:
				pc++;
				pc = buffer[pc];  // Define o novo valor de PC com base no valor em buffer[pc]
				pc--;  // Decrementa PC para compensar o incremento na próxima iteração do loop
				break;
			//JN
			case 0x90:
				if (n_flag) {
					pc++;
					pc = buffer[pc];  // Define o novo valor de PC com base no valor em buffer[pc]
					pc--;  // Decrementa PC para compensar o incremento na próxima iteração do loop
				}
				break;
			//JZ
			case 0xA0:
				if (z_flag) {
					pc++;
					pc = buffer[pc];  // Define o novo valor de PC com base no valor em buffer[pc]
					pc--;  // Decrementa PC para compensar o incremento na próxima iteração do loop
				}
				break;
			default:
				break;
		}
		pc++;  // Incrementa o valor de PC para apontar para a próxima instrução na próxima iteração do loop
	}
	
	
	printf("\nPC: %d", pc);
	printf("\nACC: %d", acumulador);
	printf("\nZ_FLAG: %d", z_flag);
	printf("\nN_FLAG: %d\n", n_flag);
	
		printf("-------------------------MEMÓRIA--------------------------\n");
	for (int i = 0; i < MAX_VAL; i++) {
		if (i != 0 && i % 16 == 0)
			printf("\n");
		printf("%02x ", buffer[i]);
	}
	printf("\n--------------------------------------------------------");
	
	return 0;
}
