#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
	int n_vendas;
    char infos[30];
    char modelo[20];
	char data[10];
} registro;


int verificarRepeticaoCampoUm(registro* banco_dados, int i){
	for(int j = 0; j < i; j++) {
		if(banco_dados[j].n_vendas == banco_dados[i].n_vendas) {
			return 1;
		}
	}
	return 0;
}

int verificaRepeticoesCampoQuatro(registro* banco_dados, char* data, int i) {
	for(int j = 0; j < i; j++) {
		if(banco_dados[j].data == data) {
			return 1;
		}
	}
	return 0;
}

void gerarCampoUm(int n, registro* banco_dados){
	srand((unsigned)time(NULL)); //Semente da random
	
	//70% dos valores do Campo1 não podem ser repetidos
	int i = 0;
	for(i; i < (0.70*n); i++){ 
		do{
			//Salva os valores do campo1(numero de vendas) no banco de dados
			banco_dados[i].n_vendas = rand()%50001;	
		}while(verificarRepeticaoCampoUm(banco_dados,i));
	}

	//30% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < (0.30*n); j++,i++){ 
		//Salva os valores do campo1(numero de vendas) no banco de dados
		banco_dados[i].n_vendas = banco_dados[j].n_vendas;
	}
} 

int gerarCampoQuatro(int n, registro* banco_dados){
	//Valores String que podem ser usados na data
	char valoresData[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
	char valoresDataAux[7] = {'1','0','9','8','7','6','5'};

	//Vetor para salvar uma data
	char data[10] = {'#','#','/','#','#','/','#','#','#','#'};

	srand((unsigned)time(NULL)); //Semente da random

	//85% dos valores do campo4 não podem ser repetidos
	int i = 0;
	for(i; i < (0.85*n); i++){
		do{ 

			//Geracao do ano
			data[9] = valoresData[rand()%10];
			data[8] = valoresDataAux[rand()%7];

			/*Se o penultimo digito da data for 0 ou 1, então de trata dos anos entre 2000 e 2018
			caso contrário, a data sera entre 1950 e 1999*/  
			if(data[8] == '0' || data[8] == '1')
				data[7] = '0';
			else
				data[7] = '9';		

			if(data[7] == '0')
				data[6] = '2';
			else
				data[6] = '1';

			//Garantir que não haverá o ano 2019
			if(data[8] == '1' && data[9] == '9'){
				while(data[9] == '9')
					data[9] = valoresData[rand()%10];
			}

			//Geracao do mes
			data[4] = valoresData[rand()%10];

			/*Se o ultimo digito do mes for 0, entao sera o mes 10, e caso for 1 ou 2 poderao ser
			os meses 01,02,11 ou 12, se não poderão ser os meses 03,04,05,06,07,08 ou 09*/
			if(data[4] == '0')
				data[3] = '1';
			else if(data[4] == '1' || data[4] == '2')
				data[3] = valoresData[rand()%2];
			else
				data[3] = '0';

			//Geracao do dia
			data[1] = valoresData[rand()%10];		

			/*Se o segundo digito do dia for 0 ou 1, o primeiro digito pode ser 0,1,2 ou 3
			se o segundo digito do dia for outro valor, o primeiro digito pode ser 0,1 ou 2*/
			if(data[1] == '0' || data[1] == '1')
				data[0] = valoresData[rand()%4];
			else
				data[0] = valoresData[rand()%3];
			
			//Fevereiro pode ter até 29 dias se for ano bissexto ou até 28 se não
			if(data[3] == '0' && data[4] == '2'){
				//Nao ha 30 ou mais dias nesse mes 
				if(data[0] == '3')
					data[0] = valoresData[rand()%3]; 
					
				//Verificar ano bissexto
				if(data[0] == '2'){			
					//Transformar o ano da String em double
					char aux1 = data[6], aux2 = data[7], aux3 = data[8], aux4 = data[9]; 
					char* verificaBissexto = malloc (4 * sizeof(char));
					verificaBissexto[0] = aux1;
					verificaBissexto[1] = aux2;
					verificaBissexto[2] = aux3;
					verificaBissexto[3] = aux4;
					int auxBissexto = atoi(verificaBissexto);

					//Se não for ano bissexto, então não pode haver dia 29
					if((auxBissexto%4) != 0 && data[1] == '9')
						data[1] = valoresData[rand()%8];
					}
			}

			//Abril, Junho, Setembro e Novembro não tem 31 dias, ira ser atribuido o dia 30 ao 31 nesses meses
			if((data[3] == '0' && data[4] == '4') || (data[3] == '0' && data[4] == '6') || (data[3] == '0' && data[4] == '9') || (data[3] == '1' && data[4] == '1')){
				if (data[0] == '3' && data[1] == '1')
					data[1] = '0';
			}
			strcpy(banco_dados[i].data, data);
		}while(verificaRepeticoesCampoQuatro(banco_dados, data, i));
	}

	//25% dos valores do campo4 devem ser repetidos
	for(int j = 0; j < (0.15*n); j++,i++){
		strcpy(banco_dados[i].data, banco_dados[j].data);
	}
}


void verificarRepeticaoCampoDois(int i, int* volume){
	for(int j = (i-1); j >= 0; j--){
		if(volume[i] == volume[j]){
			volume[i] = 40 + rand()%470;
			verificarRepeticaoCampoDois(i,volume);
		    break;
		}
	}
}

void gerarCampoDois(int n, registro* reg){
    char alimentacao[5][9] = {"ELETRICO", "FLEX", "GASOLINA", "ALCOOL", "HIBRIDO"};
    char motor[10][4] = {"1.0", "1.3", "1.5", "1.6", "1.8", "2.0", "2.8", "3.0", "3.8", "4.4"};
    int volume[n];
	srand((unsigned)time(NULL)); //Semente da random
    char campo_2[30];
    //char* campo_2 = (char*)malloc (30 * sizeof(char));
    char str[4];
	//O primeiro valor é setado fora do loop pois não é necessario verificarRepeticao
	volume[0] = 40 + rand()%470;
	
	//70% dos valores do Campo1 não podem ser repetidos
	int i, j, k, m = 0;
    while(m < (n*0.75)){
        for(k = 0; k < 5; k++){
            for(j= 0; j < 10; j++){
                strcpy(campo_2, "" ); 
                volume[i+1] = 40 + rand()%470;
                verificarRepeticaoCampoDois(i+1,volume);
                sprintf(str, "%d", volume[i+1]);
                strcat(campo_2, str);
                strcat(campo_2, " ");
                strcat(campo_2, motor[j]);
                strcat(campo_2, " ");
                strcat(campo_2, alimentacao[k]);
                strcpy(reg[m].infos, campo_2);
                m++;
                if(m >= n*0.75) break;
            }
            if(m >= n*0.75) break;
        }
    }

    i = (n*0.75);
	//25% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < (0.25*n); j++){ 
		strcpy(reg[i].infos, reg[j].infos); 
        i++;
	}
} 


