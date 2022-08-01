#include "tela.h"
#include <iostream>
#include <unistd.h>

#define tempo 2000000

using namespace std;

//Mostra a tela de escolha principal
//Pre condicao: Nenhuma
//Pos condicao: Escolha retornada pro menu
//Retorna: Escolha feita pelo usuario
int Tela_principal(){
	int in;
	printf(" ________\n");
	printf("| %s%-2s|\n", "1 AFD", "");	
	printf("|%-8s|\n", "");
	printf("| %s %-1s|\n", "2 AFE", "");
	printf("|%-8s|\n", "");
	printf("| %s%-1s|\n", "3 Sair", "");
	printf(" --------\n\n");
		
	while(!(cin >> in)){
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Entrada invalida" << endl;
	}	

	if (in != 1 && in != 2 && in != 3){
		system("clear");
		cout << "Escolha invalida\n\n";
		usleep(tempo);
		return -1;
	}
	if (in == 3){
		return 0;
	}
	return in;
}

//Mostra a tela de escolha do afd
//Pre condicao: Nenhuma
//Pos condicao: Escolha retornada pro menu
//Retorna: Escolha feita pelo usuario
int Tela_AFD(){
	int in;
	system("clear");
	printf(" ____________________\n");
	printf("| %5s%-1s|\n", "1 Carregar arquivo", "");	
	printf("|%-20s|\n", "");
	printf("| %5s%-1s|\n", "2 Processar cadeia", "");	
	printf("|%-20s|\n", "");
	printf("| %5s%-13s|\n", "3 Sair", "");
	printf(" --------------------\n\n");

	while (!(cin >> in)){
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Entrada invalida" << endl;
	}

	switch (in){
		case 1:
		case 2:
			return in;
		case 3:
			return 0;
		default:
			system("clear");
			printf("Escolha invalida\n\n");
			usleep(tempo);
			return -1;
	}

}

//Mostra a tela de escolha do afe
//Pre condicao: Nenhuma
//Pos condicao: Escolha retornada pro menu
//Retorna: Escolha feita pelo usuario
int Tela_AFE(){
	int in;
	system("clear");
	printf(" ____________________\n");
	printf("| %5s|\n", "1 Carregar arquivo ");	
	printf("|%-20s|\n", "");
	printf("| %5s%-4s|\n", "2 Converter AFE", "");	
	printf("|%-20s|\n", "");
	printf("| %5s%-13s|\n", "3 Sair", "");
	printf(" --------------------\n\n");

	while (!(cin >> in)){
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "Entrada invalida" << endl;
	}

	switch (in){
		case 1:
		case 2:
			return in;
		case 3:
			return 0;
		default:
			system("clear");
			printf("Escolha invalida\n\n");
			usleep(tempo);
			return -1;
	}
}


