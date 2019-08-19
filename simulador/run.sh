#!/bin/sh
cd $1
time make
./main
make clean
