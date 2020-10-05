#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <stdlib.h>
#include <climits>

using namespace std; 

bool check_input(string str){
	for(int i = 0; i < str.size(); i++){
		if(!isdigit(str[i])) return false;
	}
	return true;
}

int main(int argc, char * argv[]){
	if(argc == 1){
		cerr << "No arguments were entered" << '\n';
		cout << '\n';
		return 0;
	}
	string str = argv[1];
	if(!check_input(str)) {
		cerr << "Invalid value" << '\n';
		cout << '\n';
		return 0;
	}
	if(stoll(str) > INT_MAX){
		cerr << "Value out of range" << '\n';
		cout << '\n';
		return 0;
	}
	int n = stoi(str);
	for(int i = 1; i <= n; i++){
		cout << i << '\n';
	}
	cout << '\n';
}
