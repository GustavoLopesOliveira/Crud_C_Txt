/*
	@author Gustavo Lopes Olivira
	@date 28/06/2025
*/

#ifndef PESSOA_H
#define PESSOA_H

#include <string.h>
#include <stdlib.h>

typedef struct Pessoa{
	char nome[100];
	char cpf[100];
	char nacionalidade[100];
	char idade[10];
}Pessoa;

//Construtor Pessoa e auxiliares

Pessoa newPessoa(char nome[],char cpf[],char nacionalidade[],char idade[]);
void printPessoa(Pessoa);
Pessoa pesquisarPessoa(char[]); //Pesquisa 
void tiraNdeString(char[]);
void tiraNPessoa(Pessoa*);
int tamanhoArquivo();
int powInt(int,int);
int strToInt(char*);
double mediaIdade();


//Crud
void mostrarPessoas(); //Read
int cadastrarPessoa(Pessoa); //Create
int excluirPessoa(char[]); // Delete
int atualizarPessoa(char[],Pessoa); //Update

#endif
