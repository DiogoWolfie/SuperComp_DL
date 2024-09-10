## Questão 1:
Os dois códigos, mais_caro e mais_leve, seguem a mesma lógica. Ambos possuem complexidade O(nlog(n))

## Questão 2:
Todo o código foi reaproveitado. A única diferença foi a ordem de leitura do vetor e por qual vetor ele vai ser ordenado.

## Questao 3:

Estrada usada:
10 100
20 60
13 13
9 3
2 1
25 90
30 81
1 3
19 30
15 10
30 100

Heuristica do mais leve
Peso final: 79 kg
Valor final: 120 Dinheiros
###########################################


Heuristica do mais valioso
Peso final: 99 kg
Valor final: 287 Dinheiros
###########################################



## Questao 4:

Entrada:
15 100
50 30
13 13
9 5
2 9
5 20
6 23
1 15
69 30
10 35
90 50
3 8
2 3
1 12
5 10
4 6

Heuristica do mais leve
Peso final: 61 kg
Valor final: 159 Dinheiros
###########################################


Heuristica do mais valioso
Peso final: 100 kg
Valor final: 85 Dinheiros
###########################################




## Questao 5:
Bolsa com baixo limite, e pesos grandes com altos valores.

## Questao 6:
Bolsa com mesmo limite da anterior, mas com os pesos grandes com valores mais altos da lista, mas não tanto assim, e muitos pesos pequenos com valores médios, para ganharem na quantidade. 

## Questao 7:
O(nlog(n))

## Questao 8:
Depende do problema. Quando eu tenho um mochila com muitos pesos relativamente altos mas com valores igualmente altos, faz sentido usar a heusísitica do mais valioso, pois, apesar de incluir menos itens na mochila, eles somarão um valor possivelmente maior.
Agora, quando temos uma mochila com uma grande quantidade de pesos leves, e com uma boa distribuição de valores, para que não beneficie a heurística acima, pode-se recorrer a heurística do mais leve. 

## Questao 9:
Testando para a entrada no arquivo entrada1.txt, obtive o resultado abaixo:

Heuristica do mais valioso
Peso final: 372 kg
Valor final: 498 Dinheiros
###########################################


Heuristica do mais leve
Peso final: 364 kg
Valor final: 496 Dinheiros
###########################################


mochila exaustiva
entrada1.txt peso ocupado: 373 kg e valor alcancado: 601 Dinheiros

Logo, eles não alcançam o resultado esperado. (pelo menos no valor de entrada testado)




