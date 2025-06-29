/*
	@author Gustavo Lopes Olivira
	@date 28/06/2025
*/

#include "pessoa.h"
#include <stdio.h>

//Auxiliares
void printPessoa(Pessoa tmp){
	printf("%s,%s,%s,%s\n",tmp.nome,tmp.cpf,tmp.nacionalidade,tmp.idade);
}

void tiraNdeString(char tmp[]){
	int size = strlen(tmp);
	tmp[size - 1] = '\0';
}

void tiraNPessoa(Pessoa *tmp){
	tiraNdeString(tmp->nome);
	tiraNdeString(tmp->cpf);
	tiraNdeString(tmp->nacionalidade);
	tiraNdeString(tmp->idade);
}

int tamanhoArquivo(){
	FILE *arquivo = fopen("pessoas.txt","r");

	char string[500];
	int ans = 0;

	while(fgets(string,500,arquivo)){
		ans++;
	}

	return ans;
}

int powInt(int base, int expoente){
	if(base == 0) return 0;
	if(expoente == 0) return 1;
	return base * powInt(base,expoente - 1);
}

int strToInt(char *str){
	int n = strlen(str);
	int ans = 0;

	for(int i = 0; i < n; i++){
		int charToInt = (int) str[i] - '0';
		ans += charToInt * powInt(10,n-i - 1);
	}

	return ans;
}

double mediaIdade(){
	FILE *arquivo = fopen("pessoas.txt","r");

	char linha[500];
	Pessoa p;


	double soma = 0;
	int quantidade = 0;

	while(fgets(linha,500,arquivo) != NULL){
		if( (sscanf(linha,"%[^;];%[^;];%[^;];%[^;];",p.nome,p.cpf,p.nacionalidade,p.idade)) > 0){
			soma += strToInt(p.idade);
			quantidade++;
		}
	}

	if(quantidade == 0) return 0;
	return (soma/quantidade);
}

//Construtor
Pessoa newPessoa(char nome[], char cpf[], char nacionalidade[],char idade[]){
	Pessoa tmp;
	strcpy(tmp.nome,nome);
	strcpy(tmp.cpf,cpf);
	strcpy(tmp.nacionalidade,nacionalidade);
	strcpy(tmp.idade,idade);
	return tmp;
}

//Pesquisa
Pessoa pesquisarPessoa(char cpf[]){
	FILE *arquivo = fopen("pessoas.txt","r");

	char nome[100];
	char cpfSaida[100];
	char nacionalidade[100];
	char idade[100];

	char linha[500];
	Pessoa tmp = newPessoa("0","0","0","0");
	
	if(arquivo == NULL){
		printf("Não foi possivel abrir o arquivo\n");
		return tmp;
	}

	while(fgets(linha,500,arquivo) != NULL){
		if(sscanf(linha,"%[^;];%[^;];%[^;];%[^;];\n",nome,cpfSaida,nacionalidade,idade) > 0){
			if(strcmp(cpf,cpfSaida) == 0){ 
				Pessoa pessoa = newPessoa(nome,cpfSaida,nacionalidade,idade);
				tmp = pessoa;
			}
		}
	}

	fclose(arquivo);
	return tmp; 
}

//Crud

//Read
void mostrarPessoas(){
	FILE *arquivo = fopen("pessoas.txt","r+");
	char nome[100];
	char cpf[100];
	char nacionalidade[100];
	char idade[10];
	
	if(arquivo == NULL){
		printf("Não foi possivel abrir o arquivo\n");
		return;
	}

	while(fscanf(arquivo,"%[^;];%[^;];%[^;];%[^;];\n",nome,cpf,nacionalidade,idade) != EOF){
		Pessoa tmp = newPessoa(nome,cpf,nacionalidade,idade);
		printPessoa(tmp);
	}

	fclose(arquivo);
}

//Create
int cadastrarPessoa(Pessoa pessoa){
	FILE *arquivo = fopen("pessoas.txt","a+");
	if(arquivo == NULL) return 0;
	tiraNPessoa(&pessoa);
	fprintf(arquivo,"%s;%s;%s;%s;\n",pessoa.nome,pessoa.cpf,pessoa.nacionalidade,pessoa.idade);
	fclose(arquivo);
	return 1;
}



//Update

int atualizarPessoa(char *cpf, Pessoa pessoa){

	tiraNPessoa(&pessoa);

	FILE *arquivo = fopen("pessoas.txt","r");

	if(arquivo == NULL){
		return 0;
	}

	FILE *tmp = fopen("tmp.txt","w");

	if(tmp == NULL){
		fclose(arquivo);
		return 0;
	}

	Pessoa p;
	char linha[500];

	while(fgets(linha,500,arquivo) != NULL){
		if(sscanf(linha,"%[^;];%[^;];%[^;];%[^;];\n",p.nome,p.cpf,p.nacionalidade,p.idade) > 0){
			if(strcmp(cpf,p.cpf) == 0){
				p = pessoa;
			}

			fprintf(tmp,"%s;%s;%s;%s;\n",p.nome,p.cpf,p.nacionalidade,p.idade);
		}
	}

	fclose(arquivo);
	fclose(tmp);
	remove("pessoas.txt");
	rename("tmp.txt","pessoas.txt");


	return 1;
}

//Delete 

int excluirPessoa(char cpf[]){
	FILE *arquivo = fopen("pessoas.txt","r");
 
	if(arquivo == NULL){
		return 0;
	}

	FILE *tmp = fopen("tmp.txt","w");

	if(tmp == NULL){
		fclose(arquivo);
		return 0;
	}

	char linha[500];

	Pessoa p;

	while(fgets(linha,500,arquivo) != NULL){
		if(sscanf(linha,"%[^;];%[^;];%[^;];%[^;];\n",p.nome,p.cpf,p.nacionalidade,p.idade) > 0){
			if(strcmp(p.cpf,cpf) != 0){
				fprintf(tmp,"%s;%s;%s;%s;\n",p.nome,p.cpf,p.nacionalidade,p.idade);
			}
		}
	}

	fclose(arquivo);
	fclose(tmp);

	remove("pessoas.txt");
	rename("tmp.txt","pessoas.txt");

	return 1;
}




