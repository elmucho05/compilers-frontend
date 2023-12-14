#!/bin/bash

./emilia -v -o run $1 && clang++ -o run main.cpp run.o && ./run $1