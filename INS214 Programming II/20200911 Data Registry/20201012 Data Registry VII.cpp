#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <math.h>

using namespace std;

const int data_quantity = 9;
const int letter_quantity = 26;
const string header = "Cedula,Nombre,Apellido,Monto,Password,DatosCodificados";
const string fields [9] = {"Cedula", "Nombre", "Apellido", "Edad", "Sexo (H|M)", "Estado Civil (S|C)", "Grado Academico (I|M|G|P)", "Monto", "Password"};

enum DataFields {
    ID = 0, NAME = 1, LAST_NAME = 2, AGE = 3, SEX = 4, CIVIL_STATUS = 5, ACADEMIC_GRADE = 6, AMOUNT = 7, PASSWORD = 8
};

struct personal_data{
	int age;
	char sex, cs, ag;
};

string path;

class Person{
	private:
	int order = -1;
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

    static bool validateCharacter(char input, string valid_characters){
        if(valid_characters == "\n\b\r") return true;
        for(int i = 0; i < (int)valid_characters.size(); i++){
            if(input == valid_characters[i]) return true;
        }
        return false;   	//Invalid character
    }

    static string vectorCharToString(vector<char> c){
        string ret = "";
        for(int i = 0; i < (int)c.size(); i++) ret += c[i];
        return ret;
    }

	public:
	//Operators
	bool operator == (Person p) const {
		return this->data[ID] == p.data[ID];
	}	
	
	bool operator <= (Person p) const {
		return this->data[ID] <= p.data[ID];
	}	
	
	bool operator < (Person p) const {
		return this->data[ID] < p.data[ID];
	}	

	bool operator > (Person p) const {
		return this->data[ID] > p.data[ID];
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
    int getOrder(){	return order;	}

    int getId(){    return stoi(data[ID]);  }

    string getName(){   return data[NAME];  }

    string getLastName(){   return data[LAST_NAME];  }

    int getAge(){    return stoi(data[AGE]);   }    

    char getSex(){  return data[SEX][0];    }

    char getCivilStatus() { return data[CIVIL_STATUS][0]; }

    char getAcademicGrade() {   return data[ACADEMIC_GRADE][0]; }

    double getAmount(){ return stod(data[AMOUNT]);  }

    string getPassword(){   return data[PASSWORD];  }

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

    void setOrder(int order){	this->order = order; }

    void setId(int id){    data[ID] = to_string(id);  }

    void setId(string id){    data[ID] = id;  }

    void setName(string name){   data[NAME] = name;  }

    void setLastName(string last_name){   data[LAST_NAME] = last_name;  }

    void setAge(int age){    data[AGE] = to_string(age);   }    

    void setSex(char sex){  data[SEX] = sex;    }

    void setCivilStatus(char civil_status) { data[CIVIL_STATUS] = civil_status; }

    void setAcademicGrade(char academic_grade) {   data[ACADEMIC_GRADE] = academic_grade; }

    void setAmount(double amount){ data[AMOUNT] = to_string(amount);  }

    void setPassword(string password){   data[PASSWORD] = password;  }
    
	//Methods      
	
	int hashcode(){
		return (int)(tolower(getLastName()[0]));
	}
	
    static string readSpecialInput(int length = 1024, string valid_characters = "", string input_type = "normal"){
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

    static vector<string> readData(vector<int> omited_fields = {}){
        int i = 0;
        vector<string> temp_data (data_quantity, "");
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
                    temp_data[i] = readSpecialInput(11, "1234567890");
                    break;
                case NAME:
                case LAST_NAME:
                    temp_data[i] = readSpecialInput(1024, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ");
                    break;
                case AGE:
                    temp_data[i] = readSpecialInput(3, "1234567890");
                    if(stoi(temp_data[i]) > 120 || stoi(temp_data[i]) < 18) {
                        repeat = true;
                        cout << "Edad fuera del rango valido [18-120]" << '\n';
                    }
                    break;
                case SEX:
                    temp_data[i] = readSpecialInput(1, "HM");
                    break;
                case CIVIL_STATUS:
                    temp_data[i] = readSpecialInput(1, "SC");
                    break;
                case ACADEMIC_GRADE:
                    temp_data[i] = readSpecialInput(1, "IMGP");
                    break;
                case AMOUNT:
                    temp_data[i] = readSpecialInput(1024, "1234567890.", "decimal");
                    break;
                case PASSWORD:
                    string password1, password2;
                    password1 = readSpecialInput(1024, "", "password");
                    cout << fields[PASSWORD] << " otra vez: ";
                    password2 = readSpecialInput(1024, "", "password");
                    if(password1 == password2) temp_data[i] = password1;
                    else {
                        repeat = true;
                        cout << "Las passwords no coinciden" << '\n';
                    }
                    break;
            }
            if(repeat) continue;
            else i++;
        }
        return temp_data;
    }

    void editData(){
        vector<string> temp = readData({ID, PASSWORD});
        this->setData(temp);
    }

	void printData(){
	    for(int i = 0; i < data_quantity; i++){
	        if(i == PASSWORD) continue;
	        if(i > 0) cout << " ";
	        cout << this->data[i];
	    }
	    cout << '\n';
	}
};

class Registry{
	private:
	int person_quantity = 0;
	int people_counter = 0;
	int bucket_sizes[letter_quantity];
	int bucket_elements[letter_quantity];
	Person * registry[letter_quantity];
	double buffer_increase = 1.5;
	
