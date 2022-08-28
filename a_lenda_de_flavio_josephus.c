#include <stdio.h>
#include <stdlib.h>

//AGORA EU CONSEGUI FAZER ESSA PORRA SEM OLHAR NA INTERNET, COM MINHA PRÓPRIA CAPACIDADE. SOU FODA BIXO!

typedef struct no{
    int valor;//Valor do nosso nó.
    struct no *proximo;//Usamos um ponteiro para apontar ao próximo nó.
}No;//Criamos nosso tipo de dado nó.

typedef struct{
    No *inicio;//Aqui guardaremos um ponteiro que vai apontar o início da nossa lista.
    No *fim;//Aqui guardaremos um ponteiro que vai apontar o fim da nossa lista.
    int tam;//Aqui será guardado o tamanho atual da lista.
}Lista;//Criamos nosso tipo de dado lista.

void criar_lista(Lista *lista){
    lista->inicio = NULL;//Ela ainda está vazia, portanto não existe um nó de início.
    lista->fim = NULL;//Ela ainda está vazia, portanto não existe um nó de fim.
    lista->tam = 0;//Tamanho 0.
}//Iniciamos as características da nossa lista.

// procedimento para inserir no fim
void inserir(Lista *lista, int num){
    No *aux, *novo = malloc(sizeof(No));//Alocando memória para nosso novo nó.

    if(novo){//Se deu tudo certo na alocação de memória, prosseguir.
        novo->valor = num;//Já atribuindo nosso valor do novo nó que estamos fazendo.
        
        if(lista->inicio == NULL) {//Essa condição verifica se a lista está vazia, e portanto, se o nosso novo nó vai ser o primeiro da lista.
        	lista->inicio = novo;//Agora, nosso novo início da lista vai ser o nó que acabamos de criar.
			lista->fim = novo;//Agora, nosso novo fim da lista vai ser o nó que acabamos de criar.
			lista->fim->proximo = lista->inicio;//O nosso último nó(e primeiro também) vai apontar para o ínício.
        }
        else{//Caso a lista não esteja vazia, e portanto, se já há um nó de início...
        	lista->fim->proximo = novo;//Apontamos para o nó final da nossa lista e fazemos o seu próximo nó, que antes era o nó de início, agora ser o novo nó. 
        	lista->fim = novo;//O fim da lista agora é o novo nó.
        	novo->proximo = lista->inicio;//O próximo nó do nosso útimo, e também recém criado nó, vai ser o início da lista.
        }
        lista->tam++;//Nossa lista agora aumentou de tamanho.
    }
    else
        return;//Se deu errado, não fazer nada.
}

No* remover(Lista *lista, No *primeiro_homem_apos_o_ultimo_morto, int salto) {//Função que vai retornar o nó que deverá ser removido da lista
    No *anterior_removido, *removido = NULL;
    int i;

    anterior_removido = primeiro_homem_apos_o_ultimo_morto;
    for(i = 0; i < salto - 2; i++) {//Aqui fazemos um loop para termos o homem anterior ao que será morto no ponteiro "anterior_remover".
    	anterior_removido = anterior_removido->proximo;
	}
	removido = anterior_removido->proximo;//O homem que será morto, será portanto, o homem que sucede o anterior ao que será morto.
	if(removido == lista->inicio) {//Aqui é o caso de o nó que queremos remover, ser o primeiro da lista.
		lista->inicio = removido->proximo;
		lista->fim->proximo = lista->inicio;
	}
	else if(removido == lista->fim) {//Aqui, o caso dele ser o último da lista.
		anterior_removido->proximo = removido->proximo;
		lista->fim = anterior_removido;
	}
	else//E aqui caso ele esteja no meio da lista.
		anterior_removido->proximo = removido->proximo;
	lista->tam--;
	
    return removido;//Retornamos o nó que removemos, para depois armazenar o próximo homem após ele e liberar a memória do ponteiro.
}

int main(){
	
	int numero_de_casos, quantidade_de_pessoas, salto, i, t;
    
    No *removido;//Este ponteiro vai receber o retorno da função remover.
    
    scanf("%i",&numero_de_casos);
    
    for(t = 0; t < numero_de_casos; t++) {
    	
    	Lista circulo;//Declarando nossa lista.
    	criar_lista(&circulo);//Colocando os dados iniciais da nossa lista.
    	scanf("%i %i",&quantidade_de_pessoas, &salto);
    	
    	if(salto == 1)//Caso o salto seja de 1, é já sabido que o homem sobrevivente será o útimo do círculo.
			printf("%i\n",quantidade_de_pessoas);
    	else {//Caso o salto não seja de 1, prosseguir...
    		for(i = 0; i < quantidade_de_pessoas; i++)
    			inserir(&circulo, i + 1);//Inserindo as pessoas no círculo, enumeradas de 1 a n.
		
			No *primeiro_homem_apos_o_ultimo_morto = circulo.inicio;//Esse ponteiro vai guardar o homem que começaremos cada salto.
			
			while(circulo.tam > 1) {//Enquanto resta pelo menos 2 homens no nosso círculo...
				removido = remover(&circulo, primeiro_homem_apos_o_ultimo_morto, salto);//Recebe o homem que foi morto e que foi removido do círculo.
				primeiro_homem_apos_o_ultimo_morto = removido->proximo;
				free(removido);//Liberamos a memória do homem morto.
			}
			printf("Case %i: %i\n", t + 1, circulo.inicio->valor);
			free(circulo.inicio);//Liberamos a memória que estava alocando o homem que sobreviveu.
		}
	}

    return 0;
}
