/*
Metodos computacionais
David Turati
Implementação do de resolução de equações lineares pelo metodo de gauss-seidel
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//prototipos de funções
void inicio();
void aloca(float ***mt, int m, int n);
void preenche(float ***mt, int m, int n);
void imprime(float **mt, int m, int n);
int fatora (float **mt, int m, int n);



int main(){
	inicio();
	return 0;
}


//Inicio do programa
void inicio(){
	//matriz, ponteiro para ponteiro
	float **mt;
	int m,n;

	printf("Digite o número de linhas:");
	scanf("%d",&m);
	__fpurge(stdin);

	printf("Digite o numero de colunas:");
	scanf("%d",&n);
	__fpurge(stdin);

	//aloca matriz
	aloca(&mt,m,n);
	preenche(&mt,m,n);
	imprime(mt,m,n);
	fatora(mt,m,n);

}

//aloca matriz
void aloca(float ***mt, int m, int n){
	register int i;

	*mt = malloc(m * sizeof(float *));

	for (i=0;i<m;i++){
		(*mt)[i] = malloc(n * sizeof(float));
	}

}


//preenche matriz
void preenche(float ***mt, int m, int n){
	register int i,j;

	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%d%d:",i,j);
			scanf("%f",&(*mt)[i][j]);
		}
		printf("\n");
	}

}

//imprime matriz original
void imprime(float **mt, int m, int n){
	register int i,j;
	printf("Matriz original\n");
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			printf("%f ",mt[i][j]);
		}
		printf("\n");
	}

}


//funcão fatora
int  fatora(float **mt, int m, int n){
	register int i,j,k;
	float **c;
	float *modulo;
	float aux;
	float *g;
	float *x0;
	float *x1;
	float *xaux; //serivá para armazenar valor de x1 para calculo de x2
	float maiorModulo, maiorX1;
	float ver;
	float erro;
	int cont;

	//aloca matrizes e vetores
	modulo = (float *)calloc(m, sizeof(float));


	//aloca matriz c
	c = malloc(m * sizeof(float *));
		for (i=0;i<m;i++){
			c[i] = malloc((n-1) * sizeof(float));
		}


	//aloca vetores g x0 e x1
	g = (float *) calloc(m, sizeof(float)); 	//aloca vetor g
	x0 = (float *) calloc(m , sizeof(float));	//aloca vetor x0
	x1 = (float *) calloc(m , sizeof(float));	//aloca vetor x1
	xaux = (float *) calloc(m, sizeof(float));  //serivá para armazenar valor de x1 para calculo de x2


	//primeiro calculo antes do loop
	printf("Digite o erro:");
	scanf("%f",&erro);


	//calcula matriz c
	for (i=0; i<m; i++){

		aux=mt[i][i];

		for (j=0; j<n-1; j++){
			c[i][j]= -(mt[i][j]/aux);
		}

		//troca a posicai Aii por zero
		c[i][i]=0;

		//vetor g
		g[i]=mt[i][n-1]/aux; //calcula vetor g
	}



	//Imprime matriz c
	printf("\nMatriz c \n");
	for (i=0; i<m; i++){
		for (j=0; j<n-1; j++){
			printf("%f ",c[i][j]);
		}
		printf("\n");
	}


	//Imprime vetor g
	printf("\nVetor G \n");
	for(i=0;i<m;i++){
		printf("%f ",g[i]);
		x0[i]=g[i];
		xaux[i]=x0[i];
	}
	printf("\n");


	//Imprime chute inicial
	printf("\n vetor x0 \n");
	for(i=0;i<m;i++){
		printf("%f ",x0[i]);
	}
	printf("\n");
	//fim da primeira iteração antes do loop



	//Calcula vetor x1
	printf("\n");
	for (i=0;i<m;i++){
			x1[i]=0.0;
		for (j=0 ;j<m ;j++){
			x1[i] = x1[i] + (c[i][j])*(xaux[j]);
		}
			x1[i]= x1[i]+g[i];
			xaux[i]=x1[i];
	}

	//Imprime vetor x1
	printf("\n vetor x1 \n");
	for (i=0;i<m;i++){
		printf("%f ",x1[i]);
	}
	printf("\n");


	//calcula modulo erro
	for (i=0;i<m;i++){
		for (j=0;j<m;j++){
			modulo[i] = fabs(x1[i]-x0[i]);
		}
	}



	//imprime modulo x1-x0
	printf("\nModulo x1-x0\n");
	for (i=0;i<m;i++){
		printf("%f ",modulo[i]);
	}
	printf("\n");


	//maior valor de vetor modulo e maior valor de vetor x1
	maiorModulo = fabs(modulo[0]);
	maiorX1 = fabs(x1[0]);
	for(i=1;i<m;i++){
		if (fabs(maiorModulo) < fabs(modulo[i])){
			maiorModulo = modulo[i];
		}

		if (fabs(maiorX1) < fabs(x1[i])){
			maiorX1 = x1[i];
		}

	}

	//imprime maior elemento em x1
	printf("\nMaior valor em x1:");
	printf("%f",maiorX1);
	printf("\n");


	//imprime maior elemento no modulo
	printf("\nMaior valor em modulo:");
	printf("%f",maiorModulo);
	printf("\n");

	//verifica a condição de para com o erro

	ver = maiorModulo/maiorX1;
	printf("Erro:");
	printf("%f\n",ver);
	printf("\n");
	//fim da primeira iteração antes do loop


	//-------------------------------
	//-------------------------------
	//segunda iteração
	//verifica se o erro é maior que a condição de parada dada
	cont = 1;//contador para marcar o numero de iterações
	while (fabs(ver) > erro){
		cont = cont+1;

		for (i=0;i<m;i++){
			x0[i]=x1[i];
			xaux[i]=x1[i];
		}

		//calcula x1
		for (i=0;i<m;i++){
			x1[i]=0;
		for (j=0 ;j<m ;j++){
			x1[i] = x1[i] + (c[i][j])*(xaux[j]);
		}
			x1[i]= x1[i]+g[i];
			xaux[i]=x1[i];
		}

		printf("\nvetor x%d \n",cont);
		for (i=0;i<m;i++){
			printf("%f ",x1[i]);
		}
		printf("\n");

		//calcula modulo erro
		printf("\nvetor modulo x%d-x%d\n",cont,cont-1);
		for (i=0;i<m;i++){
			for (j=0;j<m;j++){
				modulo[i] = x1[i]-x0[i];
			}
		}

		//vetor do modulo x1-x0
		for (i=0;i<m;i++){
			printf("%f ",modulo[i]);
		}
		printf("\n");

		//maior valor de vetor erro e ultimo vetor
		maiorModulo = fabs(modulo[0]);
		maiorX1 = fabs(x1[0]);
		for(i=1;i<m;i++){
			if (fabs(maiorModulo) < fabs(modulo[i])){
				maiorModulo = modulo[i];
			}

			if (fabs(maiorX1) < fabs(x1[i])){
				maiorX1 = x1[i];
			}

		}

		printf("Maior valor em x%d:",cont);
		printf("%f",maiorX1);
		printf("\n");

		printf("Maior valor em modulo:");
		printf("%f",maiorModulo);
		printf("\n");

		ver = maiorModulo/maiorX1;

		printf("Erro:");
		printf("%f\n",ver);
		printf("\n");

		if ( cont == 40){
			printf("Metodo não remendado para resolver esse sistema\n");
			return 0;
		}

	}

	printf("\nSolucao");
	printf("x%d\n",cont);
	for (i=0;i<m;i++){
		printf("%f ",x1[i]);
	}
	printf("\n");
}
