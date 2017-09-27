#!/bin/bash

for TEST in *; do
  if [[ -d "$TEST" ]]; then
    cd $TEST
    ../../make.sh main.c
    ./a.out
    cd ../
    echo "$TEST COMPLETE; check for errors."
    read -p "Press any key..."
  fi
done
