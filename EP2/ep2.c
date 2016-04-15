/************************************************************************/
/* Nome: Nícolas Nogueira Lopes da Silva								*/
/* Número USP: 9277541													*/
/* Exercício-programa 2													*/
/************************************************************************/

#include <stdio.h>
#define K 4
#define MAXIMO 100

void exibirMenu(){
	printf("\nThe Ultimate Janken-Pon!\n\nInsira o valor para a dificuldade desejada.\n\n1 - Fácil\n2 - Médio\n3 - Difícil\n0 - Sair\n\n");
}

void textoBase(){
	printf("Insira 1 para pedra, 2 para tesoura e 3 para papel ou 0 para finalizar.\n");
}

void relatorio(int vitoria, int derrota, int empate){
	printf("\nRelatório de Jogadas\n\nNúmero de rodadas: %d\nVitórias: %d  (%.1f%%)\nDerrota: %d  (%.1f%%)\nEmpates: %d  (%.1f%%)\n",(vitoria+derrota+empate),vitoria,(float)vitoria*100/(vitoria+derrota+empate),derrota,(float)derrota*100/(vitoria+derrota+empate),empate,(float)empate*100/(vitoria+derrota+empate));
}

void anunciarJogada(int jogada){
	if(jogada==1){
		printf("Você jogou pedra, ");
	}else{
		if(jogada==2){
			printf("Você jogou tesoura, ");
		}else{
			printf("Você jogou papel, ");
		}
	}
}

void anunciarJogadaPC(int jogada){
	if(jogada==1){
		printf("eu joguei pedra.\n");
	}else{
		if(jogada==2){
			printf("eu joguei tesoura.\n");
		}else{
			printf("eu joguei papel.\n");
		}
	}
}