	void initialize(){
		for(int i = 0; i < letter_quantity; i++){
			bucket_sizes[i] = 1;
			bucket_elements[i] = 0;
			registry[i] = new Person[bucket_sizes[i]];
		}
	}

	int getBucketId(Person p){
		return p.hashcode() % letter_quantity;
	}
	
	int searchBucket(int bucket_id, Person p){
		//Binary Search
		Person * bucket_contents = registry[bucket_id];
		int mid, res = -1, lo = 0, hi = bucket_elements[bucket_id];
		while(lo <= hi){
			mid = (lo + hi) / 2;
			if(p <= bucket_contents[mid]){
				hi = mid - 1;
				if(p == bucket_contents[mid]) return mid;
			}
			else {
				lo = mid + 1;
			}
		}
		return -1; 
	}
	
	void sortBucket(int bucket_id){
		for(int i = 0; i < bucket_elements[bucket_id] - 1; i++){
			for(int j = 0; j < bucket_elements[bucket_id] - i - 1; j++){
				if(registry[bucket_id][j] > registry[bucket_id][j + 1]){
					Person temp = registry[bucket_id][j];
					registry[bucket_id][j] = registry[bucket_id][j + 1];
					registry[bucket_id][j + 1] = temp;
				}
			}
		}
	}

	void expandBucket(int bucket_id){
		int new_size = ceil((double)bucket_sizes[bucket_id] * buffer_increase);
		bucket_sizes[bucket_id] = new_size;
		Person * new_bucket = new Person[new_size];
		
		for(int i = 0; i < bucket_elements[bucket_id]; i++)
			new_bucket[i] = registry[bucket_id][i];

		delete [] registry[bucket_id];
		registry[bucket_id] = new_bucket;
	}

	public:
	
	Registry(){
		initialize();
	}

	Registry(vector<Person> P){
		setRegistry(P);		
	}

	vector<Person> getRegistry(){
		vector<Person> P;
		for(int i = 0; i < letter_quantity; i++){
			for(int j = 0; j < bucket_elements[i]; j++){
				P.push_back(registry[i][j]);
			}
		}
		//Bubble Sort Vector<Person>
		for(int i = 0; i < (int)P.size() - 1; i++){
			for(int j = 0; j < (int)P.size() - i - 1; j++){
				if(P[j].getOrder() > P[j + 1].getOrder()){
					Person temp = P[j];
					P[j] = P[j + 1];
					P[j + 1] = temp;
				}
			}
		}
		return P;
	}

	void setRegistry(vector<Person> P){
		initialize();
		for(int i = 0; i < P.size(); i++){
			addPerson(P[i]);
		}
	}	

	Person getPerson(string id, string last_name){
		Person p;
		p.setId(id);
		p.setLastName(last_name);
		int bucket_id = getBucketId(p);
		int element_id = searchBucket(bucket_id, p);
		if(element_id == -1) return Person();
		return registry[bucket_id][element_id];
	}
	
	bool findPerson(Person p){
		int bucket_id = getBucketId(p);
		if(searchBucket(bucket_id, p) != -1) return true;
		return false;
	}

	bool addPerson(Person p, bool give_order = true){
		int bucket_id = getBucketId(p);
		if(findPerson(p)) return false;		//Duplicate exists
		registry[bucket_id][bucket_elements[bucket_id]] = p;
		if(give_order)registry[bucket_id][bucket_elements[bucket_id]].setOrder(people_counter++);
		sortBucket(bucket_id);
		bucket_elements[bucket_id]++;
		if(bucket_elements[bucket_id] == bucket_sizes[bucket_id]) expandBucket(bucket_id);
		person_quantity++;
		return true;				//Succesful add
	}

