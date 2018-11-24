#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merging(FILE *arquivo1, FILE *arquivo2, FILE *arquivo_saida){
	 size_t len= 100;
	 int i = 0;
	 int j = 0;

	 int arq1_eof, arq2_eof;

	 
	 char *nome1 = (char *) malloc(len*sizeof(char));
	 char *nome2 = (char *) malloc(len*sizeof(char));


    //Merge
    while ((!feof(arquivo1)) && (!feof(arquivo2)))
    {
        
        printf(" \n Nome1: %s", nome1);
        printf(" \n Nome2: %s", nome2);
        
       
        if(strcmp(nome1, nome2) < 0){

          fwrite (&nome1, sizeof(char),1, arquivo_saida);
          arq1_eof = getline(&nome1, &len, arquivo1);
        }
        else if(strcmp(nome1, nome2) > 0){
           // printf(" \n Nome1: %s", nome1);
         
           fwrite (&nome1, sizeof(char),1, arquivo_saida);
           arq2_eof = getline(&nome2, &len, arquivo2);
            
        }
         else{                        
            fwrite (&nome1, sizeof(char),1, arquivo_saida);
            arq1_eof = getline(&nome1, &len, arquivo1);
            arq2_eof = getline(&nome2, &len, arquivo2);  
         }
    }

    //Termina de colocar o arq1 (se não foi ele o que acabou)
    while (!feof(arquivo1)){
      fwrite (&nome1, sizeof(char),1, arquivo_saida);
       arq1_eof = getline(&nome1, &len, arquivo1);
    }

    //Termina de colocar o arq2 (se não foi ele o que acabou)
    while (!feof(arquivo2)){
       fwrite (&nome1, sizeof(char),1, arquivo_saida);
       arq2_eof = getline(&nome2, &len, arquivo2);
    }

}

int main(int argc, char *argv[]) {
	FILE *arquivo1,*arquivo2,*arquivo_saida;
	
  arquivo1 = fopen("1arquivo.dat", "r+b");
	arquivo2 = fopen("2arquivo.dat", "r+b");
	arquivo_saida = fopen("merging.dat", "w+b");

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
         
  			//merging(arquivo1,arquivo2,arquivo_saida);
  		}

   

 
  fclose(arquivo1);
  fclose(arquivo2);
  fclose(arquivo_saida);


  return(0);
}
