/*
1) Dada uma lista de caracteres formada por uma sequência alternada de letras e dígitos, 
construa um método que retorne uma lista na qual as letras são mantidas na sequência original 
e os dígitos são colocados na ordem inversa.
Se a lista começa com uma letra, então termina com uma letra. Se a lista começa com um dígito, 
então termina por um dígito.
Exemplos:
- A 1 E 5 T 7 W 8 G → A 8 E 7 T 5 W 1 G
- 3 C 9 H 4 Q 6 → 6 C 4 H 9 Q 3

Considere a existência de um método ehDigito(ch caractere) que retorna true caso o caractere seja um digito e false caso contrário.

A sequência inicial pode ser armazenada em um vetor de caracteres, ou em uma lista encadeada (leitura como string, ou caracter a caracter).

Implemente o programa, utilizando fila e pilha na sua implementação (fila para manter as letras, e pilha para manter os números, ajudando na sua inversão). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

struct nodo{
    char item;
    struct nodo *prox;
};

typedef struct nodo Nodo;

void exibelista(Nodo *lst){
    while (lst != NULL)
    {
        printf("%c - ", lst->item);
        lst = lst->prox;
    }
}

void empilha(char valor, Nodo **lst){
    
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->item = valor;
    novo->prox = NULL;

    if (lst == NULL){
        *lst = novo;
    }
    else{
        novo->prox = *lst;
        *lst = novo;
    }
}

void enfileira(char valor, Nodo **ini, Nodo **fim){
    Nodo* aux_fim = *fim;

    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->item = valor;
    novo->prox = NULL;

    if (*ini == NULL){
        *ini = novo;
        *fim = novo;
    }

    else{
        aux_fim->prox = novo;
        *fim = novo;
    }
}

void lerlista(int tamanhoLista, Nodo **lst){
    int contador = 1;
    char valor = 'n';
    Nodo *fim_lista;

    printf("\nInforme uma sequencia de letras e numeros, intercalados (ate %d caracteres)\n", tamanhoLista);
    
    while(tamanhoLista > 0){
        printf("%d: ", contador);
        
        scanf(" %c", &valor);
        
        enfileira(valor, lst, &fim_lista);

        tamanhoLista--;
        
        contador++;
    }

    Nodo *aux = *lst;

    printf("\nA sua lista ficou na seguinte sequencia: \n");

    exibelista(aux);
}

void reordenalista(Nodo **lst, Nodo **topo, Nodo **fila_ini, Nodo **fila_fim){
    
    Nodo *aux = *lst;
    int pilha = 0;
    int fila = 0;
    
    while(aux != NULL){
        char valor = aux->item;

        if(isdigit(valor)){
            empilha(valor, topo);
            pilha ++;
        }
        else{
            enfileira(valor, fila_ini, fila_fim);
            fila ++;
        }
        aux = aux->prox;
    }


    printf("\nA sua lista numerica ficou na seguinte sequencia: \n");

    exibelista(*topo);

    printf("\nA sua lista de caracteres ficou na seguinte sequencia: \n");

    exibelista(*fila_ini);

    Nodo *aux_mais_longa;
    Nodo *aux_mais_curta;
    Nodo *aux_novo_ini;
    Nodo *aux_novo_fim;

    if(pilha > fila){
        aux_mais_longa = *topo;
        aux_mais_curta = *fila_ini;
    }
    else{
        aux_mais_longa = *fila_ini;
        aux_mais_curta = *topo;
    }

    char valor;
    int contador = pilha + fila;

    while(aux_mais_longa != NULL){
      

       valor = aux_mais_longa->item;
       enfileira(valor, &aux_novo_ini, &aux_novo_fim);

        if (aux_mais_curta != NULL){
            valor = aux_mais_curta->item;
            enfileira(valor, &aux_novo_ini, &aux_novo_fim);
            aux_mais_curta = aux_mais_curta->prox; 
        }

        aux_mais_longa = aux_mais_longa->prox;

        contador--;
        
    }

    printf("\nA sua nova lista ficou na seguinte sequencia: \n");
    exibelista(aux_novo_ini);


}

int main(){
    Nodo *lista = NULL;
    int tamanho;

    Nodo *pilha_topo = NULL;
    Nodo *fila_inicio = NULL;
    Nodo *fila_fim = NULL;

    printf("\nInforme o tamanho da lista (numero deve ser impar)\n");
    scanf("%d", &tamanho);

    lerlista(tamanho, &lista);
    reordenalista(&lista, &pilha_topo, &fila_inicio, &fila_fim);
}