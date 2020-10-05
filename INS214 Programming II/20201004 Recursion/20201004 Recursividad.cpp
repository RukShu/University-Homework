#include <iostream>
typedef long long ll;

//Sum sin TCO
int f1(int x) {
	if(x == 1) return 1;
	return x + f1(x - 1);
}

//Factorial sin TCO
ll f2 (ll x){
	if(x == 1) return 1;
	return x * f2(x - 1);
}

//GCD sin TCO
int f3 (int a, int b){
	if(b == 0) return a;
	int t = b;
	b = a % b;
	a = t;
	return f3(a, b);
}

//Sum con TCO
int f4(int x, int acc = 0){
	if(x == 0) return acc;
	return f4(x - 1, acc + x);
}

//Factorial con TCO
ll f5(ll x, ll acc = 1){
	if(x == 1) return acc;
	return f5(x - 1, acc * x);
}

//GCD con TCO
int f6(int a, int b){
	if(b == 0) return a;
	return f6(b, a % b);
}

//Sum Iterativo
int f7(int x){
	int acc = 0;
	while(x != 0){
		acc += x;
		x--;
	}
	return acc;
}

//Factorial Iterativo
ll f8(int x){
	int acc = 1;
	while(x != 0){
		acc *= x;
		x--;
	}
	return acc;
}

//GCD Iterativo
int f9(int a, int b){
	while(b != 0){
		int t = b;
		b = a%b;
		a = t;
	}
	return a;
}

int main(){
	int opt, a, b;
	while(true){
		std::cout << "Introduzca el numero funcion que desea evaluar." << '\n';
		std::cin >> opt;
		if(opt > 9 || opt < 1) {
			std::cout << "Opcion invalida" << '\n';
			continue;
		}
		break;
	}
	switch(opt){
		case 1:
		case 4:
		case 7:
			std::cout << "Introduzca un numero: ";
			std::cin >> a;
			if(opt == 1) std::cout << f1(a) << '\n';
			if(opt == 4) std::cout << f4(a) << '\n';
			if(opt == 7) std::cout << f7(a) << '\n';
			break;
		case 2:
		case 5:
		case 8:
			std::cout << "Introduzca un numero: ";
			std::cin >> a;
			if(opt == 2) std::cout << f2(a) << '\n';
			if(opt == 5) std::cout << f5(a) << '\n';
			if(opt == 8) std::cout << f8(a) << '\n';
			break;
		case 3:
		case 6:
		case 9:
			std::cout << "Introduzca dos numeros: ";
			std::cin >> a >> b;
			int x = (a > b)? a : b, y = (a > b)? b : a;
			if(opt == 3) std::cout << f3(x, y) << '\n';
			if(opt == 6) std::cout << f6(x, y) << '\n';
			if(opt == 9) std::cout << f9(x, y) << '\n';
			break;
	}
}