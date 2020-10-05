#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

const int frequency = 565, dot = 1, dash = 3, symbol = 1, letter = 3, word = 7, null = 0, time_unit = 100;
const char invalid = 'x';
const string mtree = "x"
"x"
"ET"
"IANM"
"SURWDKGO"
"HVFxLxPJBXCYZQxx"
"54x3xxx2xxxxxxx16xxxxxxx7xxx8x90";

vector<char> code;

void beep(int beep_duration, int sleep_duration){
	Beep(frequency, beep_duration * time_unit);
	Sleep(sleep_duration * time_unit);
}

string process_input(string input){
	string res = "";
	vector<char> str (input.size());
	for(int i = 0; i < str.size(); i++){
		str[i] = toupper(input[i]);
	}
	for(int i = 0; i < str.size(); i++){
		if(str[i] != ' ') break;
		str[i] = invalid;
	}
	for(int i = str.size() - 1; i > -1; i--){
		if(str[i] != ' ') break;
		str[i] = invalid;
	}
	for(int i = 1; i < str.size(); i++){
		if(str[i] == ' ' && str[i - 1] == ' ') str[i - 1] = invalid;
	}
	for(int i = 0; i < str.size(); i++){
		if(str[i] == invalid) continue;
		res += str[i];	
	}
	return res;
}

bool get_code(char letter, int idx = 1, int i = 0){
	if(idx > mtree.size() - 1) return false;
	if(mtree[idx] == letter) return true;
	code[i] = '.';
	if(get_code(letter, 2 * idx, i + 1)) return true;
	code[i] = '-';
	if(get_code(letter, 2 * idx + 1, i + 1)) return true;
	code[i] = ' ';
	return false;
}

void print_code(){
	for(int i = 0; i < code.size(); i++){
		if(code[i] == ' ') break;
		cout << code[i];
		beep(code[i] == '.'? dot : dash, symbol);
	}
	cout << ' ';
	beep(null, letter - symbol);
}

void morse_print(string str){
	for(int i = 0; i < str.size(); i++){
		code = vector<char> (6, ' ');
		if(str[i] == ' '){
			cout << "/ ";
			beep(null, word - letter);
			continue;
		}
		get_code(str[i]);
		print_code();
	}
}

int main(){
	string input;
	getline(cin, input);
	morse_print(process_input(input));
}