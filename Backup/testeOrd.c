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

void heapify(registro arr[], int n, int i) 
{ 
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
                //trata campo3
                if(strcmp(arr[l].data, arr[largest].data) > 0){
                    largest = l;
                }
            }
        }
    }
    
    if (r < n && arr[r].n_vendas == arr[largest].n_vendas){
         if(strcmp(arr[r].infos, arr[largest].infos) > 0){
            largest = r; 
        }else{
            if(strcmp(arr[r].infos, arr[largest].infos) == 0){
                //trata campo3
                if(strcmp(arr[r].data, arr[largest].data) > 0){
                    largest = r;
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
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    /*int vetor[5]= {5,4,8,7,7};
    heapSort(vetor, 5);
    for(int i = 0; i < 5; i++) printf("%d\n", vetor[i]);*/
    registro regs[n];
    FILE *arquivo, arquivores;
    arquivo = fopen("notas.dat", "rb");
    fseek(arquivo, 0, SEEK_SET);
    for(int r = 0; r < n; r++){
        fread(&regs[r].n_vendas, sizeof(regs[r].n_vendas), 1, arquivo);
        fread(&regs[r].infos, sizeof(regs[r].infos), 1, arquivo);
        fread(&regs[r].data, sizeof(regs[r].data), 1, arquivo);
       // printf("%d %s %s\n", regs[r].n_vendas, regs[r].infos, regs[r].data);
    }
    heapSort(regs, n);
    for(int r = 0; r < n; r++) printf("%d %s %s\n", regs[r].n_vendas, regs[r].infos, regs[r].data);
    fclose(arquivo); 
    return 0;
}