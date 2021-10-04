+--------------------------------------------+
|   Modo de uso de "task2.exe" (Modelo P2)   |
+--------------------------------------------+

task2.exe tenta resolver vários problemas matemáticos de sua função preestabelecida como:
    - encontrar raiz da função
    - calcular integral
    - calcular derivada de primeira ordem (finita frente, trás, central)
    - calcular derivada de primeira ordem (Richard Exptrapolation)

Para o funcionamento correto de task1.exe, é necessário fornecer um arquivo de entrada que precisa necessariamente estar localizados na mesma pasta/diretório que o executável:

    - "main_input.txt" : cada linha corresponde a um parâmetro de uso (todas as linhas devem ser preenchidas corretamentes de acordo com método escolhido)
        Linha 1: código para seleção do método a ser utilizado (ICOD)
            1: Raiz
            2: Integral
            3: Derivada Finita
            4: Derivada RE
        
        (Atenção: Dependendo do ICOD fornecido o preenchimento das linhas muda)
            
        ICOD: 1            
            Linha 2: SUBCOD - determina qual método para achar a raiz
                1: Bisseção
                2: Newton Rhapson
            Linha 3: intervalo fechado [a, b] (apenas inserir a e b separados por vírgula sem colchetes)
            Linha 4: a tolerância a ser utilizada
            Linha 5: c_1, c_2, c_3, c_4 - as constantes da função (precisam estar separadas por vírgula
            
        ICOD: 2            
            Linha 2: SUBCOD - determina qual método para calcular a integral
                1: Quadratura de Gauss-Legendre
                2: Quadratura Polinomial
            Linha 3: intervalo fechado [a, b] (apenas inserir a e b separados por vírgula sem colchetes)
            Linha 4: quantia de pontos de integração/amostragem (só devem ser de 2 a 10)
            Linha 5: c_1, c_2, c_3, c_4 - as constantes da função (precisam estar separadas por vírgula
            
        ICOD: 3            
            Linha 2: SUBCOD - determina qual método para calcular a derivada
                1: Passo para Frente
                2: Passo para Trás
                3: Central
            Linha 3: valor do ponto x a ser analisado (x=a)
            Linha 4: deltaX
            Linha 5: c_1, c_2, c_3, c_4 - as constantes da função (precisam estar separadas por vírgula
            
        ICOD: 4            
            Linha 2: valor do ponto x a ser analisado (x=a)
            Linha 3: primeiro deltaX
            Linha 4: segundo deltaX
            Linha 5: c_1, c_2, c_3, c_4 - as constantes da função (precisam estar separadas por vírgula


Ao concluir seus cálculos/processos, task2.exe gerará um arquivo de saída chamado "main_output.txt" contendo:
    - print dos dados de entrada fornecidos
    - solução para o respectivo problema

Caso ocorra algum erro, o arquivo de saída conterá informações sobre o possível motivo da falha do programa.