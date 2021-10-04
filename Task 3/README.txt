+--------------------------------------------+
|   Modo de uso de "task3.exe" (Modelo P3)   |
+--------------------------------------------+

task3.exe tenta resolver vários problemas matemáticos de sua função preestabelecida como:
    

Para o funcionamento correto de task1.exe, é necessário fornecer um arquivo de entrada que precisa necessariamente estar localizados na mesma pasta/diretório que o executável:

    - "main_input.txt" : cada linha corresponde a um conjunto de valores
        Linha 1: passo de integração (h)
		Linha 2: tempo total de integração (t)
		Linha 3: m, c, k (constantes separadas por vírgulas)
		Linha 4: a_1, a_2, a_3 (constantes separadas por vírgulas)
		Linha 5: w_1, w_2, w_3 (constantes separadas por vírgulas)


Ao concluir seus cálculos/processos, task3.exe gerará um arquivo de saída chamado "main_output.txt" contendo:
    - print dos dados de entrada fornecidos
    - um conjunto de dados de Tempo, Deslocamento, Velocidade e Aceleração escritos de 4 em 4 a cada nova linha.
		e.g.: 0.1, 0.0002288982206, 0.006825298884, 0.1350925317

Caso ocorra algum erro, o arquivo de saída conterá informações sobre o possível motivo da falha do programa.