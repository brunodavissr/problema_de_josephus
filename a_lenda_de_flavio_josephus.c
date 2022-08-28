#include <stdio.h>
#include <stdlib.h>

//AGORA EU CONSEGUI FAZER ESSA PORRA SEM OLHAR NA INTERNET, COM MINHA PR�PRIA CAPACIDADE. SOU FODA BIXO!

typedef struct no{
    int valor;//Valor do nosso n�.
    struct no *proximo;//Usamos um ponteiro para apontar ao pr�ximo n�.
}No;//Criamos nosso tipo de dado n�.

typedef struct{
    No *inicio;//Aqui guardaremos um ponteiro que vai apontar o in�cio da nossa lista.
    No *fim;//Aqui guardaremos um ponteiro que vai apontar o fim da nossa lista.
    int tam;//Aqui ser� guardado o tamanho atual da lista.
}Lista;//Criamos nosso tipo de dado lista.

void criar_lista(Lista *lista){
    lista->inicio = NULL;//Ela ainda est� vazia, portanto n�o existe um n� de in�cio.
    lista->fim = NULL;//Ela ainda est� vazia, portanto n�o existe um n� de fim.
    lista->tam = 0;//Tamanho 0.
}//Iniciamos as caracter�sticas da nossa lista.

// procedimento para inserir no fim
void inserir(Lista *lista, int num){
    No *aux, *novo = malloc(sizeof(No));//Alocando mem�ria para nosso novo n�.

    if(novo){//Se deu tudo certo na aloca��o de mem�ria, prosseguir.
        novo->valor = num;//J� atribuindo nosso valor do novo n� que estamos fazendo.
        
        if(lista->inicio == NULL) {//Essa condi��o verifica se a lista est� vazia, e portanto, se o nosso novo n� vai ser o primeiro da lista.
        	lista->inicio = novo;//Agora, nosso novo in�cio da lista vai ser o n� que acabamos de criar.
			lista->fim = novo;//Agora, nosso novo fim da lista vai ser o n� que acabamos de criar.
			lista->fim->proximo = lista->inicio;//O nosso �ltimo n�(e primeiro tamb�m) vai apontar para o �n�cio.
        }
        else{//Caso a lista n�o esteja vazia, e portanto, se j� h� um n� de in�cio...
        	lista->fim->proximo = novo;//Apontamos para o n� final da nossa lista e fazemos o seu pr�ximo n�, que antes era o n� de in�cio, agora ser o novo n�. 
        	lista->fim = novo;//O fim da lista agora � o novo n�.
        	novo->proximo = lista->inicio;//O pr�ximo n� do nosso �timo, e tamb�m rec�m criado n�, vai ser o in�cio da lista.
        }
        lista->tam++;//Nossa lista agora aumentou de tamanho.
    }
    else
        return;//Se deu errado, n�o fazer nada.
}

No* remover(Lista *lista, No *primeiro_homem_apos_o_ultimo_morto, int salto) {//Fun��o que vai retornar o n� que dever� ser removido da lista
    No *anterior_removido, *removido = NULL;
    int i;

    anterior_removido = primeiro_homem_apos_o_ultimo_morto;
    for(i = 0; i < salto - 2; i++) {//Aqui fazemos um loop para termos o homem anterior ao que ser� morto no ponteiro "anterior_remover".
    	anterior_removido = anterior_removido->proximo;
	}
	removido = anterior_removido->proximo;//O homem que ser� morto, ser� portanto, o homem que sucede o anterior ao que ser� morto.
	if(removido == lista->inicio) {//Aqui � o caso de o n� que queremos remover, ser o primeiro da lista.
		lista->inicio = removido->proximo;
		lista->fim->proximo = lista->inicio;
	}
	else if(removido == lista->fim) {//Aqui, o caso dele ser o �ltimo da lista.
		anterior_removido->proximo = removido->proximo;
		lista->fim = anterior_removido;
	}
	else//E aqui caso ele esteja no meio da lista.
		anterior_removido->proximo = removido->proximo;
	lista->tam--;
	
    return removido;//Retornamos o n� que removemos, para depois armazenar o pr�ximo homem ap�s ele e liberar a mem�ria do ponteiro.
}

int main(){
	
	int numero_de_casos, quantidade_de_pessoas, salto, i, t;
    
    No *removido;//Este ponteiro vai receber o retorno da fun��o remover.
    
    scanf("%i",&numero_de_casos);
    
    for(t = 0; t < numero_de_casos; t++) {
    	
    	Lista circulo;//Declarando nossa lista.
    	criar_lista(&circulo);//Colocando os dados iniciais da nossa lista.
    	scanf("%i %i",&quantidade_de_pessoas, &salto);
    	
    	if(salto == 1)//Caso o salto seja de 1, � j� sabido que o homem sobrevivente ser� o �timo do c�rculo.
			printf("%i\n",quantidade_de_pessoas);
    	else {//Caso o salto n�o seja de 1, prosseguir...
    		for(i = 0; i < quantidade_de_pessoas; i++)
    			inserir(&circulo, i + 1);//Inserindo as pessoas no c�rculo, enumeradas de 1 a n.
		
			No *primeiro_homem_apos_o_ultimo_morto = circulo.inicio;//Esse ponteiro vai guardar o homem que come�aremos cada salto.
			
			while(circulo.tam > 1) {//Enquanto resta pelo menos 2 homens no nosso c�rculo...
				removido = remover(&circulo, primeiro_homem_apos_o_ultimo_morto, salto);//Recebe o homem que foi morto e que foi removido do c�rculo.
				primeiro_homem_apos_o_ultimo_morto = removido->proximo;
				free(removido);//Liberamos a mem�ria do homem morto.
			}
			printf("Case %i: %i\n", t + 1, circulo.inicio->valor);
			free(circulo.inicio);//Liberamos a mem�ria que estava alocando o homem que sobreviveu.
		}
	}

    return 0;
}
