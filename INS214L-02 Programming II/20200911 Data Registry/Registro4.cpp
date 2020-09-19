#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

enum Code {
	ID = 0, NAME = 1, LAST_NAME = 2, AGE = 3, AMOUNT = 4, PASSWORD = 5
};

struct person{
	string data [6];
};

string filename = "", header = "Cedula,Nombre,Apellido,Edad,Monto,Password";
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
	for(int i = 0; i < (int)p.size(); i++){
		for(int j = 0; j < 6; j++){
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
		for(int i = 0, j = 0; i < (int)line.size(); i++){
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

bool valid_input(char input, string valid_chars){
	for(int i = 0; i < valid_chars.size(); i++){
		if(input == valid_chars[i]) return true;
	}
	return false;
}

string vector_char_to_string(vector<char> c){
	string ret = "";
	for(int i = 0; i < c.size(); i++) ret += c[i];
	return ret;
}

string read_number(){
	vector<char> ret;
	bool loop = true;
	while(loop){
		char input = getch();
		if(!valid_input(input, "0123456789\n\b\r")) continue;
		switch(input){
			case '\r':
			case '\n':
				loop = false;
				cout << '\n';
				break;
			case '\b':
				if(ret.size() == 0) continue;
				cout << "\b \b";
				ret.erase(ret.end() - 1);
				break;
			default:
				cout << input;
				ret.push_back(input);
				break;	
		}
	}
	return vector_char_to_string(ret);
}

string read_decimal(){
	vector<char> ret;
	int decimal_numbers = 0;
	bool loop = true, point = false;
	while(loop){
		char input = getch();
		if(!valid_input(input, "0123456789.\b\n\r")) continue;
		switch(input){
			case '\r':
			case '\n':
				loop = false;
				cout << '\n';
				break;
			case '\b':
				if(ret[ret.size() - 1] == '.') point = false;
				if(point) decimal_numbers--;
				if(ret.size() == 0) continue;
				cout << "\b \b";
				ret.erase(ret.end() - 1);
				break;
			case '.':
				if(ret.size() == 0) continue;
				if(point) continue;
				point = true;
				cout << '.';
				ret.push_back('.');
				break;
			default:
				if(decimal_numbers == 2) continue;
				if(point) decimal_numbers++;
				cout << input;
				ret.push_back(input);
				break;

		}
	}
	return vector_char_to_string(ret);
}

string read_password(){
	vector<char> ret;
	bool loop = true;
	while(loop){
		char input = getch();
		switch(input){
			case '\r':
			case '\n':
				loop = false;
				cout << '\n';
				break;
			case '\b':
				if(ret.size() == 0) continue;
				cout << "\b \b";
				ret.erase(ret.end() - 1);
				break;
			default:
				cout << '*';
				ret.push_back(input);
				break;	
		}
	}
	return vector_char_to_string(ret);
}

string read_id(){
	vector<char> ret;
	bool loop = true;
	while(loop){
		char input = getch();
		if(!valid_input(input, "0123456789\n\b\r")) continue;
		switch(input){
			case '\r':
			case '\n':
				loop = false;
				cout << '\n';
				break;
			case '\b':
				if(ret.size() == 0) continue;
				cout << "\b \b";
				ret.erase(ret.end() - 1);
				break;
			default:
				if(ret.size() == 11) continue;
				cout << input;
				ret.push_back(input);
				break;	
		}
	}
	return vector_char_to_string(ret);
}

bool capture_data(){
	string param [7] = {"Cedula", "Nombre", "Apellido", "Edad", "Monto", "Password", "Password de nuevo"};
	string password1, password2;
	person temp;
	while(true){	
		for(int i = 0; i < 7; i++){
			cout << param[i] << ": ";
			switch(i){
				case 0:
					temp.data[i] = read_id();
					break;
				case 1:
				case 2:
					getline(cin, temp.data[i]);
					break;
				case 3:
					while(true){
						temp.data[i] = read_number();
						if(temp.data[i] == "") break;
						if(stoi(temp.data[i]) > 120) {
							cout << "Edad invalida" << '\n';
							continue;
						}
						break;
					}
					break;
				case 4:
					temp.data[i] = read_decimal();
					break;
				case 5: 
					password1 = read_password();
					break;
				case 6:
					password2 = read_password();
					break;
			}
		}
		if(password1 != password2){
			cout << "Las passwords no coinciden" << '\n';
			continue;
		}
		temp.data[PASSWORD] = password1;
		break;
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

int search_data(){
	string line = "";
	cout << "Introduzca la cedula de la persona que busca." << '\n';
	line = read_id();
	for(int i = 0; i < (int)p.size(); i++){
		if(line == p[i].data[ID]) {
			cout << "Se ha encontrado una persona: ";
			for(int j = 0; j < 5; j++){
				if(j > 0) cout << " ";
				cout << p[i].data[j];
			}
			cout << '\n';
			getch();
			return i;
		}
	}
	cout << "No se ha encontrado la persona." << '\n';
	getch();
	return -1;
}

void list_data(){
	for(int i = 0; i < (int)p.size(); i++){
		for(int j = 0; j < 5; j++){
			if(j > 0) cout << " ";
			cout << p[i].data[j];
		}
		cout << '\n';
	}
	getch();
}

void edit_data(){
	int line_id = search_data();
	if(line_id == -1) return;
	string param [5] = {"Cedula", "Nombre", "Apellido", "Edad", "Monto"};
	person temp;
	for(int i = 1; i < 5; i++){
		cout << param[i] << ": ";
			switch(i){
				case 0:
					temp.data[i] = read_id();
					break;
				case 1:
				case 2:
					getline(cin, temp.data[i]);
					break;
				case 3:
					while(true){
						temp.data[i] = read_number();
						if(temp.data[i] == "") break;
						if(stoi(temp.data[i]) > 120) {
							cout << "Edad invalida" << '\n';
							continue;
						}
						break;
					}
					break;
				case 4:
					temp.data[i] = read_decimal();
					break;
			}
	}
	for(int i = 1; i < 5; i++){
		p[line_id].data[i] = temp.data[i];
	}
}

void delete_data(){
	int line_id = search_data();
	if(line_id == -1) return;
	p.erase(p.begin() + line_id);
}

void menu(){
	while(true){
		console_clear();
		cout << "Registro de personas v2" << '\n' << '\n';
		cout << "R - Registrar personas" << '\n';
		cout << "L - Listar personas" << '\n';
		cout << "B - Buscar personas" << '\n';
		cout << "E - Editar personas" << '\n';
		cout << "X - Eliminar personas" << '\n';
		cout << "S - Salir" << '\n';
		cout << '\n';
		cout << "Escoja una opcion: " << '\n' << '\n';
		char input = tolower(getch());
		switch(input){
			case 'r':
				while(true)
					if(!capture_data()) break;
				break;
			case 'l':
				list_data();
				break;
			case 'b':
				search_data();
				break;
			case 'e':
				edit_data();
				break;
			case 'x':
				delete_data();
				break;
			case 's':
				return;
		}
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
