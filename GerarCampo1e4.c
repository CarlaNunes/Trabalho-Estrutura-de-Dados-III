#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#define N 10

void verificarRepeticaoCampoUm(int i, int* valores){
	for(int j = (i-1); j >= 0; j--){
		if(valores[i] == valores[j]){
			valores[i] = rand()%50001;
			verificarRepeticaoCampoUm(i,valores);
			break;
		}
	}
}

void gerarCampoUm(){
	int* valores = malloc (N * sizeof(int)); //Salvar o valores gerados 
	srand((unsigned)time(NULL)); //Semente da random
	
	//O primeiro valor é setado fora do loop pois não é necessario verificarRepeticao
	valores[0] = rand()%50001; 
	
	//70% dos valores do Campo1 não podem ser repetidos
	int i = 1;
	for(i; i < (0.70*N); i++){ 
		valores[i] = rand()%50001;
		verificarRepeticaoCampoUm(i,valores);
		printf("%d\n", valores[i]);
	}

	//30% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < (0.30*N); j++,i++){ 
		valores[i] = valores[j]; 
		printf("%d\n", valores[i]);
	}
} 

int gerarCampoQuatro(){
	//Valores String que podem ser usados na data
	char valoresData[10][1] = {"0","1","2","3","4","5","6","7","8","9"}; 
	char valoresDataAux[7][1] = {"1","0","9","8","7","6","5"};

	//Vetores para salvar uma data e depois todas as datas geradas
	char data[10][1] = {"#","#","/","#","#","/","#","#","#","#"};
	char*** valores = malloc (N * sizeof(char**)); //Salvar os valores gerados
	srand((unsigned)time(NULL)); //Semente da random

	//85% dos valores do campo4 não podem ser repetidos
	int i = 1;
	for(i; i < (0.85*N); i++){ 

		//Geracao do ano
		data[9][0] = valoresData[rand()%10][0];
		data[8][0] = valoresDataAux[rand()%7][0];

		/*Se o penultimo digito da data for 0 ou 1, então de trata dos anos entre 2000 e 2018
		caso contrário, a data sera entre 1950 e 1999*/  
		if(data[8][0] == '0' || data[8][0] == '1')
			data[7][0] = '0';
		else
			data[7][0] = '9';		

		if(data[7][0] == '0')
			data[6][0] = '2';
		else
			data[6][0] = '1';

		//Garantir que não haverá o ano 2019
		if(data[8][0] == '1' && data[9][0] == '9'){
			while(data[9][0] == '9')
				data[9][0] = valoresData[rand()%10][0];
		}

		//Geracao do mes
		




		printf("%s\n", data);
	}
	
}

int main(){
	//gerarCampoUm();
	gerarCampoQuatro();
	return 0;
}