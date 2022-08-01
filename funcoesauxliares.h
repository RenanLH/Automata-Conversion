#ifndef FUNCOESAUXILIARES_H
#define FUNCOESAUXILIARES_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Dado um estado, verifica se o mesmo eh final
//Pre condicao: Automato carregado 
//Pos condicao: Retorna verdadeiro ou falso
//Parametos: String estado,Vetor de estados
int estado_is_final(string estado, vector <string> estados_finais);

//Dado um caractere, verifica se o mesmo pertence ao alfabeto
//Pre condicao: Automato carregado 
//Pos condicao: Retorna verdadeiro ou falso
//Parametos: char leitura,String contendo alfabeto
int is_alfabeto_Automato(char leitura, string alfabeto);

//Dado uma string de entrada, arruma ela de acordo com o alfabeto do afd
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Alfabeto arrumado
//Parametos: String leitura, string alfabeto
void arruma_alfabeto(string leitura, string &alfabeto);

//Dado uma string de entrada, retira os espacos desnecessarios
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: String arrumada
//Parametos: String leitura
void retira_espacos(string &leitura);

//Dado uma string de entrada, arruma ela de acordo com os estados
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Estados arrumados
//Parametos: String leitura
void arruma_estados(string leitura, vector <string> &estados);

//Mostra os estados char por char
//Pre condicao: Nenhuma
//Pos condicao: Estados mostrados na tela
//Parametos: String init com frase mostrada antes do vetor, string vetor com os estados
void print_estados_char(string init, string vetor);

//Mostra os estados string por string
//Pre condicao: Nenhuma
//Pos condicao: Estados mostrados na tela
//Parametos: String init com frase mostrada antes do vetor, vetor de stringstring vetor com os estados
void print_estados_string(string init, vector<string> vetor);

//Dado uma string in transforma ela em minuscula e coloca em aux
//Pre condicao: Nenhuma
//Pos condicao: aux contem a string in com os caracteres minusculos
//Parametos: String in com a string original, string aux com os caracteres minusculos
void To_lower(string in, string &aux);

#endif