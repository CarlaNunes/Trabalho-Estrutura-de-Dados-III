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

void heapify(registro[], int, int);

void heapSort(registro[], int);

void escreveRegistro(registro*, FILE*);

void leRegistro(registro*, FILE*);

void imprimeRegistro(registro*);
void multiway_merging(FILE **, FILE * , int);

int main(int argc, char *argv[]) {
	//Semente da funcao randomomica
	srand((unsigned)time(NULL)); 

    // Armazenamentos dos parametros recebidos na execucao do codigo
	// arguments[0] = funcao a ser executada
	char** arguments = (char**) malloc ((argc-1) * sizeof(char*));
	int aux;
	for(aux=0; aux<argc-1; aux++)
		arguments[aux] = argv[aux+1];
		
	int func = atoi(arguments[0]);

	char* nome_arq;
    char* nome_arq1;
	char* nome_arq2;
	char* nome_arq3;
	char** nomes_arqs;
    int n;
	int i, j, k;
    int flag_erro = 0;
	int flag = 0;
    registro* reg;
	registro reg1_aux;
	registro reg2_aux;

    switch(func)
    {
        // Gerar arquivo de dados
        case 1:    
			n = atoi(arguments[2]);    
            nome_arq = arguments[1]; 
			strcat(nome_arq, ".dat");

			reg = (registro*) malloc (n * sizeof(registro));

            gerarCampoUm(n, reg);
			gerarCampoDois(n, reg);
            gerarCampoTres(n, reg);
            gerarCampoQuatro(n, reg);

            //for(int i = 0; i < n; i++) printf("%d %d %s %s %s\n", i, reg[i].n_vendas, reg[i].infos, reg[i].modelo, reg[i].data);

            FILE *arquivo;
            arquivo = fopen(nome_arq, "w+b");

            for(int r = 0; r < n; r++)
                escreveRegistro(&reg[r], arquivo);

            fclose(arquivo);
                
            if(flag_erro == 0)
                printf("Arquivo gerado.\n");
            else
                printf("Falha no processamento.\n");
        break;

        // Ler e printar o arquivo
        case 2:
            nome_arq = arguments[1]; 
			strcat(nome_arq, ".dat");

            FILE *arquivo_leitura;
            arquivo_leitura = fopen(nome_arq, "r+b");

            if(arquivo_leitura != NULL)
            {
                registro* registro_aux;
                fseek(arquivo_leitura, 0, SEEK_SET);
				
                while( fread(registro_aux, sizeof(*registro_aux), 1, arquivo_leitura) != 0 ){
                    imprimeRegistro(registro_aux);
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
			nome_arq = arguments[1]; 
			strcat(nome_arq, ".dat");

            FILE *arquivo_ordenar;
            arquivo_ordenar = fopen(nome_arq, "r+b");

			int count = -1;
            if(arquivo_ordenar != NULL)
            {
                registro teste;
                //fseek(arquivo_ordenar, 0, SEEK_SET);
				////////////////////////********
                while(!feof(arquivo_ordenar)){
					leRegistro(&teste,arquivo_ordenar);
                    //printf("%d %s %s %s\n", teste.n_vendas, teste.infos, teste.modelo, teste.data);
					count++;
                }
                //fclose(arquivo_ordenar);

				n = count;
				reg = (registro*) malloc (n*sizeof(registro));
				fseek(arquivo_ordenar, 0, SEEK_SET);
				for(int r = 0; r < n; r++){
					leRegistro(&reg[r],arquivo_ordenar);
					// printf("%d %s %s\n", regs[r].n_vendas, regs[r].infos, regs[r].data);
				}
				heapSort(reg, n);
				//for(int r = 0; r < n; r++) printf("%d %s %s %s\n", reg[r].n_vendas, reg[r].modelo, reg[r].infos, reg[r].data);

				fseek(arquivo_ordenar, 0, SEEK_SET);
				for(int r = 0; r < n; r++){
					escreveRegistro(&reg[r],arquivo_ordenar);
				}

				fclose(arquivo_ordenar); 

				//printf("Linhas: %d \n", count);

                if(flag_erro == 1)
                    printf("Falha no processamento.\n");
            }
            else
                printf("Arquivo vazio.\n");

        break;

		// Merging
        case 4:
			nome_arq1 = arguments[1];
			strcat(nome_arq1, ".dat");
			nome_arq2 = arguments[2];
			strcat(nome_arq2, ".dat");
			nome_arq3 = arguments[3];
			strcat(nome_arq3, ".dat");

			FILE *arquivo1;
            arquivo1 = fopen(nome_arq1, "r+b");

			FILE *arquivo2;
           	arquivo2 = fopen(nome_arq2, "r+b");

			FILE *arquivo_saida;
            arquivo_saida = fopen(nome_arq3, "w+b");

			fseek(arquivo1, 0, SEEK_SET);
			leRegistro(&reg1_aux, arquivo1);
			//imprimeRegistro(reg1_aux);

			fseek(arquivo2, 0, SEEK_SET);
			leRegistro(&reg2_aux, arquivo2);
			//imprimeRegistro(reg2_aux);
			
			while (!feof(arquivo1) || !feof(arquivo2)){
				if( reg1_aux.n_vendas < reg2_aux.n_vendas && !feof(arquivo1) ){
					imprimeRegistro(&reg1_aux);
					escreveRegistro(&reg1_aux, arquivo_saida);
					leRegistro(&reg1_aux, arquivo1);
				}
				else if(reg1_aux.n_vendas > reg2_aux.n_vendas && !feof(arquivo2) ){
					imprimeRegistro(&reg2_aux);
					escreveRegistro(&reg2_aux, arquivo_saida);
					leRegistro(&reg2_aux, arquivo2);
				}
				else{   
					if(reg1_aux.infos < reg2_aux.infos && !feof(arquivo1) ){
						imprimeRegistro(&reg1_aux);
						escreveRegistro(&reg1_aux, arquivo_saida);
						leRegistro(&reg1_aux, arquivo1);
					}    
					else if(reg1_aux.infos > reg2_aux.infos && !feof(arquivo2) ){     
						imprimeRegistro(&reg2_aux);
						escreveRegistro(&reg2_aux, arquivo_saida);
						leRegistro(&reg2_aux, arquivo2);
					}
					else{
						if(reg1_aux.modelo < reg2_aux.modelo && !feof(arquivo1) ){
							imprimeRegistro(&reg1_aux);
							escreveRegistro(&reg1_aux, arquivo_saida);
							leRegistro(&reg1_aux, arquivo1);
						}    
						else if(reg1_aux.modelo > reg2_aux.modelo && !feof(arquivo2) ){     
							imprimeRegistro(&reg2_aux);
							escreveRegistro(&reg2_aux, arquivo_saida);
							leRegistro(&reg2_aux, arquivo2);
						}
						else{
							if(reg1_aux.data < reg2_aux.data && !feof(arquivo1) ){
								imprimeRegistro(&reg1_aux);
								escreveRegistro(&reg1_aux, arquivo_saida);
								leRegistro(&reg1_aux, arquivo1);
							}    
							else if(reg1_aux.data > reg2_aux.data && !feof(arquivo2) ){     
								imprimeRegistro(&reg2_aux);
								escreveRegistro(&reg2_aux, arquivo_saida);
								leRegistro(&reg2_aux, arquivo2);
							}
							else{
								imprimeRegistro(&reg1_aux);
								imprimeRegistro(&reg2_aux);
								escreveRegistro(&reg1_aux, arquivo_saida);
								escreveRegistro(&reg2_aux, arquivo_saida);
								leRegistro(&reg1_aux, arquivo1);
								leRegistro(&reg2_aux, arquivo2);
							}	
						}
					}
				}			
			}

			fclose(arquivo1);
			fclose(arquivo2);
			fclose(arquivo_saida);
        break;

		// Matching
        case 5:
			nome_arq1 = arguments[1];
			strcat(nome_arq1, ".dat");
			nome_arq2 = arguments[2];
			strcat(nome_arq2, ".dat");
			nome_arq3 = arguments[3];
			strcat(nome_arq3, ".dat");

			FILE *arq_entrada1;
            arq_entrada1 = fopen(nome_arq1, "r+b");

			FILE *arq_entrada2;
           	arq_entrada2 = fopen(nome_arq2, "r+b");

			FILE *arq_saida;
            arq_saida = fopen(nome_arq3, "w+b");

			flag = 0;
			/*
				0: existem mais nomes
				1: nao existem mais nomes
			*/

			fseek(arq_entrada1, 0, SEEK_SET);
			leRegistro(&reg1_aux, arq_entrada1);
			//imprimeRegistro(reg1_aux);
			if(feof(arq_entrada1)) 
				flag = 1;

			fseek(arq_entrada2, 0, SEEK_SET);
			leRegistro(&reg2_aux, arq_entrada2);
			//imprimeRegistro(reg2_aux);
			if(feof(arq_entrada2)) 
				flag = 1;

			while(flag == 0){
				if(reg1_aux.n_vendas < reg2_aux.n_vendas){
					leRegistro(&reg1_aux, arq_entrada1);

					if(feof(arq_entrada1)) 
						flag = 1;
				}
				else if(reg1_aux.n_vendas > reg2_aux.n_vendas){
					leRegistro(&reg2_aux, arq_entrada2);

					if(feof(arq_entrada2)) 
						flag = 1;
				}
				else{ 
					escreveRegistro(&reg1_aux, arq_saida);

					leRegistro(&reg1_aux, arq_entrada1);
					leRegistro(&reg2_aux, arq_entrada2);

					if(feof(arq_entrada1) || feof(arq_entrada2)) 
						flag = 1;
				}
			}

			fclose(arq_entrada1);
			fclose(arq_entrada2);
			fclose(arq_saida);
        break;

		// Multiway merging
		case 6:
			//printf("Argumentos: %d \n", argc);
			nomes_arqs = (char**) malloc( (argc-2) * sizeof(char*));
			for(k=0; k<(argc-3); k++) {
				nomes_arqs[k] = arguments[k+1]; // nome dos arquivos de entrada
				//printf("Entrada %s \n", nomes_arqs[k]);
			}
			nome_arq = arguments[argc-2]; // nome do arquivo de saida
			//printf("Saida %s \n", nome_arq);

			/*registro menor_registro;

			for(i=0; i<n; i++){
				fread(&nome[i], sizeof(menor), 1, arquivo[i]);
				do {
						fread(&nome[i], sizeof(Registro), 1, arquivo[i]);
						menor.n_vendas = nome[i].n_vendas;
						if(nome[i].n_vendas < menor.n_vendas){
								menor = nome[i];
							fwrite (&menor, sizeof(char),1, arq_saida );
						}

						else{
							fwrite (&nome[j], sizeof(char),1, arq_saida );
						}

					j++;

				} while (!feof(arquivo[i]) ); // enquanto não chegar ao final do arquivo*/

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
	
	//70% dos valores do Campo1 não podem ser repetidos
	int aux1, aux2, i = 0;
	aux2 = 0.30*n;
	aux1 = n - aux2;
	
	for(i; i < aux1; i++){ 
		do{
			//Salva os valores do campo1(numero de vendas) no banco de dados
			banco_dados[i].n_vendas = 1 + rand()%50000;	
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
    //char campo_2[30];
    char* campo_2 = (char*)malloc (30 * sizeof(char));
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
	char marca[27][15] = {"VOLKSWAGEM","CHEVROLET","NISSAN","TOYOTA","HONDA","HYUNDAI","KIA","FIAT","FORD","RENAULT","AUDI","BMW","DODGE","MITSUBISHI","SUBARU","JEEP","MAHINDRA","GEELY","TESLA","AGRALE","IVECO","CADILLAC","VOLVO","BUGATTI","MASERATI","GURGEL","MERCEDES"};
	char letra[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'Y', 'Z'};
	char numero[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char indice[3];
	char campo_aux[20];

	int i, j;
	int random_1;
	int random_2;
	int random_3;
	int aux_rep = (int) (0.8*n);

	for(i=0; i<aux_rep; i++) {
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

	for(i=aux_rep, j=0; j<n-aux_rep; i++, j++)
	{
		strcpy(banco_dados[i].modelo, banco_dados[rand()%aux_rep].modelo);
		//printf("%s", banco_dados[i].modelo);
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
			//printf("%s \n", data);
			strcpy(banco_dados[i].data, data);
		}while(verificaRepeticoesCampoQuatro(banco_dados, data, i));
	}

	//25% dos valores do campo4 devem ser repetidos
	for(int j = 0; j < aux2; j++,i++){
		strcpy(banco_dados[i].data, banco_dados[j].data);
	}
}

void heapify(registro arr[], int n, int i) { 
	int largest = i; // Initialize largest as root 
	int l = 2*i + 1; // left = 2*i + 1 
	int r = 2*i + 2; // right = 2*i + 2 
	registro aux;

	if (l < n && arr[l].n_vendas > arr[largest].n_vendas){
		largest = l;
	}

	if (r < n && arr[r].n_vendas > arr[largest].n_vendas) 
		largest = r;  

		
	if (l < n && arr[l].n_vendas == arr[largest].n_vendas){
			if(strcmp(arr[l].infos, arr[largest].infos) > 0){
			largest = l; 
		}else{
			if(strcmp(arr[l].infos, arr[largest].infos) == 0){
				if(strcmp(arr[l].modelo, arr[largest].modelo) > 0){
					largest = l;
				}else{
					if(strcmp(arr[l].modelo, arr[largest].modelo) == 0){
						if(strcmp(arr[l].data, arr[largest].data) > 0){
							largest = l;
						}
					}
				}
			}
		}
	}

	if (r < n && arr[r].n_vendas == arr[largest].n_vendas){
			if(strcmp(arr[r].infos, arr[largest].infos) > 0){
			largest = r; 
		}else{
			if(strcmp(arr[r].infos, arr[largest].infos) == 0){
				if(strcmp(arr[r].modelo, arr[largest].modelo) > 0){
					largest = r;
				}else{
					if(strcmp(arr[r].modelo, arr[largest].modelo) == 0){
						if(strcmp(arr[r].data, arr[largest].data) > 0){
							largest = r;
						}
					}
				}
			}
		}
	}
		// If largest is not root 
		if (largest != i) 
		{ 
			aux = arr[i];
			arr[i] = arr[largest];
			arr[largest] = aux;
			heapify(arr, n, largest); 
		} 
 } 

 // main function to do heap sort 
 void heapSort(registro arr[], int n) 
 { 
     // Build heap (rearrange array) 
     registro aux;
     for (int i = n / 2 - 1; i >= 0; i--) 
         heapify(arr, n, i); 
   
     // One by one extract an element from heap 
     for (int i=n-1; i>=0; i--){ 
         aux = arr[i];
         arr[i] = arr[0];
         arr[0] = aux;
         heapify(arr, i, 0); 
    } 
} 
void status(FILE* arquivo){
	char* status;
	if(fread(status, 1, 1, arquivo) == 0){
		*status = '1';
		fwrite(status, 1, 1, arquivo);
	}else{
		*status = '0';
		fwrite(status, 1, 1, arquivo);
	}
}
void escreveRegistro(registro* reg, FILE* arquivo){
	fwrite(&(reg->n_vendas), sizeof(reg->n_vendas), 1, arquivo);
	fwrite(reg->infos, sizeof(reg->infos), 1, arquivo);
	fwrite(reg->modelo, sizeof(reg->modelo), 1, arquivo);
	fwrite(reg->data, sizeof(reg->data), 1, arquivo);
}

void leRegistro(registro* reg, FILE* arquivo){
	fread(&(reg->n_vendas), sizeof(reg->n_vendas), 1, arquivo);
	fread(reg->infos, sizeof(reg->infos), 1, arquivo);
	fread(reg->modelo, sizeof(reg->modelo), 1, arquivo);
	fread(reg->data, sizeof(reg->data), 1, arquivo);
	//printf("%d %s %s %s\n", reg->n_vendas, reg->infos, reg->modelo, reg->data);
}

void imprimeRegistro(registro* reg){
	printf("%d %s %s %s\n", reg->n_vendas, reg->infos, reg->modelo, reg->data);
}
int is_valid(const int *valido, int n){
    int i;

    for (i = 0; i < n; i++) {
        if(valido[i] == 1){
            return 1;
        }
    }

    return 0;
}

int encontra_menor(const Registro *tmp, const int *valido, int n){
    int menor;
    int i;

    //Encontra primeiro válido
    for (i = 0; i < n; i++) {
        if (valido[i]){
            menor = i;
            break;
        }
    }

    //Compara com os demais (apenas com os válidos)
    for (i = menor+1; i < n; i++) {
        if ((valido[i]) && (tmp[i].n_vendas < tmp[menor].n_vendas)) {
            menor = i;
        }
    }

    return menor;
}

void multiway_merging(FILE **arquivo, FILE *arq_saida , int n){
    int i = 0;

    int menor_indice;

    Registro *tmp = (Registro *) malloc(n * sizeof(Registro));
    int *valido = (int *) malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        //Se valido[i] for menor que 1, deu erro ou EOF
        valido[i] = fread(&tmp[i], sizeof(Registro), 1, arquivo[i]);
    }

    while(is_valid(valido, n)){
        menor_indice = encontra_menor(tmp, valido, n);
        fwrite(&tmp[menor_indice], sizeof(Registro),1, arq_saida);
        valido[menor_indice] = fread(&tmp[menor_indice], sizeof(Registro), 1, arquivo[menor_indice]);
    }
   
    free(tmp);
    free(valido);

}
