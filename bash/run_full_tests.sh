#!/bin/bash
# Adaptado de @GuiDavilaP #

# Garante que estamos no diretório correto
cd "$(dirname "$0")/.."

# Cria diretórios para resultados
mkdir -p results/csvs

# Inicializa arquivos CSV com cabeçalhos
echo "n,tempo,resultado" > results/csvs/tempo_vs_n.csv
echo "vies,probabilidade_vitoria" > results/csvs/prob_vs_vies.csv
echo "fracao_jogos,probabilidade_vitoria" > results/csvs/prob_vs_fracao.csv
echo "vies,fracao_jogos,probabilidade_vitoria" > results/csvs/prob_vs_vies_fracao.csv

# Compila o programa
make

# Função para extrair resultado (sim=1, não=0)
get_result() {
    if [[ $1 == "sim" ]]; then
        echo 1
    else
        echo 0
    fi
}

echo "Executando testes de número de equipes..."
# Teste 1: Tempo vs Número de equipes
for file in test/num_equipes/n*.txt; do
    n=$(echo $file | grep -o '[0-9]\+' | head -1)
    start_time=$(date +%s.%N)
    result=$(./bin/main < "$file")
    end_time=$(date +%s.%N)
    execution_time=$(echo "$end_time - $start_time" | bc)
    result_binary=$(get_result "$result")
    echo "$n,$execution_time,$result_binary" >> results/csvs/tempo_vs_n.csv
done

echo "Executando testes de viés..."
# Teste 2: Probabilidade de vitória vs Viés
for vies_dir in test/vies_equipe/b*; do
    vies=$(basename "$vies_dir" | sed 's/b\(.*\)/\1/' | tr '_' '.')
    total_wins=0
    num_tests=0
    for file in "$vies_dir"/test_*.txt; do
        ((num_tests++))
        result=$(./bin/main < "$file")
        if [[ $result == "sim" ]]; then
            ((total_wins++))
        fi
    done
    if [ $num_tests -gt 0 ]; then
        prob=$(echo "scale=3; $total_wins / $num_tests" | bc)
        echo "$vies,$prob" >> results/csvs/prob_vs_vies.csv
    fi
done

echo "Executando testes de fração de jogos..."
# Teste 3: Probabilidade de vitória vs Fração de jogos
for fracao_dir in test/frac_jogos/f*; do
    fracao=$(basename "$fracao_dir" | sed 's/f\(.*\)/\1/' | tr '_' '.')
    total_wins=0
    num_tests=0
    for file in "$fracao_dir"/test_*.txt; do
        ((num_tests++))
        result=$(./bin/main < "$file")
        if [[ $result == "sim" ]]; then
            ((total_wins++))
        fi
    done
    if [ $num_tests -gt 0 ]; then
        prob=$(echo "scale=3; $total_wins / $num_tests" | bc)
        echo "$fracao,$prob" >> results/csvs/prob_vs_fracao.csv
    fi
done

echo "Executando testes de pareamento viés-fração..."
# Teste 4: Probabilidade de vitória vs Viés e Fração
echo "vies,fracao_jogos,probabilidade_vitoria" > results/csvs/prob_vs_vies_fracao.csv

for vies_fracao_dir in test/vies_fracao/b*_f*; do
    basename=$(basename "$vies_fracao_dir")
    
    # Improved extraction for viés and fração values
    vies=$(echo "$basename" | sed -E 's/b([0-9-]+)_([0-9]+).*/\1.\2/')
    fracao=$(echo "$basename" | sed -E 's/.*_f([0-9]+)_([0-9]+).*/\1.\2/')
    
    # Debug: print extracted values
    echo "Processando diretório: $basename (viés=$vies, fração=$fracao)" >&2
    
    # Validate extracted values
    if ! [[ $vies =~ ^-?[0-9]+\.[0-9]+$ ]] || ! [[ $fracao =~ ^[0-9]+\.[0-9]+$ ]]; then
        echo "Erro: Valores inválidos extraídos de $basename (viés=$vies, fração=$fracao)" >&2
        continue
    fi
    
    # Reset counters for each directory
    total_wins=0
    num_tests=0
    
    # Process all test files in this directory
    for file in "$vies_fracao_dir"/test_*.txt; do
        if [ -f "$file" ]; then
            ((num_tests++))
            result=$(./bin/main < "$file")
            if [[ $result == "sim" ]]; then
                ((total_wins++))
            fi
        fi
    done
    
    # Calculate probability for this combination
    if [ $num_tests -gt 0 ]; then
        prob=$(echo "scale=3; $total_wins / $num_tests" | bc)
        echo "$vies,$fracao,$prob" >> results/csvs/prob_vs_vies_fracao.csv
    fi
done

# Sort results numerically by vies and fracao, preserving header
(head -n 1 results/csvs/prob_vs_vies_fracao.csv && tail -n +2 results/csvs/prob_vs_vies_fracao.csv | sort -t, -k1n -k2n) > results/csvs/temp.csv
mv results/csvs/temp.csv results/csvs/prob_vs_vies_fracao.csv

echo "Testes concluídos! Resultados salvos em:"
echo "- results/csvs/tempo_vs_n.csv"
echo "- results/csvs/prob_vs_vies.csv"
echo "- results/csvs/prob_vs_fracao.csv"
echo "- results/csvs/prob_vs_vies_fracao.csv"