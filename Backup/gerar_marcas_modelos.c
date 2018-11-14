#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
	char marcas[21][15] = {"Volkswagem","Chevrolet","Nissan","Toyota","Honda","Hyundai","Kia","Fiat","Ford","Renault","Audi","BMW","Dodge","Mitsubishi","Subaru","Mercedez","Cadillac","JAC","LIFAN","Pegeout","Citroen"};
    char modelos[121][15] = {"Gol", "Golf", "Virtus", "Amarok", "Polo", "Up", "Saveiro", "Jetta", "Passat", "S10", "Prisma", "Cobalt", "Celta", "Onix", "Cruze", "Zafira", "Spin", "Tracker", "Captiva","Corsa", "Frontier", "Versa", "Centra","Prius", "March", "Yaris", "Hilux", "Corolla", "Civic", "HR-V", "WR-V", "Fit", "Accord", "HB20", "ix35", "Tucson", "SantaFe", "VeraCruz", "Creta", "HB20-S", "HB20-X", "Azera", "Elantra", "Sorento", "Picanto", "Optima", "Cerato", "Sportage", "Uno", "Palio", "Punto", "Strada", "Toro", "Argo", "Cronos","Linea", "Ka", "Ranger", "Fiesta", "Focus", "Ecoesport", "Fusion", "Logan", "Sandero", "Kangoo", "Clio", "A3","A4","A8", "X-1","X-5","Ram", "Changer", "Chalenger", "L-2000", "Lancer", "ACX", "PajeroDakar", "PajeroTR4", "Forester", "Neo","ClasseA","ClasseB","ClasseE","Escalade","SRX","CTS-V","Calais","T40","J6","T5","J2","J5","T6","T8","530","X60","620","X80","208","308","408","2008","3008","5008","C3","Aircross","C4Louge","C4Picasso"};
    FILE *arq_texto;
    int i; 
    int j;
    arq_texto = fopen("Saída.txt", "w");
	if(arq_texto == NULL){
			printf("Erro, nao foi possivel abrir o arquivo\n");
	}
	else{
		for(i = 0; i<21;i++){
			for(j = 0; j<109;j++){
				printf("\n %s %s \n",marcas[i],modelos[j]);
				fprintf(arq_texto, " \n %s %s \n",marcas[i],modelos[j]);
			}	
		}
	}
	fclose(arq_texto);
	getchar();	
	return 0;
}
