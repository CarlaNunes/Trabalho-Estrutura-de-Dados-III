#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "manipularArquivo.h"

void heapify(registro[], int, int);

void heapSort(registro[], int);

int is_valid(const int*, int);

int encontra_menor(const registro*, const int*, int);

void multiway_merging(FILE**, FILE*, int);

int main(int argc, char *argv[]) {
	/*Semente da funcao randomomica*/
	srand((unsigned)time(NULL)); 

	char** arguments;

	int func, n;
	int i, j, k, r, aux;
    int flag_erro = 0;
	int flag = 0;
	int count = -1;
	/*Tamanho máximo dos subarquivos iniciais (capacidade do buffer)*/
	int pag = 1000;
	int numS, x = 0;
	int iter = 0, s, p, num;
	FILE *sub[11];
	char subArq[11][12];
	registro reg_auxiliar;

	char* nome_arq;
    char* nome_arq1;
	char* nome_arq2;
	char* nome_arq3;
	char** nomes_arqs;
	char estado;

    registro* reg;
	registro reg1_aux;
	registro reg2_aux;

    /* Armazenamentos dos parametros recebidos na execucao do codigo
	    arguments[0] = funcao a ser executada */
	arguments = (char**) malloc ((argc-1) * sizeof(char*));
	for(aux=0; aux<argc-1; aux++)
	{
		arguments[aux] = argv[aux+1];
		/*printf("Argumentos %d: %s \n", aux, arguments[aux]);*/
	}
		
	func = atoi(arguments[0]);

	if(func == 1)  /* Gerar arquivo de dados */
	{
		n = atoi(arguments[2]);    
		nome_arq = arguments[1]; 

		/*cria um vetor de registros de tamanho n gera os campos, já os adicionando no vetor*/
		reg = (registro*) malloc (n * sizeof(registro));

		gerarCampoUm(n, reg);
		gerarCampoDois(n, reg);
		gerarCampoTres(n, reg);
		gerarCampoQuatro(n, reg);


		FILE *arquivo;
		/*muda o status do arquivo para 0*/ 
		arquivo = fopen(nome_arq, "w+b");
		estado = '0';
		fwrite(&estado,1,1, arquivo);

		/*grava os registros no arquivo*/
		for(r = 0; r < n; r++)
			escreveRegistro(&reg[r], arquivo);

		/*muda o status do arquivo para 1*/
		fseek(arquivo, 0, SEEK_SET);
		estado = '1';
		fwrite(&estado,1,1, arquivo);
		fclose(arquivo);
			
		if(flag_erro == 0)
			printf("Arquivo gerado.\n");
		else
			printf("Falha no processamento.\n");
	}

    else if(func == 2) /* Ler e printar o arquivo */
	{
		nome_arq = arguments[1]; 

		FILE *arquivo_leitura;
		/*abre o arquivo, e se o mesmo não estiver vazio:*/
		arquivo_leitura = fopen(nome_arq, "r+b");

		if(arquivo_leitura != NULL)
		{
			registro registro_aux;
			/*muda o status do arquivo para 0*/
			fseek(arquivo_leitura, 0, SEEK_SET);
			estado = '0';
			fwrite(&estado,1,1, arquivo_leitura);
			/*Lê registro um por um e os printa*/
			while( fread(&registro_aux, sizeof(registro_aux), 1, arquivo_leitura) != 0 ){
				imprimeRegistro(&registro_aux);
			}
			/*muda o status do arquivo para 1*/
			fseek(arquivo_leitura, 0, SEEK_SET);
			estado = '1';
			fwrite(&estado,1,1, arquivo_leitura);
			fclose(arquivo_leitura);

			if(flag_erro == 1)
				printf("Falha no processamento.\n");
		}
		else
			printf("Arquivo vazio.\n");
	}
            
    else if(func == 3)   /* Ordenação interna */
	{
		nome_arq = arguments[1]; 
		/*abre o arquivo inicial, e se o mesmo não estiver vazio:*/
		FILE *arquivo_ordenar;
		arquivo_ordenar = fopen(nome_arq, "r+b");

		int count = -1;
		if(arquivo_ordenar != NULL)
		{
			registro teste;
			/*muda o status do arquivo para 0*/
			fseek(arquivo_ordenar, 0, SEEK_SET);
			estado = '0';
			fwrite(&estado,1,1, arquivo_ordenar);
			while(!feof(arquivo_ordenar)){
				leRegistro(&teste,arquivo_ordenar);
				count++;
			}
			n = count;
			reg = (registro*) malloc (n*sizeof(registro));
			fseek(arquivo_ordenar, 0, SEEK_SET);
			/*Le registro por registro e escreve em um vetor desse tipo*/
			for(r = 0; r < n; r++){
				leRegistro(&reg[r],arquivo_ordenar);
			}
			/*ordena o vetor obtido e o armazena no arquivo final*/
			heapSort(reg, n);

			fseek(arquivo_ordenar, 0, SEEK_SET);
			for(r = 0; r < n; r++){
				escreveRegistro(&reg[r],arquivo_ordenar);
			}

			/*muda o status do arquivo para 1*/
			fseek(arquivo_ordenar, 0, SEEK_SET);
			estado = '1';
			fwrite(&estado,1,1, arquivo_ordenar);
			fclose(arquivo_ordenar); 


			if(flag_erro == 1)
				printf("Falha no processamento.\n");
		}
		else
			printf("Arquivo vazio.\n");
	}
			

	else if(func == 4) /* Merging */
	{
		nome_arq1 = arguments[1];
		nome_arq2 = arguments[2];
		nome_arq3 = arguments[3];

		/*printf("Argumentos: %s, %s, %s \n", arguments[1], arguments[2], arguments[3]);
		printf("Nome dos arquivos: %s, %s, %s \n", nome_arq1, nome_arq2, nome_arq3);*/

		FILE *arquivo1;
		arquivo1 = fopen(nome_arq1, "r+b");
		fseek(arquivo1, 0, SEEK_SET);
		estado = '0';
		fwrite(&estado,1,1, arquivo1);

		FILE *arquivo2;
		arquivo2 = fopen(nome_arq2, "r+b");
		fseek(arquivo2, 0, SEEK_SET);
		fwrite(&estado,1,1, arquivo2);

		FILE *arquivo_saida;
		arquivo_saida = fopen(nome_arq3, "w+b");
		fseek(arquivo_saida, 0, SEEK_SET);
		fwrite(&estado,1,1, arquivo_saida);

		leRegistro(&reg1_aux, arquivo1);

		leRegistro(&reg2_aux, arquivo2);
		
		while (!feof(arquivo1) || !feof(arquivo2)){
			if( reg1_aux.n_vendas < reg2_aux.n_vendas && !feof(arquivo1) ){
				escreveRegistro(&reg1_aux, arquivo_saida);
				leRegistro(&reg1_aux, arquivo1);
			}
			else if(reg1_aux.n_vendas > reg2_aux.n_vendas && !feof(arquivo2) ){
				escreveRegistro(&reg2_aux, arquivo_saida);
				leRegistro(&reg2_aux, arquivo2);
			}
			else if (reg1_aux.n_vendas == reg2_aux.n_vendas){   
				if(reg1_aux.infos < reg2_aux.infos && !feof(arquivo1) ){
					escreveRegistro(&reg1_aux, arquivo_saida);
					leRegistro(&reg1_aux, arquivo1);
				}    
				else if(reg1_aux.infos > reg2_aux.infos && !feof(arquivo2) ){     
					escreveRegistro(&reg2_aux, arquivo_saida);
					leRegistro(&reg2_aux, arquivo2);
				}
				else if(reg1_aux.infos == reg2_aux.infos ){
					if(reg1_aux.modelo < reg2_aux.modelo && !feof(arquivo1) ){
						escreveRegistro(&reg1_aux, arquivo_saida);
						leRegistro(&reg1_aux, arquivo1);
					}    
					else if(reg1_aux.modelo > reg2_aux.modelo && !feof(arquivo2) ){     
						escreveRegistro(&reg2_aux, arquivo_saida);
						leRegistro(&reg2_aux, arquivo2);
					}
					else if(reg1_aux.modelo == reg2_aux.modelo){
						if(reg1_aux.data < reg2_aux.data && !feof(arquivo1) ){
							escreveRegistro(&reg1_aux, arquivo_saida);
							leRegistro(&reg1_aux, arquivo1);
						}    
						else if(reg1_aux.data > reg2_aux.data && !feof(arquivo2) ){     
							escreveRegistro(&reg2_aux, arquivo_saida);
							leRegistro(&reg2_aux, arquivo2);
						}
						else if(reg1_aux.data == reg2_aux.data){
							escreveRegistro(&reg1_aux, arquivo_saida);
							escreveRegistro(&reg2_aux, arquivo_saida);
							leRegistro(&reg1_aux, arquivo1);
							leRegistro(&reg2_aux, arquivo2);
						}	
					}
				}
			}			
		}
		estado = '1';
		fseek(arquivo1, 0, SEEK_SET);	
		fwrite(&estado,1,1, arquivo1);
		fseek(arquivo2, 0, SEEK_SET);	
		fwrite(&estado,1,1, arquivo2);
		fseek(arquivo_saida, 0, SEEK_SET);	
		fwrite(&estado,1,1, arquivo_saida);

		fclose(arquivo1);
		fclose(arquivo2);
		fclose(arquivo_saida);
	}

		
	else if(func == 5) /* Matching */
	{
		nome_arq1 = arguments[1];
		nome_arq2 = arguments[2];
		nome_arq3 = arguments[3];

		/*printf("Argumentos: %s, %s, %s \n", arguments[1], arguments[2], arguments[3]);
		printf("Nome dos arquivos: %s, %s, %s \n", nome_arq1, nome_arq2, nome_arq3);*/

		FILE *arq_entrada1;
		arq_entrada1 = fopen(nome_arq1, "r+b");
		fseek(arq_entrada1, 0, SEEK_SET);
		estado = '0';
		fwrite(&estado,1,1, arq_entrada1);

		FILE *arq_entrada2;
		arq_entrada2 = fopen(nome_arq2, "r+b");
		fseek(arq_entrada2, 0, SEEK_SET);
		fwrite(&estado,1,1, arq_entrada2);

		FILE *arq_saida;
		arq_saida = fopen(nome_arq3, "w+b");
		fseek(arq_saida, 0, SEEK_SET);
		fwrite(&estado,1,1, arq_saida);
	
		leRegistro(&reg1_aux, arq_entrada1);
	
		leRegistro(&reg2_aux, arq_entrada2);

		while (!feof(arq_entrada1) || !feof(arq_entrada2)){
			if( reg1_aux.n_vendas < reg2_aux.n_vendas && !feof(arq_entrada1) ){
				leRegistro(&reg1_aux, arq_entrada1);
			}
			else if(reg1_aux.n_vendas > reg2_aux.n_vendas && !feof(arq_entrada2) ){
				leRegistro(&reg2_aux, arq_entrada2);
			}
			else{   
				if(reg1_aux.infos < reg2_aux.infos && !feof(arq_entrada1) ){
					escreveRegistro(&reg1_aux, arq_saida);
					escreveRegistro(&reg2_aux, arq_saida);
					leRegistro(&reg1_aux, arq_entrada1);
				}    
				else if(reg1_aux.infos > reg2_aux.infos && !feof(arq_entrada2) ){     
					escreveRegistro(&reg2_aux, arq_saida);
					escreveRegistro(&reg1_aux, arq_saida);
					leRegistro(&reg2_aux, arq_entrada2);
				}
				else{
					if(reg1_aux.modelo < reg2_aux.modelo && !feof(arq_entrada1) ){
						escreveRegistro(&reg1_aux, arq_saida);
						escreveRegistro(&reg2_aux, arq_saida);
						leRegistro(&reg1_aux, arq_entrada1);
					}    
					else if(reg1_aux.modelo > reg2_aux.modelo && !feof(arq_entrada2) ){     
						escreveRegistro(&reg2_aux, arq_saida);
						sescreveRegistro(&reg1_aux, arq_saida);
						leRegistro(&reg2_aux, arq_entrada2);
					}
					else{
						if(reg1_aux.data < reg2_aux.data && !feof(arq_entrada1) ){
							escreveRegistro(&reg1_aux, arq_saida);
							escreveRegistro(&reg2_aux, arq_saida);
							leRegistro(&reg1_aux, arq_entrada1);
						}    
						else if(reg1_aux.data > reg2_aux.data && !feof(arq_entrada2) ){     
							escreveRegistro(&reg2_aux, arq_saida);
							escreveRegistro(&reg1_aux, arq_saida);
							leRegistro(&reg2_aux, arq_entrada2);
						}
						else if(reg1_aux.data == reg2_aux.data){
							escreveRegistro(&reg1_aux, arq_saida);
							escreveRegistro(&reg2_aux, arq_saida);
							leRegistro(&reg1_aux, arq_entrada1);
							leRegistro(&reg2_aux, arq_entrada2);
						}	
					}
				}
			}			
		}

		estado = '1';
		fseek(arq_entrada1, 0, SEEK_SET);	
		fwrite(&estado,1,1, arq_entrada1);
		fseek(arq_entrada2, 0, SEEK_SET);	
		fwrite(&estado,1,1, arq_entrada2);
		fseek(arq_saida, 0, SEEK_SET);	
		fwrite(&estado,1,1, arq_saida);

		fclose(arq_entrada1);
		fclose(arq_entrada2);
		fclose(arq_saida);
	}
		
	else if(func == 6) /* Multiway merging */
	{
		FILE** arqs_entrada = (FILE**) malloc( (argc-3) * sizeof(FILE*));

		for(r=0; r<(argc-3); r++) {
			estado = '0';
			arqs_entrada[r] = fopen(arguments[r+1], "r+b");
			fseek(arqs_entrada[r], 0, SEEK_SET);
			fwrite(&estado,1,1, arqs_entrada[r]);
			/*printf("Arquivo entrada %d: %s \n", r, arguments[r+1]);
			if(arqs_entrada[r] == NULL) printf("Erro ao abrir arquivo de entrada! \n");*/
		}
		FILE *arq_saida = fopen(arguments[argc-2], "w+b");
		fseek(arq_saida, 0, SEEK_SET);
		fwrite(&estado,1,1, arq_saida);
		/*printf("Arquivo saida: %s \n", arguments[argc-2]);
		if(arq_saida == NULL) printf("Erro ao abrir arquivo de saida! \n");*/

		multiway_merging(arqs_entrada, arq_saida, argc-3);
		estado = '1';

		for(r=0; r<(argc-3); r++) {
			fseek(arqs_entrada[r], 0, SEEK_SET);
			fwrite(&estado,1,1, arqs_entrada[r]);
			fclose(arqs_entrada[r]);
		}
		fseek(arq_saida, 0, SEEK_SET);
		fwrite(&estado,1,1, arq_saida);
		fclose(arq_saida);
	}
		
	else if(func == 7) /* Ordenação externa */
	{
		nome_arq1 = arguments[1];
		nome_arq2 = arguments[2];

		/*abre o arquivo a ser ordenado e muda o estatus para 0*/
		FILE *arquivo_ordenar, *arq_saida;
		arquivo_ordenar = fopen(nome_arq1, "r+b");
		fseek(arquivo_ordenar, 0, SEEK_SET);
		estado = '0';
		fwrite(&estado,1,1, arquivo_ordenar);


		r = 0;
		aux = 0;
		
		if (arquivo_ordenar != NULL){
			registro teste;
			/*conta quantos registros o arquivo possui*/
			while (!feof(arquivo_ordenar)){
				fread(&teste.n_vendas, sizeof(teste.n_vendas), 1, arquivo_ordenar);
				fread(&teste.infos, sizeof(teste.infos), 1, arquivo_ordenar);
				fread(&teste.modelo, sizeof(teste.modelo), 1, arquivo_ordenar);
				fread(&teste.data, sizeof(teste.data), 1, arquivo_ordenar);
				count++;
			}

			n = count;

			if(n % pag == 0) numS = n/pag;
			else numS = n/pag + 1;
			/*divide o arquivo original em subarquivos respeitando o tamanho do buffer de 1000 registros
			ordenando cada subarquivo em RAM*/
			reg = (registro *)malloc(n * sizeof(registro));
			fseek(arquivo_ordenar, 0, SEEK_SET);
			while(!feof(arquivo_ordenar) && x < n){
				for (s = 0; s < pag ; s++){
					if(feof(arquivo_ordenar) || x >= n){
					fread(&reg[s].n_vendas, sizeof(reg_auxiliar.n_vendas), 1, arquivo_ordenar);
					fread(&reg_auxiliar.infos, sizeof(reg_auxiliar.infos), 1, arquivo_ordenar);
					fread(&reg_auxiliar.modelo, sizeof(reg_auxiliar.modelo), 1, arquivo_ordenar);
					fread(&reg_auxiliar.data, sizeof(reg_auxiliar.data), 1, arquivo_ordenar);
							break;
					}
					fread(&reg[s].n_vendas, sizeof(reg[s].n_vendas), 1, arquivo_ordenar);
					fread(&reg[s].infos, sizeof(reg[s].infos), 1, arquivo_ordenar);
					fread(&reg[s].modelo, sizeof(reg[s].modelo), 1, arquivo_ordenar);
					fread(&reg[s].data, sizeof(reg[s].data), 1, arquivo_ordenar);
					aux++;
					x++;
				}
				heapSort(reg, pag);

				sprintf(subArq[r], "sub_%d.dat", r+1);
				sub[r] = fopen(subArq[r], "w+b");

				for (p = 0; p < aux; p++){
					fwrite(&reg[p].n_vendas, sizeof(reg[p].n_vendas), 1, sub[r]);
					fwrite(&reg[p].infos, sizeof(reg[p].infos), 1, sub[r]);
					fwrite(&reg[p].modelo, sizeof(reg[p].modelo), 1, sub[r]);
					fwrite(&reg[p].data, sizeof(reg[p].data), 1, sub[r]);
				}
				aux = 0;
				r++;
			}
			/*munda o status do arquivo orignal para 1 e o fecha*/
			fseek(arquivo_ordenar, 0, SEEK_SET);
			estado = '1';
			fwrite(&estado,1,1, arquivo_ordenar);
			fclose(arquivo_ordenar);

			for(k = 0; k < numS; k++){
				fclose(sub[k]);
			}
			/*Enquanto o número de subarquivos for maior do que um, realiza-se o merge com os subarquivos, par a par.
			Caso o número de subarquivos seja ímpar, o último é deixado para a próxima iteração.
			Cada subarquivo gerado permanece em disco após a operação*/
			num = numS;
			while(numS > 1){
				if(numS%2 == 0){
					numS = numS/2;
					for (i = 0; i < (numS); i++){
						sprintf(subArq[num], "sub_%d.dat", num*10);
						sub[num] = fopen(subArq[num], "w+b");
						sub[2*iter] = fopen(subArq[2*iter], "r+b");
						sub[(2*iter)+1] = fopen(subArq[(2*iter)+1], "r+b");

						sort_merge(sub[2*iter], sub[(2*iter)+1], sub[num]);
						/*Após o merge, caso o número de subarquivos for um, esse subarquivo é passado para o arquivo 
						de saída com nome determinado ao chamar o executável*/
						if(numS == 1){
							fseek(sub[num], 0, SEEK_SET);
							arq_saida = fopen(nome_arq2, "w+b");
							while(fread(&reg_auxiliar, sizeof(reg_auxiliar), 1,sub[num]) != 0 ){
								escreveRegistro(&reg_auxiliar, arq_saida);
							}
							fclose(arq_saida);
						}
						fclose(sub[2*iter]);
						fclose(sub[(2*iter)+1]);
						fclose(sub[num]);
						num++;
						iter++;
					}
					
				}else{
					if (numS%2 != 0){
						aux = numS - 1;
						for (j = 0; j < (aux/2); j++){
							sprintf(subArq[num], "sub_%d.dat", num*10);
							sub[num] = fopen(subArq[num], "w+b");
							sub[2*iter] = fopen(subArq[2*iter], "r+b");
							sub[(2*iter)+1] = fopen(subArq[(2*iter)+1], "r+b");

							sort_merge(sub[2*iter], sub[(2*iter)+1], sub[num]);
							fclose(sub[2*iter]);
							fclose(sub[(2*iter)+1]);
							fclose(sub[num]);
							num++;
							iter++;
						}
						numS = (numS/2) + 1;
					}
				}
				
			}

		
		if (flag_erro == 1)
			printf("Falha no processamento.\n");
		}
		else
			printf("Arquivo vazio.\n");


	}

    return 0;
}


