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
	double sum = 0, counter = 0;
	string str;
	while(true){
		getline(cin, str);
		if(str == "") break;
		if(!check_input(str)) {
			cout << "Invalid value" << '\n';
			continue;
		}
		if(stoll(str) > INT_MAX){
			cout << "Value out of range" << '\n';
			continue;
		}
		sum += stoi(str);
		counter++;
	}
	if(counter != 0) cout << sum / counter << '\n';
	cout << '\n';
}