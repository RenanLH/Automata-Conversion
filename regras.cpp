#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "funcoesauxliares.h"
#include "regras.h"
using namespace std;


//Dado uma string de entrada, arruma ela de acordo com as transicoes do afd
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Regras arrumadas
//Parametos: String leitura, vetor de regras afd, string alfabeto
void arruma_transicao_afd(string leitura, vector <Regras_AFD> &regras, string alfabeto){
	int inicio = leitura.find('(') + 1;
	string aux;
	Regras_AFD regras_aux;
	
 	for (; leitura.at(inicio) != ',' ; inicio++){
		if (leitura.at(inicio) != ' '){
			aux +=  leitura.at(inicio);
		}
	}

	retira_espacos(aux);
	regras_aux.estado_atual = aux;

	for (; leitura.at(inicio) != ')' ; inicio++){
		if(is_alfabeto_Automato(leitura.at(inicio), alfabeto)){
			regras_aux.caracter = leitura.at(inicio);
			break;
		}
	}

	inicio = leitura.find('=') +1;
	aux.clear();
	for(;inicio < leitura.size(); inicio++){
		if (leitura.at(inicio) != '\n'){
			aux += leitura.at(inicio);
		}
	}
	retira_espacos(aux);
	regras_aux.estado_pos_transicao = aux;

	regras.push_back(regras_aux);
}

//Dado uma string de entrada, arruma ela de acordo com as transicoes do afe
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Regras arrumadas
//Parametos: String leitura, vetor de regras afe, string alfabeto
void arruma_transicao_afe(string leitura, vector <Regras_AFE> &regras, string alfabeto){
	int inicio = leitura.find('(') + 1;
	string temp;
	Regras_AFE regras_temp;
	
 	for (; leitura.at(inicio) != ','  ; inicio++){
		temp +=  leitura.at(inicio);	
	}
	retira_espacos(temp);

	regras_temp.estado_atual = temp;

	for (; leitura.at(inicio) != ')' ; inicio++){
		if(is_alfabeto_Automato(leitura.at(inicio), alfabeto)|| leitura.at(inicio) == '@'){
			regras_temp.caracter = leitura.at(inicio);
			break;
		}

	}

	inicio = leitura.find('=') +1;
	temp.clear();
	for(;inicio < leitura.size(); inicio++){
		
		if (leitura.at(inicio) == ','){
			retira_espacos(temp);
			regras_temp.estados_pos_transicao.push_back(temp);
			temp.clear();
		}else if (leitura.at(inicio) != '\n'){
			temp += leitura.at(inicio);
		}
	}

	retira_espacos(temp);
	regras_temp.estados_pos_transicao.push_back(temp);

	regras.push_back(regras_temp);
}

//Dado um caracter e um estado ele devolve o estado pos transicao
//Pre condicao: Vetor de regras carregado
//Pos condicao: Estado pos transicao adquirido
//Parametos: Char caracter, string estado atual, vetor de regras, e string pos transicao
void processa_regra_afd(char caracter, std::string pos, vector <Regras_AFD> regras, string &estado_pos_transicao){
	estado_pos_transicao.clear();
	for (int i = 0; i < regras.size(); i++){
		if ((regras[i].estado_atual == pos) && (regras[i].caracter == caracter)){	
			estado_pos_transicao = regras[i].estado_pos_transicao;
			return;
		}
	}
}

//Dado um caracter e um estado ele devolve o estado pos transicao
//Pre condicao: Vetor de regras carregado
//Pos condicao: Estado pos transicao adquirido
//Parametos: Char caracter, string estado atual, vetor de regras, e string pos transicao
void processa_regra_AFE(char caracter, string pos, vector <Regras_AFE> regras,  vector <string> &estados_pos_transicao){
	auto it = estados_pos_transicao.begin();
	for (int i = 0; i < regras.size(); i++){
		if ((regras[i].estado_atual == pos) && (regras[i].caracter == caracter)){
			for (int j = 0; j < regras[i].estados_pos_transicao.size(); j++){
				it = find (estados_pos_transicao .begin(), estados_pos_transicao .end(), regras[i].estados_pos_transicao[j]);
				if (!(estados_pos_transicao.end() - it)){
					estados_pos_transicao.push_back(regras[i].estados_pos_transicao[j]);
				}

			}			
		}
	}				
}

//Mostra todas as regras do vetor de regras
//Pre condicao: Vetor de regras carregado
//Pos condicao: Regras mostradas na tela
//Parametos: Vetor de regras
void print_Regras(vector <Regras_AFD> regras){
	for (auto it = 0; it < regras.size(); it++){
		cout << "(" ;
		for_each(regras[it].estado_atual.begin(), regras[it].estado_atual.end(), [](char c) {cout << c;});
		cout << "," << regras[it].caracter << ")= ";
		for_each(regras[it].estado_pos_transicao.begin(), regras[it].estado_pos_transicao.end(), [](char c) {cout << c;}); cout << endl;
	}
}
