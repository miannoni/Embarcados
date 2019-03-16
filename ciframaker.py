nome = input()

octave = 4
lista_notas = []
inputinho = input().split()

notas = [
	["C"		,	16.35],#	2109.89
	["C#","Db"	,	17.32],#	1991.47
	["D"		,	18.35],#	1879.69
	["D#","Eb"	,	19.45],#	1774.20
	["E"		,	20.60],#	1674.62
	["F"		,	21.83],#	1580.63
	["F#","Gb"	,	23.12],#	1491.91
	["G"		,	24.50],#	1408.18
	["G#","Ab"	,	25.96],#	1329.14
	["A"		,	27.50],#	1254.55
	["A#","Bb"	,	29.14],
	["B"		,	30.87],
	["P"		,	-1]
]

while True:

	lista_notas.append(inputinho)
	inputinho = input()
	if inputinho == "ACABOU":
		break
	inputinho = inputinho.split()

print("double " + nome + "[][2] = {")

for i in range(0,len(lista_notas)):
	# print("DEBUG: "+ str(lista_notas[i]))
	for j in range(0, len(lista_notas[i])):
		for k in notas:
			if lista_notas[i][j][1:] in k:
				nota = k[-1]
		if nota != -1:
			print("{8, " + str(2**(int(lista_notas[i][j][0]) + octave) * nota) + "}, ")
		else:
			print("{8, -1}, ")

print("{-1, -1} };")
# print("}")