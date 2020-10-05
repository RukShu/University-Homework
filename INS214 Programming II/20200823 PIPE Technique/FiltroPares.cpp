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

int main(){
	int n;
	string str;
	while(true){
		getline(cin, str);
		if(str == "") break;
		if(!check_input(str)) {
			cerr << "Invalid value" << '\n';
			continue;
		}
		if(stoll(str) > INT_MAX){
			cerr << "Value out of range" << '\n';
			continue;
		}
		n = stoi(str);
		if(n % 2 == 0) cout << n << '\n';
	}
	cout << '\n';
}
