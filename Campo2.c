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


void verificarRepeticaoCampoDois(int i, int* volume){
	for(int j = (i-1); j >= 0; j--){
		if(volume[i] == volume[j]){
			volume[i] = 40 + rand()%470;
			verificarRepeticaoCampoDois(i,volume);
		    break;
		}
	}
}

char** gerarCampoDois(int n, registro* reg){
    char alimentacao[5][9] = {"ELETRICO", "FLEX", "GASOLINA", "ALCOOL", "HIBRIDO"};
    char motor[10][4] = {"1.0", "1.3", "1.5", "1.6", "1.8", "2.0", "2.8", "3.0", "3.8", "4.4"};
    int volume[n];
	srand((unsigned)time(NULL)); //Semente da random
    char campo_2[30];
    //char* campo_2 = (char*)malloc (30 * sizeof(char));
    char str[4];
    char** campo2 = malloc (n * sizeof (char *));
    for(int t = 0; t < n; t++) campo2[t] = malloc(30*sizeof (char));
	
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
                //campo2[m] = campo_2;
               // printf("%s %d %s\n", campo_2, m, campo2[m]);
                m++;
                if(m >= n*0.75) break;
            }
            if(m >= n*0.75) break;
            //printf("%d %s\n", m, campo2[m-1]);
        }
        //printf("%d %s\n", m, campo2[m-1]);
    }

    i = (n*0.75);
	//25% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < (0.25*n); j++){ 
		strcpy(reg[i].infos, reg[j].infos); 
        i++;
	}
    return campo2;
} 


int main(){
	//gerarCampoUm();
    int n = 100;
    char** campo2;
    registro reg[n];
    /*char *campo2[30];
    campo2[0] = "oi, tudo bem?\n";
    printf("%s", campo2[0]);*/
	campo2 = gerarCampoDois(n, reg);
    for(int i = 0; i < 100; i++) printf("%d   %s\n", i, reg[i].infos);

    //for(int i = 0; i < n; i++) printf("%d   %s\n", i, campo2[i]);
	return 0;
}