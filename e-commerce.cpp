#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

const int TAM_MAX = 3;
typedef struct{
	int codigo;
	char descricao[40];
	char categoria;
	int qtd_estoque;
	float preco;
	int desconto;
	bool carrinho = false;
}Produto;

typedef struct{
	int codigo;
	char descricao[40];
	char categoria;
	int qtd_estoque;
	float preco;
	int desconto;
}Item_do_Carrinho;

void data_hora_atual(int &dia, int &mes, int &ano, int &hora, int &min, int &seg) {
	time_t t = time(NULL);
	struct tm lt = *localtime(&t);
	ano = lt.tm_year + 1900;
	mes = lt.tm_mon + 1;
	dia = lt.tm_mday;
	hora = lt.tm_hour;
	min = lt.tm_min;
	seg = lt.tm_sec;
}
void ordenar_por_descricao(Produto produtos[], int qtd);
void ordenar_por_codigo(Produto produtos[], int *qtd);
int lerQuantidade();
int lerCodigo();
void menu_principal(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);
void menu_produtos(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);
void menu_carrinho(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);



void ordenar_por_codigo(Produto produtos[], int *qtd){
	bool trocou = true;
	int aux;
	for(int k = *qtd-1; k > 0 && trocou; k--){
		for(int i = 0; i < k; i++){
			if(produtos[i].codigo > produtos[i+1].codigo){
						aux = produtos[i+1].codigo;
						produtos[i+1].codigo = produtos[i].codigo;
						produtos[i].codigo = aux;
						trocou = true;
			}
		}
	}
}

int buscarProduto(Produto produtos[], int *qtd, int codigo){	
	int inicio = 0;
	int fim = *qtd-1;
	while(inicio <=fim){
		int meio = (inicio+fim)/2;
		if(produtos[meio].codigo == codigo){
			return meio;
		}
		else if(produtos[meio].codigo > codigo){
			fim = meio-1;
		}
		else{
			inicio = meio+1;
		}
	}
	return -1;
}

void incluir_no_carrinho(Produto produtos[], int *qtd, Item_do_Carrinho carrinho[], int *qtdCarrinho){
	int codigo = lerCodigo();
	int posicao = buscarProduto(produtos, qtd, codigo);
	if(posicao == -1){
		printf("ERRO: Produto nao encontrado\n");
	}
	else if(produtos[posicao].carrinho == true){
		
	}
	else{
		int quantidade = lerQuantidade();
		if(quantidade > produtos[posicao].qtd_estoque){
			printf("ERRO: Produto não tem estoque o suficiente\n");
		}
		
	}
	
	
}

void listar_produtos_carrinho(Produto produtos[], int qtd){
		if(qtd == 0){
			printf("Carrinho vazio!\n");
		}
		else{
			ordenar_por_descricao(produtos, qtd);
			printf("---------------------------------------------------------------------\n");
			printf("Codigo Descricao                       Categ.  Qtd     Preco Desconto\n");
			printf("---------------------------------------------------------------------\n");
			for(int i = 0; i < qtd; i++){
				printf("%03d    %-32s  %c    %4d  %8.2f %8.1f\n", produtos[i].codigo, produtos[i].descricao, produtos[i].categoria, produtos[i].qtd_estoque, produtos[i].preco, produtos[i].desconto);
			}
			printf("---------------------------------------------------------------------\n");	
		}
		
}

void menu_carrinho(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho){
	listar_produtos_carrinho(produtos, qtdCarrinho);
	int opcao;
	printf("\n================\n");
	printf("Menu do Carrinho\n");
	printf("================\n");
	printf("1-Incluir\n2-Excluir\n3-Aumentar\n4-Diminuir\n5-Esvaziar\n6-Comprar\n7-Voltar\n");
	do{
		printf("Opcao: ");
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 7){
			printf("Opcao invalida\n");
		}
	}while(opcao < 1 || opcao > 7);
	
	switch(opcao){
		case 1:
			incluir_no_carrinho(produtos, &qtd, carrinho, &qtdCarrinho);
			break;
		case 7:
			menu_principal(produtos, qtd, carrinho, qtdCarrinho);
			break;
	}
	
}

