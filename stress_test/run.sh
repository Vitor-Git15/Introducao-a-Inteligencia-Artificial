#!/bin/bash

# Executável e pasta de teste
EXEC="./bin/main"
TEST_FOLDER="./tests"
RESULT_FOLDER="./stress_test/results"

# Opções do algoritmo
OPTIONS=("B" "I" "U" "A" "G")

# Arquivos de entrada
FILES=("H1.in" "E1.in" "I1.in")

# Número de repetições
REPEATS=10

# Loop pelas opções de algoritmo
for OPTION in "${OPTIONS[@]}"; do
    # Loop pelos arquivos de entrada
    for FILE in "${FILES[@]}"; do
        # Caminho completo do arquivo de entrada
        INPUT_FILE="$TEST_FOLDER/$FILE"

        # Conteúdo do arquivo de entrada
        CONTENT=$(<"$INPUT_FILE")

        # Loop para repetir o teste
        for ((i = 1; i <= REPEATS; i++)); do
            # Nome do arquivo de saída
            OUTPUT_FILE="${FILE%.in}-${i}"  # Remove a extensão .in e adiciona .out

            # Executa o teste e redireciona a saída para o arquivo de saída
            $EXEC $OPTION $CONTENT > "$RESULT_FOLDER/$OPTION/$OUTPUT_FILE"

            # Mostra mensagem de conclusão
            echo "Teste com $FILE e opção $OPTION concluído. Saída salva em $OUTPUT_FILE"
        done
    done
done