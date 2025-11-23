#!/bin/bash

#Instancia 100 nodos
for restarts in 10 50 100 500 1000; do
    for seed in 1 2 3 4 5 6 7 8 9 10; do
        ./HC+Restart 100 0 7 1 $seed $restarts 0
    done
done

#Modificar archivo salida en main.cpp

wait