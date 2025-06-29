/*
	@author Gustavo Lopes Olivira
	@date 28/06/2025
*/

#include <stdio.h>
#include "pessoa.h"


int main(){
	
	int opcao;

	do{
		printf("\n---Menu---\n");
		printf("1 - Mostrar Pessoas\n");
		printf("2 - Cadastrar Pessoa\n");
		printf("3 - Atualizar Pessoa\n");
		printf("4 - Excluir Pessoa\n");
		printf("5 - Pesquisar Pessoa\n");
		printf("6 - Media das Idades\n");
		printf("0 - Sair\n");
		scanf("%d",&opcao);

		//limpar o br
		getchar();
		
		printf("\n");

		if(opcao == 1){ // Read
				mostrarPessoas();
		}else if(opcao == 2){ //Create
			char nome[100];
			char cpf[100];
			char nacionalidade[100];
			char idade[100];

			printf("Digite o nome:\n");
			fgets(nome,100,stdin);
			printf("Digite o cpf: \n");
			fgets(cpf,100,stdin);
			printf("Digite a nacionalidade: \n");
			fgets(nacionalidade,100,stdin);
			printf("Digite a idade: \n");
			fgets(idade,100,stdin);

			Pessoa pessoa = newPessoa(nome,cpf,nacionalidade,idade);
			
			int response = cadastrarPessoa(pessoa);
			if(response == 0){
				printf("\nOcorreu um erro !!\n");
			}else{
				printf("\nCadastrado com sucesso !!\n");
			}
			
				
		}else if(opcao == 3){ //Update
			char cpfAntigo[100];
			
			printf("Digite o cpf da Pessoa a ser atualizada\n");
			scanf("%s",cpfAntigo);

			//Limpar o Buffer

			getchar();

			char cpfNovo[100],nome[100],nacionalidade[100],idade[100];

			printf("Digite o novo nome:\n");
			fgets(nome,100,stdin);

			printf("Digite o novo cpf:\n");
			fgets(cpfNovo,100,stdin);

			printf("Digite a nova nacionalidade:\n");
			fgets(nacionalidade,100,stdin);

			printf("Digite a nova idade:\n");
			fgets(idade,100,stdin);

			Pessoa pessoa = newPessoa(nome,cpfNovo,nacionalidade,idade);

			int response = atualizarPessoa(cpfAntigo,pessoa);

			if(response == 1){
				printf("Atualizado com sucesso !!\n");
			}else{
				printf("Não foi possivel atualizar !!\n");
			}
			

		}else if(opcao == 4){ //Delete
			char cpf[100];

			printf("Digite o cpf da Pessoa a ser deletada:\n");
			scanf("%s",cpf);

			getchar();//limpar o buffer

			int response = excluirPessoa(cpf);

			if(response == 1){
				printf("Excluida com sucesso !!\n");
			}else{
				printf("Cpf não cadastrado\n");
			}


		}else if(opcao == 5){ //Pesquisa
			char cpf[100];

			printf("\nDigite o cpf da Pessoa a ser pesquisada:\n");
			scanf("%s",cpf);

			getchar(); //Limpar o buffer
			

			Pessoa pessoa = pesquisarPessoa(cpf);

			if(strcmp(pessoa.nome,"0") == 0){
				printf("Este cpf não esta cadastrado !!\n");
			}else{
				printPessoa(pessoa);

			}
			
		}else if(opcao == 6){
			printf("A media das idades : %.0lf \n",mediaIdade());
		}


	}while(opcao != 0);

}

