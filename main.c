/**
 * [V] - Cadastrar
 * [V] - Listar
 * [ ] - Aprovados
 * [ ] - Reprovados
 * [ ] - Salvar no arquivo
 * [ ] - Ler do arquivo
 * [V] - Menu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "layout.h"

#define PESO_N1 1
#define PESO_N2 2
#define TAMANHO_INICIAL_LISTA 20
#define NOME_SISTEMA "Sistema de Controle de Alunos"

// Aluno
typedef struct {
	int codigo;
	char nome[50];
	float nota1;
	float nota2;
} Aluno;

// Lista
typedef struct {
	Aluno *aluno;
	int quantidade;
	int maximo;
} Lista;

// Funcoes principais de sistema
Lista* criaLista(int quantidadeMaxima);
Aluno* criaAluno(int codigo, char* nome, float nota1, float nota2);
void adicionarAluno(Lista* lista, Aluno* aluno);
float calculaMedia(Aluno* aluno);
char* resolveSituacao(Aluno* aluno);

// Funcoes de tela e menus
void cabecalho(char* menu);

void menuPrincipal();
void imprimeMenuPrincipal();

void menuCadastro();
void imprimeCadastroAluno(char* nome, float nota1, float nota2);

void menuListar();
void imprimeListaAlunos(int ini);

void menuAprovados();
void imprimeListaAprovados();


// Funcoes de mensagem
void setMensagemAviso(char *msg);
void imprimeMensagemAviso();

// Funcoes de debug
Lista* criaListaFake();
void imprimeLista(Lista* lista);
void imprimeAluno(Aluno* aluno);

// Variaveis globais
char _mensagem_aviso[255];
Lista* lista_;

int main () {

//	lista_ = criaLista(TAMANHO_INICIAL_LISTA);
	lista_ = criaListaFake();

	menuPrincipal();

	return EXIT_SUCCESS;
}

// Funcoes principais de sistema
Lista* criaLista(int quantidadeMaxima) {

	Lista* lista = (Lista*)malloc(sizeof(Lista));
	lista->aluno = (Aluno*)malloc(quantidadeMaxima*sizeof(Aluno));
	lista->quantidade = 0;
	lista->maximo = quantidadeMaxima;

	return lista;
}
Aluno* criaAluno(int codigo, char* nome, float nota1, float nota2) {

	Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
	aluno->codigo = codigo;
	strcpy(aluno->nome, nome);
	aluno->nota1 = nota1;
	aluno->nota2 = nota2;

	return aluno;
}
void adicionarAluno(Lista* lista, Aluno* aluno) {

	if (lista->quantidade >= lista->maximo)
		return;

	lista->aluno[lista->quantidade] = *aluno;
	lista->quantidade += 1;

	free(aluno);
}
float calculaMedia(Aluno* aluno) {
	return (PESO_N1*aluno->nota1 + PESO_N2*aluno->nota2)/(PESO_N1+PESO_N2);
}
char* resolveSituacao(Aluno* aluno) {

	float media = calculaMedia(aluno);
	if (media >= 7) {
		return "Aprovado";
	} else {
		return "Reprovado";
	}
}


// Funcoes de tela e menus
void cabecalho(char* menu) {
	filledLine();
	line(NOME_SISTEMA, 'C');
	line(menu, 'C');
	filledLine();
	imprimeMensagemAviso();
}

void menuPrincipal(){

	char *opcao = (char*)malloc(sizeof(char));

	while (1) {

		clearScreen();
		imprimeMenuPrincipal();
		printf("Digite sua opcao: ");
		scanf(" %c", opcao);

		switch(*opcao) {
			case '1':
				clearScreen();
				menuCadastro();
				break;

			case '2':
				clearScreen();
				menuListar();
				break;

			case '3':
				break;

			case '4':
				break;

			case 'd':
			case 'D':
				clearScreen();
				imprimeLista(lista_);
				printf("Digite qualquer para voltar: ");
				scanf(" %c", opcao);
				break;
			case '0':
				clearScreen();
				free(opcao);
				return;
		}
	}
}
void imprimeMenuPrincipal() {
	cabecalho("Menu principal");
	emptyLine();
	line("1. Cadastrar", 'L');
	emptyLine();
	line("2. Lista", 'L');
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	line("0. Sair", 'L');
	emptyLine();
	filledLine();
}

void menuCadastro(){

	char *opcao = (char*)malloc(sizeof(char));
	char *msg;
	char *nome;
	float nota1, nota2;

	nome = malloc(50*sizeof(char));
	msg = malloc(50*sizeof(char));

	strcpy(nome, "");
	nota1 = 0;
	nota2 = 0;

	while (1) {

		clearScreen();
		imprimeCadastroAluno(nome, nota1, nota2);
		printf("Digite sua opcao: ");
		scanf(" %[^\n]", opcao);

		switch(*opcao) {
			case '1':
				clearScreen();
				imprimeCadastroAluno(nome, nota1, nota2);
				printf("Digite o nome do aluno: ");
				scanf(" %[^\n]", nome);
				break;

			case '2':
				clearScreen();
				imprimeCadastroAluno(nome, nota1, nota2);
				printf("Digite a nota 1: ");
				scanf(" %f", &nota1);
				break;

			case '3':
				clearScreen();
				imprimeCadastroAluno(nome, nota1, nota2);
				printf("Digite a nota 2: ");
				scanf(" %f", &nota2);
				break;

			case '4':
				if (!strcmp(nome,"")){
					setMensagemAviso("Nome deve ser informado!");
				} else {
					adicionarAluno(lista_,
							criaAluno(lista_->quantidade, nome, nota1, nota2));

					sprintf(msg, "Aluno '%s' cadastrado com sucesso!", nome);
					setMensagemAviso(msg);

					strcpy(nome, "");
					nota1 = 0;
					nota2 = 0;
				}
				break;

			case '0':
				free(msg);
				free(opcao);
				free(nome);
				return;
				break;
		}
	}
}
void imprimeCadastroAluno(char* nome, float nota1, float nota2) {

	char *aux = (char*)malloc(80*sizeof(char));

	cabecalho("Cadastro de alunos");
	emptyLine();
	sprintf(aux, "1. Nome:  %s", nome);
	line(aux, 'L');
	emptyLine();
	sprintf(aux, "2. Nota 1:  %.2f", nota1);
	line(aux, 'L');
	emptyLine();
	sprintf(aux, "3. Nota 2:  %.2f", nota2);
	line(aux, 'L');
	emptyLine();
	line("4. Salvar", 'L');
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	emptyLine();
	line("0. Voltar", 'L');
	emptyLine();
	filledLine();

	free(aux);
}

void menuListar(){

	int ini = 0;
	char *opcao = (char*)malloc(sizeof(char));

	while (1) {

		clearScreen();
		imprimeListaAlunos(ini);
		printf("Digite sua opcao: ");
		scanf(" %[^\n]", opcao);

		switch(*opcao) {

		case '1':
			ini -= 4;
			if(ini < 0){
				ini = 0;
			}
			break;

		case '2':
			if (ini+4 < lista_->quantidade) {
				ini += 4;
			}
			break;

		case '0':
			free(opcao);
			return;
		}
	}
}
void imprimeListaAlunos(int ini){

	char *aux = (char*)malloc(80*sizeof(char));
	int i;

	cabecalho("Lista de alunos");

	for (i=ini; i<ini+4; i++) {
		emptyLine();
		if(!strcmp(lista_->aluno[i].nome, "")) {
			emptyLine();
			emptyLine();
		} else {

			sprintf(aux, "Nome: %s (%s)", lista_->aluno[i].nome, resolveSituacao(&lista_->aluno[i]));
			line(aux, 'C');

			sprintf(aux, "  Notas: %.2f - %.2f    Media: %.2f",
						lista_->aluno[i].nota1,
						lista_->aluno[i].nota2,
						calculaMedia(&lista_->aluno[i]));
			line(aux, 'C');
		}
	}

	emptyLine();
	emptyLine();
	line("1 - Anterior | Proximo - 2", 'C');
	line("0. Voltar", 'L');
	emptyLine();
	filledLine();

	free(aux);
}

void menuAprovados(){

}
void imprimeListaAprovados(){

}



// Funcoes de mensagem
void setMensagemAviso(char* msg) {
	strcpy(_mensagem_aviso, msg);
}
void imprimeMensagemAviso() {
	if(strcmp(_mensagem_aviso, "")) {
		line(_mensagem_aviso, 'C');
		strcpy(_mensagem_aviso, "");
	} else {
		emptyLine();
	}
}

// Funcoes de debug
Lista* criaListaFake() {

	Lista* lista = criaLista(TAMANHO_INICIAL_LISTA);
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "Nicolas Anelli", 7.5, 7.4));
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "John Wick", 10.0, 7.5));
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "Britney Spear", 10.0, 5.0));
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "Slim Shady", 5.4, 5.8));
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "Shakira", 7.0, 7.0));
	adicionarAluno(lista,
			criaAluno(lista->quantidade, "Jack-Jack", 10.0, 10.0));

	return lista;
}
void imprimeLista(Lista* lista){

	int i;

	printf("Lista: %x\n", (unsigned int)lista);
	printf("- Tamanho atual: %d\n", lista->quantidade);
	printf("- Tamanho maximo: %d\n", lista->maximo);
	printf("- Alunos: \n");
	for (i=0; i<lista->quantidade; i++) {
		imprimeAluno(&lista->aluno[i]);
		printf("\n");
	}
	printf("\n\n");

}
void imprimeAluno(Aluno* aluno) {

	printf("\t Aluno %d: %s\n", aluno->codigo, aluno->nome);
	printf("\t Notas: 1. [%.2f] - 2. [%.2f]\n", aluno->nota1, aluno->nota2);
	printf("\t Media final: [%.2f]\n", calculaMedia(aluno));
}











