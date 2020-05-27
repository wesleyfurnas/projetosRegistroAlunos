#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>
#define MAXCPF 99999999999
#define MINCPF 01000000000
//Remove uma raiz 
No* removeRaiz(No* raiz){
    No *pai, *novaRaiz;
    if(raiz->dir == NULL) novaRaiz = raiz->esq;
    else if(raiz->esq == NULL) novaRaiz = raiz->dir;
    else{
        pai = raiz;
        No* sucessor = raiz->dir;
 
        while(sucessor->esq != NULL){
            pai = sucessor;
            sucessor = sucessor->esq;
        }
 
        raiz->chave = sucessor->chave;
        pai->esq = removeRaiz(sucessor);
        return raiz;
    }
    free(raiz);
    return novaRaiz;
}
 
No* remover(No* raiz, long int chave){
    if(raiz->chave == chave) return removeRaiz(raiz);
 
    No *no = raiz, *pai = NULL;
    while(no->chave != chave){
        pai = no;
        if(chave < no->chave) no = no->esq;
        else no = no->dir;
    }
 
    if(pai->chave > chave) pai->esq = removeRaiz(no);
    else pai->dir = removeRaiz(no);
 
    return raiz;
}
	

//Libera a arvore inteira
No* liberarArvore(No* raiz){
    if(raiz != NULL){
        No* esq = raiz->esq;
        No* dir = raiz->dir;
        free(raiz);
        liberarArvore(esq);
        liberarArvore(dir);
    }
}
//Devolve uma arvore que tem a chave igual ao parametro
No* buscar(No* raiz, long  int   key){
	if (raiz == NULL) return NULL;
	if (raiz->chave == key) return raiz;
	else if ( raiz->chave > key) return buscar(raiz->esq,key);
	else return buscar(raiz->dir,key);
}
No* buscarPai(No *raiz,long int chave){
	No* pai = NULL;
	No* raizAtual =raiz;
	while(raiz->chave != chave){
		pai = raizAtual;
		if(raizAtual->chave > chave){
			raizAtual = raizAtual->esq;
		}else raizAtual = raizAtual->dir;
	}
	return pai;

}

int totalNo(No* raiz){
	if (raiz == NULL) return 0;
	return totalNo(raiz->esq) + totalNo(raiz->dir) + 1 ;
}
void imprime(No* raiz){
	if (raiz == NULL) return;
	if (raiz != NULL) {
		imprime(raiz->esq);
		printf("\n");
		printf("Nome:            %s \n", raiz->aluno);
		printf("CURSO:           %s \n", raiz->curso);
		if(raiz->chave >= 1000000000 && raiz->chave <= 9999999999)
		printf ("CPF :            0%ld \n", raiz->chave);
		else
		printf ("CPF :            %ld \n", raiz->chave);
		printf("Mensalidade:     %d \n", raiz->mensalidade);
		printf("Tempo:           %d \n", raiz->tempo);
		printf("Idade:           %d  \n",raiz->idade);
		printf("\n");
		imprime(raiz->dir);
	}
}

No* criar(long int chave){
	No* novo = (No*) malloc (sizeof(No));
	novo-> esq = NULL;
	novo-> dir = NULL;
	novo->chave = chave;
	// Variaveis de controle 
	char cIdade[100];
	char cMeses[100];
	char ctempo[100];
	char cMensalidade[100];
	// limpar buffer
	__fpurge(stdin);    
	printf("Digite o curso : ");
	scanf("%[^\n]",novo->curso);
	__fpurge(stdin);
	printf("Digite o nome : ");
	scanf("%[^\n]",novo->aluno);
	__fpurge(stdin);
	printf("Digite a idade: ");
	volta1:
	scanf("%[^\n]",cIdade);
	__fpurge(stdin);
	// Variaveis inteiras usuario pode vir a digitar letras 
	// Caso idade negativa ou fora do normal

	if(atoi(cIdade) < 1 | atoi(cIdade) > 200 | soNumero(cIdade) != 0){ 		
		system("clear || clean");								 // Aviso de erro. Digita novamente
		printf("Idade invalida !\n");	
		printf("Por favor, digite novamente: "); 
		goto volta1;
	//Idade normal, armazena na variavel idade

	}else
		novo->idade = atoi(cIdade);	
                             
	printf("Digite a qtd de meses do curso : ");
	volta2:
	scanf("%[^\n]",cMeses);
	__fpurge(stdin);
	// CASO INFORME TEMPO NEGATIVO 
	 // Aviso de erro. Digita novamente
	if(atoi(cMeses) < 1 | soNumero(cMeses) != 0){
		system("clear || clean");
		printf("Quantidade de meses invalida!\n");            
		printf("Por favor, digite novamente: ");          
		goto volta2;
	//Caso periodo informado seja normal armazena na variavel meses
	}else
		novo->tempo = atoi(cMeses);
                        
	printf("Digite o valor da mensalidade: ");
	volta3:
	scanf("%[^\n]", cMensalidade);
	__fpurge(stdin);
    //Mensalidade negativa não faz sentido.
	// Mensagem de errro. Digita novamente.
	if(atoi(cMensalidade) < 1 | soNumero(cMensalidade) != 0 ){ 
		system("clear || clean");
		printf("Mensalidade invalida! \n");
		printf("Por favor, digite novamente: ");  	 					  
		goto volta3;
	// Armazena na variavel mensalidade, caso não haja erro.
	}else
		novo->mensalidade = atoi(cMensalidade);	                   
	//RETORNA O ALUNO ADICIONADO
	return novo;
}


