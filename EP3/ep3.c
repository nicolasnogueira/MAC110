/************************************************************************/
/* Nome: Nícolas Nogueira Lopes da Silva								*/
/* Número USP: 9277541													*/
/* Exercício-programa 3													*/
/************************************************************************/

#include <stdio.h>
#define TAM 4096

/*TAM REPRESENTA O TAMANHO DA MENSAGEM A SER DECODIFICADA*/

/*FUNÇÃO PARA CONVERTER UM CHAR DADO EM INT*/

int charParaInt(char c){
	int i;

	if(c==' '||c=='_'){
		i = 0;
	}else{
		if(c=='.'){
			i = 27;
		}else{
			i = (int)c-64;
		}
	}

	return i;
}

/*FUNÇÃO PARA CONVERTER UM INT DADO EM CHAR*/

char intParaChar(int i){
	char c;

	if(i==0){
		c = '_';
	}else{
		if(i==27){
			c = '.';
		}else{
			c = (char)i+64;
		}
	}
	return c;
}

/*FUNÇÃO PARA CALCULAR ENTRE DOIS NÚMEROS*/

int mdc(int k,int n){
  	int mdc,r; 
	mdc = k;

	while (n!=0){
	  r = mdc % n;
	  mdc = n;
	  n = r;
	}

  return mdc;
}

/*TRANSFORMA A MENSAGEM A SER LIDA EM UM VETOR DE INT*/

void ciphertext(FILE * entrada,int ciphercode[], int *n){
	int leitura = 0,cont=0;
	char caractere;
	while (leitura!=EOF){
        leitura = fscanf(entrada, "%c", &caractere);
        ciphercode[cont] = charParaInt(caractere);
        cont++;
    }
    *n=cont-1;
}

/*FUNÇÃO PARA VALIDAR UM MENSAGEM COM UM DICIONÁRIO DADO*/

/*ELE PERCORRE TODAS AS PALAVRAS DO DICIONÁRIO VERIFICANDO CADA LETRA	*/
/*USANDO COMO ORIENTAÇÃO O VETOR COM A POSIÇÃO DE CADA LETRA INICIAL	*/
/*DE TODAS AS PALAVRAS E RETORNA UM INT QUE VALE 1 SE A PALAVRA EXISTE	*/
/*E 0 SE A PALAVRA NÃO FOI ENCONTRADA NO DICIONÁRIO						*/	

int validaPlainCode(int plaincode[],int n, int dicindex[], FILE * dicionario){
	int i,j,indexpalavra=0,index=0,leitura=1,palavrabateu=0;
	int qntpalavras=0,qntbateu=0,ok;
	char palavra[30],caractere=' ';
	/* PERCORRE O PLAINCODE*/
	for(i=0;i<n;i++){
		/*VERIFICA SE A PALAVRA É UM PONTO OU ESPAÇO*/
		if(plaincode[i]!=0&&plaincode[i]!=27){
			/*POPULA OUTRO VETOR COM OS CHARS DA PALAVRA A SER PROCURADA*/
			palavra[indexpalavra] = intParaChar(plaincode[i]);
			indexpalavra++;
		}else{
			/*VERIFICA SE O ÚLTIMO CARACTERE FOI UM PONTO OU ESPAÇO*/
			if(indexpalavra>0){
				/*ACRESCENTA UM NO CONTADOR DE PALAVRAS EM VERIFICAÇÃO*/
				qntpalavras++;
				palavrabateu=0;
				/*PERCORRE O DICIONÁRIO*/
				for(j=0;dicindex[j]!=-1&&!palavrabateu;j++){
					palavrabateu=0;
					index=0;
					ok=1;
					fseek(dicionario, dicindex[j]-1, SEEK_SET);
					leitura = fscanf(dicionario, "%c", &caractere);
					/*VARRE UM LINHA DO DICIONÁRIO*/
					while(caractere!='\n' && leitura!=EOF && ok==1 && 
						palavra[index]!=-1 && index<indexpalavra){
						/*VERIFICA SE AS LETRAS DO VETOR DE PALAVRA UTIZADO	*/
						/*BATEM COM AS LETRAS DA PALAVRA DO DICIONÁRIO		*/
						if(palavra[index]!=caractere){
							ok = 0;
						}
						index++;
						leitura = fscanf(dicionario, "%c", &caractere);
					}
					/* VERIFICA QUANDO UMA PALAVRA BATEU*/
					if(caractere=='\n'&&index==indexpalavra){
						if(ok){
							palavrabateu=1;
							qntbateu++;
						}
					}
				}
			/*RESETA O CONTADOR INDEXPALAVRA DO VETOR PALAVRA*/
			indexpalavra=0;
			}
		}
	}
	index++;
	/*VERIFICA SE A QUANTIDADE DE PALAVRAS CONFIRMADAS */
	/*É IGUAL DE PALAVRAS NA FRASE*/
	if(qntbateu==qntpalavras){
		ok=1;
	}else{
		ok=0;
	}
	return ok;
}

/*ESCREVE O VETOR QUE DECODIFICAMOS NO ARQUIVO DE SAÍDA*/
void plaintext(FILE * saida, int plaincode[],int n){
	int i;
	for(i=0;i<n;i++){
		fprintf(saida, "%c", intParaChar(plaincode[i]));
	}
}

/*PERCORRE O DICIONÁRIO E GUARDA ONDE COMEÇA CADA PALAVRA NO DICIONÁRIO*/
void lerDicionario(FILE * dicionario,int dicindex[]){
	int leitura=0,i=1,flag=0;
	char caractere;
	dicindex[0]=0;
	leitura = fscanf(dicionario, "%c", &caractere);
	while(leitura!=EOF){
		if(flag==1){
			dicindex[i]=ftell(dicionario);
			i++;
			flag=0;
		}
		if(caractere=='\n'){
			flag=1;
			
		}
		leitura = fscanf(dicionario, "%c", &caractere);
	}
	/*FIXA UM VALOR DE FIM PARA O VETOR DO DICIONÁRIO*/
	dicindex[i]=-1;
}

int main(){
	FILE * entrada;
	FILE * dicionario;
	FILE * saida;
	int ciphercode[TAM], plaincode[TAM], dicindex[29859];
	int n=0,k,achou=0,i;

	/*PREPARA OS ARQUIVOS E GERA O VETOR DICIONÁRIO*/
	dicionario = fopen("dicionario.txt", "r");
	lerDicionario(dicionario, dicindex);
	entrada = fopen("DECRYPT.IN", "r");
	ciphertext(entrada,ciphercode,&n);
	saida = fopen("DECRYPT.OUT","w");

	for(k=1;k<=300 && achou==0;k++){
		if(mdc(k,n)==1){
			/*TENTA DECRIPTAR USANDO ESTE K*/
			for(i=0;i<n;i++){
				plaincode[k*i%n]=(ciphercode[i] + i)%28;
			}
			/* VALIDAR PLAINCODE*/
			achou = validaPlainCode(plaincode, n, dicindex, dicionario);
			if(achou==1){
				printf("k = %d, n = %d\n",k,n);
				plaintext(saida,plaincode,n);
			}
		}
	}

	/*FECHA OS ARQUIVOS*/

	fclose(entrada);
	fclose(saida);
	fclose(dicionario);

	return 0;
}