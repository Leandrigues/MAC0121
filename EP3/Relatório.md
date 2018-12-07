# **EP3 - MAC0121**

***Como funciona seu algoritmo? Qual a ideia geral?***

A ideia do programa é, basicamente, percorrer o array das panquecas com uma variável que vai "diminuindo" o vetor como no selection sort, encontrar o valor máximo desse sub-vetor e jogá-lo para o final do array e depois flipar na posição da variável que percorre o array para que o valor máximo fique em sua posição correta. 

***Qual sua estimativa de complexidade de tempo de seu algoritmo para ordenar n panquecas?***

A complexidade é *O(n²)*, devido a um laço externo que percorre o vetor, enquanto um interno que percorre os subvetores à direita criados pelo lado externo.

***Qual o número mı́nimo e máximo de flips seu algoritmo faz para ordenar uma sequência?***

**Mínimo:** 0 flips (vetor já ordenado). Considerando apenas casos de vetor desordenado, 1 flip é o caso mínimo.

**Máximo:** Para um vetor de tamanho *n*, o algoritmo resolve em no máximo 2n-3 flips.

Como, para ordenar cada número é necessário 2 flips, temos, 2n flips. Porém, o último elemento não precisa ser flipado, tendo em vista que já estará em seu lugar certo, então temos 2n-2 (2 flips evitados) . O penúltimo elemento, por sua vez, só precisa de 1 flip para ser ordenado (ou zero), pois ele e o último formam um subvetor de 2 elementos, que podem estar na ordem correta ou não. Portanto, no pior caso, teremos 2n-3 flips.

***Mostre sequências em que seu algoritmo realiza o número máximo e mı́nimo de flips.***

**Mínimo:**

**1 2 3 4 5 6 7 8** 
flip(0): 8 7 6 5 4 3 2 1

Tamanho do vetor: 5 

Quantidade de flips: 1

**Máximo**: 

**3 9 1 5 7** 
flip(1): 3 7 5 1 9 
flip(0): 9 1 5 7 3 
flip(3): 9 1 5 3 7 
flip(1): 9 7 3 5 1 
flip(3): 9 7 3 1 5 
flip(2): 9 7 5 1 3 
flip(3): 9 7 5 3 1 

Tamanho do vetor: 5

Quantidade de flips: 7 (2n-3)

***Mostre sequências em que seu algoritmo não realiza o número mı́nimo possı́vel de flips para***
***ordenar uma sequência.***

**4 7 6 5 1 3 2** 
flip(1): 4 2 3 1 5 6 7 
flip(0): 7 6 5 1 3 2 4 
flip(3): 7 6 5 4 2 3 1 
flip(5): 7 6 5 4 2 1 3 
flip(4): 7 6 5 4 3 1 2 
flip(5): 7 6 5 4 3 2 1 

Tamanho do vetor: 7

Quantidade de flips: 6

**50 60 20 30** 
flip(1): 50 30 20 60 
flip(0): 60 20 30 50 
flip(1): 60 50 30 20 

Tamanho do vetor: 4

Quantidade de flips: 3

**1 3 2** 
flip(1): 1 2 3 
flip(0): 3 2 1 

Tamanho do vetor: 3

Quantidade de flips: 2

***Você consegue alguma estimativa para a qualidade do seu algoritmo, ou seja, por exemplo, o***
***número de flips dado por seu algoritmo é limitado por uma constante vezes o número ótimo***
***de flips? Ou, o número de flips do seu algoritmo é limitado por n (número de panquecas)***
***vezes o ótimo?***

No caso médio, em que elementos adjacentes do vetor **ordenado** não estão adjacentes no vetor **desordenado**, é posssível ordenar o vetor utilizando *n* flips. No meu algoritmo, o caso médio para este tipo de vetor é ordenado em cerca de **2n - c**, sendo **c** uma constante entre 3 e n-1.

***Imagine uma versão do problema em que as panquecas tenham um lado mais queimado que***
***deva ficar voltado para baixo. Seu algoritmo funciona neste caso?***

Considerando que as posições iniciais das panquecas (se estão para cima ou para baixo) sejam aleatórias, meu algoritmo não resolve este caso.

