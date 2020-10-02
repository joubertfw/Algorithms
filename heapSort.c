/*HeapSort: V[0...m]
    -O indice 0 e a raiz da arvore
    -O pai de qualquer indice f a f/2 (piso)
    -O filho esq de um indice p a 2p + 1 (ele so existe se 2p + 1 <= m)
    -O filho dir de um indice p a 2p + 2 (ele so existe se 2p + 2 <= m)
    -O valor de todo pai e maior ou igual que seus dois filhos: V[f/2] >= V[f]
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long comps = 0, copies = 0;

void troca (int V[], int a, int b){
    int aux = V[a];
    V[a] = V[b];
    V[b] = aux;
    copies += 3;
}

void heapify (int V[], int i, int f){   //Funcao que organiza os valores em forma de heap
    int left = 2*i + 1, right = 2*i + 2, maior = i;   //define os filhos de i
    comps++;
    if (left <= f && V[left] > V[maior])
        maior = left;
    comps++;
    if (right <= f && V[right] > V[maior])
        maior = right;
    comps++;
    if (maior != i){
        troca(V, i, maior);
        heapify(V, maior, f);
    }
}

void HS (int V[], int i, int f){
    int cont, size = f - i + 1;
    comps++;
    for (cont = (int) size/2 - 1; cont >= 0; cont--){
        comps++;
        heapify(V, cont, f);
    }
    comps++;
    for (cont = f; cont > 0; cont--){
        comps++;
        troca(V, 0, cont);
        f--;
        heapify(V, 0, f);
    }
}

void imprimeVetor(int *V, int tam){
    int i;
    for (i = 0; i < tam; i++)
        printf("%d\n", V[i]);
}

int* lerArquivo (char *argv, int *tam){
    FILE *f = fopen (argv, "r");
    if(f == NULL){
        printf("Arquivo nao encontrado.");
        return NULL;
    }
    int i;
    while (fscanf(f, "%d ", &i) != EOF)
        (*tam)++;
    int *V = (int*) calloc (*tam, sizeof(int));
    rewind(f);
    for (i = 0; i < *tam; i++)
        fscanf(f, "%d ", &V[i]);
    fclose(f);
    return V;
}

int main (int argc, char* argv[]){
    if (argc < 2){
        printf("Argumentos insuficientes.");
        return -1;
    }
    int tam = 0, i, *V = lerArquivo(argv[1], &tam);
    if (V == NULL){
        printf("Vetor esta vazio!");
        return -1;
    }
    printf("\nO vetor nao ordenado:\n");
    //imprimeVetor(V, tam);
    printf("\nVetor ordenado:\n");
    clock_t tempo;
    tempo = clock();
    HS(V, 0, tam - 1);
    tempo = clock() - tempo;
    //imprimeVetor(V, tam);
    printf("\nTempo de execucao: %lf ms", ((double) tempo*1000)/(CLOCKS_PER_SEC));
    printf("\nQtd de comparacoes: %ld", comps);
    printf("\nQtd de copias: %ld\n", copies);
    return 0;
}
