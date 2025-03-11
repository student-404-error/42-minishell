#!/bin/bash

dir=$(pwd)
adad
valgrind -q --track-fds=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --show-reachable=yes  ./minishell