void ordenar_por_descricao(Produto produtos[], int qtd){
	bool trocou = true;
	char auxiliar[40];
	for(int k = qtd-1; k > 0 && trocou; k--){
		for(int i = 0; i < k; i++){
			if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
						strcpy(auxiliar, produtos[i+1].descricao);
						strcpy(produtos[i+1].descricao, produtos[i].descricao);
						strcpy(produtos[i].descricao, auxiliar);
						trocou = true;
			}
		}
	}
}

void ordenar_por_preco(Produto produtos[], int qtd){
	bool trocou = true;
	float aux;
	char auxiliar[40];
	for(int k =qtd-1;k > 0 && trocou;k--){
			for(int i = 0; i < k; i++){
				if(produtos[i].preco > produtos[i+1].preco){
				aux = produtos[i+1].preco;
				produtos[i+1].preco = produtos[i].preco;
				produtos[i].preco = aux;
				trocou = true;
			}
			else if(produtos[i].preco == produtos[i+1].preco){
				if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
						strcpy(auxiliar, produtos[i+1].descricao);
						strcpy(produtos[i+1].descricao, produtos[i].descricao);
						strcpy(produtos[i].descricao, auxiliar);
						trocou = true;
				}
			}
		}
	}
}

void ordenar_por_categoria(Produto produtos[], int qtd){
	bool trocou = true;
	char aux;
	char auxiliar[40];
	for(int k =qtd-1; k > 0 && trocou;k--){
		trocou = false;
		for(int i = 0; i < k; i++){
			if(produtos[i].categoria > produtos[i+1].categoria){
				aux = produtos[i+1].categoria;
				produtos[i+1].categoria = produtos[i].categoria;
				produtos[i].categoria = aux;
				trocou = true;
			}
			else if(produtos[i].categoria == produtos[i+1].categoria){
				if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
					strcpy(auxiliar, produtos[i+1].descricao);
					strcpy(produtos[i+1].descricao, produtos[i].descricao);
					strcpy(produtos[i].descricao, auxiliar);
					trocou = true;
				}
			}
		}
	}
}

void consultar(Produto produtos[], int qtd, int opcao){
	if(qtd == 0){
		printf("Não há produtos cadastrados\n");
	}
	else{
		if(opcao == 4){
			ordenar_por_categoria(produtos, qtd);
		}
		else{
			ordenar_por_preco(produtos, qtd);
		}
		printf("---------------------------------------------------------------------\n");
		printf("Codigo Descricao                       Categ.  Qtd     Preco Desconto\n");
		printf("---------------------------------------------------------------------\n");
		for(int i = 0; i < qtd; i++){
			printf("%03d    %-32s  %c    %4d  %8.2f %8.1f\n", produtos[i].codigo, produtos[i].descricao, produtos[i].categoria, produtos[i].qtd_estoque, produtos[i].preco, produtos[i].desconto);
		}
		printf("---------------------------------------------------------------------\n");
			
	}

	
	
}

int lerDesconto(){
	int desconto;
	do{
		printf("Desconto: ");
		scanf("%d", &desconto);
		if(desconto < 0 || desconto > 99){
			printf("Desconto deve estar no intervalo de 0 a 99\n");
		}
	}while(desconto < 0 || desconto > 99);
	
	return desconto;
}

int numero_de_casas_decimais(float n){
	int fator = 1;
	int qtd = 0;
	while(fmod(n*fator,1)!= 0){
		fator *=10;
		qtd++;
	}
	return qtd; 
}

float lerPreco(){

	float preco;
	int casas_decimais;
	do{
		printf("Preco: ");
		scanf("%f", &preco);
		casas_decimais = numero_de_casas_decimais(preco);
		if(preco <= 0 || preco > 9999999.99 || casas_decimais > 2){
			printf("Preco deve ser maior que zero e deve ter no máximo 2 casas decimais\n");
		}
	}while(preco <= 0 || preco > 9999999.99 || casas_decimais > 2);
	
	return preco;
}

int lerQuantidade(){
	int qtd_estoque;
	do{
		printf("Quantidade: ");
		scanf("%d", &qtd_estoque);
		if(qtd_estoque < 1 || qtd_estoque > 9999){
			printf("Quantidade deve estar dentro do intervalo de 1 a 9999\n");
		}
	}while(qtd_estoque < 1 || qtd_estoque > 9999);
	
	return qtd_estoque;
	
}

