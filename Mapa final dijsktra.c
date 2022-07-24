#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>

//Número do meu RA: 20215202508
//Números utilizados: 2 0 2 1 5 2 0

int vertices, origem, destino, resultado;
float custo;
float *custos = NULL;

void grafo_criar(void);
void grafo_procurar(void);
void dijsktra(int vertices, int origem, int destino, float *custos);

//Execução do código e chamado de funções
int main (){
			
	setlocale(LC_ALL, "Portuguese");

    int op = 0;

//    do{
    	system("cls");
		printf("Bem vindo ao algorítmo de Dijsktra!\n");
//    	printf("\nEscolha uma opção: \n1 - Adcionar um grafo\n2 - Procurar o menor caminho\n0 - Sair\n\n");
//        scanf("%d", &op);

//        switch(op){
//            case 1:
            grafo_criar();
//            break;

//            case 2:
            grafo_procurar();
//            break;

//        }

//    } while(op != 0);

    return 0;
}

//Função responsável por criar o grafo
//Aparentemente OK
void grafo_criar(void){
    int i, j;

    //Dimensionamento do grafo
    do{

        printf("\nInsira o número de vertices: ");
        scanf("%d", &vertices);
        
        if(vertices > 5){
            printf("Número de vértices maior que o disponível!");
        }
        
    } while(vertices < 3);

    //testa isso aqui rapidao
    resultado = vertices * vertices;
    
    if(!custos){
        free(custos);
    }

    custos = (float*)malloc(sizeof(float)*resultado);
    if(custos == NULL){

        printf("Memória insuficiente!");
        exit(-1);

    }
    
    //validar isso
    for(i = 0; i <= resultado; i++){
        for(j = 0; j <= vertices; j++){
        	custos[i] = -1;
		}
    }

    //Definição da origem
    do{
		
		system("cls");
        printf("\nInforme as arestas\n");
        do{

            printf("\nOrigem, entre 1 e %d ou 0 para retornar ao menu: ", vertices);
            scanf("%d", &origem);

        } while(origem < 0 || origem > vertices);

    	//Definição do percurso
       	if(origem){

	        do{
	
	            printf("\nDestino, entre 1 e %d, exceto %d: ", vertices, origem);
	            scanf("%d", &destino);
	
	        } while(destino < 1 || destino > vertices || destino == origem);

			//Custo do percurso	   		
			do{
		
		        printf("\nDigite o valor de %d para %d: R$ ", origem, destino);
		        scanf("%f", &custo);
		
		    } while(custo < 0);
	
			custos[(origem - 1) * vertices + destino - 1] = custo;
		
		}
	
	} while(origem);

}

//Função responsável por procurar o menor percurso
//Aparentemente Ok
void grafo_procurar(void){
    
	int i, j;
    
    system("cls");
    printf("Lista dos menores caminhos do grafo dado: \n\n");
    
    for(i = 1; i<= vertices; i++){
        for(j = 1; j<= vertices; j++){
            dijsktra(vertices, i, j, custos);
        }
    }
    
}

//O algoritmo de Dijsktra
//O problema é que ele so da o mais barato e não é o que quero
void dijsktra(int vertices, int origem, int destino, float *custos){

     int *ant, *tmp, *z, i, v, count = 0;
     double dist[vertices], min;

     ant = (int *) calloc(vertices, sizeof(int *));
     if( ant == NULL){
         printf("Memória insuficiente!");
         exit(-1);
     }

     tmp = (int *)calloc(vertices, sizeof(int *));
     if( tmp == NULL){
         printf("Memória insuficiente!");
         exit(-1);
     }

     z = (int *)calloc(vertices, sizeof(int *));
     if( z == NULL){
         printf("Memória insuficiente!");
         exit(-1);
     }

     for(i = 0; i < vertices; i++){
        
         if(custos[(origem - 1) * vertices + i] != -1){
             ant[i] = origem -1;
             dist[i] = custos[(origem - 1) * vertices + i];
         } else{
             ant[i] = (-1);
             dist[i] = HUGE_VAL;
         }

         z[i] = 0;

     }

 	z[origem - 1] = 1;
     dist[origem - 1] = 0;
 
     do{
         min = HUGE_VAL;        
         for(i = 0; i < vertices; i++){
             if(!z[i]){
                 if(dist[i] >= 0 && dist[i] < min){
                     min = dist[i];v = i;
                 }
             }
         }
         if(min != HUGE_VAL && v != destino - 1){
             z[v] = 1;            
             for (i = 0; i < vertices; i++){
                 if(!z[i]){
                     if(custos[v*vertices + i] != -1 && dist[v] + custos[v*vertices + i] < dist[i]){
                         dist[i] = dist[v] + custos[v*vertices + i];
                         ant[i] = v;
                     }
                 }
             }
         }

     } while( v!= destino - 1 && min != HUGE_VAL);

 	if(min != HUGE_VAL){   

 		printf("\nDe %d para %d\n", origem, destino);
						
         i = destino;
         i = ant[i - 1];
        
 		while(i != (-1)){
             tmp[count] = i + 1;
             count++;
             i = ant[i];
         }

         for(i = count; i > 0; i--){
             printf("%d -> ", tmp[i - 1]);
 		}
		
 		printf("%d", destino);
         printf("\nCusto: R$ %.3lf\n",(float) dist[destino - 1]); 

     }

 }
