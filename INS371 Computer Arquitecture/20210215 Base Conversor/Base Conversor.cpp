#include <string>
#include <iostream>
#include <string>
#include <map>

#define ERROR -13

typedef long long ll;

using namespace std;

const string symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int max_base = symbols.size();

map<char, int> sym_map;

ll pow(int base, int power){
	ll result = 1;
	for(int i = 0; i < power; i++) result *= base;
	return result;
}

void map_symbols(){
	for(int i = 0; i < (int)symbols.size(); i++){
		sym_map[symbols[i]] = i;
	}
}

ll to_base_10(string number, int base){
	//Converts a number from a base to base 10.
	ll result = 0;
	for(int i = 0; i < (int)number.size(); i++){
		int symbol_value = sym_map[number[(number.size() - 1) - i]];
		if(symbol_value >= base) return ERROR;
		result += pow(base, i) * symbol_value;
	}
	return result;
}

string convert_base(string number, int old_base, int base){
	//Converts a number from an old_base to a new base.
	string result = "";
    ll x = to_base_10(number, old_base);
    if(x == ERROR) {
    	cout << "Error: invalid symbol detected." << '\n';
    	return "-1";
    }
	while(x){
        if(x < base && x != 0) {
            result = symbols[x] + result;
            x = 0;
            break;
        }
        int mod = x % base;
        result = symbols[mod] + result;
        x /= base;
    }
    return result;
}

int main(){
	map_symbols();
	int old_base, new_base;
	string number;
	cout << "Insert number: ";
	cin >> number;
	cout << "Insert the number's base: ";
	cin >> old_base;
	cout << "Insert the new number's base: ";
	cin >> new_base;
	if(old_base < 1 || old_base > max_base || new_base < 1 || new_base > max_base){
		cout << "Error: bases should be within range [2-" << max_base << "]" << '\n';
		return -1;
	}
	cout << convert_base(number, old_base, new_base) << '\n';
}
