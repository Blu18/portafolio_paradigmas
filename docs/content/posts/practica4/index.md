+++
date = '2025-05-29'
draft = false
title = 'Practica 4: Paradigma Lógico'
+++

# Introducción
El paradigma lógico es un estilo de programación basado en la lógica matemática. En lugar de dar instrucciones paso a paso, el programador define hechos y reglas, y el programa resuelve problemas haciendo inferencias lógicas.
Un ejemplo típico es Prolog, donde defines relaciones y el lenguaje encuentra respuestas a partir de ellas. Es útil en inteligencia artificial y sistemas expertos.

En esta práctica se explicaran programas basicos del paradigma funcional en prolog.

# Desarrollo

### Programas Basicos:
En la sesión de esta practica se analizaron 5 progras básicos para comprender mejor este paradigma. A continuación se muestran los programas.

##### Torres de Hanoi
```prolog
move(1,X,Y,_) :-   write('Move top disk from '), write(X), write(' to '), 
                    write(Y), nl.move(N,X,Y,Z) :-   N>1,   M is N-1,   move(M,X,Z,Y),   move(1,X,Y,_),   move(M,Z,Y,X).
```
Este codigo utiliza recursivida, si hay un solo disco, lo mueve directamente de la torre de origen a la torre destino.
Si hya mas de un disco, mueve los discos superiores a la torre auxiliar, mueve el disco más grande a la torre destino y luego mueve
los discos de la torre auxiliar a la destino.

##### Minimo y Máximo
```prolog
find_max(X, Y, X) :- X >= Y, !.find_max(X, Y, Y) :- X < Y.find_min(X, Y, X) :- X =< Y, !.find_min(X, Y, Y) :- X > Y.
```
Este programa define predicados para encontrar el máximo y el mínimo entre dos numeros.
*find_max*: Devuelve el mayor de los dos números.
*find_min*: Devuelve el menor de los dos números.

##### Segmento de recta
```prolog
vertical(seg(point(X,_),point(X,_))).horizontal(seg(point(_,Y),point(_,Y))).oblique(seg(point(X1,Y1),point(X2,Y2)))   :-X1 \== X2,      Y1 \== Y2.
```
Este programa clasifica segmentos de recta:
- *vertical*: El segmento es vertiCal si ambos puntos tienen la misma X.
- *horizontal*: El segmento es horizontal si ambos puntos tienen la misma Y.
- *vertical*: El segmento es oblicuo si ni X ni Y son iguales en los puntos extremos.

##### El mono y el plátano
```prolog
move(state(middle,onbox,middle,hasnot),   grasp,   state(middle,onbox,middle,has)).move(state(P,onfloor,P,H),   
climb,   state(P,onbox,P,H)).move(state(P1,onfloor,P1,H),   drag(P1,P2),   state(P2,onfloor,P2,H)).move(state(P1,onfloor,B,H),  
walk(P1,P2),   state(P2,onfloor,B,H)).canget(state(_,_,_,has)).canget(State1) :-   move(State1,_,State2),   canget(State2).
```
Este programa modela un problema clásico donde un mono tiene que alcanzar un platana. En el codigo se definen los movimientos posibles del mono (caminar, arrastar la caja, trepar la caja y agarrar el platano). El predicado *canget* es el que determina si el mono puede o no alcanzar el plátano desde un estado inicial.

##### Lista Enlazada
```prolog
add_front(L,E,NList) :- NList = node(E,L).add_back(nil, E, NList) :-   NList = node(E,nil).   
add_back(node(Head,Tail), E, NList) :-   add_back(Tail, E, NewTail),   NList = node(Head,NewTail).
```
En este programa se implementas operaciones basicas de listas enlazadas para añadir nodos en la parte frontal o trasera de la lista.
- *add_front*: Agrega un elemento al inicio de la lista.
- *add_back*: Agrega un elemento al final de la lista.
- Utiliza la estructura node(Elemento, Siguiente) para representar los nodos y nil para el final de la lista.

# Conclusión    
A través de esta práctica, se comprendió el enfoque declarativo del paradigma lógico, donde los programas se estructuran mediante hechos y reglas en lugar de instrucciones secuenciales. Los ejemplos analizados, como las Torres de Hanoi, la identificación de mínimo y máximo, la clasificación de segmentos, el problema del mono y el plátano, y las listas enlazadas, permitieron observar cómo Prolog resuelve problemas mediante inferencia lógica y recursividad.

