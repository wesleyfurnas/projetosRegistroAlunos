//AUTOR : JOSE WESLEY E AYRTON SOUZA

#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
#include <string.h>
#define MAXCPF 99999999999
#define MINCPF 01000000000 
int main()
{

	No* raiz = NULL;
	int soLetra = 0;           // VARIAVEL PRA VER SE TEM LETRA EM UMA STRING
	No* aux = NULL;
	long  int CPF;              // VARIAVEL CPF DO ALUNO
	char opcao[100];            // BUFFER QUE ARMAZENA A OPCAO DIGITADA POR UM ALUNO
	int ganho;					// VARIAVEL PARA ARMAZENAR GANHO TOTAL
	int escolha = 1;             // VARIAVEL PARA ESCOLHER O MOMENTO DE SAIR DO PROGRAMA
	int qtdNo;                  // variavel que diz quantos há

	// CRIA ARQUIVO E CARREGA OS ALUNOS DO ARQUIVO
	FILE *p = fopen("teste2.txt","r");
	raiz = openARQ(raiz,p);
	//FECHA ARQUIVO
	fclose(p);
	system("clear || clean" );                                                          
	while (escolha > 0)
	{
		strcpy(opcao,"100");                                                                // Toda vez que sair de uma dar opcoes a string opcao recebe 100
																							// Apenas para caso usuario dê ENTER e fique no MENU  mesmo assim
		volta:                                             									// Enquanto não digitar opcao entre 1 e 7 não entra no case
		system("clear || clean" );
		MENU2();
		printf("\n");
		printf("               DIGITE UMA DAS OPCOES ACIMA: ");
		__fpurge(stdin);
		scanf("%[^\n]", opcao);	
		__fpurge(stdin);

		if(atoi(opcao) < 1 | atoi(opcao) > 8 | soNumero(opcao)!= 0)           // Funcao atoi recebe a string e converte em uma das 7 opcoes
				goto volta;
						                        											
		switch(atoi(opcao))
		{
			case(1): 																	   //Adiciona um novo aluno no sistema
				system("clear || clean" );	
				printf("Digite o CPF do aluno: ");
				scanf("%[^\n]", opcao);	 
				__fpurge(stdin);
				converteCPF(opcao);
				soLetra = soNumero(opcao);
				// Caso usuario digite CPF com letra
				if(soLetra != 0)
				{
					erroDeCPF(opcao);                                  
					break;
				}
				//CASO USUARIO DIGITE NUMERO MUITO GRANDE
				if(strlen(opcao) > 11)
				{
					erroDeCPF(opcao);                                   
					break;
				}                             
				if( atol(opcao) < MINCPF | atol(opcao) > MAXCPF )                                            // Controle caso digite letra ou negativo ou  
				{                            
					erroDeCPF(opcao);                                  
					break;
				}else
				CPF = atol(opcao);
				__fpurge(stdin);                                                            //Limpa o buffer com fpurge(stdin);
															
				if(buscar(raiz,CPF) == NULL)
				{
					raiz = inserir(raiz,CPF);
					printf("Aluno adicionado com sucesso! \n");
					printf("\n");
					printf("DIGITE QUALQUER TECLA...\n");
					__fpurge(stdin);                                						 //Codigo extra pra printar corretamente
					scanf("%[^\n]", opcao);
					break;
				}
				else 
				{
					printf("Este aluno ja existe no registro . \n");
					printf("\n");
					printf("DIGITE QUALQUER TECLA...\n");
					__fpurge(stdin);														//Codigo extra pra printar corretamente
					scanf("%[^\n]", opcao);
				}
				break;
			case(2):
					system("clear || clean" );
					printf("Digite o CPF do aluno a ser removido do sistema: \n");    	//Codigo extra pra printar corretamente
					scanf("%[^\n]", opcao);
					__fpurge(stdin);
					converteCPF(opcao);                                                  //Converte caso digite CPF iniciado por zero
					
					soLetra = soNumero(opcao);
					// Caso usuario digite CPF com letra
					if(soLetra != 0)
					{
						erroDeCPF(opcao);                                  
						break;
					}
					if( atol(opcao) < 1 | atol(opcao) > MAXCPF)     // Controle caso digite letra ou negativo ou  
					{                            
					    erroDeCPF(opcao);                                
					    break;		                                       
					}else
					{
					CPF = atol(opcao);                                                         // CPF valido e armazenado em CPF
					}
					
					__fpurge(stdin);
					if(buscar(raiz,CPF) != NULL){                       						// Remove aluno caso esteja no sistema;
					  	raiz = remover(raiz,CPF);
						printf("\n");
						printf("##########################################################################################################################\n");
					  	printf("                                                                                                                          \n");
						printf("                                           ALUNO REMOVIDO COM SUCESSO !                                                   \n");
						printf("                                                                                                                          \n");
						printf("##########################################################################################################################\n");
						printf("DIGITE QUALQUER TECLA...\n");
						__fpurge(stdin);
						scanf("%[^\n]", opcao);
					}else{
						printf("##########################################################################################################################\n");
						printf("                                                                                                                          \n");
						printf("                                    ALUNO NAO ENCONTRADO!                                                                 \n");
						printf("                                                                                                                          \n");
						printf("##########################################################################################################################\n");
						printf("                                                                                                                          \n");
						printf("DIGITE QUALQUER TECLA...\n");    // codigo extra pra printar aluno corretamente
						__fpurge(stdin); 
						scanf("%[^\n]", opcao);	
					}
					break;
			case(3):
				op3(raiz);
				break;
			case(4): 
				 	op4(raiz);	
					break;
			case(5):		
					system("clear || clean");					// Modifica um aluno. Curso ou nome;
					printf("DIGITE O CPF DO ALUNO EM PROCURADO: ");
					scanf("%[^\n]", opcao);
					__fpurge(stdin); 
				    soLetra = soNumero(opcao);
					// Caso usuario digite CPF com letra
					if(soLetra != 0)
					{
						system("clear || clean");
						erroDeCPF(opcao);                                   
						break;
					// CASO USUARIO NAO DIGITE LETRA, MAS DIGITE INICIANDO COM ZERO
					}
				    converteCPF(opcao);
					CPF = atol(opcao);
					__fpurge(stdin);
					if(buscar(raiz,CPF) != NULL)
					{
						No* aux = buscar(raiz,CPF);
						// imprime o aluno
						printf("                                          ALUNO ENCONTRADO!                                  \n"); 
						imprimeAluno(aux);                   
						menuMudanca();
						char mudar[100];
						scanf("%[^\n]", mudar);
						__fpurge(stdin);  
						// MUDA O CURSO
						if(atoi(mudar) == 1)                               //Verifica se muda curso
						{
							printf("DIGITE O NOVO CURSO: ");
							scanf("%[^\n]", aux->curso);
							__fpurge(stdin);
						//MUDA O NOME DO ALUNO		
						}else if(atoi(mudar) == 2)                          //Verifica se muda nome
						{
							printf("DIGITE O NOVO NOME DO ALUNO: ");
							scanf("%[^\n]", aux->aluno);
							__fpurge(stdin);
						//MUDA A IDADE DO ALUNO	
						}else if(atoi(mudar) == 3){
							volta7:
							printf("DIGITE A NOVA IDADE DO ALUNO: ");       
							scanf("%[^\n]", mudar);
							__fpurge(stdin);
							converteCPF(mudar); 
							soLetra = soNumero(mudar);
							// Caso usuario digite CPF com letra
							if(soLetra != 0)
							{	
								system("clear || clean" );
								printf("IDADE INVALIDA!!.\n");								             
		                       	goto volta7;                                    
								break;
							}                            
							if(atoi(mudar) > 0 && atoi(mudar) < 200  ){ // VERIFICA IDADE VALIDA
								aux->idade = atoi(mudar);
								system("clear || clean" );
								flagSucesso(mudar);
							} 
							else {
							    system("clear || clean" );
								printf("IDADE INVALIDA.\n");
								goto volta7; 
							}                                   //CASO DIGITA IDADE MAIOR   
						// MUDA O VALOR DA MENSALIDADE
						}else if(atoi(mudar) == 4){
							volta8 :
							printf("DIGITE A NOVA MENSALIDADE DO ALUNO: ");       
							scanf("%[^\n]", mudar);
							__fpurge(stdin);
							converteCPF(mudar);                             
							if(atoi(mudar) > 0 && soNumero(mudar) == 0 ){  // VERIFICA IDADE VALIDA
								aux->mensalidade = atoi(mudar);
								system("clear || clean" );
								flagSucesso(mudar); 
								imprimeAluno(aux);	
							} 
							else {
								system("clear || clean" );
								printf("MENSALIDADE INVALIDA.\n");
								goto volta8; 
							}          
						//MUDA O TEMPO DE CURSO                     
						}else if(atoi(mudar) == 5){
							volta9 :
							printf("DIGITE O NOVO TEMPO DO CURSO: ");       
							scanf("%[^\n]", mudar);
							__fpurge(stdin);
							converteCPF(mudar);                             
							if(atoi(mudar) > 0 && soNumero(mudar) == 0){             // VERIFICA MENSALIDAE VALIDA
								system("clear || clean" );
								flagSucesso(mudar); 
								imprimeAluno(aux);						
							} 
							else {
								system("clear || clean" );
								printf("PERIODO DE TEMPO INVALIDO.\n");
								goto volta9; 
							}                                  
						}else{
							printf("OPCAO INVALIDA.\n");
							printf("DIGITE QUALQUER TECLA...\n");
							scanf("%[^\n]", mudar);
							__fpurge(stdin);
							system("clear || clean" );
						}
					}else {                                      // Caso o aluno não consta nos dados
						printf("Aluno nao encontrado!\n");
						printf("DIGITE QUALQUER TECLA...\n");    // codigo extra pra printar aluno corretamente
						__fpurge(stdin);
						scanf("%[^\n]", opcao);
					}
					break;
			case (6): 
					system("clear || clean" );
					ganho = lucro(raiz);
				    printf("#############################################################################################################################\n");
					printf("\n");
					printf("                                     SEU LUCRO TOTAL EH  %d REAIS. \n",ganho);         
					printf("\n");
					printf("#############################################################################################################################\n");
					printf("DIGITE QUALQUER TECLA...\n");              //Codigo extra para printar corretamente
					__fpurge(stdin);
					scanf("%[^\n]", opcao);	
					break;
			case(7):
				 raiz = liberarArvore(raiz);
				 if(raiz == NULL){
					printf("\n");
					printf("#############################################################################################################################\n");
					printf("\n");
					printf("                                          SUCESSO AO DELETAR !!                                                              \n"); 
					printf("\n");
					printf("#############################################################################################################################\n");
				}
				 else  printf("Erro ao deletar. \n");

				 printf("DIGITE QUALQUER TECLA...\n");  // codigo extra pra printar aluno corretamente
				 printf("\n");				
				 __fpurge(stdin); 
				 scanf("%[^\n]", opcao);
				 system("clear || clean" );
				 break;
			case(8):
				 escolha = 0;
				 system("clear || clean" );
				 break;
			default: 
				system("clear || clean" );
				break;
		}
	}
	// ABRE E ESCREVE OS DADOS EM UM ARQUIVO
	p = fopen("teste2.txt","w");
	qtdNo = totalNo(raiz);
	if(p == NULL) printf("ERRO AO ESCREVER NO ARQUIVO. \n");
	writeARQ(raiz, p);
	fclose(p);
	
}














