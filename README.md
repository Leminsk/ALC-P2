# ALC-P2
Segundo Trabalho(Prova) Disciplinar para COC473 - Álgebra Linear Computacional consiste em criar uma pequena biblioteca de cálculo numérico para: 

#### **Task 1:** 
- Dado o sistema de equações não lineares abaixo:  
  - ![equation1](https://github.com/Leminsk/ALC-P2/blob/main/Task%201/equations/equation1.png "Equation 1")  
  - ![equation2](https://github.com/Leminsk/ALC-P2/blob/main/Task%201/equations/equation2.png "Equation 2")  
  - ![equation3](https://github.com/Leminsk/ALC-P2/blob/main/Task%201/equations/equation3.png "Equation 3")  
- Encontrar os valores das constantes c<sub>2</sub>, c<sub>3</sub> e c<sub>4</sub> dado um par de valores de entrada &theta;<sub>1</sub> e &theta;<sub>2</sub> por meio do Método de Newton ou pelo Método de Broyden.
  

#### **Task 2:**
- Dada a função abaixo:
  - ![function](https://github.com/Leminsk/ALC-P2/blob/main/Task%202/function.png "Function")
- E sendo fornecidos os dados c<sub>1</sub>, c<sub>2</sub>, c<sub>3</sub> e c<sub>4</sub> como entrada:
  - Encontrar a raiz num intervalo [a,b] pelo Método da Bisseção ou Método de Newton, com o ponto de partida igual a (a+b)/2
  - Calcular valor da integral definida num intervalo [a,b] usando a Quadratura de Gauss-Legendre ou Quadratura Polinomial. Podendo escolher o número de integração entre 2 e 10.
  - Calcular a derivada num ponto x=a, sendo &Delta;x fornecido na entrada, e podendo escolher o método de diferenças finitas passo a frente, passo atrás ou diferença central
  - Estimar o valor da derivada pela extrapolação de Richard (p=1) a partir de dois valores &Delta;x fornecidos


#### **Task 3:**
- Dado como entrada as constantes m, c, k, a<sub>1</sub>, a<sub>2</sub>, a<sub>3</sub>, w<sub>1</sub>, w<sub>2</sub>, w<sub>3</sub>, um passo de integração (h) e tempo total de integração (T), resolver a seguinte equação diferencial pelo método Runge-Kutta-Nyström:
  - ![diff1](https://github.com/Leminsk/ALC-P2/blob/main/Task%203/differential-equation/rkn-eq1.png "Diff 1")
  - ![diff1](https://github.com/Leminsk/ALC-P2/blob/main/Task%203/differential-equation/rkn-eq2.png "Diff 1")
  - ![diff1](https://github.com/Leminsk/ALC-P2/blob/main/Task%203/differential-equation/rkn-eq3.png "Diff 1")

## Compilação
Algumas funções utilizadas nos programas necessitam do C++11, portanto é preciso compilar com a flag adequada:  
- `g++ -std=c++11 task1.cpp -o task1`  
- `g++ -std=c++11 task2.cpp -o task2`  
- `g++ -std=c++11 task3.cpp -o task3`  

Os executáveis (.exe) presentes neste repositório foram compilados em uma máquina com Windows 10 e g++ (tdm64-1) 5.1.0.

## Modo de Uso
TODO: preencher (tem no um README.txt pra cada um por agora)
