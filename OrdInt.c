#include <stdio.h>
#include "registro.h"

int main(){
    tEntrada aluno, novoAluno;
    FILE *arquivo;
    int achou; // logico

    arquivo = fopen("notas.dat", "r+");
    if(!arquivo)
        perror("O arquivo nao foi aberto");
    else{
        /* leitura dos dados do aluno*/
        printf("RA: ");
        scanf("%d", &novoAluno.ra);
        printf("Nota: ");
        scanf("%f", &novoAluno.nota);

        /* busca pelo registro do aluno */
        achou = 0; // falso
        while(!achou && fread(&aluno, sizeof(aluno), 1, arquivo) != 0)
            if(aluno.ra == novoAluno.ra)
            achou = 1; // verdadeiro

            /* verifica o fim do while */
        if(achou){

            /* retorna a posição corrente
            para o inicio do registro */
            fseek(arquivo, -sizeof(aluno), SEEK_CUR);

            /* escreve todo o registro novo
            sobre o anterior */
            fwrite(&novoAluno, sizeof(novoAluno),
            1, arquivo);
            printf("Registro alterado\n"); 
        else{
            /* aproveita que a posicao corrente
            esta no fim do arquivo e escreve */
            fwrite(&novoAluno, sizeof(novoAluno),
            1, arquivo);
            printf("Novo registro acrescentado\n");
        }
        /* fecha o arquivo */
        fclose(arquivo);
    }
    return 0;
}