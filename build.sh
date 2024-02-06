#!/bin/bash

if [[ $1 == "clean" ]]; then
    rm -rf build
fi

path=`dirname $(readlink -f $0)`

cmake -B build

cmake --build build -j 24