void heapify(registro arr[], int n, int i) { 
	int largest = i; 
	int l = 2*i + 1; 
	int r = 2*i + 2; 
	registro aux;

	if (l < n && arr[l].n_vendas > arr[largest].n_vendas)
		largest = l;

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

	if (largest != i) 
	{ 
		aux = arr[i];
		arr[i] = arr[largest];
		arr[largest] = aux;
		heapify(arr, n, largest); 
	} 
 } 

void heapSort(registro arr[], int n) 
{ 
	int i;
    registro aux;
    for (i = n / 2 - 1; i >= 0; i--) 
		heapify(arr, n, i); 

	for (i = n-1; i>=0; i--){ 
		aux = arr[i];
		arr[i] = arr[0];
		arr[0] = aux;
		heapify(arr, i, 0); 
    } 
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

int encontra_menor(const registro *tmp, const int *valido, int n){
    int menor;
    int i;

    /*Encontra primeiro válido*/
    for (i = 0; i < n; i++) {
        if (valido[i]){
            menor = i;
            break;
        }
    }

    /*Compara com os demais (apenas com os válidos)*/
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

    registro *tmp = (registro *) malloc(n * sizeof(registro));
    int *valido = (int *) malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        /*Se valido[i] for menor que 1, deu erro ou EOF*/
        valido[i] = fread(&tmp[i], sizeof(registro), 1, arquivo[i]);
    }

    while(is_valid(valido, n)){
        menor_indice = encontra_menor(tmp, valido, n);
        fwrite(&tmp[menor_indice], sizeof(registro),1, arq_saida);
        valido[menor_indice] = fread(&tmp[menor_indice], sizeof(registro), 1, arquivo[menor_indice]);
    }
   
    free(tmp);
    free(valido);
}

