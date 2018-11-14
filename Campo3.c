#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int n_vendas;
    char infos[30];
    char modelo[20];
	char data[10];
} registro;

int verificaRepeticoes(registro* banco_dados, char* modelo, int i) {
	for(int j = 0; j < i; j++) {
		if(banco_dados[j].modelo == modelo) {
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	//printf("%d ", n);
	//getchar();	
	srand(time(NULL));

	char marca[27][15] = {"VOLKSWAGEM","CHEVROLET","NISSAN","TOYOTA","HONDA","HYUNDAI","KIA","FIAT","FORD","RENAULT","AUDI","BMW","DODGE","MITSUBISHI","SUBARU","JEEP","MAHINDRA","GEELY","TESLA","AGRALE","IVECO","CADILLAC","VOLVO","BUGATTI","MASERATI","GURGEL","MERCEDES"};
	char letra[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
	char numero[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char indice[2];
	char campo_aux[20];
	registro banco_dados[n];

	FILE *arq_texto;
	arq_texto = fopen("campo_3.txt", "w");	

	int i;
	int random_1;
	int random_2;
	int random_3;
	for(i=0; i<(0.8*n); i++) {
		do{
			random_1 = rand() % 28;
			indice[0]= letra[random_1];
			random_2 = rand() % 10;
			indice[1]= numero[random_2]; 
			strcpy(campo_aux, indice);
			//printf("%s \n", campo_aux);
			strcat(campo_aux, " ");
			random_3 = rand() % 27;
			strcat(campo_aux, marca[random_3]);
		} while (verificaRepeticoes(banco_dados, campo_aux, i));
		
		strcpy(banco_dados[i].modelo, campo_aux);
		//printf("%s", base_dados[i].modelo);
		//printf("\n");
		//printf("A: %s", campo_aux);
		//printf("\n");
		fprintf(arq_texto, campo_aux);
		fprintf(arq_texto, "\n");
	}

	/*int j;
	for(j = 0; j < 0.2 * n; j++)
	{

	}*/

	fclose(arq_texto);

	//getchar();	

	return 0;
}
