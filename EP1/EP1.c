/*
  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES
  DESSE EP E QUE PORTANTO NÃO CONSTITUEM DESONESTIDADE ACADÊMICA
  OU PLÁGIO.  
  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR TODAS AS CÓPIAS
  DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO E
  DESONESTIDADE ACADÊMICA SERÃO TRATADOS SEGUNDO OS CRITÉRIOS
  DIVULGADOS NA PÁGINA DA DISCIPLINA.
  ENTENDO QUE EPS SEM ASSINATURA NÃO SERÃO CORRIGIDOS E,
  AINDA ASSIM, PODERÃO SER PUNIDOS POR DESONESTIDADE ACADÊMICA.

  Nome : Leandro Rodrigues da Silva
  Professor: Carlos Ferreira
  NUSP : 10723944
  Turma: 45 (BCC 2018)
*/

#include <stdio.h>
#include <stdlib.h>

// Função que calcula a quantidade de passos para cada numero dentro do intervalo
// digitado pelo usuário, além de inserir no vetor a quantidade de passos em suas respectivas
// posições.
int collatz (long int inicio, long int fim,  int *vetor)
{
    int flag, passos;
    long int percorreIntervalo, numAtual,posAtual, indiceVetor;
    for (percorreIntervalo = inicio; percorreIntervalo <= fim; percorreIntervalo++)
    {
        indiceVetor = percorreIntervalo - inicio;
        numAtual = percorreIntervalo;
        passos = 0;
        flag = 1; 
        while (numAtual != 1 && flag)
        {
            posAtual = numAtual - inicio;
            if (posAtual < fim-inicio && posAtual > 0 &&vetor[posAtual] !=0)
            {                passos+= vetor[posAtual];
                flag = 0;
            }
            if (flag && numAtual % 2 != 0)
            {   
                numAtual = (numAtual * 3) +1;
                passos++;
            }
            else if (flag)
            {
            numAtual = numAtual / 2;
            passos++;

            }
        }
        vetor[indiceVetor] = passos;
        printf("%d\n", passos);
    }
}

int main()
{
    long int inicio, fim;
    scanf("%ld %ld", &inicio, &fim);
    int *vetor; 
    // Cria um vetor do tamanho do intervalo digitado pelo usuário
    vetor = malloc((fim-inicio+1) * sizeof(int *));
    for (int k = 0; k <= fim; k++)
    {
        vetor[k] = 0;
    }
    // Chama a função que calcula a conjectura de Collatz.
    collatz(inicio, fim, vetor);
    free(vetor);
}

