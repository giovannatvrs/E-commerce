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
	int qtd;
	float preco;
	int desconto;
}Item_do_Carrinho;




int buscar_produto_carrinho(Item_do_Carrinho carrinho[], int *qtdCarrinho, int codigo);
int ordernar_por_codigo(Item_do_Carrinho carrinho[], int qtdCarrinho);
int numero_de_casas_decimais(float n);
int buscarProduto(Produto produtos[], int *qtd, int codigo);
void ordenar_por_descricao(Item_do_Carrinho carrinho[], int qtdCarrinho);
void ordenar_por_descricao(Produto produtos[], int qtd);
void ordenar_por_codigo(Produto produtos[], int qtd);
int lerQuantidade();
int lerCodigo();
void menu_principal(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);
void menu_produtos(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);
void menu_carrinho(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho);

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

esvaziar_carrinho(Produto produtos[], int *qtd, Item_do_Carrinho carrinho[], int *qtdCarrinho){
	int posicao;
	for(int i = 0; i < *qtdCarrinho; i++){
		posicao = buscarProduto(produtos, qtd, carrinho[i].codigo);
		produtos[posicao].qtd_estoque+=carrinho[i].qtd;
		produtos[posicao].carrinho=false;
	}
	*qtdCarrinho=0;
}

void excluir_produto_carrinho(Produto produtos[], int *qtd, Item_do_Carrinho carrinho[], int *qtdCarrinho){
	int codigo = lerCodigo();
	int posicao_produtos = buscarProduto(produtos, qtd, codigo);
	int posicao_carrinho = buscar_produto_carrinho(carrinho, qtdCarrinho, codigo);
	if(posicao_produtos == -1){
		printf("ERRO: Produto nao encontrado\n");
	}
	else if(produtos[posicao_produtos].carrinho == false){
		printf("ERRO: Produto não esta no carrinho\n");
	}
	else{
		produtos[posicao_produtos].qtd_estoque += carrinho[posicao_carrinho].qtd;
		produtos[posicao_produtos].carrinho = false;
		for(int i = posicao_carrinho; i <= *qtdCarrinho-1; i++) {
			carrinho[i] = carrinho[i+1];
		}
		(*qtdCarrinho)--;
	}
}

void excluir_produto(Produto produtos[], int *qtd){
	int codigo = lerCodigo();
	int posicao = buscarProduto(produtos, qtd, codigo);
	if(posicao == -1){
		printf("ERRO: Produto não encontrado\n");
	}
	else if(produtos[posicao].carrinho == true){
		printf("ERRO: Produto está no carrinho\n");
	}
	else if(produtos[posicao].qtd_estoque > 0){
		printf("ERRO: Produto possui estoque > 0\n");
	}
	else{
		for(int i = posicao; i < *qtd-1; i++) {
			produtos[i] = produtos[i+1];
		}
		(*qtd)--;
	}
}

int ordernar_por_codigo(Item_do_Carrinho carrinho[], int qtdCarrinho){
	Item_do_Carrinho aux;
	bool trocou = true;
	for(int k = qtdCarrinho-1; k >0 && trocou; k--){
		trocou = false;
		for(int i = 0; i < k;i++){
			if(carrinho[i].codigo > carrinho[i+1].codigo){
				aux = carrinho[i];
				carrinho[i] = carrinho[i+1];
				carrinho[i+1] = aux;
				trocou = true;
			}
			
		}
	}
}

int buscar_produto_carrinho(Item_do_Carrinho carrinho[], int *qtdCarrinho, int codigo){
	ordernar_por_codigo(carrinho, *qtdCarrinho);
	int inicio = 0;
	int fim = *qtdCarrinho-1;
	while(inicio<=fim){
		int meio = (inicio+fim)/2;
		if(carrinho[meio].codigo == codigo){
			return meio;
		}
		else if(carrinho[meio].codigo >codigo){
			fim = meio-1;
		}
		else{
			inicio = meio+1;
		}
	}
	return -1;
	
}


