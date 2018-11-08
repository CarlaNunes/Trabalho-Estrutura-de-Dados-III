#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void verificarRepeticaoCampoDois(int i, int* volume){
	for(int j = (i-1); j >= 0; j--){
		if(volume[i] == volume[j]){
			volume[i] = 40 + rand()%470;
			verificarRepeticaoCampoDois(i,volume);
			break;
		}
	}
}

void gerarCampoDois(int n, char** campo2){
    char alimentacao[5][9] = {"ELETRICO", "FLEX", "GASOLINA", "ALCOOL", "HIBRIDO"};
    char motor[10][4] = {"1.0", "1.3", "1.5", "1.6", "1.8", "2.0", "2.8", "3.0", "3.8", "4.4"};
    int volume[n];
	srand((unsigned)time(NULL)); //Semente da random
    char* campo_2 = (char*)malloc (30 * sizeof(char));
    char str[4];

	
	//O primeiro valor é setado fora do loop pois não é necessario verificarRepeticao
	volume[0] = 40 + rand()%470;
	
	//70% dos valores do Campo1 não podem ser repetidos
	int i, j, k, m = 0;

    for(i = 0; i < (n*0.75); i++){
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
                //campo2[m] = campo_2;
                //printf("%s %d %s\n", campo_2, m, campo2[m]);
                
            }
        }
        campo2[m] = campo_2;
        m++;
    }
    /*i = (n*0.75);
	//25% dos valores do Campo1 devem ser repetidos
	for(int j = 0; j < (0.25*n); j++){ 
		campo2[i] = campo_2; 
        i++;
	}*/
} 


int main(){
	//gerarCampoUm();
    int n = 100;
    char** campo2 = malloc (n * sizeof (char *));
	gerarCampoDois(n, campo2);

    for(int i = 0; i < 75; i++) printf("%d   %s\n", i, campo2[i]);
	return 0;
}