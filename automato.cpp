#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "automato.h"
#include "funcoesauxliares.h"

using namespace std;

//Carrega o afd de um arquivo txt
//Pre condicao: Nenhuma
//Pos condicao: o afd é carregado
//Parametos: String in especificando o nome do arquivo, struct Automato onde o afd sera guardado,vetor de struct Regras o qual as regras do afd serao guardadas
//Retorno: Automato com os dados carregados  
Automato *Carrega_afd_arquivo(string in, Automato *afd, vector<Regras_AFD> &regras_afd){
	ifstream file;
	file.open(in);
	if (file.is_open()){
		if (!afd){
			afd = new Automato;
		}
		string line;
		string aux;
		while( getline(file,line)){
			To_lower(line, aux);
			if (aux.find("alfabeto") != -1){
				arruma_alfabeto(line, afd->alfabeto);
			}
			else if (aux.find("estado") != -1){
				arruma_estados(line, afd->estados);
			}
			else if (aux.find("inicial") != -1){
				arruma_alfabeto(line, afd->estado_inicial);
			}
			else if (aux.find("fina") != -1){
				arruma_estados(line, afd->estados_finais);
			}
			else if (!line.empty()){	
				arruma_transicao_afd(line, regras_afd, afd->alfabeto);
			}
			aux.clear();
		}
		file.close();
		
	}else {
		cout << "Erro - abertura do arquivo" << endl;
		exit(-1);
	}
	return afd;
}

//Carrega o afe de um arquivo txt
//Pre condicao: Nenhuma
//Pos condicao: o afe é carregado
//Parametos: String in especificando o nome do arquivo, struct Automato onde o afe sera guardado,vetor de struct Regras o qual as regras do afe serao guardadas
//Retorno: Automato com os dados carregados  
Automato *Carrega_afe_arquivo(string in, Automato *afe, vector <Regras_AFE> &regras_afe){
	ifstream file;
	
	string line;
	string aux;

	file.open(in);
	
	if (!file.is_open()){
		cout << "Erro - abertura do arquivo" << endl;
		exit(-1);
	}

	if (!afe){
		afe = new Automato;
	}

	while (getline(file, line)){
		To_lower(line, aux);

		if (aux.find("alfabeto") != -1){
			arruma_alfabeto(line, afe->alfabeto);

		}
		else if (aux.find("estado") != -1){
			arruma_estados(line, afe->estados);
		}
		else if (aux.find("inicial") != -1){
			arruma_alfabeto(line, afe->estado_inicial);
		}
		else if (aux.find("fina") != -1){
			arruma_estados(line, afe->estados_finais);
		}

		else if (!line.empty()){	
			arruma_transicao_afe(line, regras_afe, afe->alfabeto);
		}
		aux.clear();

	}
	
	file.close();

	return afe;
}

//Processa uma cadeia de caracteres no afd
//Pre condicao: afd carregado do arquivo
//Pos condicao: cadeia processada sendo aceita ou nao
//Parametos: Vetor de struct Regras contendoa as regras do afd, struct Automato contendo o afd, string in especificando o nome do arquivo 
void Processa_cadeia(vector <Regras_AFD> regras, Automato *afd, string &in){
	if (afd){
		string estado_atual = afd->estado_inicial;
		string estado_temp;
		
		for ( ; in.size(); ){
			cout << "[" << estado_atual << "]" <<  in << endl;
			processa_regra_afd(in.at(0), estado_atual ,regras, estado_temp );
			
			if (estado_temp.empty()){
				break;
			}

			estado_atual = estado_temp;
			estado_temp.clear();
			in.erase(in.begin());
		}
		
		cout << "[" << estado_atual << "]" << endl;
		
		if (estado_is_final(estado_atual, afd->estados_finais) && in.empty()){
			cout << "ACEITA" <<endl;
		}
		else 
			cout << "REJEITA" <<endl;

	}
	else printf("Automato nao carregado\n");
}

//Procura uma regra do afe que contenha o carracter @
//Pre condicao: afe carregado do arquivo
//Pos condicao: Estados onde é possivel se alcancar lendo @ são adquiridos
//Parametos: int self que indica se o estado deve ser inserido no vetor de fechamentos, Struct afe com os dados
//			 string estado qual indica o estado atual, vetor de regras para verificação, vetor de vetor de estados o qual serão guardados os novos estados
//			 vetor de string auxiliar para guardar os pre estados durante a recursao 	 	 
void Procura_vazio(int self, Automato *afe, string estado, vector <Regras_AFE> regras, vector<vector<string>> &estados, vector <string> &estados_aux){	
	
	for (int i = 0; i < regras.size(); i++){
		if (regras[i].estado_atual == estado && regras[i].caracter == '@'){
			for (int j = 0; j < regras[i].estados_pos_transicao.size(); j++){
				estados_aux.push_back(regras[i].estados_pos_transicao[j]);
				Procura_vazio(0, afe, regras[i].estados_pos_transicao[j], regras, estados, estados_aux);
			}

		}
	}

	if (self){
		estados_aux.push_back (estado);
		sort(estados_aux.begin(), estados_aux.end());

		if (estado == afe->estado_inicial){
			estados.insert(estados.begin(), estados_aux);
		}
		else{
			estados.push_back(estados_aux);
		}

	}
}

//Faz o fechamento inicial ultilizando o procura vazio
//Pre condicao: afe carregado do arquivo
//Pos condicao: Fechamentos iniciais criados
//Parametos: Automato afe com os dados, vetor de string estados com os estados, vetor de regras, vetor de vetor de string que ira conter os fechamentos 
void Fechamento(Automato *afe,vector <string> estados, vector <Regras_AFE> regras, vector<vector<string>> &fechamentos){
	vector <string> estados_aux;
	for (int i = 0; i < estados.size(); i++){
		Procura_vazio(1, afe, estados[i], regras, fechamentos, estados_aux);
		estados_aux.clear();
	}
}	