void diminuir_quantidade(Produto produtos[], int *qtd, Item_do_Carrinho carrinho[], int *qtdCarrinho){
	printf("====================================\n");
	printf("Diminuir Qtd de Produto do Carrinho\n");
	printf("====================================\n");
	int codigo = lerCodigo();

	int posicao = buscarProduto(produtos, qtd, codigo);
	int posicaoCarrinho = buscar_produto_carrinho(carrinho, qtdCarrinho, codigo);
	if(posicao == -1){
		printf("ERRO: Produto nao encontrado\n");
	}
	else if(buscar_produto_carrinho(carrinho, qtdCarrinho, codigo) == -1){
			printf("ERRO: Produto nao esta no carrinho\n");
	}
	else{
		
			carrinho[posicaoCarrinho].qtd--;
			produtos[posicao].qtd_estoque++;
			printf("Produto diminuido com sucesso!\n");	
	
		
	}
}

void aumentar_quantidade(Produto produtos[], int *qtd, Item_do_Carrinho carrinho[], int *qtdCarrinho){
	printf("====================================\n");
	printf("Aumentar Qtd de Produto do Carrinho\n");
	printf("====================================\n");
	int codigo = lerCodigo();

	int posicao = buscarProduto(produtos, qtd, codigo);
	int posicaoCarrinho = buscar_produto_carrinho(carrinho, qtdCarrinho, codigo);
	if(posicao == -1){
		printf("ERRO: Produto nao encontrado\n");
	}
	else if(buscar_produto_carrinho(carrinho, qtdCarrinho, codigo) == -1){
			printf("ERRO: Produto nao esta no carrinho\n");
	}
	else{
		if(produtos[posicao].qtd_estoque <= 0){
			printf("ERRO: Produto nao tem estoque o suficiente\n");
		}
		else{
			carrinho[posicaoCarrinho].qtd++;
			produtos[posicao].qtd_estoque--;
			printf("Produto aumentado com sucesso!\n");	
		}
		
		
	}
}
int alterarDesconto(){
	int desconto;
	do{
		printf("Desconto (-1 para manter o desconto atual): ");
		scanf("%d", &desconto);
		if(desconto < -1 || desconto > 99){
			printf("Desconto deve ser -1 ou estar no intervalo de 0 a 99\n");
		}
	}while(desconto < -1 || desconto > 99);
	
	return desconto;
}

float alterarPreco(){

	float preco;
	int casas_decimais;
	do{
		printf("Preco (0 para manter o preco atual): ");
		scanf("%f", &preco);
		casas_decimais = numero_de_casas_decimais(preco);
		if(preco < 0 || preco > 9999999.99 || casas_decimais > 2){
			printf("Preco deve ser 0 ou maior que zero e deve ter no máximo 2 casas decimais\n");
		}
	}while(preco < 0 || preco > 9999999.99 || casas_decimais > 2);
	
	return preco;
}

int alterarQuantidade(){
	int qtd_estoque;
	do{
		printf("Quantidade (0 para manter a quantidade atual): ");
		scanf("%d", &qtd_estoque);
		if(qtd_estoque < 0 || qtd_estoque > 9999){
			printf("Quantidade deve ser 0 ou estar dentro do intervalo de 1 a 9999\n");
		}
	}while(qtd_estoque < 0 || qtd_estoque > 9999);
	
	return qtd_estoque;
	
}

void alterarProduto(Produto produtos[], int *qtd){
	int codigo = lerCodigo();
	int posicao = buscarProduto(produtos, qtd, codigo);
	if(posicao == -1){
		printf("ERRO: Produto não encontrado\n");
	}
	else if(produtos[posicao].carrinho == true){
		printf("ERRO: Produto esta no carrinho\n");
	}
	else{
		int quantidade = alterarQuantidade();
		float p = alterarPreco();
		int d = alterarDesconto();
		if(quantidade != 0){
			produtos[posicao].qtd_estoque = quantidade;
		}
		if(p != 0){
			produtos[posicao].preco = p;
		}
		if(d != -1){
			produtos[posicao].desconto = d;
		}
		printf("Produto alterado com sucesso!\n");
	}
}

