#!/bin/bash

# Programas e arquivos de entrada
programs=("guloso_max_itens.c" "guloso_custo_beneficio.c" "bp_programacao_dinamica.c")
executables=("gulosoMax" "gulosoCB" "dinamica")
input_files=("instances_01_KP/large_scale/knapPI_1_100_1000_1" "instances_01_KP/large_scale/knapPI_1_200_1000_1" "instances_01_KP/large_scale/knapPI_1_500_1000_1" "instances_01_KP/large_scale/knapPI_1_1000_1000_1" "instances_01_KP/large_scale/knapPI_1_2000_1000_1" "instances_01_KP/large_scale/knapPI_1_5000_1000_1" "instances_01_KP/large_scale/knapPI_1_10000_1000_1" "instances_01_KP/large_scale/knapPI_2_100_1000_1" "instances_01_KP/large_scale/knapPI_2_200_1000_1" "instances_01_KP/large_scale/knapPI_2_500_1000_1" "instances_01_KP/large_scale/knapPI_2_1000_1000_1" "instances_01_KP/large_scale/knapPI_2_2000_1000_1" "instances_01_KP/large_scale/knapPI_2_5000_1000_1" "instances_01_KP/large_scale/knapPI_2_10000_1000_1" "instances_01_KP/large_scale/knapPI_3_100_1000_1" "instances_01_KP/large_scale/knapPI_3_200_1000_1" "instances_01_KP/large_scale/knapPI_3_500_1000_1" "instances_01_KP/large_scale/knapPI_3_1000_1000_1" "instances_01_KP/large_scale/knapPI_3_2000_1000_1" "instances_01_KP/large_scale/knapPI_3_5000_1000_1" "instances_01_KP/large_scale/knapPI_3_10000_1000_1")

# Número de execuções por programa/entrada
exec_times=5

# Arquivo para armazenar os resultados
output_file="resultados.txt"
echo "" > "$output_file"  # Limpa o arquivo de saída

# Compilar os programas
for i in "${!programs[@]}"; do
    gcc -O3 -o "${executables[$i]}" "${programs[$i]}" || { echo "Erro ao compilar ${programs[$i]}"; exit 1; }
done

# Função para calcular a média
calc_media() {
    local sum=0
    for val in "$@"; do
        sum=$(echo "$sum + $val" | bc)
    done
    echo "scale=6; $sum / $exec_times" | bc
}

# Rodar os programas e capturar a média das saídas
for input in "${input_files[@]}"; do
    echo "Executando com o arquivo de entrada: $input" >> "$output_file"
    for exe in "${executables[@]}"; do
        echo "Executando $exe com $input" >> "$output_file"
        
        # Variáveis para somar os resultados e tempos
        result_sum=0
        time_sum=0
        
        # Executa o programa 5 vezes
        for ((i=1; i<=exec_times; i++)); do
            result_output=$("./$exe" < "$input")
            
            # Extrai as duas saídas (result e cpuTimeUsed)
            result=$(echo "$result_output" | awk '{print $1}')
            time_used=$(echo "$result_output" | awk '{print $2}')
            
            # Acumula os valores
            result_sum=$(echo "$result_sum + $result" | bc)
            time_sum=$(echo "$time_sum + $time_used" | bc)
            
            echo "Execução $i: result = $result, cpuTimeUsed = $time_used" >> "$output_file"
        done

        # Calcula as médias
        avg_result=$(echo "scale=6; $result_sum / $exec_times" | bc)
        avg_time=$(echo "scale=6; $time_sum / $exec_times" | bc)

        # Salva a média no arquivo
        echo "Média (result): $avg_result, Média (cpuTimeUsed): $avg_time" >> "$output_file"
        echo "-------------------------------------" >> "$output_file"
    done
done

echo "Todos os resultados foram armazenados no arquivo 'resultados.txt'"