char lerCategoria(){
	char categoria;
	do{
		fflush(stdin);
		printf("Categoria: ");
		scanf("%c", &categoria);
		fflush(stdin);
		categoria = toupper(categoria);
		if(categoria < 'A' || categoria > 'E'){
			printf("Categoria deve ser A, B, C, D e E\n");
		}
	}while(categoria < 'A' || categoria > 'E');
	
	return categoria;
}



void tirar_espacos_extras(char* s){
	int i;
    // lado esquerdo
    for(i = 0; i < strlen( s ) && *( s + i ) ==' '; i++);

    strcpy(s, s + i);
    
	int len = strlen(s);
    // lado direito
    for(i = len-1; i >= 0 && *( s + i ) == ' ';i--);

    *(s + i+1)  = '\0';
}


int contar_caracteres(char s[]){
	int qtd_caracteres = 0;
	for(int i = 0; s[i] != '\0'; i++){
		qtd_caracteres++;
	}
	return qtd_caracteres;
}


void lerString(char* descricao){
	int qtd;
	
	do{
		fflush(stdin);
		printf("Descricao: ");
		scanf("%[^\n]", descricao);
		tirar_espacos_extras(descricao);
		strupr(descricao);
		qtd = contar_caracteres(descricao);
		if(qtd < 4 || qtd > 40){
			printf("Descricao deve ter de 4 a 30 caracteres\n");
		}
	}while(qtd < 4 || qtd>40);
}

int lerCodigo(){
	int codigo;
	do{
		printf("Codigo: ");
		scanf("%d", &codigo);
		if(codigo < 1 || codigo > 999){
			printf("O codigo deve estar entre 1 a 999\n");
		}
		
	}while(codigo < 1 || codigo > 999);
	
	return codigo;
}


void incluirProduto(Produto produtos[], int *qtd){
	Produto produto;
	int codigo;
	printf("\n-------------------\n");
	printf("Inclusao de produto\n");
	printf("-------------------\n");
	int indice;
	do{
		codigo = lerCodigo();
		ordenar_por_codigo(produtos, qtd);
		indice = buscarProduto(produtos, qtd, codigo);
		if(indice != -1){
			printf("ERRO: Produto ja cadastrado\n");
		}
	}while(indice != -1);
	produto.codigo = codigo;
	lerString(produto.descricao);
	produto.categoria = lerCategoria();
	produto.qtd_estoque = lerQuantidade();
	produto.preco = lerPreco();
	produto.desconto = lerDesconto();
	produto.carrinho = false;
	produtos[*qtd] = produto;
	(*qtd)++;
	
}


void menu_produtos(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho){
	int opcao;
	printf("\n================\n");
	printf("Menu de Produtos\n");
	printf("================\n");
	printf("1-Incluir\n2-Excluir\n3-Alterar\n4-Consultar por Categoria\n5-Consultar por preco\n6-Voltar\n");
	do{
		printf("Opcao: ");
		scanf("%d", &opcao);
		if(opcao < 1 || opcao > 6){
			printf("Opcao invalida\n");
		}
	}while(opcao < 1 || opcao > 6);
	
	switch(opcao){
		case 1:
			incluirProduto(produtos, &qtd);
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);
			break;
		case 4:
			consultar(produtos, qtd, opcao);
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);	
			break;
		case 5:
			consultar(produtos, qtd, opcao);
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);
			break;	
		case 6:
			menu_principal(produtos, qtd, carrinho, qtdCarrinho);
			break;	
		
	}
}

void menu_principal(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho){
	int opcao;
	printf("\n===================================\n");
	printf("E-Commerce - Menu Principal (1.0)\n");
	printf("===================================\n");
	printf("1-Carrinho\n2-Produtos\n3-Pedidos\n4-Fim\n");
	do{
	   printf("Opcao: ");
	   scanf("%d", &opcao);
	   if(opcao < 1 || opcao > 4){
	   		printf("Opcao invalida\n");
	   }
	}while(opcao < 1 || opcao > 4);
	
	switch(opcao){
		case 1:
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);
			break;	
		case 2:
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);	
			break;
		case 4:
			return;	
	}
	
}


int main(){
	Item_do_Carrinho carrinho[TAM_MAX];
	Produto produtos[TAM_MAX];
	int qtdProdutos = 0;
	int qtdCarrinho = 0;
	menu_principal(produtos, qtdProdutos, carrinho, qtdCarrinho);
}
