#============================================#
|   Modo de uso de "task1.exe" (modelo P2)   |
#============================================#

task1.exe tenta resolver um sistema não linear de equações dado um conjunto de parâmetros theta_1 e theta_2.

Para o funcionamento correto de task1.exe, é necessário fornecer um arquivo de entrada que precisa necessariamente estar localizados na mesma pasta/diretório que o executável:

    - "main_input.txt" : cada linha corresponde a um parâmetro de uso (todas as linhas devem ser preenchidas corretamentes independente do método escolhido)
        Linha 1: código para seleção do método a ser utilizado (ICOD)
            1: Newton
            2: Broyden
        Linha 2: theta_1, theta_2 (necessitam estar separados por VÍRGULA)
        Linha 3: a tolerância a ser utilizada


Ao concluir seus cálculos/processos, task1.exe gerará um arquivo de saída chamado "main_output.txt" contendo:
    - print dos dados de entrada fornecidos
    - solução para c_2, c_3 e c_4

Caso ocorra algum erro, o arquivo de saída conterá informações sobre o possível motivo da falha do programa.