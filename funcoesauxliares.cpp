#define ever ;;
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "funcoesauxliares.h"
using namespace std;

//Dado um estado, verifica se o mesmo eh final
//Pre condicao: Automato carregado 
//Pos condicao: Retorna verdadeiro ou falso
//Parametos: String estado,Vetor de estados
//Retorna: Verdadeiro ou falso
int estado_is_final(string estado, vector <string> estados_finais){
	return find(estados_finais.begin(), estados_finais.end(), estado) != estados_finais.end();
}

//Dado um caractere, verifica se o mesmo pertence ao alfabeto
//Pre condicao: Automato carregado 
//Pos condicao: Retorna verdadeiro ou falso
//Parametos: char leitura,String contendo alfabeto
//Retorna: Verdadeiro ou falso
int is_alfabeto_Automato(char leitura, string alfabeto){
	return find(alfabeto.begin(), alfabeto.end(), leitura) != alfabeto.end();
}

//Dado uma string de entrada, arruma ela de acordo com o alfabeto do afd
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Alfabeto arrumado
//Parametos: String leitura, string alfabeto
void arruma_alfabeto(string leitura, string &alfabeto){
	int inicio = leitura.find('{') + 1;
	if (!inicio){
		inicio = leitura.find('=') + 1;
	}
	for (; inicio < leitura.size(); inicio++){
		if (isdigit(leitura.at(inicio)) || isalpha(leitura.at(inicio))){
			alfabeto += leitura.at(inicio); 
		}
	}
}

//Dado uma string de entrada, retira os espacos desnecessarios
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: String arrumada
//Parametos: String leitura
void retira_espacos(string &leitura){
	for(ever){
		if (leitura.front() == ' '){
			leitura.erase(leitura.begin());
		}
		else if (leitura.back() == ' '){
			leitura.pop_back();
		}else {
			return;
		}
	}
}

//Dado uma string de entrada, arruma ela de acordo com os estados
//Pre condicao: Arquivo de leitura aberto
//Pos condicao: Estados arrumados
//Parametos: String leitura
void arruma_estados(string leitura, vector <string> &estados){
	int inicio = leitura.find('{') + 1;
	string temp;

	if (!inicio){
		inicio = leitura.find('=') +1;
	}

	for (; inicio < leitura.size(); inicio++){
		if (leitura.at(inicio) == ','){
			retira_espacos(temp);
			estados.push_back(temp);
			temp.clear();
		}else 
			temp += leitura.at(inicio);

	}
	retira_espacos(temp);

	temp.erase(temp.end()-1);
	estados.push_back(temp);
}

//Mostra os estados char por char
//Pre condicao: Nenhuma
//Pos condicao: Estados mostrados na tela
//Parametos: String init com frase mostrada antes do vetor, string vetor com os estados
void print_estados_char(string init, string vetor){
	cout << init;
	for (int it = 0; it != vetor.size(); it++){
			cout << vetor[it];
			if (it < vetor.size()-1){
				cout << ',';
			}
			else cout << "}" << endl;
		}

}


//Mostra os estados string por string
//Pre condicao: Nenhuma
//Pos condicao: Estados mostrados na tela
//Parametos: String init com frase mostrada antes do vetor, vetor de stringstring vetor com os estados
void print_estados_string(string init, vector<string> vetor){
	cout << init;
	for (int it = 0; it != vetor.size(); it++){
			cout << vetor[it];
			if (it < vetor.size()-1){
				cout << ',';
			}
			else cout << "}" << endl;
		}

}
//Dado uma string in transforma ela em minuscula e coloca em aux
//Pre condicao: Nenhuma
//Pos condicao: aux contem a string in com os caracteres minusculos
//Parametos: String in com a string original, string aux com os caracteres minusculos
void To_lower(string in, string &aux){
	for (int i = 0; i < in.size(); i++){
		aux += tolower(in[i]);
	}
}
