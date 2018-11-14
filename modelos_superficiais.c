#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
	int n_vendas;
    char infos[30];
    char modelo[20];
	char data[10];
} registro;

int main(int argc, char *argv[]){
	//int n = (int)argv[1];
	int n = 6000;
	srand(time(NULL));

	char marca[27][15] = {"VOLKSWAGEM","CHEVROLET","NISSAN","TOYOTA","HONDA","HYUNDAI","KIA","FIAT","FORD","RENAULT","AUDI","BMW","DODGE","MITSUBISHI","SUBARU","JEEP","MAHINDRA","GEELY","TESLA","AGRALE","IVECO","CADILLAC","VOLVO","BUGATTI","MASERATI","GURGEL","MERCEDES"};
	char letra[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
	char numero[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char indice[2];
	char campo_aux[20];
	char campo_3[n][20];

	FILE *arq_texto;
	arq_texto = fopen("campo_3.txt", "w");	

	int i;
	int random_1;
	int random_2;
	int random_3;
	for(i=0; i<n; i++)
	{
		random_1 = rand() % 28;
		indice[0]= letra[random_1];
		random_2 = rand() % 10;
		indice[1]= numero[random_2]; 
		strcpy(campo_aux, indice);
		//printf("%s \n", campo_aux);
		strcat(campo_aux, " ");
		random_3 = rand() % 27;
		strcat(campo_aux, marca[random_3]);
		//campo_3[i][0] = campo_aux;
		printf("%s", campo_aux);
		printf("\n");
		fprintf(arq_texto, campo_aux);
		fprintf(arq_texto, "\n");
	}

	fclose(arq_texto);


				/*

				if(i == 0 && j<=10){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}
			
				if(i == 1 &&  j>=10 && j<=19){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}

				if(i == 2 && j>15 && j<=19 ){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}

				if(i == 3 && j>15 && j<=19 ){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}
					
				if(i == 4 && j>19 && j<=30 ){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	
			
				if(i == 5 && j>30 && j<=50 ){
					printf("\n %s Modelo A%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
					printf("\n %s Modelo B%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	

				if(i == 6 && j>50 && j<=80 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	

				if(i == 7 && j>80 && j<=100 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	
			
				if(i == 8 && j>100 && j<=160 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	

				if(i == 9 && j>160 && j<=200 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	

				if(i == 10 && j>200 && j<=250 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	

				if(i == 11 && j>250 && j<=300 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	
				
				if(i ==  13 && j>400 && j<=450 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}	
				
				if(i == 14 && j>450 && j<=500 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}

				if(i == 15 && j>500 && j<=550 ){
						printf("\n %s Modelo A%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo A%d",marcas[i],j);
						printf("\n %s Modelo B%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo B%d",marcas[i],j);
						printf("\n %s Modelo C%d",marcas[i],j);
						fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}		
			}
	}
	}*/

	//getchar();	

	return 0;
}
