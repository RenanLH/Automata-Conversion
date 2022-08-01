
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "tela.h"
#include "automato.h"
#include "regras.h"
#include "funcoesauxliares.h"

using namespace std;

#define tempo 2000000

int main(){
	int choice;
	Automato *afd = NULL;
	Automato *afe = NULL;
	string in;

	vector <Regras_AFD> regras_afd;
	vector <Regras_AFE> regras_afe;
	
	for (;;){
		system("clear");
		choice = Tela_principal();
		switch (choice){
			case 1: //AFD
				for (;choice;){
					choice = Tela_AFD();
					switch(choice){
						case 1: // Carrega arq
							system("clear");
							if (afd){
								delete afd;	
								regras_afd.clear();
								afd = NULL;
							}
							cout << "Nome do arq: ";
							cin >> in;
							if (in.find (".txt") == -1){
								in += ".txt";
							}
							afd = Carrega_afd_arquivo(in, afd, regras_afd);

							break;
						case 2: // Processa
							system("clear");
							cout << "entrada: ";
							cin >> in;
							Processa_cadeia(regras_afd, afd, in);
							cout << "\nSair - S" << endl;
							cin >> in; 
							break;
					}
				}
				break;
			case 2: //AFE
				for (; choice;){
					choice = Tela_AFE(); 
					switch (choice){
						case 1: // Carrega arq
							system("clear");
							cout << "Nome do arq: ";
							cin >> in;
							if (in.find (".txt") == -1){
								in += ".txt";
							}
							if (afe){
								delete afe;
								regras_afe.clear();
								afe = NULL;
							}
							afe = Carrega_afe_arquivo(in, afe, regras_afe);

							break;
						case 2: //Converte
							system("clear");
							if (afe){
								if (afd){
									delete afd;	
									regras_afd.clear();
									afd = NULL;
								}
								afd = AFE_to_AFD(afe, regras_afe, regras_afd, afd);
								
								print_Automato(afd);
								print_Regras(regras_afd);
								
								cout << "\nSair - S" << endl;
								cin >> in;
							}
							else {
								cout << "Automato nao carregado" << endl;
								usleep(tempo);	
							}
							break; 
					} 
				} 
				break;
			case 0: 
				if (afd){
					delete afd;	
					regras_afd.clear();
				}
				if (afe){
					delete afe;
					regras_afe.clear();
				}
				return 0;
			default: 
				break;
		}
	}

}