void sort_merge(FILE* arquivo1, FILE* arquivo2, FILE* arquivo_saida){
		registro reg1_aux, reg2_aux;
		leRegistro(&reg2_aux, arquivo2);
		leRegistro(&reg1_aux, arquivo1);

		while (!feof(arquivo1) || !feof(arquivo2)){
			if( reg1_aux.n_vendas < reg2_aux.n_vendas && !feof(arquivo1) ){
				escreveRegistro(&reg1_aux, arquivo_saida);
				leRegistro(&reg1_aux, arquivo1);

			}
			else if(reg1_aux.n_vendas > reg2_aux.n_vendas && !feof(arquivo2) ){
				escreveRegistro(&reg2_aux, arquivo_saida);
				leRegistro(&reg2_aux, arquivo2);

			}
			else{   
				if(reg1_aux.infos < reg2_aux.infos && !feof(arquivo1) ){
					escreveRegistro(&reg1_aux, arquivo_saida);
					leRegistro(&reg1_aux, arquivo1);
	
				}    
				else if(reg1_aux.infos > reg2_aux.infos && !feof(arquivo2) ){     
					escreveRegistro(&reg2_aux, arquivo_saida);
					leRegistro(&reg2_aux, arquivo2);
				}
				else{
					if(reg1_aux.modelo < reg2_aux.modelo && !feof(arquivo1) ){
						escreveRegistro(&reg1_aux, arquivo_saida);
						leRegistro(&reg1_aux, arquivo1);
					}    
					else if(reg1_aux.modelo > reg2_aux.modelo && !feof(arquivo2) ){   
						escreveRegistro(&reg2_aux, arquivo_saida);
						leRegistro(&reg2_aux, arquivo2);
					}
					else{
						if(reg1_aux.data < reg2_aux.data && !feof(arquivo1) ){
							escreveRegistro(&reg1_aux, arquivo_saida);
							leRegistro(&reg1_aux, arquivo1);
						}    
						else if(reg1_aux.data > reg2_aux.data && !feof(arquivo2) ){     
							escreveRegistro(&reg2_aux, arquivo_saida);
							leRegistro(&reg2_aux, arquivo2);
						}
						else{
							escreveRegistro(&reg1_aux, arquivo_saida);
							escreveRegistro(&reg2_aux, arquivo_saida);
							leRegistro(&reg1_aux, arquivo1);
							leRegistro(&reg2_aux, arquivo2);
						}	
					}
				}
			}			
		}

}