int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
    registro reg[n];
    float pi2, pi = 3.14;
    registro teste;
    FILE *arquivo;

    gerarCampoDois(n, reg);
    gerarCampoUm(n, reg);
	gerarCampoQuatro(n, reg);
    for(int i = 0; i < n; i++) printf("%d %d %s  %s\n", i, reg[i].n_vendas, reg[i].infos, reg[i].data);

    //grava no arquivo

    arquivo = fopen("notas.dat", "a+b");
    for(int r = 0; r < n; r++){
        fwrite(&reg[r].n_vendas, sizeof(reg[r].n_vendas), 1, arquivo);
        fwrite(&reg[r].infos, sizeof(reg[r].infos), 1, arquivo);
        fwrite(&reg[r].data, sizeof(reg[r].data), 1, arquivo);
    }



    //printa o arquivo
    fseek(arquivo, 0, SEEK_SET);
    for(int r = 0; r < n; r++){
        fread(&teste.n_vendas, sizeof(reg[r].n_vendas), 1, arquivo);
        fread(&teste.infos, sizeof(reg[r].infos), 1, arquivo);
        fread(&teste.data, sizeof(reg[r].data), 1, arquivo);
        printf("%d %s %s\n", teste.n_vendas, teste.infos, teste.data);
    }
    
    fclose(arquivo);
    return 0;
}