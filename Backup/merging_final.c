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


void merging(FILE *arquivo1, FILE *arquivo2, FILE *arquivo_saida){
		 Registro nome1,nome2;

	  //Merge ordenando por vendas
     
       fread(&nome1, sizeof(Registro), 1, arquivo1);
       fread(&nome2, sizeof(Registro), 1, arquivo2);
       
    do {
       
        fread(&nome1, sizeof(Registro), 1, arquivo1);
        fread(&nome2, sizeof(Registro), 1, arquivo2);
        if(nome1.n_vendas < nome2.n_vendas){
          printf("\n %d, %s, %s, %s ",nome1.n_vendas, nome1.infos,nome1.modelo,nome1.data);
          fwrite (&nome1, sizeof(char),1, arquivo_saida);
          //arq1_eof = getline(&nome1, &len, arquivo1);
        }
        else if(nome1.n_vendas > nome2.n_vendas){
           fwrite (&nome2, sizeof(Registro),1, arquivo_saida);
            
        }
         else{                        
            fwrite (&nome1, sizeof(char),1, arquivo_saida);
          }

        
    
    } while (!feof(arquivo1)&& !feof(arquivo1) ); // enquanto não chegar ao final do arquivo

       
}

int main(int argc, char *argv[]) {
	FILE *arquivo1,*arquivo2,*arquivo_saida;
	
    arquivo1 = fopen("1arquivo.dat", "r+b");
	arquivo2 = fopen("2arquivo.dat", "r+b");
	arquivo_saida = fopen("merging_2.dat", "w+b");

	if(arquivo1 == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }

	  
	 if(arquivo2 == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }

  

	  if(arquivo_saida == NULL){
	      printf("Erro, nao foi possivel abrir o arquivo\n");
	  }

  		else{
           
  			merging(arquivo1,arquivo2,arquivo_saida);
  		}

   

 
  fclose(arquivo1);
  fclose(arquivo2);
  fclose(arquivo_saida);


  return(0);
}
