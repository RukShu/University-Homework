#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

const int data_quantity = 9;
const string header = "Cedula,Nombre,Apellido,Monto,Password,DatosCodificados";
const string fields [9] = {"Cedula", "Nombre", "Apellido", "Edad", "Sexo (H|M)", "Estado Civil (S|C)", "Grado Academico (I|M|G|P)", "Monto", "Password"};

enum DataFields {
    ID = 0, NAME = 1, LAST_NAME = 2, AGE = 3, SEX = 4, CIVIL_STATUS = 5, ACADEMIC_GRADE = 6, AMOUNT = 7, PASSWORD = 8
};

struct person{
    vector<string> data;
    void initialize(){
        data = vector<string> (9, ""); 
    }
};

struct personal_data{
	int age;
	char sex, cs, ag;
};

class Person{
	private:
	vector<string> data = vector<string> (9, "");	
	
	int encodeData(int age, char sex, char cs, char ag){
		int code = 0;
		if(sex == 'M') code = code | 0b1000;
		if(cs == 'C') code = code | 0b100;
		if(ag == 'M') code = code | 0b01;
		if(ag == 'G') code = code | 0b10;
		if(ag == 'P') code = code | 0b11;
		code += (age << 4);
		return code;
	}

	personal_data decodeData(int code){
		personal_data pd;
		pd.sex = "HM"[(code & 0b1000) == 0b1000];
		pd.cs = "SC"[(code & 0b100) == 0b100];
		pd.ag = "IMGP"[code & 0b11];
		pd.age = code >> 4;
		return pd;
	}

	public:
	//Operators
	bool operator == (Person p) const {
		return this->data[ID] == p.data[ID];
	}	
	
	bool operator == (string str) const {
		return this->data[ID] == str;
	}

	//Constructors
	Person() = default;
	
	Person(string line){
		this->setData(line);
	}

	Person(vector<string> s){
		this->setData(s);
	}
		
	//Getter
	string getData(){
		string line = "";
		for(int j = 0; j < data_quantity; j++){
			if(j == AGE || j == SEX || j == CIVIL_STATUS || j == ACADEMIC_GRADE) continue;
         		if(j > 0) line += ",";
        		line += this->data[j];
       		}
		line += ",";
		line += to_string(encodeData(stoi(this->data[AGE]), this->data[SEX][0], this->data[CIVIL_STATUS][0], this->data[ACADEMIC_GRADE][0]));
		return line;
	}

	//Setter
	void setData(string line){
		string word = "";
		for(int i = 0, j = 0; i < (int)line.size(); i++){
	            if(line[i] == ','){
	                this->data[j++] = word;
			while(j == AGE || j == SEX || j == CIVIL_STATUS || j == ACADEMIC_GRADE) j++;
	                word = "";
	                continue;
	            }
	            word += line[i];
	        }
		personal_data pd = decodeData(stoi(word));
		this->data[AGE] = to_string(pd.age);
		this->data[SEX] = pd.sex;
		this->data[CIVIL_STATUS] = pd.cs;
		this->data[ACADEMIC_GRADE] = pd.ag;
	}
	
	void setData(vector<string> s){
		for(int i = 0; i < data_quantity; i++){
        		if(s[i] == "") continue;
        		this->data[i] = s[i];
    		}
	}	

	//Methods
	
	void printData(){
	    for(int i = 0; i < data_quantity; i++){
	        if(i == PASSWORD) continue;
	        if(i > 0) cout << " ";
	        cout << this->data[i];
	    }
	    cout << '\n';
	}
};

string path;
vector<Person> p;

void consoleClear(){
	cout << flush;
	system("CLS");
}

void loadData(){
    string line;
    ifstream fin(path);
    //File validation
    getline(fin, line);
    if(line != header) return;
    //File read
    while(!fin.eof()){
        getline(fin, line);
       	p.push_back(line);
    }
}

void saveData(){
    ofstream fout(path);
    fout << header << '\n';
    for(int i = 0; i < (int)p.size(); i++){
        if(i > 0) fout << '\n';
	fout << p[i].getData();
    }
}

bool validateCharacter(char input, string valid_characters){
    if(valid_characters == "\n\b\r") return true;
    for(int i = 0; i < (int)valid_characters.size(); i++){
		if(input == valid_characters[i]) return true;
	}
	return false;   	//Invalid character
}

string vectorCharToString(vector<char> c){
    string ret = "";
	for(int i = 0; i < (int)c.size(); i++) ret += c[i];
	return ret;
}

