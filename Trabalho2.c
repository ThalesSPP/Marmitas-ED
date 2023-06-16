#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct pedido{
    int cod;
    char hora[6];
    char tam;
    char nome[50];
    char local[100];
    struct pedido *prox;
} Pedido;

Pedido *lista = NULL;

void fazerPedido();
void realizarEntrega();
void exibirPedidos();
void ordenarPedidos();

/*A função main simplesmente têm um switch case que repassa o serviço para as funções respectivas de cada opção*/

int main(void){

    int escolha = 0;
    while(escolha != 5){
        printf("Delivery de Marmitas\n");
        printf("1 - Fazer Pedido\n");
        printf("2 - Realizar Entrega\n");
        printf("3 - Exibir Pedidos\n");
        printf("4 - Ordenar Pedidos\n");
        printf("5 - Sair\n");

        printf("\nDigite a sua escolha: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                fazerPedido();

                break;
            case 2:
                realizarEntrega();

                break;
            case 3:
                exibirPedidos();

                break;
            case 4:
                ordenarPedidos();

                break;
            case 5:
                return 0;
            default:
                printf("\nEscolha invalida!\n");
        }
    }

    return 0;
}

/*A função fazerPedido solicita ao usuário os detalhes de um novo pedido e cria uma nova estrutura 
Pedido para armazená-lo. Em seguida, verifica se a lista está vazia e, se estiver, atribui o novo 
pedido à variável lista. Caso contrário, percorre a lista até o último pedido e adiciona o novo pedido no final.*/

void fazerPedido(){

    Pedido *novoPedido = (Pedido *) malloc(sizeof(Pedido));
    novoPedido->prox = NULL;

    printf("\nDigite o codigo do pedido: ");
    scanf("%d", &novoPedido->cod);

    printf("Digite a hora do pedido (HH:MM): ");
    scanf("%s", novoPedido->hora);

    printf("Digite o tamanho da marmita (P, M, G): ");
    scanf(" %s", &novoPedido->tam);

    printf("Digite o nome do cliente: ");
    scanf("%s", novoPedido->nome);

    printf("Digite a localizacao do cliente: ");
    scanf(" %[^\n]s", novoPedido->local);

    if(lista == NULL){
        lista = novoPedido;
    } 
    
    else{
        Pedido * atual = lista;

        while(atual->prox != NULL){
            atual = atual->prox;
        }

        atual->prox = novoPedido;
    }

    printf("\nPedido adicionado com sucesso!\n\n");
}

/*A função realizarEntrega solicita ao usuário o código do pedido entregue. Em seguida, percorre a 
lista de pedidos procurando por um pedido com o código correspondente. Se encontrar o pedido, remove-o 
da lista, exibe suas informações e libera a memória alocada para ele.*/

void realizarEntrega(){

    int cod;

    printf("\nDigite o codigo do pedido entregue: ");
    scanf("%d", &cod);

    if(lista == NULL){
        printf("Nao ha pedidos na lista.\n");
    }
    
    else{
        Pedido *anterior = NULL;
        Pedido *atual = lista;
        
        while(atual != NULL){

            if(atual->cod == cod){

                if(anterior == NULL){
                    lista = atual->prox;
                }
                
                else{
                    anterior->prox = atual->prox;
                }

                printf("\nPedido entregue\n");
                printf("Detalhes do pedido:\n");
                printf("Codigo: %d\n", atual->cod);
                printf("Hora: %s\n", atual->hora);
                printf("Tamanho da marmita: %c\n", atual->tam);
                printf("Nome do cliente: %s\n", atual->nome);
                printf("Localizacao: %s\n", atual->local);

                free(atual);

                return;
            }

            anterior = atual;
            atual = atual->prox;
        }

        printf("Nao foi encontrado pedido com este codigo.\n\n");
    }
}

/*A função exibirPedidos percorre a lista de pedidos e exibe as informações de cada pedido na tela.
Se a lista estiver vazia, exibe uma mensagem informando que não há pedidos.*/

void exibirPedidos(){

    if(lista == NULL){
        printf("\nNao ha pedidos na lista.\n\n");
    } 
    
    else{
        printf("\nPedidos:\n");
        Pedido *atual = lista;

        while(atual != NULL){

            printf("\nCodigo: %d\n", atual->cod);
            printf("Hora: %s\n", atual->hora);
            printf("Tamanho da marmita: %c\n", atual->tam);
            printf("Nome do cliente: %s\n", atual->nome);
            printf("Localizacao: %s\n", atual->local);
            printf("\n\n");

            atual = atual->prox;
        }
    }
}

/*A função ordenarPedidos permite ao usuário escolher um critério de ordenação (por hora do pedido ou por 
tamanho da marmita). Em seguida, utiliza o algoritmo de ordenação Bubble Sort para ordenar a lista de pedidos 
com base no critério escolhido.*/

void ordenarPedidos(){
    if(lista == NULL || lista->prox == NULL){
        printf("\nO numero de pedidos e inferior a 2, dessa forma nao precisa de ordenacao.\n");

        return;
    }

    int opcao;

    printf("\nEscolha a ordenacao desejada:\n");
    printf("1 - Por Hora do pedido\n");
    printf("2 - Por Tamanho da Marmita\n");

    printf("Digite a sua escolha: ");
    scanf("%d", &opcao);

    Pedido *atual;
    Pedido *anterior;

    int troca;

    switch(opcao){
        case 1: 
            while(troca){
                troca = 0;
                anterior = NULL;
                atual = lista;

                while(atual->prox != NULL){
                    Pedido *proximo = atual->prox;

                    if(strcmp(atual->hora, proximo->hora) > 0){
                        troca = 1;

                        if(anterior != NULL){
                            anterior->prox = proximo;
                        }

                        else{
                            lista = proximo;
                        }

                        atual->prox = proximo->prox;
                        proximo->prox = atual;
                        anterior = proximo;
                    }

                    else{
                        anterior = atual;
                        atual = atual->prox;
                    }
                }
            }

            printf("\nPedidos ordenados por Hora do pedido.\n\n");

            break;
        case 2:
            while(troca){
                troca = 0;
                anterior = NULL;
                atual = lista;

                while(atual->prox != NULL){
                    Pedido *proximo = atual->prox;

                    if((atual->tam == 'G' && proximo->tam != 'G') || (atual->tam == 'g' && proximo->tam != 'g')){
                        troca = 1;
                        if(anterior != NULL){
                            anterior->prox = proximo;
                        }

                        else{
                            lista = proximo;
                        }

                        atual->prox = proximo->prox;
                        proximo->prox = atual;
                        anterior = proximo;
                    }

                    else if((atual->tam == 'M' && proximo->tam == 'P') || (atual->tam == 'm' && proximo->tam == 'p')){
                        //fiquei literalmente duas horas para descobrir que tinha que usar as aspas simples ao inves das duplas =(
                        troca = 1;

                        if(anterior != NULL){
                            anterior->prox = proximo;
                        }

                        else{
                            lista = proximo;
                        }

                        atual->prox = proximo->prox;
                        proximo->prox = atual;
                        anterior = proximo;
                    }

                    else{
                        anterior = atual;
                        atual = atual->prox;
                    }
                }
            }

            printf("\nPedidos ordenados por Tamanho da Marmita.\n\n");

            break;
        default:
            printf("\nEscolha invalida.\n\n");
    }
}