void ordenar_por_codigo(Produto produtos[], int *qtd){
	bool trocou = true;
	Produto auxiliar;
	for(int k = *qtd-1; k > 0 && trocou; k--){
		for(int i = 0; i < k; i++){
			if(produtos[i].codigo > produtos[i+1].codigo){
						auxiliar = produtos[i+1];
						produtos[i+1] = produtos[i];
						produtos[i] = auxiliar;
						trocou = true;
			}
		}
	}
}

int buscarProduto(Produto produtos[], int *qtd, int codigo){
	ordenar_por_codigo(produtos, qtd);	
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
	Item_do_Carrinho item;
		int posicao;
		int codigo = lerCodigo();
		posicao = buscarProduto(produtos, qtd, codigo);
		if(posicao == -1){
			printf("ERRO: Produto nao encontrado\n");
		}
		else if(produtos[posicao].carrinho == true){
			printf("ERRO: Produto ja esta no carrinho");
		}
		else{
			int quantidade = lerQuantidade();
			if(quantidade > produtos[posicao].qtd_estoque){
				printf("ERRO: Produto não tem estoque o suficiente\n");
			}
			else{
				item.categoria = produtos[posicao].categoria;
				item.codigo =  produtos[posicao].codigo;
				item.desconto = produtos[posicao].desconto;
				strcpy(item.descricao, produtos[posicao].descricao);
				item.preco = produtos[posicao].preco;
				item.qtd = quantidade;
				produtos[posicao].carrinho = true;
				produtos[posicao].qtd_estoque-=quantidade;
				carrinho[*qtdCarrinho] = item;
				(*qtdCarrinho)++;
				printf("Produto incluído com sucesso!\n");
			}	
		}	
	

}

void listar_produtos_carrinho(Item_do_Carrinho carrinho[], int qtdCarrinho){
		if(qtdCarrinho == 0){
			printf("Carrinho vazio!\n");
		}
		else{
			ordenar_por_descricao(carrinho, qtdCarrinho);
			printf("---------------------------------------------------------------------\n");
			printf("Codigo Descricao                       Categ.  Qtd     Preco Desconto\n");
			printf("---------------------------------------------------------------------\n");
			for(int i = 0; i < qtdCarrinho; i++){
				printf("%03d    %-32s  %c    %4d  %8.2f %8.1f\n", carrinho[i].codigo, carrinho[i].descricao, carrinho[i].categoria, carrinho[i].qtd, carrinho[i].preco, carrinho[i].desconto);
			}
			printf("---------------------------------------------------------------------\n");	
		}
		
}

void menu_carrinho(Produto produtos[], int qtd, Item_do_Carrinho carrinho[], int qtdCarrinho){
	listar_produtos_carrinho(carrinho, qtdCarrinho);
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
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);
			break;
		case 2:
			excluir_produto_carrinho(produtos, &qtd, carrinho, &qtdCarrinho);
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);	
		case 3:
			aumentar_quantidade(produtos, &qtd, carrinho, &qtdCarrinho);
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);
			break;	
		case 4:
			diminuir_quantidade(produtos, &qtd, carrinho, &qtdCarrinho);
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);	
			break;
		case 5:
			esvaziar_carrinho(produtos, &qtd, carrinho, &qtdCarrinho);
			menu_carrinho(produtos, qtd, carrinho, qtdCarrinho);	
		case 7:
			menu_principal(produtos, qtd, carrinho, qtdCarrinho);
			break;
	}
	
}

