/************************************************************************/
/* Nome: Nícolas Nogueira Lopes da Silva				*/
/* Número USP: 9277541							*/
/* Exercício-programa 1							*/
/************************************************************************/

#include <stdio.h>
int main(){

	/* VARIÁVEIS */

	int n,m,pr,g=0,acabou=0;

	/************************************************************************/
	/* n - valor para n do jogo (peças na mesa)				*/
	/* m - valor para m do jogo (máximo de peças que podem ser retiradas)	*/
	/* pr - peças que foram retiradas					*/
	/* g - variável que indica ganhador, 0 para Computador e 1 para Jogador	*/
	/* acabou - variável que indica se o jogo acabou			*/
	/************************************************************************/

	printf("Jogo NIM\n\nEntre com os valores para n e m.\n");
	scanf("%d %d",&n,&m);
	printf("O jogo começou!\n\n");

	/* Decisão para saber quem começará o jogo, se o n é múltiplo de m+1 o Computador começará */

	if(n%(m+1)!=0){
		/* Computador inicia */
		printf("Vez do Computador.\n");

		/* Decisão que contém a estratégia para a vitória do Computador, sempre deixar múltiplos de m+1 ao jogador */

		if(n%(m+1)>=1){
			pr = n%(m+1);
		}else{
			pr = m;
		}
		n = n - pr;
		if(n == 0){
			acabou = 1;
			g = 0;
		}
		printf("Computador retirou %d peça(s). Restaram %d peça(s) na mesa.\n\n",pr,n);
	}

	/* Loop que possui a jogada de ambos os jogadores enquanto o jogo não acabar */

	while(acabou!=1){
		printf("Vez do Jogador.\n");
		printf("Entre com o número de peças a serem retiradas.\n");
		scanf("%d",&pr);
		n = n - pr;
		if(n == 0){
			acabou = 1;
			g = 1;
		}
		printf("Jogador retirou %d peça(s). Restaram %d peça(s) na mesa.\n\n",pr,n);

		/* Decisão que verifica se o Jogador ganhou nesta rodada, caso ele não ganhe então o jogo continua */

		if(acabou!=1){
			printf("Vez do Computador.\n");
			if(n%(m+1)>=1){
				pr = n%(m+1);
			}else{
				pr = m;
			}
			n = n - pr;
			if(n == 0){
				acabou = 1;
				g = 0;
			}
			printf("Computador retirou %d peça(s). Restaram %d peça(s) na mesa.\n\n",pr,n);
		}
	}

	/* Decisão que exibe o ganhador */

	if(g == 0){
		printf("Computador ganhou!\n");
	}else{
		printf("Jogador ganhou!\n");
	}
	return 0;
}
