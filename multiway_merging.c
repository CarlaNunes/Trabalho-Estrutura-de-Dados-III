//Dando problema de leitura
//Imaginei vetores de arquivos e de registros,pois, não sabemos quantos arquivos iremos usar.

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


void multiway_merging(FILE **arquivo, FILE *arq_saida , int n){
    int i = 0,j = 0;

    Registro menor;
        struct  Registro *nome = malloc(n * sizeof(struct Resgistro));


       for(i = 0;i < n; i++){
         fread(&nome[i], sizeof(Registro), 1, arquivo[i]);
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

        } while (!feof(arquivo[i]) ); // enquanto não chegar ao final do arquivo



    }

 free(nome);

}

int main(int argc, char *argv[]) {
    int n = 2;
	FILE** arquivo = malloc(sizeof(FILE*) * (n-1));//Criar e alocar vetor de arquivos pois, não sabemos quantos iremos usar.
	FILE *arq_saida;

    //Estou considerando somente 2 arquivos no teste.
    arquivo[0] = fopen("notas.dat", "r+b");
	arquivo[1] = fopen("notas2.dat", "r+b");
	arq_saida = fopen("multiway.dat", "w+b");

	if(arquivo[0] == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }


	 if(arquivo[1] == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }



	  if(arq_saida  == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }

  		else{

  			multiway_merging(*arquivo,arq_saida ,n);
  		}




  fclose(arquivo[0]);
  fclose(arquivo[1]);
  fclose(arq_saida);

  free(arquivo);


  return(0);
}