int main(){

	/* VARIÁVEIS */

	/*************************************************************************************************/
	/*a,b,m e x(semente) - variáveis do gerador de números aleatórios								 */
	/*rx - divisão do número aleatório gerado para obter um número entre 0 e 1 						 */
	/*i - índice do for utilizado para analisar as última K jogadas no modo Médio					 */
	/*opt - indicador do modo escolhido a ser jogado												 */
	/*jogada - jogada escolhida pelo usuário														 */
	/*jogadapc - jogada do pc 																		 */
	/*ljogada - variável utilizada para armazenar a última jogada do usuário						 */
	/*vitoria, derrota e empate - indicador do placar geral das rodadas em um modo 					 */
	/*jogadas[] - vetor que armazena todas as jogadas no modo Médio 								 */
	/*contpedra,conttesoura e contpapel - contador de ocorrência dos elementos na análise do Médio   */
	/*status - Status da última rodada (MODO DIFÍCIL) - 0 para derrota, 1 para empate, 2 para vitória*/
	/*************************************************************************************************/

	/*ESCOLHA DO K*/

	/*Escolhi K como 4 pois deste modo é possível verificar mudanças drásticas de ciclos de jogadas e corrigi-los e ainda ignorar múltiplas jogadas*/
	/*consecutivas para obter o mínimo de derrotas possíveis, o que não seria tão possível com valores maiores de K*/

	int a=22695477,b=1,i,opt,jogada,jogadapc=0,ljogada=0,vitoria=0,derrota=0,empate=0, jogadas[MAXIMO],contpedra=0,conttesoura=0,contpapel=0,status=0;
	unsigned long m=4294967296,x=10;
	float rx;

	/* INÍCIO */

	exibirMenu();
	scanf("%d",&opt);
	while(opt!=0){

		/* RESETAR DADOS */
		vitoria = 0;
		derrota = 0;
		empate = 0;

		if(opt==1){
			/* MODO FÁCIL */
			textoBase();
			scanf("%d",&jogada);
			while(jogada!=0){
				/* RODADA FÁCIL */
				anunciarJogada(jogada);

				/* GERADOR DE NÚMEROS ALEATÓRIOS */
				/* Ao dividir algum número da sequência por m, é possível obter um número */
				/* entre 0 e 1, sendo possível encaixá-los em um dos intervalos propostos */

				x = (a*x + b)%m;
				rx = (float)x/m;
				if(rx<(float)1/3){
			    	/* PC JOGA PEDRA */
			    	jogadapc = 1;
			    }else{
			    	if(rx<(float)2/3){
			    		/* PC JOGA TESOURA */
			    		jogadapc = 2;
			    	}else{
			    		/* PC JOGA PAPEL */
			    		jogadapc = 3;
			    	}
			   	}
			   	anunciarJogadaPC(jogadapc);
			   	/* ANÁLISE VENCEDOR */
			   	if((jogada==1&&jogadapc==2)||(jogada==2&&jogadapc==3)||(jogada==3&&jogadapc==1)){
			   		/* JOGADOR VENCEU */
			   		vitoria++;
			   		printf("Você ganhou!\n\n");
			   	}else{
			   		if((jogada==1&&jogadapc==3)||(jogada==2&&jogadapc==1)||(jogada==3&&jogadapc==2)){
			   			/* PC VENCEU */
			   			derrota++;
			   			printf("Eu ganhei!\n\n");
			   		}else{
			   			/* EMPATE */
			   			empate++;
			   			printf("Empatamos!\n\n");
			   		}
			   	}
			   	textoBase();
			   	scanf("%d",&jogada);
			}
			/* RELATÓRIO JOGOS */
			relatorio(vitoria, derrota, empate);
		}else{
			if(opt==2){
				/* MODO MÉDIO */
				textoBase();
				scanf("%d",&jogada);
				while(jogada!=0){
					/* RODADA MÉDIO */
					anunciarJogada(jogada);
					/* COM O % MAX É POSSÍVEL PERCORRER O VETOR CIRCULARMENTE */
					jogadas[(vitoria+empate+derrota)%MAXIMO]=jogada;
					if((vitoria+empate+derrota)<K){
						/* JOGADAS NA FORMA ALEATÓRIA ATÉ OBTER AS K PARTIDAS NECESSÁRIAS */
						x = (a*x + b)%m;
						rx = (float)x/m;
						if(rx<(float)1/3){
					    	/* PC JOGA PEDRA */
					    	jogadapc = 1;
					    }else{
					    	if(rx<(float)2/3){
					    		/* PC JOGA TESOURA */
					    		jogadapc = 2;
					    	}else{
					    		/* PC JOGA PAPEL */
					    		jogadapc = 3;
					    	}
					   	}
					}else{
						/* ESTRATÉGIA MODO MÉDIO */
						contpedra=0;
						contpapel=0;
						conttesoura=0;
						for(i=K;i>0;i--){
							if(jogadas[((vitoria+derrota+empate)-i-1)%MAXIMO]==jogadas[(vitoria+derrota+empate-1)]){
								/*ANALISAMOS A PRÓXIMA JOGADA */
								if(jogadas[((vitoria+derrota+empate)-i)%MAXIMO]==1){
									contpedra++;
								}else{
									if(jogadas[((vitoria+derrota+empate)-i)%MAXIMO]==2){
										conttesoura++;
									}else{
										contpapel++;
									}
								}
							}
						}
						/*SE O JOGADOR CONTINUAR O COMPORTAMENTO DE SUAS JOGADAS, O PRÓXIMO ELEMENTO A SER JOGADO*/
						/*PODE SER PREVISTO ANALISANDO AS ÚLTIMAS K JOGADAS, ONDE A ÚLTIMA JOGADA SERVE DE BASE  */
						/*PARA A ANÁLISE DAS ANTERIORES*/

						if(contpapel>conttesoura){
							if(contpapel>contpedra){
								/* PC JOGA TESOURA - PESSOA TENDE A JOGAR PAPEL*/ 
								jogadapc = 2;
							}else{
								/* PC JOGA PAPEL - PESSOA TENDE A JOGAR PAPEL OU PEDRA*/
								jogadapc = 3;
							}
						}else{
							if(conttesoura==contpapel){
								if(conttesoura>contpedra){
									/*PC JOGA TESOURA - PESSOA TENDE A JOGAR TESOURA OU PAPEL*/
									jogadapc = 2;
								}else{
									/*PC JOGA PAPEL (AS POSSIBILIDADES AQUI SÃO: PROB IGUAIS AOS TRÊS OU PROB DE PEDRA É     */
									/*MAIOR, COMO A PROB DAS PESSOAS JOGAREM PEDRA É MAIOR SEGUNDO OS ESTUDOS, JOGA-SE PAPEL)*/
									/*LINK ESTUDO http://arxiv.org/pdf/1404.5199v1.pdf*/
									jogadapc = 3;
								}
							}else{
								if(conttesoura>contpedra){
									/*PC JOGA PEDRA - PESSOA TENDE A JOGAR TESOURA*/
									jogadapc = 1;
								}else{
									if(conttesoura==contpedra){
										/*PC JOGA PEDRA - PESSOA TENDE A JOGAR TESOURA OU PEDRA*/
										jogadapc = 1;
									}else{
										/*PC JOGA PAPEL - PESSOA TENDE A JOGAR PEDRA*/
										jogadapc = 3;
									}
								}
							}
						}
					}
					anunciarJogadaPC(jogadapc);
					/* ANÁLISE VENCEDOR */
				   	if((jogada==1&&jogadapc==2)||(jogada==2&&jogadapc==3)||(jogada==3&&jogadapc==1)){
				   		/* JOGADOR VENCEU */
				   		vitoria++;
				   		printf("Você ganhou!\n\n");
				   	}else{
				   		if((jogada==1&&jogadapc==3)||(jogada==2&&jogadapc==1)||(jogada==3&&jogadapc==2)){
				   			/* PC VENCEU */
				   			derrota++;
				   			printf("Eu ganhei!\n\n");
				   		}else{
				   			/* EMPATE */
				   			empate++;
				   			printf("Empatamos!\n\n");
				   		}
				   	}
				   	textoBase();
				   	scanf("%d",&jogada);
				}
				/* RELATÓRIO JOGOS */
				relatorio(vitoria, derrota, empate);	
			}else{
				/* MODO DIFÍCIL */
				textoBase();
				scanf("%d",&jogada);
				while(jogada!=0){
					/* RODADA DIFÍCIL */
					anunciarJogada(jogada);

					/*ESTRATÉGIA DA RESPOSTA CONDICIONAL*/

					/*As pessoas quando ganham tendem a jogar o mesmo elemento na rodada seguinte, logo sempre quando se perde o pc   */
					/*deve jogar o elemento que ganha do que o oponente jogou na partida anterior. Quando as pessoas perdem ou empatam*/
					/*tendem a mudar sua estratégia, deste modo o pc joga o que ganha da sua jogada na rodada anterior.*/

					/*Exemplo: uma pessoa perde com papel para uma tesoura, logo ela jogará tesoura ou pedra. Sendo assim, ao jogar pedra*/
					/*ela evita uma derrota, o pc segue esta estratégia.*/

					/*Link: http://www.techtimes.com/articles/6438/20140503/winning-rock-paper-scissors-game-chinese-scientists.htm*/

					if(vitoria+empate+derrota==0){
						/*PRIMEIRA RODADA PC JOGA PAPEL*/
						jogadapc=3;
					}else{
						/*VERIFICAÇÃO PARA SABER SE A ÚLTIMA RODADA FOI VITÓRIA*/
						if(status==2){
							/*LÓGICA PARA JOGAR SEMPRE O QUE GANHA DA SUA JOGADA NA RODADA ANTERIOR*/
							if((jogadapc+2)%3==0){
								jogadapc=3;
							}else{
								jogadapc=(jogadapc+2)%3;
							}
						}else{
							/*LÓGICA PARA JOGAR SEMPRE O QUE GANHA DA JOGADA DO OPONENTE NA RODADA ANTERIOR*/
							if((ljogada+2)%3==0){
								jogadapc=3;
							}else{
								jogadapc=(ljogada+2)%3;
							}
						}

					}
					anunciarJogadaPC(jogadapc);
					/* ANÁLISE VENCEDOR */
				   	if((jogada==1&&jogadapc==2)||(jogada==2&&jogadapc==3)||(jogada==3&&jogadapc==1)){
				   		/* JOGADOR VENCEU */
				   		vitoria++;
				   		printf("Você ganhou!\n\n");
				   		status=0;
				   	}else{
				   		if((jogada==1&&jogadapc==3)||(jogada==2&&jogadapc==1)||(jogada==3&&jogadapc==2)){
				   			/* PC VENCEU */
				   			derrota++;
				   			printf("Eu ganhei!\n\n");
				   			status=2;
				   		}else{
				   			/* EMPATE */
				   			empate++;
				   			printf("Empatamos!\n\n");
				   			status=1;
				   		}
				   	}
				   	ljogada = jogada;
				   	textoBase();
				   	scanf("%d",&jogada);
				}
				/* RELATÓRIO JOGOS */
				relatorio(vitoria, derrota, empate);	
			}
		}
		exibirMenu();
		scanf("%d",&opt);
	}

	printf("Obrigado por jogar o The Ultimate Janken-Pon! Até a próxima o/ \n");

	return 0;
}