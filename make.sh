#!/bin/bash

gcc -O2 ../../lib/quantum_emulator.c $1
./a.out
