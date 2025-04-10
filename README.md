# E-commerce
Programa em C/C++ que simula um e-commerce feito para um trabalho de Técnicas de Programação I. O programa possui os mesmos menus e mesmos layouts da interface com o usuário que foram implementados no protótipo ecommerce.exe, disponível 	para 	baixar 	no 	link: https://www.dropbox.com/sh/0f86f5978ji89bc/AACvUaEU4yezDW0SBHLkQyPAa?dl=0

## Funcionalidades Implementadas
### Inclusão de Produtos
  São necessários informações sobre o código do produto, descrição, categoria, quantidade em estoque, preço e desconto para incluir um profuto.
-	Código: valor inteiro de 1 a 999. 
-	Descrição: 4 a 40 caracteres (espaços em branco no início e no fim não contam). 
-	Categoria: caracter A, B, C, D ou E. 
-	Quantidade em estoque: valor inteiro de 1 a 9999. 
-	Preço unitário: valor real de 0.01 a 9999999.99 (máximo de duas casas decimais). 
-	Desconto: valor inteiro de 0 a 99 
-	Não podem existir dois produtos com o mesmo código. 
-	Caso o usuário digite um valor inválido, apresente uma mensagem de erro e solicite o dado novamente.
  
### Exclusão de Produtos
  É necessário informar o código do produto.
- Produto não pode ser excluído se estiver no carrinho. 
- Produto não pode ser excluído se tiver com estoque maior que zero. 

### Alteração de Produtos
  É necessário informar o código do produto. Podem ser alterados a quantidade em estoque, o preço e o desconto.
-	Produto não pode ser alterado se estiver no carrinho. 
-	Quantidade em estoque só pode ser aumentada, nunca diminuída. 
-	Quantidade em estoque: valor inteiro de 1 a 9999. Se o usuário digitar 0 a quantidade atual não é alterada. 
-	Preço: valor real de 0.01 a 9999999.99 (máximo de duas casas decimais). Se o usuário digitar 0 o preço atual não é alterado. 
-	Desconto: valor inteiro de 0 a 99. Se o usuário digitar -1 o desconto atual não é alterado. 
-	Caso o usuário digite um valor inválido, uma mensagem de erro é apresentada e o dado é solicitado novamente.

### Consulta de produtos por categoria 
-	Os produtos são apresentados de acordo com o layout do protótipo e estão ordenados por categoria e, dentro da categoria, por descrição (sempre em ordem crescente). 
-	Se não houver produtos cadastrados, a mensagem "Não há produtos cadastrados" é exibida.

### Consulta de produtos por preço 
-	Os produtos são apresentados de acordo com o layout do protótipo e estão ordenados por preço (em ordem crescente). 
-	Se não houver produtos cadastrados é apresentada a mensagem "Não há produtos cadastrados".
  
### Listagem dos produtos carrinho 
-	A listagem é apresentada sempre antes do menu e está ordenada por descrição do produto. 
-	Se o carrinho estiver vazio, a mensagem "Carrinho vazio" é apresentada. 

### Incluir produto no carrinho
  É necessário informar o código do produto e a quantidade. 
-	Quantidade: valor inteiro > 0. Caso o usuário digite uma quantidade inválida, uma mensagem de erro é apresentada e a quantidade de produto a ser incluída no carrinho é solicitada novamente. 
-	Produto não pode ser incluído mais de uma vez no carrinho. 
-	Produto só pode ser incluído no carrinho se a quantidade solicitada for menor ou igual a quantidade do produto em estoque. 
-	Se o produto for incluído, a quantidade deve ser abatida do estoque do produto. 

### Excluir produto do carrinho
  É necessário informar o código do produto. 
- Se o produto for excluído, a quantidade deve retornar ao estoque do produto.
  
### Aumentar quantidade de produto do carrinho
  É necessário informar o código do produto. 
-	A quantidade no carrinho é aumentada em uma unidade. 
-	Produto só pode ter sua quantidade aumentada se houver estoque do produto. 
-	A quantidade é abatida do estoque do produto. 

### Diminuir quantidade de produto do carrinho
  É necessário informar o código do produto. 
-	A quantidade no carrinho é diminuída em uma unidade.
-	A quantidade deve retornar ao estoque do produto 

### Esvaziar carrinho 
- As quantidades dos produtos do carrinho devem retornar ao estoque.
  
### Concluir compra:
  - É necessário que o usuário informe o CPF do comprador, o número do cartão de crédito, o mês/ano da validade do cartão e o código de segurança. 
-	Se o carrinho estiver vazio a compra não poderá ser efetuada e a mensagem "Carrinho vazio" é apresentada. 
-	CPF: CPF válido. 
-	Número do CC: deve ser um número de cartão de crédito válido das bandeiras VISA ou Mastercard 	(como mostrado no link: 
https://suporte.braspag.com.br/hc/pt-br/articles/360050638051-Como-validar-umcart%C3%A3o-Mod10). 
-	Mês/ano da validade:  maior ou igual ao mês/ano corrente 
-	Código de segurança: um inteiro no intervalo de 111 a 999 
-	O sistema deve registrar a data/hora da compra (data/hora atual do computador) 
-	Os pedidos possuem um número de identificação, que é gerado sequencialmente, iniciando em 1. 

### Consultar pedidos 
-	A listagem dos pedidos é ordenada de forma decrescente por data/hora do pedido. 
-	Dentro de cada pedido, os produtos estão ordenados de forma crescente por descrição. 

## Informações gerais 
-	A quantidade máxima de produtos e pedidos é 100. 
-	Todas as strings são armazenadas em caixa alta. 
-	A implementação segue o layout de interface definido no protótipo ecommerce.exe. 
-	Não poderão ser utilizadas variáveis globais, apenas constantes globais.  Todos os vetores deverão ser criados na função main e passados para as demais funções via parâmetros. 

