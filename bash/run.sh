#!/bin/bash

#echo "Running generate_tests.sh..."
#./bash/generate_tests.sh

echo "Running run_full_tests.sh..."
./bash/run_full_tests.sh

echo "Generating graphs..."
python3 /home/max/projects/AlgAvançados/Vencedor_Torneio/src/aux/generate_graphs.py

echo "All tasks completed."