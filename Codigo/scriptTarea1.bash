#!/bin/bash

#Instancia 10 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 10 0 7 1 $seed 10 0
done

#Instancia 20 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 20 0 11 1 $seed 10 0
done

#Instancia 30 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 30 0 15 0 $seed 10 0
done

#Instancia 50 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 50 0 27 4 $seed 10 0
done

#Instancia 70 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 70 0 18 0 $seed 10 0
done

#Instancia 80 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 80 0 42 4 $seed 10 0
done

#Instancia 100 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 100 0 45 4 $seed 10 0
done

#Instancia 110 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 110 0 52 0 $seed 10 0
done

#Instancia 120 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 120 0 62 0 $seed 10 0
done

#Instancia 140 nodos
for seed in 1 2 3 4 5 6 7 8 9 10; do
    ./HC+Restart 140 0 72 1 $seed 10 0
done

wait