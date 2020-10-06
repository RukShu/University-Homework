function f1 (a)
	if a == 0 then return 0 end
	return a + f1(a - 1)
end

function f2 (a)
	if a == 1 then return 1 end
	return a * f2(a - 1)
end

function f4 (a, x)
	if a == 0 then return x end
	return f4(a - 1, x + a)
end

function f5 (a, x)
	if a == 1 then return x end
	return f5(a - 1, x * a)
end

function f6 (a, b)
	if b == 0 then return a end
	return f6(b, a % b)
end

function f7 (a, x)
	for i = a, 0, -1 do
		x = x + i
	end 
	return x
end 

function f8 (a, x)
	for i = a, 1, -1 do
		x = x * i
	end
	return x
end

function f9 (a, b)
	while b do
		if b == 0 then break end
		t = b
		b = a % b
		a = t
	end
	return a
end

print("Escoge un programa: \n")
print("1 - Sumatoria sin TCO")
print("2 - Factorial sin TCO")
print("4 - Sumatoria con TCO")
print("5 - Factorial con TCO")
print("6 - GCD de Euclides")
print("7 - Sumatoria Iterativa")
print("8 - Factorial Iterativo")
print("9 - GCD de Euclides Iterativo")

n = io.read("*n")
if n < 1 or n > 9 or n == 3 then
	print("Opcion invalida")
	os.exit()
end

if n == 1 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f1(a))
end
if n == 2 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f2(a))
end
if n == 4 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f4(a, 0))
end
if n == 5 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f5(a, 1))
end
if n == 6 then
	print("Introduzca dos numeros")
	a, b = io.read("*n", "*n")
	if a < b then
		t = b
		b = a
		a = t
	end
	print(f6(a, b)) 
end
if n == 7 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f7(a, 0))
end
if n == 8 then
	print("Introduzca un numero")
	a = io.read("*n")
	print(f8(a, 1))
end
if n == 9 then
	print("Introduzca dos numeros")
	a, b = io.read("*n", "*n")
	if a < b then
		t = b
		b = a
		a = b
	end
	print(f9(a, b)) 
end