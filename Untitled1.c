#include <stdio.h>
#include <stdlib.h>

struct caminhao {
    char nome[50];
    float consumo; 		//km por litro
    float capacidade; 	//em m³
    float cargaM;
};
struct produto {
    float altura; 		//em cm
    float largura; 		//em cm
    float comprimento; 	//em cm
    float peso;
    int qnt;
    float pesoTotal;
    float areaTotal; 	//em m³
    char origem;
    char destino;
};
struct locais {
    char origem;
    char destino;
    int distancia; 		//em km
};

//---------------------------------------------------------------------//

void ReadProduct(struct produto prod);
void ReadProduct(struct produto prod) {
    printf("Lembrando que o seu produto deve vir empacotado. ");
    printf("Nosso serviço nao se responsabiliza por possveis danos a mercadoria,\n caso o cliente não tome os devidos cuidados com as caixas dos produtos.");
    
	printf("\n\nDigite a altura do seu produto (em cm):  ");
    fflush(stdin);
    scanf("%f", &prod.altura);
    printf("\nDigite a largura do seu produto (em cm):  ");
    fflush(stdin);
    scanf("%f", &prod.largura);
    printf("\nDigite o comprimento do seu produto (em cm):  ");
    fflush(stdin);
    scanf("%f", &prod.comprimento);
    printf("\nDigite o peso do seu produto (em kilos por unidade):  ");
    fflush(stdin);
    scanf("%f", &prod.peso);
    printf("\nQual a quantia de produtos você deseja transportar:  ");
    fflush(stdin);
    scanf("%d", &prod.qnt);
}
void ProdCalcs(struct produto prod);
void ProdCalcs(struct produto prod) {
	prod.areaTotal = ((prod.altura * prod.comprimento * prod.largura) / 1000000) * prod.qnt;
	prod.pesoTotal = prod.peso * prod.qnt;
}

//-----------------------------------------------------------------//
main()
{
	//controllers
	int i, l, c; //Controle dos loops, controle do local, cotrolador de consumo
	int b = -1, better[10], d; //controlador ID veiculos, lista ID veiculos, ID definitivo
	int litros = 0, comp; //quantidade de combustivel gasta, variavel de comparação
	char urlv[] = "veiculos.txt", urll[] = "locais.txt";
    FILE *arq;
    
    //Obsjetos e resultados
    struct caminhao veic[10];
    struct locais loc[45];
    struct produto prod;
    float tempo, dias; //em horas, em dias...
    float valor; //em reais
    
	
    //leitura dos veiculos
    arq = fopen(urlv, "r");
    if(arq == NULL) printf("Erro, nao foi possivel abrir o arquivo\n"); //tratamento de erro
	else { //preencher os structs com as informações do txt
        for (i = 0; i < 10; i++) {
            fscanf(arq ,"%s - %lf - %lf - %lf\n", veic[i].nome, veic[i].consumo, veic[i].capacidade, veic[i].cargaM);
        }
    }
    fclose(arq);
	
	//leitura dos locais
    arq = fopen(urll, "r");
    if(arq == NULL) printf("Erro, nao foi possivel abrir o arquivo\n"); //tratamento de erro
	else { //preencher os structs com as informações do txt
        for (i = 0; i < 45; i++) {
            fscanf(arq ,"%s - %s - %d\n", loc[i].origem, loc[i].destino, loc[i].distancia);
        }
    }
    fclose(arq);
	
	//make a home screen to this mothefocking system
	
    ReadProduct(prod);
    ProdCalcs(prod);
    //Mecanismos de Origem e Destino
    
    //Procurando pelo melhor veiculo
    for (i = 0; i < 10; i++) {
    	if (veic[i].capacidade > prod.areaTotal) { //Deve comportar toda a mercadoria
    		if (veic[i].cargaM > prod.pesoTotal) { //Deve aguentar todo o peso
    			b = 0;
				better[b] = i;
    			b++;
			}
		}
	}
	if (b = -1) {
		printf("Nenhum de nossos veiculos se adequa as suas necessidades de transporte"); //Fluxo de execao
	}
	else { //Separação do fluxo principal
		for (i = 0; i < 45; i++) { //procura pela origem e destino, para encontrar a distancia entre ambos
			if (loc[i].origem = prod.origem) {
				if (loc[i].destino = prod.destino) {
					l = i;
				}
			}
		}
		
		//calculo do tempo
		tempo = (loc[l].distancia / 80);
		//adicao do descanso e tempo da companhia
		tempo = (tempo + ((tempo/10) * 8) + 4);
		
		i = better[0];
		comp = loc[l].distancia * veic[i].consumo; //setting a default value to comparation
		
		for (c = 1; c < b; c++) {
			i = better[c];
			litros = loc[l].distancia * veic[i].consumo; //continua pegando os valores do resto do array
			
			if (litros < comp) {
				d = i;
			}
		}
		
		//valor dos litros definitivo
		litros = loc[l].distancia * veic[i].consumo;
		
		//calculo do valor do combustivel
		valor = litros * 2.45;
		//adicona o valor por tempo da companhia e taxa fixa
		valor = valor + ((tempo * 10) + 10);
		
		dias = tempo / 24;
		//apresentar nome do veiculo (veic[i].nome), tempo gasto, valor
		printf("\n\nApos avaliacao do sistema o melhor veiculo para o transporte de sua mercadoria e o %s", veic[i].nome);
		printf("\nTendo o valor de transporte de R$ %4.2f  e podendo levar até %3.0d dias", valor, dias);
		printf("\nFavor entrar em contato com o setor de contratos com essas informacoes e as informacoes de seu produto para efetivar o contrato de transporte");
	}
	
	system("PAUSE");
}

