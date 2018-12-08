#ifndef MANIPULARARQUIVO_H

    #include <stdio.h>
    #include <stdlib.h>

    typedef struct
    {
        int n_vendas;
        char infos[30];
        char modelo[20];
        char data[10];
    } registro;

    int verificarRepeticaoCampoUm(registro*, int);

    void verificarRepeticaoCampoDois(int, int*);

    int verificaRepeticoesCampoTres(registro*, char*, int);

    int verificaRepeticoesCampoQuatro(registro*, char*, int);

    void gerarCampoUm(int, registro*);

    void gerarCampoDois(int, registro*);

    void gerarCampoTres(int, registro*);

    void gerarCampoQuatro(int, registro*);

    void escreveRegistro(registro*, FILE*);

    void leRegistro(registro*, FILE*);

    void imprimeRegistro(registro*);

#endif