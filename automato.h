#ifndef AUTOMATO_H
#define AUTOMATO_H

#include "regras.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


typedef struct Automato{
	string alfabeto;
	vector <string> estados;
	string estado_inicial;
	vector <string> estados_finais;
}Automato;

//Carrega o afd de um arquivo txt
//Pre condicao: Nenhuma
//Pos condicao: o afd é carregado
//Parametos: String in especificando o nome do arquivo, struct Automato onde o afd sera guardado,vetor de struct Regras o qual as regras do afd serao guardadas
Automato *Carrega_afd_arquivo(string in, Automato *afd, vector<Regras_AFD> &regras_afd);

//Carrega o afe de um arquivo txt
//Pre condicao: Nenhuma
//Pos condicao: o afe é carregado
//Parametos: String in especificando o nome do arquivo, struct Automato onde o afe sera guardado,vetor de struct Regras o qual as regras do afe serao guardadas
Automato *Carrega_afe_arquivo(string in, Automato *afe, vector <Regras_AFE> &regras_afe);

//Processa uma cadeia de caracteres no afd
//Pre condicao: afd carregado do arquivo
//Pos condicao: cadeia processada sendo aceita ou nao
//Parametos: Vetor de struct Regras contendoa as regras do afd, struct Automato contendo o afd, string in especificando o nome do arquivo 
void Processa_cadeia(vector <Regras_AFD> regras, Automato *afd, string &in);

//Procura uma regra do afe que contenha o carracter @
//Pre condicao: afe carregado do arquivo
//Pos condicao: Estados onde é possivel se alcancar lendo @ são adquiridos
//Parametos: int self que indica se o estado deve ser inserido no vetor de fechamentos, Struct afe com os dados
//			 string estado qual indica o estado atual, vetor de regras para verificação, vetor de vetor de estados o qual serão guardados os novos estados
//			 vetor de string auxiliar para guardar os pre estados  	 	 
void Procura_vazio(int self, Automato *afe, string estado, vector <Regras_AFE> regras, vector<vector<string>> &estados, vector <string> &estados_aux);

//Faz o fechamento inicial ultilizando o procura vazio
//Pre condicao: afe carregado do arquivo
//Pos condicao: Fechamentos iniciais criados
//Parametos: Automato afe com os dados, vetor de string estados com os estados, vetor de regras, vetor de vetor de string que ira conter os fechamentos 
void Fechamento(Automato *afe,vector <string> estados, vector <Regras_AFE> regras, vector<vector<string>> &fechamentos);

//Procura se um fechamento ja existe
//Pre condicao: Fechamentos criados 
//Pos condicao: Posicao no qual o fechamento esta é adquirida
//Parametos: Vetor de vetor de string com os fechamentos, Vetor de string com o fechamento  
int procura_fechamento(vector <vector <string>> fechamentos, vector <string> fechamento);

//Transforma um estado em fechamento
//Pre condicao: Fechamentos criados 
//Pos condicao: Estado é transformado em fechamento
//Parametos: Struct com afd, vetor de string com o estado, vetor de vetor de string com os fechamentos, vetor de string o qual o fechamento sera armazenado
void Transforma_em_fechamentos(Automato *afd, vector <string> estado, vector<vector <string>> fechamentos, vector <string> &fechamento);

//Transforma um afe em afd 
//Pre condicao: Afe carregado do arquivo 
//Pos condicao: Afe é transformado 
//Parametos: Automato afe com os dados, vetor de regras com as regras do afe, vetor de regras afd o qual serao guardadas as novas regras, automato afd novo
Automato* AFE_to_AFD(Automato *afe, vector <Regras_AFE> regras_afe, vector <Regras_AFD> &regras_afd, Automato *afd);

//Mostra os dados de um automato
//Pre condicao: Automato existente 
//Pos condicao: Automato mostrado na tela
//Parametos: Struct Automato com o automato a ser mostrado  
void print_Automato(Automato *automato);

#endif
