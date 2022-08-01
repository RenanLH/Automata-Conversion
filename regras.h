#ifndef REGRAS_H
#define REGRAS_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Regras_AFE{
	string estado_atual;
	char caracter;
	vector<string> estados_pos_transicao;
}Regras_AFE;

typedef struct Regras_AFD{
	string estado_atual;
	char caracter;
	string estado_pos_transicao;	
}Regras_AFD;



//Dado uma string de entrada, arruma ela de acordo com as transicoes do afd
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Regras arrumadas
//Parametos: String leitura, vetor de regras afd, string alfabeto
void arruma_transicao_afd(string leitura, vector <Regras_AFD> &regras, string alfabeto);

//Dado uma string de entrada, arruma ela de acordo com as transicoes do afe
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Regras arrumadas
//Parametos: String leitura, vetor de regras afe, string alfabeto
void arruma_transicao_afe(string leitura, vector <Regras_AFE> &regras, string alfabeto);

//Dado um caracter e um estado ele devolve o estado pos transicao
//Pre condicao: Vetor de regras carregado
//Pos condicao: Estado pos transicao adquirido
//Parametos: Char caracter, string estado atual, vetor de regras, e string pos transicao
void processa_regra_afd(char caracter, string pos, vector <Regras_AFD> regras, string &estado_pos_transicao);

//Dado um caracter e um estado ele devolve o estado pos transicao
//Pre condicao: Vetor de regras carregado
//Pos condicao: Estado pos transicao adquirido
//Parametos: Char caracter, string estado atual, vetor de regras, e string pos transicao
void processa_regra_AFE(char caracter, string pos, vector <Regras_AFE> regras,  vector <string> &estados_pos_transicao);

//Mostra todas as regras do vetor de regras
//Pre condicao: Vetor de regras carregado
//Pos condicao: Regras mostradas na tela
//Parametos: Vetor de regras
void print_Regras(vector <Regras_AFD> regras);



#endif