//Procura se um fechamento ja existe
//Pre condicao: Fechamentos criados 
//Pos condicao: Posicao no qual o fechamento esta é adquirida
//Parametos: Vetor de vetor de string com os fechamentos, Vetor de string com o fechamento  
//Retorno: Posicao o qual o fechamento se encontra, ou -1 se não encontrado
int procura_fechamento(vector <vector <string>> fechamentos, vector <string> fechamento){
	auto it = find (fechamentos.begin(), fechamentos.end(), fechamento);
	
	if(it == fechamentos.end()){
		return -1;	
	}	
	return it - fechamentos.begin();
}

//Transforma um estado em fechamento
//Pre condicao: Fechamentos criados 
//Pos condicao: Estado é transformado em fechamento
//Parametos: Struct com afd, vetor de string com o estado, vetor de vetor de string com os fechamentos, vetor de string o qual o fechamento sera armazenado
void Transforma_em_fechamentos(Automato *afd, vector <string> estado, vector<vector <string>> fechamentos, vector <string> &fechamento){
	int indice;
	auto it = afd->estados.begin();
	for (int i = 0; i < estado.size(); i++){
		it = find(afd->estados.begin(), afd->estados.end(), estado[i]);
		
		if (it != afd->estados.end()){
			indice = it - afd->estados.begin();
			for (int j = 0; j < fechamentos[indice].size(); j++){
				if (find(fechamento.begin(), fechamento.end(), fechamentos[indice][j]) == fechamento.end() ){
					fechamento.push_back(fechamentos[indice][j]);
				}
			}
	
		}else {
			indice = -1;
		}
		
	}	
}

//Transforma um afe em afd 
//Pre condicao: Afe carregado do arquivo 
//Pos condicao: Afe é transformado 
//Parametos: Automato afe com os dados, vetor de regras com as regras do afe, vetor de regras afd o qual serao guardadas as novas regras, automato afd novo
//Retorna o afd transormado 
Automato* AFE_to_AFD(Automato *afe, vector <Regras_AFE> regras_afe, vector <Regras_AFD> &regras_afd, Automato *afd){

	int aux ,i = 0;	
	string str_aux;
	vector <vector <string>> fechamentos;
	vector <vector <string>> fechamentos_aux;
	vector <string> estados_pos_transicao;
	vector <string> estados_aux;
	Regras_AFD regra_aux;
	
	Fechamento(afe, afe->estados, regras_afe, fechamentos);
	fechamentos_aux.push_back(fechamentos[0]);

	
	if (!afd){
		
		afd = new Automato;
	}

	afd->alfabeto = afe->alfabeto;
	afd->estado_inicial = "r0";
	for(int j = -1; j < i; j++){
		for (int alfa = 0; alfa < afe->alfabeto.size(); alfa++){
			estados_pos_transicao.clear();
			estados_aux.clear();	

			for(int fec = 0; fec != fechamentos_aux[j+1].size(); fec++){
				processa_regra_AFE(afe->alfabeto[alfa], fechamentos_aux[j+1][fec], regras_afe,  estados_aux);
			}

			if (!estados_aux.empty()){
				sort(estados_aux.begin(), estados_aux.end());

				Transforma_em_fechamentos(afe, estados_aux, fechamentos, estados_pos_transicao);
				sort(estados_pos_transicao.begin(), estados_pos_transicao.end());

				regra_aux.estado_atual = "r" + to_string(j+1);

				for (int k = 0; k < afe->estados_finais.size(); k++){

					if (find(fechamentos_aux[i].begin(), fechamentos_aux[i].end(), afe->estados_finais[k]) != fechamentos_aux[i].end()){
						str_aux = "r" + to_string(i);
						if (find(afd->estados_finais.begin(), afd->estados_finais.end(), str_aux) == afd->estados_finais.end()){
							afd->estados_finais.push_back(str_aux);
						}		
						str_aux.clear();
					}
				}

				if (find(afd->estados.begin(), afd->estados.end(), regra_aux.estado_atual) == afd->estados.end()){
					afd->estados.push_back(regra_aux.estado_atual);
				}
				regra_aux.caracter = afe->alfabeto[alfa];
				aux = procura_fechamento(fechamentos_aux, estados_pos_transicao);

				if(aux == -1){
					fechamentos_aux.push_back(estados_pos_transicao);
					i++;
					regra_aux.estado_pos_transicao = "r" + to_string(i);
										
				}else {
					regra_aux.estado_pos_transicao = "r" + to_string(aux);
				}
				if (find(afd->estados.begin(), afd->estados.end(), regra_aux.estado_pos_transicao) == afd->estados.end()){
					afd->estados.push_back(regra_aux.estado_pos_transicao);
				}
				regras_afd.push_back(regra_aux);
				
			}

		}
		if (i > 100 ){
			cout << "Erro de conversao (Mais de 100 estados)" << endl;
			exit(-1);
		}
	}


	return afd;
}

//Mostra os dados de um automato
//Pre condicao: Automato existente 
//Pos condicao: Automato mostrado na tela
//Parametos: Struct Automato com o automato a ser mostrado  
void print_Automato(Automato *automato){
	if (automato){
		string aux = "alfabeto={";
		print_estados_char(aux, automato->alfabeto);		
		aux  = "estados={";	
		print_estados_string(aux, automato->estados);
		cout << "inicial=" << automato->estado_inicial << endl;
		aux = "finais={";
		print_estados_string(aux, automato->estados_finais);
		
	}
}