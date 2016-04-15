/************************************************************************/
/* Nome: Nícolas Nogueira Lopes da Silva								*/
/* Número USP: 9277541													*/
/* Exercício-programa 4													*/
/************************************************************************/
#include <stdio.h>
#define MAX 500

void insere_fila(int x,int y,int valor,int f[3][MAX],int *final){

	/* ESTRUTURA DA FILA */

	/* índice 0 - coordenada x 				*/
	/* índice 1 - coordenada y				*/
	/* índice 2 - valor da casas			*/

	*final=*final+1;
	f[0][*final%MAX]=x;
	f[1][*final%MAX]=y;
	f[2][*final%MAX]=valor+1;

	/*Neste caso valor representa o valor da casa anterior à inserida na fila*/
}

void empilhar(int x, int y, int valor, int p[3][MAX], int *topo){

	/* ESTRUTURA DA PILHA */

	/* índice 0 - coordenada x 				*/
	/* índice 1 - coordenada y				*/
	/* índice 2 - valor da casas			*/
	/* índice 3 - número de casas checadas	*/

	*topo = *topo+1;
	p[0][*topo%MAX]=x; 
	p[1][*topo%MAX]=y; 
	p[2][*topo%MAX]=valor; 
	p[3][*topo%MAX]=0; 

	/*Neste caso valor sempre é descrescente conforme é inserido na pilha*/
}

void imprimirCaminho(int p[4][MAX], int topo){
	int i;
	for(i=0;i<=topo;i++){
		printf("(%d, %d) ", p[0][(topo-i)%MAX], p[1][(topo-i)%MAX]);
	}
	printf("\n\n");
}

/*Exibe a matriz com '*' indicando por onde Thomas andou*/

void exibeCaminho(int A[MAX][MAX], int p[4][MAX], int topo, int x, int y){
	int i,j,B[MAX][MAX];

	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			B[i][j]=A[i][j];
		}
	}

	for(i=0;i<=topo;i++){
		if(i!=0&&i!=topo){
			B[p[0][topo-i]][p[1][topo-i]]=-2;
		}else{
			if(i==0)
				B[p[0][topo-i]][p[1][topo-i]]=-3; /*-3 para início*/
			else
				B[p[0][topo-i]][p[1][topo-i]]=-4; /*-4 para final*/
		}
		
	}

	for(i=0;i<x;i++){
		printf("|");
		for(j=0;j<y;j++){
			if(B[i][j]>=-1){
				printf("%2d ", B[i][j]);
			}else{
				if(B[i][j]==-3){
					printf(" T ");
				}else{
					if(B[i][j]==-4){
						printf(" S ");
					}else{
						printf(" * ");
					}						
				} 
			}
		}
		printf("|\n");
	}
	printf("\n");
}

void acharCaminhos(int A[MAX][MAX], int si, int sj, int x, int y){
	/*CRIOU UMA PILHA*/
	int pilha[4][MAX],xtmp=si,ytmp=sj,topo=-1,valor,cont=0,chegou=0;

	/*EMPILHOU PRIMEIRO ELEMENTO*/
	empilhar(xtmp, ytmp, A[xtmp][ytmp], pilha, &topo);
	valor=pilha[2][topo%MAX];

	/*CHECAGEM PARA VER SE TODOS OS ELEMENTOS FORAM DESEMPILHADOS*/
	while(topo>=0){
		chegou=0;
		/*VERIFICA SE DETERMINADA CASA JÁ FOI CHECADA*/
		if(pilha[3][topo%MAX]==0){
			/*ATUALIZA CONTADOR DE CHECAGENS NA PILHA*/
			pilha[3][topo%MAX]++;
			/*VERIFICA SE A CASA É UM VALOR DE INTERESSE*/
			if(xtmp-1>=0&&A[xtmp-1][ytmp]==valor-1){
				xtmp = xtmp-1;
				empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
				valor--;
			}
		}else{
			if(pilha[3][topo%MAX]==1){
				pilha[3][topo%MAX]++;
				if(ytmp-1>=0&&A[xtmp][ytmp-1]==valor-1){
					ytmp = ytmp-1;
					empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
					valor--;
				}
			}else{
				if(pilha[3][topo%MAX]==2){
					pilha[3][topo%MAX]++;
					if(xtmp+1<x&&A[xtmp+1][ytmp]==valor-1){
						xtmp = xtmp+1;
						empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
						valor--;
					}					
										
				}else{
					if(pilha[3][topo%MAX]==3){
						pilha[3][topo%MAX]++;
						if(ytmp+1<y&&A[xtmp][ytmp+1]==valor-1){
							ytmp = ytmp+1;
							empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
							valor--;
						}
							
					}else{
						/*DESEMPILHA QUANDO AS CASAS AO REDOR FORAM CHECADAS*/
						topo = topo-1;
						xtmp=pilha[0][topo%MAX];
						ytmp=pilha[1][topo%MAX];
						valor=pilha[2][topo%MAX];
					}
				}
			}
		}

		/* VERIFICA SE UM CAMINHO CHEGOU AO FIM (CHEGOU AO VALOR 1)*/

		if(A[xtmp][ytmp]==1){
			/*PROCURA A CASA DE VALOR 0*/
			if(xtmp-1>=0&&A[xtmp-1][ytmp]==0){
				chegou=1;
				xtmp = xtmp-1;
				empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
			}else{
				if(ytmp+1<y&&A[xtmp][ytmp+1]==0){
					chegou=1;
					ytmp = ytmp+1;
					empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
				}else{
					if(xtmp+1<x&&A[xtmp+1][ytmp]==0){
						chegou=1;
						xtmp = xtmp+1;
						empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
					}else{
						if(ytmp-1>=0&&A[xtmp][ytmp-1]==0){
							chegou=1;
							ytmp = ytmp-1;
							empilhar(xtmp, ytmp, A[xtmp][ytmp],pilha, &topo);
						}
					}
				}
			}
			/*EXIBE CAMINHO SE ACHOU UMA CASA 0*/
			if(chegou){
				cont++;
				printf("Caminho %d\n\n",cont);
				exibeCaminho(A,pilha, topo, x, y);
				imprimirCaminho(pilha, topo);
			}
			/*DESEMPILHANDO A CASA DE VALOR 1 E A DE VALOR 0*/

			topo = topo-2;
			xtmp=pilha[0][topo%MAX];
			ytmp=pilha[1][topo%MAX];
			valor=pilha[2][topo%MAX];
		}		
	}
	printf("Quantidade de caminhos possíveis: %d\n",cont);
	
}