string readSpecialInput(int length = 1024, string valid_characters = "", string input_type = "normal"){
	bool loop = true, point = false;
    int decimal_numbers = 0;
    vector <char> ret;
	while(loop){
		char input = getch();
		if(!validateCharacter(input, valid_characters + "\n\b\r")) continue;
		switch(input){
			case '\r':
			case '\n':
				if(ret.size() == 0) continue;
				loop = false;
				cout << '\n';
				break;
			case '\b':
				if(ret.size() == 0) continue;
                if(input_type == "decimal"){
                    if(ret[ret.size() - 1] == '.') point = false;
                    if(point) decimal_numbers--;
                }
				cout << "\b \b";
				ret.erase(ret.end() - 1);
				break;
			default:
				if((int)ret.size() == length) continue;
                if(input_type == "normal") cout << input;
                if(input_type == "password") cout << "*";
                if(input_type == "decimal"){
                    if(decimal_numbers == 2) continue;
                    if(point && input != '.') decimal_numbers++;
                    if(input == '.'){
                        if(ret.size() == 0) continue;
                        if(point) continue;
                        point = true;
                    }
                    cout << input;
                }
				ret.push_back(input);
				break;
		}
	}
	return vectorCharToString(ret);
}

vector<string> readData(vector<int> omited_fields = {}){
    int i = 0;
    vector<string> data (data_quantity, "");
    while(i < data_quantity){
        bool repeat = false;
        bool omited_field = false;
        for(int j = 0; j < (int)omited_fields.size(); j++) if(i == omited_fields[j]) omited_field = true;
        if(omited_field){
            i++;
            continue;
        }
        cout << fields[i] << ": ";
        switch(i){
            case ID:
                data[i] = readSpecialInput(11, "1234567890");
                break;
            case NAME:
            case LAST_NAME:
                data[i] = readSpecialInput();
                break;
            case AGE:
                data[i] = readSpecialInput(3, "1234567890");
                if(stoi(data[i]) > 120 || stoi(data[i]) < 18) {
                    repeat = true;
                    cout << "Edad fuera del rango valido [18-120]" << '\n';
                }
                break;
            case SEX:
                data[i] = readSpecialInput(1, "HM");
                break;
            case CIVIL_STATUS:
                data[i] = readSpecialInput(1, "SC");
                break;
            case ACADEMIC_GRADE:
                data[i] = readSpecialInput(1, "IMGP");
                break;
            case AMOUNT:
                data[i] = readSpecialInput(1024, "1234567890.", "decimal");
                break;
            case PASSWORD:
                string password1, password2;
                password1 = readSpecialInput(1024, "", "password");
                cout << fields[PASSWORD] << " otra vez: ";
                password2 = readSpecialInput(1024, "", "password");
                if(password1 == password2) data[i] = password1;
                else {
                    repeat = true;
                    cout << "Las passwords no coinciden" << '\n';
                }
                break;
        }
        if(repeat) continue;
        else i++;
    }
    return data;
}

int searchDataRow(string id){
    for(int i = 0; i < (int)p.size(); i++){
        if(p[i] == id) return i; //ID was found
    }
    return -1;  //ID was not found
}

int searchData(){
    cout << "Introduzca la cedula a buscar: ";
    string input = readSpecialInput(11, "1234567890");
    int row = searchDataRow(input);
    if(row == -1) {
        cout << "No se encontro a ninguna persona" << '\n';
        return -1;
    }
    cout << "Se encontro la siguiente persona: " << '\n';
    p[row].printData();
    return row;
}

void addData(){
    bool loop = true;
    while(loop){
        vector<string> temp = readData();
        cout << "Continuar sin guardar (C) | Guardar y continuar (G) | Salir sin guardar (S)" << '\n';
        char input = readSpecialInput(1, "CGSX")[0];
        switch(input){
            case 'C':
                break;
            case 'G':
                p.push_back(temp);
                break;
            case 'S':
                loop = false;
                break;
            case 'X':
                loop = false;
                p.push_back(temp);
                break;
        }
    }
}

void editData(){
    int row = searchData();
    if(row == -1) return;
    vector<string> temp = readData({ID, PASSWORD});
    p[row].setData(temp);
}

void listData(){
    for(int i = 0; i < (int)p.size(); i++){
        p[i].printData();
    }
}

void deleteData(){
    int row = searchData();
    if(row == -1) return;
    p.erase(p.begin() + row);
}

void menu(){
    while(true){
        consoleClear();
        cout << "Registro de Datos V" << '\n' << '\n';
        cout << "1 - Agregar Personas" << '\n';
        cout << "2 - Buscar Persona" << '\n';
        cout << "3 - Listar Personas" << '\n';
        cout << "4 - Borrar Persona" << '\n';
        cout << "5 - Editar Persona" << '\n';
        cout << "6 - Salir" << '\n';
        cout << '\n';
        char input = readSpecialInput(1, "123456")[0];
        switch(input){
            case '1':
                addData();
                break;
            case '2':
                searchData();
                break;
            case '3':
                listData();
                break;
            case '4':
                deleteData();
                break;
            case '5':
                editData();
                break;
            case '6':
                return;
                break;
        }
        getch();
    }
}

int main(int argc, char * argv[]){
    if(argc < 2) {
        cout << "Error: No arguments were given." << '\n';
        return 1;
    }
    path = argv[1];
    loadData();
    menu();
    saveData();
}