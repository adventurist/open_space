#!/usr/bin/env bash

g++ -std=c++17 -pthread -I include src/main.cpp src/open_space.cpp src/node.cpp -o open_space
