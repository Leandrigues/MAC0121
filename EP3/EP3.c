#include <stdio.h>
#include <stdlib.h>

void flip(int* panquecas, int n, int indice){
    /* Função que executa o flip */
    int i, k, aux;

    for(i = indice, k = n-1; i < k;k--, i++){
        aux = panquecas[i];
        panquecas[i] = panquecas[k];
        panquecas[k] = aux;
    }
}

void flipaPanquecas(int* panquecas, int n){
    /* Função que executa a ordenação */
    int i, j, max, flips = 0;
    for(i = 0; i < n; i++){
        max = i;
        for(j = i; j < n; j++){
            if (panquecas[j] > panquecas[max]){
                max = j;
            }
        }
        
        if(max != i){
            if(max != n-1){
                printf("%d ", max);
                flip(panquecas, n, max);
                flips++;
            }
            printf("%d ", i);
            flip(panquecas, n, i);
            flips++;
        }
    }
}

int main(){
    int n, *panquecas, i;
    scanf("%d", &n);
    panquecas = malloc(sizeof(int)*n);
    for(i = 0; i < n; i ++){
        scanf("%d" , &panquecas[i]);
    }
    flipaPanquecas(panquecas, n);
}