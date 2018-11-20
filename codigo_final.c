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

int verificarRepeticaoCampoUm(registro*, int);

void verificarRepeticaoCampoDois(int, int*);

int verificaRepeticoesCampoTres(registro*, char*, int);

int verificaRepeticoesCampoQuatro(registro*, char*, int);

void gerarCampoUm(int, registro*);

void gerarCampoDois(int, registro*);

void gerarCampoTres(int, registro*);

void gerarCampoQuatro(int, registro*);

int main(int argc, char *argv[]) {
    // Possiveis parametros recebidos na execucao do codigo
    int arg1 = atoi(argv[1]);
    char* arg2 = argv[2];
    char* arg3 = argv[3];
    char* arg4 = argv[4];

    char* nome_arq1;
	char* nome_arq2;
	char* nome_arq3;
    int n;
    int flag_erro = 0;
    registro* reg;

    switch(arg1)
    {
        // Gerar arquivo de dados
        case 1:        
            nome_arq1 = arg2; 
            n = atoi(arg3);
			reg = (registro*) malloc (n * sizeof(registro));

            gerarCampoUm(n, reg);
			//gerarCampoDois(n, reg);
            gerarCampoTres(n, reg);
            gerarCampoQuatro(n, reg);

            //for(int i = 0; i < n; i++) printf("%d %d %s  %s\n", i, reg[i].n_vendas, reg[i].infos, reg[i].data);

            FILE *arquivo;
            arquivo = fopen(nome_arq1, "w+b");

            for(int r = 0; r < n; r++){
                fwrite(&reg[r].n_vendas, sizeof(reg[r].n_vendas), 1, arquivo);
                fwrite(&reg[r].infos, sizeof(reg[r].infos), 1, arquivo);
                fwrite(&reg[r].modelo, sizeof(reg[r].modelo), 1, arquivo);
                fwrite(&reg[r].data, sizeof(reg[r].data), 1, arquivo);
            }

            fclose(arquivo);
                
            if(flag_erro == 0)
                printf("Arquivo gerado.\n");
            else
                printf("Falha no processamento.\n");
        break;

        // Ler e printar o arquivo
        case 2:
            nome_arq1 = arg2; 

            FILE *arquivo_leitura;
            arquivo_leitura = fopen(nome_arq1, "r+b");

            if(arquivo_leitura != NULL)
            {
                registro teste;
                fseek(arquivo_leitura, 0, SEEK_SET);
				////////////////////////********
                while(!feof(arquivo_leitura)){
                    fread(&teste.n_vendas, sizeof(teste.n_vendas), 1, arquivo_leitura);
                    fread(&teste.infos, sizeof(teste.infos), 1, arquivo_leitura);
                    fread(&teste.modelo, sizeof(teste.modelo), 1, arquivo_leitura);
                    fread(&teste.data, sizeof(teste.data), 1, arquivo_leitura);
                    printf("%d %s %s %s\n", teste.n_vendas, teste.infos, teste.modelo, teste.data);
                }
                fclose(arquivo_leitura);

                if(flag_erro == 1)
                    printf("Falha no processamento.\n");
            }
            else
                printf("Arquivo vazio.\n");
        break;

        // Ordenação interna
        case 3:

        break;

		// Merging
        case 4:

        break;

		// Matching
        case 5:
			nome_arq1 = arg2;
			nome_arq2 = arg3;
			nome_arq3 = arg4;

			FILE *arq_entrada1;
            arq_entrada1 = fopen(nome_arq1, "r+b");

			FILE *arq_entrada2;
           	arq_entrada2 = fopen(nome_arq2, "r+b");

			FILE *arq_saida;
            arq_saida = fopen(nome_arq3, "w+b");

			int flag = 0;
			/*
				0: existem mais nomes
				1: nao existem mais nomes
			*/

			registro reg1_aux;
			fseek(arq_entrada1, 0, SEEK_SET);
			fread(&reg1_aux.n_vendas, sizeof(reg1_aux.n_vendas), 1, arq_entrada1);
			fread(&reg1_aux.infos, sizeof(reg1_aux.infos), 1, arq_entrada1);
			fread(&reg1_aux.modelo, sizeof(reg1_aux.modelo), 1, arq_entrada1);
			fread(&reg1_aux.data, sizeof(reg1_aux.data), 1, arq_entrada1);
			printf("%d %s %s %s\n", reg1_aux.n_vendas, reg1_aux.infos, reg1_aux.modelo, reg1_aux.data);
			if(feof(arq_entrada1)) 
				printf("Arquivo acabou \n");

			registro reg2_aux;
			fseek(arq_entrada2, 0, SEEK_SET);
			fread(&reg2_aux.n_vendas, sizeof(reg2_aux.n_vendas), 1, arq_entrada2);
			fread(&reg2_aux.infos, sizeof(reg2_aux.infos), 1, arq_entrada2);
			fread(&reg2_aux.modelo, sizeof(reg2_aux.modelo), 1, arq_entrada2);
			fread(&reg2_aux.data, sizeof(reg2_aux.data), 1, arq_entrada2);
			//printf("%d %s %s %s\n", reg2_aux.n_vendas, reg2_aux.infos, reg2_aux.modelo, reg2_aux.data);

			fclose(arq_entrada1);
			fclose(arq_entrada2);
			fclose(arq_saida);
        break;

		// Multiway merging
		case 6:

        break;

		// Ordenação externa
		case 7:

        break;

    }

    return 0;
}