void imprimeAluno(No* raiz){
	    printf("##############################################################################################################################\n");		    
		printf("Nome:           %s \n", raiz->aluno);
		printf("CURSO :         %s  \n", raiz->curso);
		if(raiz->chave >= 1000000000 && raiz->chave <= 9999999999)   // Codigo extra para incluir zero na impressa do CPF iniciados por zero
		printf ("CPF :           0%ld  \n", raiz->chave);
		else
		printf ("CPF :           %ld  \n", raiz->chave);
		printf("Idade:          %d \n",raiz->idade);
		printf("Mensalidade:    %d \n", raiz->mensalidade);
		printf("Tempo:          %d \n", raiz->tempo);
		printf("\n");
        printf("##################################################################################################################################\n");
		printf("\n");
}

void writeARQ(No* raiz, FILE *p){
	if(raiz == NULL) return;
	if(raiz != NULL)
	{		 
		writeARQ(raiz->esq, p);
		fprintf(p,"%s°%s°%ld°%d°%d°%d°\n", raiz->aluno, raiz->curso,raiz->chave, raiz->idade,raiz->mensalidade, raiz->tempo);
		writeARQ(raiz->dir, p);
	}
}

No* inserir(No* raiz,long int chave){
	No * novo = criar(chave);
	if(raiz == NULL) return novo;
	if (raiz-> chave == chave) return raiz;
	else{
		No* pai = NULL;
		No *raizAtual = raiz;
			while (raizAtual != NULL){
				pai = raizAtual;
				if(chave  > raizAtual->chave ) raizAtual = raizAtual->dir;
				else if (raizAtual->chave > chave ) raizAtual = raizAtual->esq;
				else return raiz;
			}
		if (pai->chave > chave)  
				pai->esq = novo;
		else 
				pai->dir = novo;	
	}
	return raiz;
}

int altura(No* raiz){
	if(raiz == NULL) return 0;
	if (raiz->esq == NULL && raiz->dir == NULL) return 0;
	 if(altura(raiz->esq ) > altura(raiz->dir)) return 1 + altura(raiz->esq ) ;
	else  return altura(raiz->dir) +1 ; 
}

int level(No* raiz, long int chave ){
	if(raiz == NULL) return 0;
	if (raiz->chave == chave) return 0;
	else if (raiz->chave > chave ) return 1 + level(raiz->esq, chave);
	else if(raiz->chave < chave ) return 1 + level(raiz->dir,chave);
}

int lucro(No* raiz){

	if(raiz == NULL) return 0;
	return (raiz->mensalidade*raiz->tempo) + lucro(raiz->dir) + lucro(raiz->esq);
}
 // NO FUNCAO QUE PRINTA O MENU 
void MENU2(){
	printf("               	############################################\n");
	printf("          	##                                        ##\n");
	printf("          	##             MENU                       ##\n");
	printf("          	##                                        ##\n");
	printf("          	##     1. Adicionar Aluno/Curso.          ##\n");
	printf("          	##     2. Excluir.                        ##\n");
	printf("        	##     3. Listar Aluno/Curso.             ##\n");
	printf("        	##     4. Buscar Aluno/Curso.             ##\n");
	printf("		##     5. Modificar Aluno/Curso.          ##\n");
	printf("		##     6. Gerar total do lucro.           ##\n");
	printf("		##     7. Excluir todos alunos.           ##\n");
	printf("		##     8. Sair do programa.               ##\n");
	printf("		##                                        ##\n");
	printf("		############################################\n");
}
int folha(No* raiz){

	if (raiz == NULL) return 0;
    if(raiz->dir == NULL && raiz->esq == NULL ) return 1;
	else return folha(raiz->dir) + folha(raiz->esq);

}













