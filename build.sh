#!/bin/bash

path=`dirname $(readlink -f $0)`

cmake -B build

cmake --build build -j 24

