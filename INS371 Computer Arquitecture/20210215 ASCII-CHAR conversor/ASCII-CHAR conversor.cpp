#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(){
		string raw_input;
		getline(cin, raw_input);
		stringstream ss(raw_input);
		string code;
		ss >> code;
//		cerr << input1;
		if(code == "ASCII"){		// ASCII to char
			string number;
			ss >> number;
//			cerr << number;
			char result = (char)(stoi(number));
			cout << "CHAR " << result << '\n';
		}
		if(code == "CHAR"){			// char to ASCII
			string character;
			ss >> character;
//			cerr << character;
			int result = (int)character[0];
			cout << "ASCII " <<result << '\n';
		}
}