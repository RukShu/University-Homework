#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

enum Code {
	ID = 0, NAME = 1, LAST_NAME = 2, AGE = 3
};

struct person{
	string data [4];
};

string filename = "", header = "Cedula,Nombre,Apellido,Edad";
vector<person> p;

void console_clear(){
	cout << flush;
	system("CLS");
}

void check_file(){
	ifstream fin(filename);	
	string line = "";
	getline(fin, line);
	fin.close();
	if(line == header) return;
	ofstream fout(filename);
	fout << header << '\n';
	fout.close();
}

void save_data(){
	ofstream fout(filename);
	fout << header << '\n';
	for(int i = 0; i < p.size(); i++){
		for(int j = 0; j < 4; j++){
			if(j > 0) fout << ",";
			fout << p[i].data[j];
		}
		fout << '\n';
	}
	fout.close();
}

void load_data(){
	string line = "";
	ifstream fin(filename);
	fin >> line;
	while(!fin.eof()){
		getline(fin, line);
		line += ",";
		p.push_back({});
		string word = "";
		for(int i = 0, j = 0; i < line.size(); i++){
			if(line[i] == ','){
				p[p.size() - 1].data[j++] = word;
				word = "";
				continue;
			}
			word += line[i];
		}
		if(p[p.size() - 1].data[ID] == "") p.erase(p.end() - 1);
	}
	fin.close();
}

bool capture_data(){
	string param [4] = {"Cedula", "Nombre", "Apellido", "Edad"};
	person temp;
	for(int i = 0; i < 4; i++){
		cout << param[i] << ": ";
		getline(cin, temp.data[i]);
	}
	while(true){
		cout << "Grabar(G), Continuar(C), Salir(S)? G|C|S" << '\n';
		char input = tolower(getch());
		switch(input){
			case 'g':
				p.push_back(temp);
				return 1;
			case 'c':
				return 1;
			case 's':
				return 0;
			default:
				cout << "Opcion invalida." << '\n' << '\n';
		}
	}
	return 0;
}

void menu(){
	while(true){
		if(!capture_data()) return;
	}
}

void debug_p(){
	console_clear();
	for(int i = 0; i < p.size(); i++){
		for(int j = 0; j < 4; j++){
			if(j > 0) cout << " ";
			cout << p[i].data[j]; 
		}
		cout << '\n';
	}
}

int main(int argc, char * argv[]){
	if(argc == 1){
		cout << "Error: No se ha introducido el nombre de ningun documento." << '\n';
		return 0;
	}
	filename = argv[1];
	check_file();
	load_data();
	menu();
	save_data();
}