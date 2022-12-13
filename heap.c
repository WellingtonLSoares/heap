#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP* HEAP_create(int n, COMP* compara){
    HEAP* heap = malloc(sizeof(HEAP));
    heap-> comparador = compara;
    heap-> N = n;
    heap-> P = 0;
    heap-> elems = malloc(n * sizeof(void *));

    // zerando a heap
    for (int i = 0; i < n; i++) {
        heap-> elems[i] = NULL;
    }

    return heap;
}

void HEAP_add(HEAP* vetor, void* newelem){
    if (vetor-> P < vetor-> N) { // verifica se a heap está cheia
        if (vetor-> P == 0) { // verifica se a heap está vazia
            vetor-> elems[0] = newelem; // add o primeiro elemento
            vetor-> P += 1;
        } else {
            vetor-> elems[vetor-> P] = newelem; // add no primeiro espaço vazio da heap
            vetor-> P += 1;

            for (int i = vetor-> P - 1; i > 0; i = i/2) { // percorre a heap começando ultimo elemento ate o primeiro
                if (vetor-> comparador(vetor-> elems[i], vetor-> elems[i/2]) == 1) { // se elems[i] < elems[i/2]
                    void* aux = vetor-> elems[i];
                    vetor-> elems[i] = vetor-> elems[i/2]; // movendo os elementos na heap
                    vetor-> elems[i/2] = aux;
                }
            }
        }
    }
}

void move(HEAP* vetor, int pos){
    if(2 * pos < vetor-> P){
        int son = 2 * pos;

        if (2 * pos + 1 < vetor-> P) {
            if(vetor-> comparador(vetor-> elems[2*pos], vetor-> elems[2 * pos + 1]) == 1) { // se elems[2*pos] < elems[2 * pos + 1]
                son = 2 * pos; // son = 2p
            }
            else{
                son = 2 * pos + 1; // son = 2p + 1
            } 
        }
        if (vetor->comparador(vetor-> elems[son], vetor-> elems[pos]) == 1) { // se son < pos
            void* aux = vetor-> elems[son];
            vetor-> elems[son] = vetor-> elems[pos]; // organizando a heap
            vetor-> elems[pos] = aux;

            move(vetor, son);
        }
    }
}

void* HEAP_remove(HEAP* vetor){
    void* aux = vetor-> elems[0]; // aux recebe o maior elemento
    vetor-> elems[0] = vetor-> elems[vetor-> P - 1];
    vetor-> elems[vetor-> P - 1] = aux;
    vetor-> P -= 1; // atualizando a lista

    move(vetor, 0); // organizando a heap apos as mudanças

    return vetor-> elems[vetor-> P];
}