int verificarRepeticaoCampoUm(registro* banco_dados, int i){
	for(int j = 0; j < i; j++) {
		if(banco_dados[j].n_vendas == banco_dados[i].n_vendas) {
			return 1;
		}
	}
	return 0;
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

int verificaRepeticoesCampoTres(registro* banco_dados, char* modelo, int i) {
	for(int j = 0; j < i; j++) {
		if(banco_dados[j].modelo == modelo) {
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
	int aux1, aux2, i = 0;
	aux2 = 0.30*n;
	aux1 = n - aux2;
	
	for(i; i < aux1; i++){ 
		do{
			//Salva os valores do campo1(numero de vendas) no banco de dados
			banco_dados[i].n_vendas = rand()%50001;	
		}while(verificarRepeticaoCampoUm(banco_dados,i));
	}

	//30% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < aux2; j++,i++){ 
		//Salva os valores do campo1(numero de vendas) no banco de dados
		banco_dados[i].n_vendas = banco_dados[j].n_vendas;
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
		for(j= 0; j < 10; j++){
        	for(k = 0; k < 5; k++){
            
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

void gerarCampoTres(int n, registro* banco_dados){
	srand(time(NULL));
	char marca[27][15] = {"VOLKSWAGEM","CHEVROLET","NISSAN","TOYOTA","HONDA","HYUNDAI","KIA","FIAT","FORD","RENAULT","AUDI","BMW","DODGE","MITSUBISHI","SUBARU","JEEP","MAHINDRA","GEELY","TESLA","AGRALE","IVECO","CADILLAC","VOLVO","BUGATTI","MASERATI","GURGEL","MERCEDES"};
	char letra[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
	char numero[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char indice[3];
	char campo_aux[20];

	int i, j;
	int random_1;
	int random_2;
	int random_3;
	for(i=0; i<(int)(0.8*n); i++) {
		do{
			strcpy(campo_aux, "");

			random_1 = rand() % 28;
			random_2 = rand() % 10;
			sprintf(indice, "%c%c", letra[random_1], numero[random_2]);
			//printf("%s\n", indice);
			strcat(campo_aux, indice);

			strcat(campo_aux, " ");
			random_3 = rand() % 27;
			strcat(campo_aux, marca[random_3]);
			//printf("%s \n", campo_aux);
		} while (verificaRepeticoesCampoTres(banco_dados, campo_aux, i));
		
		strcpy(banco_dados[i].modelo, campo_aux);
		//printf("%s\n", banco_dados[i].modelo);
	}

	for(i=0.8*n, j=0; j<(int)(0.2*n); i++, j++)
	{
		strcpy(banco_dados[i].modelo, banco_dados[j].modelo);
		//printf("%s", banco_dados[j+(int)0.8*n].modelo);
		//printf("\n");
	}
}

void gerarCampoQuatro(int n, registro* banco_dados){
	//Valores String que podem ser usados na data
	char valoresData[10] = {'0','1','2','3','4','5','6','7','8','9'}; 
	char valoresDataAux[7] = {'1','0','9','8','7','6','5'};

	//Vetor para salvar uma data
    char data[10];
	sprintf(data, "##/##/####");
	//char data[10] = {'#','#','/','#','#','/','#','#','#','#'};

	srand((unsigned)time(NULL)); //Semente da random

	//85% dos valores do campo4 não podem ser repetidos
	int aux1, aux2, i = 0;
	aux2 = 0.15*n;
	aux1 = n - aux2;
	
	for(i; i < aux1; i++){
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

			/*Se o segundo digito do dia for 0, o primeiro digito pode ser 1,2 ou 3,
			se o segundo digito do dia for 1, o primeiro digito pode ser 0,1,2 ou 3,
			se o segundo digito do dia for outro valor, o primeiro digito pode ser 0,1 ou 2*/
			if(data[1] == '0') 
				data[0] = 1 + valoresData[rand()%3];
			else if (data[1] == '1') 
				data[0] = valoresData[rand()%4];
			else
				data[0] = valoresData[rand()%3];
			
			//Fevereiro pode ter até 29 dias se for ano bissexto ou até 28 se não
			if(data[3] == '0' && data[4] == '2'){
				//Nao ha 30 ou mais dias nesse mes 
				if(data[0] == '3')
					data[0] = 1 + valoresData[rand()%2]; 
					
				//Verificar ano bissexto
				if(data[0] == '2'){			
					//Transformar o ano da String em double
					char aux3 = data[6], aux4 = data[7], aux5 = data[8], aux6 = data[9]; 
					char* verificaBissexto = malloc (4 * sizeof(char));
					verificaBissexto[0] = aux3;
					verificaBissexto[1] = aux4;
					verificaBissexto[2] = aux5;
					verificaBissexto[3] = aux6;
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
	for(int j = 0; j < aux2; j++,i++){
		strcpy(banco_dados[i].data, banco_dados[j].data);
	}
}