void ordenar_por_descricao(Item_do_Carrinho carrinho[], int qtdCarrinho){
	bool trocou = true;
	Item_do_Carrinho auxiliar;
	for(int k = qtdCarrinho-1; k > 0 && trocou; k--){
		for(int i = 0; i < k; i++){
			if(strcmp(carrinho[i].descricao, carrinho[i+1].descricao)>0){
						auxiliar = carrinho[i+1];
						carrinho[i+1] = carrinho[i];
						carrinho[i] = auxiliar;
						trocou = true;
			}
		}
	}
}

void ordenar_por_descricao(Produto produtos[], int qtd){
	bool trocou = true;
	Produto auxiliar;
	for(int k = qtd-1; k > 0 && trocou; k--){
		for(int i = 0; i < k; i++){
			if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
						auxiliar = produtos[i+1];
						produtos[i+1] = produtos[i];
						produtos[i] = auxiliar;
						trocou = true;
			}
		}
	}
}

void ordenar_por_preco(Produto produtos[], int qtd){
	bool trocou = true;
	Produto auxiliar;
	for(int k =qtd-1;k > 0 && trocou;k--){
			for(int i = 0; i < k; i++){
				if(produtos[i].preco > produtos[i+1].preco){
				auxiliar = produtos[i+1];
				produtos[i+1]= produtos[i];
				produtos[i] = auxiliar;
				trocou = true;
			}
			else if(produtos[i].preco == produtos[i+1].preco){
				if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
						auxiliar = produtos[i+1];
						produtos[i+1] = produtos[i];
						produtos[i]= auxiliar;
						trocou = true;
				}
			}
		}
	}
}

void ordenar_por_categoria(Produto produtos[], int qtd){
	bool trocou = true;
	Produto auxiliar;
	for(int k =qtd-1; k > 0 && trocou;k--){
		trocou = false;
		for(int i = 0; i < k; i++){
			if(produtos[i].categoria > produtos[i+1].categoria){
				auxiliar = produtos[i+1];
				produtos[i+1] = produtos[i];
				produtos[i] = auxiliar;
				trocou = true;
			}
			else if(produtos[i].categoria == produtos[i+1].categoria){
				if(strcmp(produtos[i].descricao, produtos[i+1].descricao)>0){
					auxiliar = produtos[i+1];
					produtos[i+1] =  produtos[i];
					produtos[i] = auxiliar;
					trocou = true;
				}
			}
		}
	}
}

void consultar(Produto produtos[], int *qtd, int opcao){
	if(*qtd == 0){
		printf("Não há produtos cadastrados\n");
	}
	else{
		if(opcao == 4){
			ordenar_por_categoria(produtos, *qtd);
		}
		else{
			ordenar_por_preco(produtos, *qtd);
		}
		printf("---------------------------------------------------------------------\n");
		printf("Codigo Descricao                       Categ.  Qtd     Preco Desconto\n");
		printf("---------------------------------------------------------------------\n");
		for(int i = 0; i < *qtd; i++){
			printf("%03d    %-32s  %c    %4d  %8.2f %8.1f\n", produtos[i].codigo, produtos[i].descricao, produtos[i].categoria, produtos[i].qtd_estoque, produtos[i].preco, (float)produtos[i].desconto);
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
	//do{
		codigo = lerCodigo();
		//ordenar_por_codigo(produtos, qtd);
		//indice = buscarProduto(produtos, qtd, codigo);
		//if(indice != -1){
			//printf("ERRO: Produto ja cadastrado\n");
		//}
	//}while(indice != -1);
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
		case 2:
			excluir_produto(produtos, &qtd);
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);	
		case 3:
			alterarProduto(produtos, &qtd);	
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);
		case 4:
			consultar(produtos, &qtd, opcao);
			menu_produtos(produtos, qtd, carrinho, qtdCarrinho);	
			break;
		case 5:
			consultar(produtos, &qtd, opcao);
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
