#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char marcas[15][15] = {"Volkswagem","Chevrolet","Nissan","Toyota","Honda","Hyundai","Kia","Fiat","Ford","Renault","Audi","BMW","Dodge","Mitsubishi","Subaru"};
   // char modelos[83][15] = {"Gol", "Golf", "Virtus", "Amarok", "Polo", "Up", "Saveiro", "Jetta", "Passat", "S10", "Prisma", "Cobalt", "Celta", "Onix", "Cruze", "Zafira", "Spin", "Tracker", "Captiva","Corsa", "Frontier", "Versa", "Centra","Prius", "March", "Yaris", "Hilux", "Corolla", "Civic", "HR-V", "WR-V", "Fit", "Accord", "HB20", "ix35", "Tucson", "SantaFe", "VeraCruz", "Creta", "HB20-S", "HB20-X", "Azera", "Elantra", "Sorento", "Picanto", "Optima", "Cerato", "Sportage", "Uno", "Palio", "Punto", "Strada", "Toro", "Argo", "Cronos","Linea", "Ka", "Ranger", "Fiesta", "Focus", "Ecoesport", "Fusion", "Logan", "Sandero", "Kangoo", "Clio", "A3","A4","A8", "X-1","X-5","Ram", "Changer", "Chalenger", "L-2000", "Lancer", "ACX", "PajeroDakar", "PajeroTR4", "Forester", "Neo"};
    FILE *arq_texto;
    int i; 
    int j;
    arq_texto = fopen("Saída.txt", "w");
	if(arq_texto == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
	}
	else{
		for(i = 0; i<15;i++){
			for(j = 0; j<551;j++){
				if(i == 0 && j<=10){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);
				}
			
				if(i == 1 &&  j>=10 && j<=19){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

				}
				if(i == 2 && j>15 && j<=19 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);


				}
				if(i == 3 && j>15 && j<=19 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);


				}
					
				if(i == 4 && j>19 && j<=30 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			
				if(i == 5 && j>30 && j<=50 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	

			if(i == 6 && j>50 && j<=80 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			if(i == 7 && j>80 && j<=100 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			
			if(i == 8 && j>100 && j<=160 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			if(i == 9 && j>160 && j<=200 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			if(i == 10 && j>200 && j<=250 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			if(i == 11 && j>250 && j<=300 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			if(i == 12 && j>350 && j<=400 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			
			if(i ==  13 && j>400 && j<=450 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}	
			
			if(i == 14 && j>450 && j<=500 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}

			if(i == 15 && j>500 && j<=550 ){
					printf("\n %s Modelo C%d",marcas[i],j);
					fprintf(arq_texto, " \n %s Modelo C%d",marcas[i],j);

			
			}		
		}
	}
}
	fclose(arq_texto);
	getchar();	
	return 0;
}
