#!/bin/sh
set -eu
cd "$(dirname "$0")"

echo '+ clang++ -std=c++20 -g -O0 -Wall -Wextra -fno-omit-frame-pointer test_vector.cpp -o test_vector'
clang++ -std=c++20 -g -O0 -Wall -Wextra -fno-omit-frame-pointer test_vector.cpp -o test_vector

echo '+ ./test_vector'
./test_vector

echo '+ clang++ -std=c++20 -g -O0 -Wall -Wextra -fno-omit-frame-pointer main.cpp -o main'
clang++ -std=c++20 -g -O0 -Wall -Wextra -fno-omit-frame-pointer main.cpp -o main

echo '+ ./main'
./main