long int  soma(No* raiz){
	if(raiz == NULL) return 0;
	return raiz->chave + soma(raiz->dir) + soma(raiz->esq);
}

No* minimo(No* raiz){
	if (raiz == NULL) return NULL;
	if(raiz->esq == NULL) return raiz;
	else return minimo(raiz->esq);
}

No* maximo(No* raiz){
	if (raiz == NULL) return NULL;
	if(raiz->dir == NULL) return raiz;
	else return maximo(raiz->dir);
}



No* readARQ (No* raiz, char nome[], char curso[], long int chave, int idade,int mensalidade, int tempo){

	No* novo = (No*) malloc (sizeof(No));
	// PREENCHENDO INFORMACOES DO ALUNO
	novo->chave = chave;
	strcpy(novo->curso,curso);
	strcpy(novo->aluno,nome);		
	novo->idade = idade;	                           
	novo->tempo = tempo;	                            
	novo->mensalidade = mensalidade; 
     // CASO A ARVORE ESTEJA VAZIA ELE SERA A RAIZ
	if(raiz == NULL)
	{
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
	// CASO ELE JA ESTEJA NA ARVORE, RETORNA A ARVORE NORMAL
	if (raiz->chave == chave) return raiz;
	else{
		No* pai = NULL;
		No *raizAtual = raiz;
			while (raizAtual != NULL){
				pai = raizAtual;
				if(chave > raizAtual->chave) raizAtual = raizAtual->dir;
				else if (raizAtual->chave > chave) raizAtual = raizAtual->esq;
				else return raiz;
			}
		if (pai->chave > chave)  
				pai->esq = novo;
		else 
				pai->dir = novo;	
	}
	return raiz;
}

// FUNCAO QUE LÊ O ARQUIVO
No* openARQ(No* raiz, FILE *f){                 
	// VARIAVEIS PARA ARMAZENAR OS CAMPOS DA STRUCT
	char *campo;
	char aluno[100];
	char curso[100];
	char opcao[100];
    long int chave;
	int idade = 10, mensalidade =100, tempo =1000;
	char linhaATUAL[400];
	int i = 0;

	if(f == NULL){
		printf("ERRO AO LER ARQUIVO .\n");
	}
	
	// Navega entre as linhas do arquivo
	while( fgets(linhaATUAL,sizeof(linhaATUAL),f) != NULL)              
	{	
		printf("\n\n");
		i = 0;
		// PEGA O NOME DO ALUNO
		campo = (char*)strtok(linhaATUAL, "°");
		strcpy(aluno,campo);
		printf("O aluno eh: %s\n", aluno);
		//PEGA O RESTANTE DAS INFORMAÇOES
		while(campo!= NULL ){
			opcao[0] = '\0';
			campo = (char*)strtok(NULL, "°");
			if(i == 0){
				strcpy(curso, campo);
				printf("O curso eh: %s\n", curso);
				i++;
			}else if(i == 1){
				strcpy(opcao,campo);
			    converteCPF(opcao);
				chave = atol(opcao);
				printf("O CPF eh: %ld\n", chave);
				i++;
			}else if(i == 2){
				strcpy(opcao, campo);
				idade = atoi(opcao);
				i++;
				printf("A idade eh: %d\n", idade);
			}else if(i == 3){
				strcpy(opcao, campo);
				mensalidade = atoi(opcao);
				i++;
				printf("A mensalidade eh: %d\n", mensalidade);
			}else if(i == 4){
				strcpy(opcao, campo);
				tempo = atoi(opcao);
				printf("O tempo eh: %d\n", tempo);
				i++;
			}
  		}
		// ADICIONA O ALUNO NA ARVORE 
		raiz = readARQ (raiz,aluno, curso, chave, idade,mensalidade, tempo);  
	}
	// RETORNA A ARVORE COM OS ALUNO ADICIONADOS
	return raiz;
}
// CONVERTE. RECEBE UMA STRING INICIADA POR ZERO E DEVOLVE SEM O ZERO .EX.: CONVERTECPF(070234566) = 70234566
void converteCPF(char CPF[]){
	int i;
	int j = 1;

	while (CPF[0] == '0' && CPF[1] != '\0'){
		if(strlen(CPF) > 1){
			for(i = 1; i < strlen(CPF); i++)
			{
				CPF[i-1] = CPF[i];			
			}
		    CPF[strlen(CPF)-1] = '\0';	
		}
	}
}
// FUNCAO QUE PRINTA MENU PRA MUDAR CAMPOS DO ALUNO
void menuMudanca(){
                
		printf("1- Mudar curso.\n");		
		printf("2- Mudar nome.\n");
		printf("3- Mudar idade.\n");
		printf("4- Mudar mensalidade.\n");
		printf("5- Mudar tempo do curso.\n");
}
// FUNCAO QUE VERIFICA SE TEM ALGUMA LETRA, RETORNA 1 SE TEM LETRA E ZERO CASO NAO TENHO LETRA
int soNumero(char CPF[]){ 
	int i = 0;
	int controle = 0 ; 
	
	while (CPF[i] != '\0' ){
 		if(CPF[i] != '1' && CPF[i] != '2' && CPF[i] != '3' && CPF[i] != '4' && CPF[i] != '5' && CPF[i] != '6' && CPF[i] != '7' && CPF[i] != '8' && CPF[i] != 			'9'  && CPF[i] != '0') 		
				controle = 1; 	
		else controle = controle ; 	i++; 
	} 	

	return controle; 
}

void op3(No *raiz){
	char opcao[100];
	system("clear || clean" );
	if(raiz == NULL){
		printf("\n");
		printf("##################################################################################################################################\n");
		printf("\n");
		printf("                                          A  LISTA ESTÁ VAZIA!!               \n"); 
		printf("\n");
		printf("##################################################################################################################################\n");
		printf("DIGITE QUALQUER TECLA...\n");                                  // codigo extra pra printar corretamente
		__fpurge(stdin); 
		scanf("%[^\n]", opcao);
	}
	// imprime todos os alunos;
	else {
		printf("                                                 LISTA DE ALUNOS                                                                 \n");
		printf("##################################################################################################################################\n");
		imprime(raiz);
		printf("##################################################################################################################################\n");
		printf("DIGITE QUALQUER TECLA...\n");                                  // codigo extra pra printar corretamente
		__fpurge(stdin); 
		scanf("%[^\n]", opcao);
	}

}

void op4(No* raiz){
  long int CPF;
  char opcao[100];
  system("clear || clean");								// busca um aluno, dado seu CPF;
  printf("Digite o CPF do aluno: \n");
  scanf("%ld",&CPF);
  __fpurge(stdin);
 	 if(buscar(raiz,CPF) != NULL)
 	 {
		No* aux = buscar(raiz,CPF);
		system("clear || clean");		
		printf("                                                  ALUNO ENCONTRADO                  \n");
		imprimeAluno(aux);
		printf("DIGITE QUALQUER TECLA...\n");      //codigo extra pra printar aluno corretamente
		__fpurge(stdin);
		scanf("%[^\n]", opcao);
		}else {
				printf("##################################################################################################################################\n");
				printf("                                                                                                                                  \n");
				printf("                                      ALUNO NAO ENCONTRADO!                                                                       \n");
				printf("                                                                                                                                  \n");
				printf("##################################################################################################################################\n");
				printf("                                                                                                                                  \n");
				printf("DIGITE QUALQUER TECLA...\n");    // codigo extra pra printar aluno corretamente
				__fpurge(stdin); 
				scanf("%[^\n]", opcao);
		}
}



void erroDeCPF(char buffer[]){

						printf("\n");								             // Caso CPF numero fora do range                         
						printf("##########################################################################################################################\n");
						printf("                                                                                                                          \n");
						printf("                                       CPF INVALIDO!                                                                     \n");
						printf("                                                                                                                          \n");
						printf("##########################################################################################################################\n");
						printf("                                                                                                                          \n");
						printf("DIGITE QUALQUER TECLA...\n");    // codigo extra pra printar aluno corretamente 
						scanf("%[^\n]", buffer);	                               
						__fpurge(stdin); 


}


void  flagSucesso(char buffer[]){
					printf("                                                                                                                \n"); 
					printf("################################################################################################################\n");
					printf("                                                                                                                \n");
					printf("                                ALTERACAO FEITA COM SUCESSO!                                                    \n");
					printf("                                                                                                                \n");
					printf("################################################################################################################\n");
					printf("                                                                                                                \n"); 

				    printf("DIGITE QUALQUER TECLA...\n");    // codigo extra pra printar aluno corretamente 
					scanf("%[^\n]",buffer);	                               
					__fpurge(stdin);
}