	bool removePerson(Person p){
		int bucket_id = getBucketId(p);
		if(!findPerson(p)) return false;		//Person does not exist
		int element_id = searchBucket(bucket_id, p);
		for(int i = element_id; i < bucket_elements[bucket_id] - 1; i++){
			registry[bucket_id][i] = registry[bucket_id][i + 1]; 
		}
		registry[bucket_id][bucket_elements[bucket_id] - 1] = Person();
		bucket_elements[bucket_id]--;
		person_quantity--;
		return true;
	}

	bool editPerson(Person pold, Person pnew){
		if(!findPerson(pold)) return false;	//Person does not exist
		removePerson(pold);
		addPerson(pnew, false);
		return true;
	}		
};

class FileIO{
	private:

	public:

	static vector<Person> loadCSV(){
   		string line;
		vector<Person> P;
    		ifstream fin(path);
    		//File validation
    		getline(fin, line);
    		if(line != header) return vector<Person> (0);
    		//File read
   		while(!fin.eof()){
       			getline(fin, line);
       			P.push_back(line);
    		}
		return P;
	}

	static void saveCSV(Registry R){
		vector<Person> P = R.getRegistry();
		ofstream fout(path);
   		fout << header;
    		for(int i = 0; i < P.size(); i++){
        		fout << '\n';
			fout << P[i].getData();
    		}
	}
};

Registry R;

void consoleClear(){
	cout << flush;
	system("CLS");
}

Person searchPerson(){
        cout << "Introduzca la cedula a buscar: ";
        string id = Person::readSpecialInput(11, "1234567890");
	cout << "Introduzca la primera letra de su apellido: ";
	string last_name_first_letter = Person::readSpecialInput(1, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	Person p = R.getPerson(id, last_name_first_letter);
	if(p == Person()) {
		cout << "No se encontro ninguna persona." << '\n';
	}
	else {
		cout << "Se encontro una persona: " << '\n';
		p.printData(); 
	}
	return p;
}

void addPerson(){
    bool loop = true;
    while(loop){
        vector<string> temp = Person::readData();
        cout << "Continuar sin guardar (C) | Guardar y continuar (G) | Salir sin guardar (S)" << '\n';
        char input = Person::readSpecialInput(1, "CGSX")[0];
        switch(input){
            case 'C':
                break;
            case 'G':
                if(R.addPerson(Person(temp))) cout << "Operacion exitosa." << '\n';
		else cout << "Operación fallida: Duplicado encontrado." << '\n';
                break;
            case 'S':
                loop = false;
                break;
            case 'X':
                loop = false;
                if(R.addPerson(Person(temp))) cout << "Operacion exitosa." << '\n';
		else cout << "Operación fallida: Duplicado encontrado." << '\n';
                break;
        }
    }
}

void editPerson(){
	Person p1 = searchPerson();
	if(p1 == Person()) return;
	Person p2 = p1;
	p2.setData(Person::readData({ID, PASSWORD}));
	if(R.editPerson(p1, p2)) cout << "Operacion exitosa." << '\n';
	else cout << "No se ha encontrado a la persona." << '\n';
}

void listPeople(){
	vector<Person> P = R.getRegistry();
	for(int i = 0; i < P.size(); i++){
		P[i].printData();
	}
}

void deletePerson(){
	Person p = searchPerson();
	if(p == Person()) return;
	if(R.removePerson(p)) cout << "Operacion exitosa." << '\n';
	else cout << "No se ha encontrado a la persona." << '\n';
}

void menu(){
    while(true){
        consoleClear();
        cout << "Registro de Datos VII" << '\n' << '\n';
        cout << "1 - Agregar Personas" << '\n';
        cout << "2 - Buscar Persona" << '\n';
        cout << "3 - Listar Personas" << '\n';
        cout << "4 - Borrar Persona" << '\n';
        cout << "5 - Editar Persona" << '\n';
        cout << "6 - Salir" << '\n';
        cout << '\n';
        char input = Person::readSpecialInput(1, "123456")[0];
        switch(input){
            case '1':
                addPerson();
                break;
            case '2':
                searchPerson();
                break;
            case '3':
                listPeople();
                break;
            case '4':
                deletePerson();
                break;
            case '5':
                editPerson();
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
    R.setRegistry(FileIO::loadCSV());
    menu();
    FileIO::saveCSV(R);
}