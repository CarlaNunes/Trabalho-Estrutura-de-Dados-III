#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int n_vendas;
  char infos[30];
  char modelo[20];
  char data[10];
} Registro;

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

int main(int argc, char *argv[]) {
    int n = 2;//Considerando no caso 2 arquivos de teste.
	FILE** arquivo = (FILE**) malloc(n * sizeof(FILE*));//Criar e alocar vetor de arquivos pois, não sabemos quantos iremos usar.
	FILE *arq_saida;

    char nome[20];
    int i;

    for (i = 0; i < n; i++){
        sprintf(nome, "%darq.dat", (i+1));
        arquivo[i] = fopen(nome,"r+b");
        if (arquivo[i] == NULL){
            printf("Erro, nao foi possivel abrir o arquivo de entrada %s\n", nome);
            exit(1);
        }
    }

	arq_saida = fopen("multiway.dat", "w+b");

    if(arq_saida  == NULL){
        printf("Erro, nao foi possivel abrir o arquivo de saída\n");
        exit(1);
    }

    multiway_merging(arquivo, arq_saida, n);


    for (i = 0; i < n; i++) {
        fclose(arquivo[i]);
    }
    fclose(arq_saida);

    free(arquivo);
    return(0);
}