int populaMatriz(int A[MAX][MAX],int x, int y,int si, int sj, int ti, int tj){
	/*CRIAR UMA FILA*/
	int fila[3][MAX],xtmp,ytmp,cmc=0,final=0,chegou=0;


	fila[0][0]=ti;
	fila[1][0]=tj;
	fila[2][0]=0;
	A[ti][tj]=-2; /* inicializando a posição de Thomas com -2*/

	/*VERIFICA QUANDO A PILHA ESTÁ ZERADA*/
	while(cmc%MAX<=final%MAX){
		xtmp=fila[0][cmc];
		ytmp=fila[1][cmc];
		/*PROCURA CASAS AO REDOR VÁLIDAS PARA SEREM ALTERADAS*/
		if(xtmp-1>=0&&A[xtmp-1][ytmp]==0){
			if(xtmp-1==si&&ytmp==sj){
				chegou=1;
				A[xtmp-1][ytmp]=fila[2][cmc]+1;
			}else{
				insere_fila(xtmp-1,ytmp,fila[2][cmc],fila,&final);
				A[xtmp-1][ytmp]=fila[2][cmc]+1;
			}
		}
		if(ytmp-1>=0&&A[xtmp][ytmp-1]==0){
			if(xtmp==si&&ytmp-1==sj){
				chegou=1;
				A[xtmp][ytmp-1]=fila[2][cmc]+1;
			}else{
				insere_fila(xtmp,ytmp-1,fila[2][cmc],fila,&final);
				A[xtmp][ytmp-1]=fila[2][cmc]+1;
			}
		}
		if(xtmp+1<x&&A[xtmp+1][ytmp]==0){
			if(xtmp+1==si&&ytmp==sj){
				chegou=1;
				A[xtmp+1][ytmp]=fila[2][cmc]+1;
			}else{
				insere_fila(xtmp+1,ytmp,fila[2][cmc],fila,&final);
				A[xtmp+1][ytmp]=fila[2][cmc]+1;
			}
		}
		if(ytmp+1<y&&A[xtmp][ytmp+1]==0){
			if(xtmp==si&&ytmp+1==sj){
				chegou=1;
				A[xtmp][ytmp+1]=fila[2][cmc]+1;
			}else{
				insere_fila(xtmp,ytmp+1,fila[2][cmc],fila,&final);
				A[xtmp][ytmp+1]=fila[2][cmc]+1;
			}
		}

		/*Este acréscimo no cmc é equivalente ao remove_fila que foi retirado
		pois neste caso não é preciso retornar os valores retirados*/
		cmc++;
	}

	A[ti][tj]=0; /* corrigindo valor para backtracking (posição do Thomas)*/
	if(!chegou){
		printf("Não existe caminho possível!\n");
	}

	/*RETORNA 1 CASO EXISTA CAMINHO POSSÍVEL E 0 CASO CONTRÁRIO*/
	return chegou;
}

void exibeMatriz(int A[MAX][MAX], int x, int y,int si, int sj, int ti, int tj){
	int i,j;
	printf("\nMatriz populada por números\n\n");
	for(i=0;i<x;i++){
		printf("|");
		for(j=0;j<y;j++){
			if(si==i&&sj==j){
				printf(" S ");
			}else{
				if(ti==i&&tj==j){
					printf(" T ");
				}else{
					printf("%2d ",A[i][j]);
				}
			}
		}
		printf("|\n");
	}
	printf("\n");
}

int main(){
	FILE * labirinto;
	int ti,tj,si,sj,x,y,i,j,chegou;
	int A[MAX][MAX];
	labirinto = fopen("labirinto.txt","r");

	/*COORDENADAS THOMAS*/
	fscanf(labirinto,"%d",&ti);
	fscanf(labirinto,"%d",&tj);

	printf("Thomas: (%d, %d)\n",ti,tj);

	/*COORDENADAS SAÍDAS*/
	fscanf(labirinto,"%d",&si);
	fscanf(labirinto,"%d",&sj);

	printf("Saída: (%d, %d)\n",si,sj);

	/*TAMANHO DA MATRIZ LABIRINTO*/
	fscanf(labirinto,"%d",&x);
	fscanf(labirinto,"%d",&y);

	printf("Matriz: %d x %d\n\n",x,y);

	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			fscanf(labirinto,"%d",&A[i][j]);
		}
	}

	chegou = populaMatriz(A,x,y,si,sj,ti,tj);
	exibeMatriz(A,x,y,si,sj,ti,tj);

	if(chegou)
		acharCaminhos(A, si, sj, x, y);

	return 0;
}